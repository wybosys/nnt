
# include "Core.h"
# include "CorePlot+WSI.h"
# include "Math+WSI.h"
# import "CPBarLayer.h"
# import "CGShadow.h"
# import "CGAnimation.h"

WSI_BEGIN

@interface CPBarPlot ()

-(void)drawBarInContext:(CGContextRef)context recordIndex:(NSUInteger)index;
-(BOOL)barAtRecordIndex:(NSUInteger)index basePoint:(CGPoint *)basePoint tipPoint:(CGPoint *)tipPoint;
-(BOOL)barIsVisibleWithBasePoint:(CGPoint)basePoint;
-(CGMutablePathRef)newBarPathWithContext:(CGContextRef)context recordIndex:(NSUInteger)recordIndex;
-(CGMutablePathRef)newBarPathWithContext:(CGContextRef)context basePoint:(CGPoint)basePoint tipPoint:(CGPoint)tipPoint;

@end

@implementation CPBarPlot (WSI)

@end

@interface UICPBarPlotPrivate : NSObject {
    UICPBarPlot *d_owner;
    NSMutableArray *indicators;
    NSMutableArray *bars;
    int moving_selected_last;
    int touch_selected_last;
}

@property (nonatomic, assign) UICPBarPlot *d_owner;
@property (nonatomic, retain) NSMutableArray *indicators;
@property (nonatomic, retain) NSMutableArray *bars;
@property (nonatomic) int moving_selected_last, touch_selected_last;

@end

@interface UICPBarPlot (WSI)

- (void)drawIndicatorsInContext:(CGContextRef)context;
- (void)drawIndicatorInContext:(CGContextRef)context indicator:(UICPIndicatorLayer*)indicator;

@end

@implementation UICPBarPlotPrivate

@synthesize d_owner;
@synthesize indicators, bars;
@synthesize moving_selected_last, touch_selected_last;

- (id)init {
    self = [super init];
    
    indicators = [NSMutableArray new];
    bars = [NSMutableArray new];
    
    moving_selected_last = NSNotFound;
    touch_selected_last = NSNotFound;
    
    return self;
}

- (void)dealloc {
    [indicators release];
    [bars release];
    
    [super dealloc];
}

@end

@implementation UICPBarPlot (WSI)

- (void)drawIndicatorsInContext:(CGContextRef)context {
    if ([d_ptr.indicators count] == 0)
        return;
    
    CGContextSaveGState(context);
    
    // draw live line
    CGContextBeginPath(context);
    CGMutablePathRef ph_line = CGPathCreateMutable();
    
    CGPathMoveToPoint(ph_line, nil, 0, 0);
    CGPathAddLineToPoint(ph_line, nil, 100, 100);
    
    CGContextAddPath(context, ph_line);
    if (indicatorLiveLineStyle == nil) {
        indicatorLiveLineStyle = [[UICPMutableLineStyle alloc] init];
        indicatorLiveLineStyle.lineColor = [UICPColor blackColor];
        indicatorLiveLineStyle.lineWidth = 2.f;
    }    
    [indicatorLiveLineStyle setLineStyleInContext:context];
    CGContextStrokePath(context);
    CGPathRelease(ph_line);
    
    // draw each indicator
    for (UICPIndicatorLayer *indicator in d_ptr.indicators) {
        [self drawIndicatorInContext:context indicator:indicator];
    }
    
    CGContextRestoreGState(context);
}

- (void)drawIndicatorInContext:(CGContextRef)context indicator:(CPIndicatorLayer *)indicator {
    CGContextSaveGState(context);
    
    CGContextRestoreGState(context);
}

@end

@implementation UICPBarPlot

@synthesize allowInteractiveMoveIndicator;
@synthesize indicatorLiveLineStyle;
@synthesize indicatorLiveLineOffset;
@synthesize barShadow, barAnimation;
@synthesize movingSelectedEnable;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(UICPBarPlot);
    
    indicatorLiveLineOffset = 10.f;
    
    return self;
}

- (void)dealloc {
    [indicatorLiveLineStyle release];
    [barShadow release];
    [barAnimation release];
    [indicatorLiveLineStyle release];
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)renderAsVectorInContext:(CGContextRef)context {
    // clean
    for (CPAnnotation *anno in d_ptr.bars) {
        [self removeAnnotation:anno];
    }
    [d_ptr.bars removeAllObjects];
    
    // base render
    [super renderAsVectorInContext:context];
    
    // draw indicators
    [self drawIndicatorsInContext:context];
}

- (void)drawBarInContext:(CGContextRef)context recordIndex:(NSUInteger)index {
    // Get base and tip points
    CGPoint basePoint, tipPoint;
    BOOL barExists = [self barAtRecordIndex:index basePoint:&basePoint tipPoint:&tipPoint];
    if ( !barExists ) return;
    
    // Return if bar is off screen
	if ( ![self barIsVisibleWithBasePoint:basePoint] ) return;
    
	CGMutablePathRef path = [self newBarPathWithContext:context basePoint:basePoint tipPoint:tipPoint];
    
    if (path) {

        CGRect bound = CGPathGetBoundingBox(path);
        
        // use annonation
        CPAnnotation *bar = [CPAnnotation new];
        CPBarLayer *barlayer = [[CPBarLayer alloc] initWithFrame:bound];
        bar.contentLayer = barlayer;
        [self addAnnotation:bar];
        [d_ptr.bars addObject:bar];
        [barlayer release];
        [bar release];
        
        // other
        // shadow
        CGShadow *currentBarShadow = self.barShadow;
		if ( [self.dataSource respondsToSelector:@selector(barShadowFillForBarPlot:recordIndex:)]) {
            CGShadow *fill = [(id <UICPBarPlotDataSource>)self.dataSource barShadowFillForBarPlot:self recordIndex:index];
            if ( fill ) currentBarShadow = fill;
        }
        barlayer.shadowColor = currentBarShadow.shadowColor.cgColor;
        barlayer.shadowOffset = currentBarShadow.offset;
        barlayer.shadowOpacity = currentBarShadow.opacity;
        barlayer.shadowRadius = currentBarShadow.radius;
        
        // fill
        CPFill *currentBarFill = self.fill;
		if ( [self.dataSource respondsToSelector:@selector(barFillForBarPlot:recordIndex:)] ) {
			CPFill *dataSourceFill = [(id <CPBarPlotDataSource>)self.dataSource barFillForBarPlot:self recordIndex:index];
			if ( dataSourceFill ) currentBarFill = dataSourceFill;
		}
        barlayer.layerFill = currentBarFill;
		
        // border
        barlayer.layerBorderLineStyle = self.lineStyle;
        
        // animation
        CGAnimation *currentBarAni = self.barAnimation;
        if ([self.dataSource respondsToSelector:@selector(barAnimationForBarPlot:recordIndex:)]) {
            CGAnimation *ani = [(id<UICPBarPlotDataSource>)self.dataSource barAnimationForBarPlot:self recordIndex:index];
            if (ani) currentBarAni = ani;
        }
        
        if (currentBarAni) {
            CAKeyframeAnimation *ani = [CAKeyframeAnimation animationWithKeyPath:@"bounds"];
            ani.duration = currentBarAni.duration;
            ani.values = [NSArray arrayWithObjects:
                           [NSValue valueWithCGRect:CGRectMake(0, 0, bound.size.width, 0)],
                           [NSValue valueWithCGRect:CGRectMake(0, 0, bound.size.width, bound.size.height)],
                           nil];        
            ani.calculationMode = kCAAnimationLinear;
            [barlayer addAnimation:ani forKey:kCATransition];
        }
     
        CGPathRelease(path);
    }
}

- (void)addIndicator:(CPIndicatorLayer *)indicator {
    [d_ptr.indicators addObject:indicator];
}

- (BOOL)pointingDeviceDownEvent:(id)event atPoint:(CGPoint)interactionPoint {
    BOOL result = NO;
	CPGraph *theGraph = self.graph;
	CPPlotArea *thePlotArea = self.plotArea;
	if ( !theGraph || !thePlotArea ) return NO;
	
	id <UICPBarPlotDelegate> theDelegate = self.delegate;
	if ( [theDelegate respondsToSelector:@selector(barPlot:barWasSelectedAtRecordIndex:)] ) {
    	// Inform delegate if a point was hit
        CGPoint plotAreaPoint = [theGraph convertPoint:interactionPoint toLayer:thePlotArea];
		
		NSUInteger barCount = self.cachedDataCount;
		
        BOOL seled = NO;
		for ( NSUInteger ii = 0; ii < barCount; ii++ ) {
			CGMutablePathRef path = [self newBarPathWithContext:NULL recordIndex:ii];
			
			if ( CGPathContainsPoint(path, nil, plotAreaPoint, false) ) {				
				CGPathRelease(path);                
                result = YES;
                seled = YES;
                if (ii != d_ptr.touch_selected_last && d_ptr.touch_selected_last != NSNotFound) {
                    if ([theDelegate respondsToSelector:@selector(barPlot:barWasUnselectedAtRecordIndex:)])
                        [theDelegate barPlot:self barWasUnselectedAtRecordIndex:d_ptr.touch_selected_last];                     
                }
                if (d_ptr.touch_selected_last != ii) {
                    [theDelegate barPlot:self barWasSelectedAtRecordIndex:ii]; 
                    d_ptr.touch_selected_last = ii;      
                }
				break;
			}
			
			CGPathRelease(path);			
		}
        
        if (!seled && d_ptr.touch_selected_last != NSNotFound) {    
            if ([theDelegate respondsToSelector:@selector(barPlot:barWasUnselectedAtRecordIndex:)])
                [theDelegate barPlot:self barWasUnselectedAtRecordIndex:d_ptr.touch_selected_last];             
            d_ptr.touch_selected_last = NSNotFound;
        }
    }
    else {
        result = [super pointingDeviceDownEvent:event atPoint:interactionPoint];
    }
    
	return result;
}

- (BOOL)pointingDeviceUpEvent:(id)event atPoint:(CGPoint)interactionPoint {
    id <UICPBarPlotDelegate> theDelegate = self.delegate;
    
    if (movingSelectedEnable) {
        if (d_ptr.moving_selected_last != NSNotFound) {            
            if ([theDelegate respondsToSelector:@selector(barPlot:barWasUnselectedAtRecordIndex:)])
                [theDelegate barPlot:self barWasUnselectedAtRecordIndex:d_ptr.moving_selected_last];
            d_ptr.moving_selected_last = NSNotFound;
        }
    }
    
    return [super pointingDeviceUpEvent:event atPoint:interactionPoint];
}

- (BOOL)pointingDeviceDraggedEvent:(id)event atPoint:(CGPoint)interactionPoint {
    BOOL ret = [super pointingDeviceDraggedEvent:event atPoint:interactionPoint];
    
    CPGraph *theGraph = self.graph;
    CPPlotArea *thePlotArea = self.plotArea;
    if ( !theGraph || !thePlotArea ) return NO;
    
    id <UICPBarPlotDelegate> theDelegate = self.delegate;
    
    if (movingSelectedEnable) {                               
        if ( [theDelegate respondsToSelector:@selector(barPlot:barWasSelectedAtRecordIndex:)] ) {
            // Inform delegate if a point was hit
            CGPoint plotAreaPoint = [theGraph convertPoint:interactionPoint toLayer:thePlotArea];
            
            NSUInteger barCount = self.cachedDataCount;

            BOOL seled = NO;
            for ( NSUInteger ii = 0; ii < barCount; ii++ ) {
                CGMutablePathRef path = [self newBarPathWithContext:NULL recordIndex:ii];
                
                if ( CGPathContainsPoint(path, nil, plotAreaPoint, false) ) {                    
                    CGPathRelease(path);
                    seled = YES;
                    if (ii != d_ptr.moving_selected_last && d_ptr.moving_selected_last != NSNotFound) {
                        if ([theDelegate respondsToSelector:@selector(barPlot:barWasUnselectedAtRecordIndex:)])
                             [theDelegate barPlot:self barWasUnselectedAtRecordIndex:d_ptr.moving_selected_last];                         
                    }
                    if (ii != d_ptr.touch_selected_last && d_ptr.touch_selected_last != NSNotFound) {
                        if ([theDelegate respondsToSelector:@selector(barPlot:barWasUnselectedAtRecordIndex:)])
                            [theDelegate barPlot:self barWasUnselectedAtRecordIndex:d_ptr.touch_selected_last];                         
                        d_ptr.touch_selected_last = NSNotFound;
                    }
                    if (ii != d_ptr.moving_selected_last) {
                        [theDelegate barPlot:self barWasSelectedAtRecordIndex:ii];
                        d_ptr.moving_selected_last = ii;
                    }                    
                    break;
                }
                
                CGPathRelease(path);			
            }
            
            if (!seled && d_ptr.moving_selected_last != NSNotFound) {    
                if ([theDelegate respondsToSelector:@selector(barPlot:barWasUnselectedAtRecordIndex:)])
                     [theDelegate barPlot:self barWasUnselectedAtRecordIndex:d_ptr.moving_selected_last];             
                d_ptr.moving_selected_last = NSNotFound;
            }
            
            ret = seled;
        }
    }
    
    return ret;
}

- (CPBarLayer*)barLayer:(NSUInteger)idx {
    CPAnnotation *anno = [d_ptr.bars objectAtIndex:idx];
    return (CPBarLayer*)anno.contentLayer;
}

@end

WSI_END