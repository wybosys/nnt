
# import "Core.h"
# import "CorePlot+WSI.h"
# import "Math+WSI.h"

WSI_BEGIN

@interface CPPieChart ()

- (CGFloat)radiansForPieSliceValue:(CGFloat)pieSliceValue;
- (void)drawSliceInContext:(CGContextRef)context centerPoint:(CGPoint)centerPoint radialOffset:(CGFloat)radialOffset startingValue:(CGFloat)startingValue width:(CGFloat)sliceWidth fill:(CPFill *)sliceFill;
- (void)addSliceToPath:(CGMutablePathRef)slicePath centerPoint:(CGPoint)center startingAngle:(CGFloat)startingAngle finishingAngle:(CGFloat)finishingAngle;
- (void)renderAsVectorInContext:(CGContextRef)context;
- (void)drawOverlayInContext:(CGContextRef)context centerPoint:(CGPoint)centerPoint;
- (CGFloat)normalizedPosition:(CGFloat)rawPosition;
- (BOOL)angle:(CGFloat)touchedAngle betweenStartAngle:(CGFloat)startingAngle endAngle:(CGFloat)endingAngle;

@end

@implementation CPPieChart (WSI)

- (CGPoint)centerPoint:(CGContextRef)context {
    CGRect plotAreaBounds = self.plotArea.bounds;
	CGPoint anchor = self.centerAnchor;
	CGPoint centerPoint = CGPointMake(plotAreaBounds.origin.x + plotAreaBounds.size.width * anchor.x,
									  plotAreaBounds.origin.y + plotAreaBounds.size.height * anchor.y);
	centerPoint = [self convertPoint:centerPoint fromLayer:self.plotArea];
	centerPoint = CPAlignPointToUserSpace(context, centerPoint);
    return centerPoint;
}

@end

@interface UICPPieChartPrivate : NSObject {
    UICPPieChart *d_owner;
    NSMutableArray *indicators;
    CGPoint evtpt_rotate;
    CGPoint pt_center;
    NSMutableArray *tmp_annos;
    NSMutableArray *tmp_annos_indicators;
    
    NSTimer *timer_animation;
	NSTimer *timer_stopAnimation;
    int move_dirc;
    int move_position;
    int move_speed;
    
    int slice_lst_dragging;
}

@property (nonatomic, assign) UICPPieChart *d_owner;
@property (nonatomic, retain) NSMutableArray *indicators;
@property (nonatomic) CGPoint evtpt_rotate;
@property (nonatomic) CGPoint pt_center;
@property (nonatomic, retain) NSMutableArray *tmp_annos;
@property (nonatomic, retain) NSMutableArray *tmp_annos_indicators;
@property (nonatomic, retain) NSTimer *timer_animation;
@property (nonatomic, retain) NSTimer *timer_stopAnimation;
@property (nonatomic) int move_dirc;
@property (nonatomic) int move_position;
@property (nonatomic) int move_speed;
@property (nonatomic) int slice_lst_dragging;

- (int)hitTestSlice:(CGPoint)point;

@end

@interface UICPPieChart (WSI)

- (void)drawIndicatorsInContext:(CGContextRef)context;
- (void)drawIndicatorInContext:(CGContextRef)context indicator:(UICPIndicatorLayer*)indicator;

@end

@implementation UICPPieChartPrivate

@synthesize d_owner;
@synthesize indicators;
@synthesize pt_center;
@synthesize evtpt_rotate;
@synthesize tmp_annos;
@synthesize tmp_annos_indicators;
@synthesize timer_animation,timer_stopAnimation;
@synthesize move_dirc,move_position;
@synthesize move_speed;
@synthesize slice_lst_dragging;

- (id)init {
    self = [super init];
    
    indicators = [NSMutableArray new];
    tmp_annos = [NSMutableArray new];
    tmp_annos_indicators = [NSMutableArray new];
    slice_lst_dragging = -1;
    
    return self;
}

- (void)dealloc {
    [indicators release];
    [tmp_annos release];
    [tmp_annos_indicators release];
    [super dealloc];
}

- (int)hitTestSlice:(CGPoint)point {
    int ret = -1;
    
    CPGraph *theGraph = d_owner.graph;
	CPPlotArea *thePlotArea = d_owner.plotArea;    
    if (!theGraph || !thePlotArea) return -1;
    
    // hittest
    CGPoint plotAreaPoint = [theGraph convertPoint:point toLayer:thePlotArea];
    NSUInteger sampleCount = d_owner.cachedDataCount;
    if ( sampleCount == 0 ) return -1;
    
    CGRect plotAreaBounds = thePlotArea.bounds;
    CGPoint anchor = d_owner.centerAnchor;
    CGPoint centerPoint = CGPointMake(plotAreaBounds.origin.x + plotAreaBounds.size.width * anchor.x,
                                      plotAreaBounds.origin.y + plotAreaBounds.size.height * anchor.y);
    centerPoint = [d_owner convertPoint:centerPoint fromLayer:thePlotArea];
    
    id <CPPieChartDataSource> theDataSource = (id <CPPieChartDataSource>)d_owner.dataSource;
    BOOL dataSourceProvidesRadialOffsets = [theDataSource respondsToSelector:@selector(radialOffsetForPieChart:recordIndex:)];
    
    CGFloat dx = plotAreaPoint.x - centerPoint.x;
    CGFloat dy = plotAreaPoint.y - centerPoint.y;
    //CGFloat distanceSquared = dx * dx + dy * dy;
    
    CGFloat touchedAngle = [d_owner normalizedPosition:cg_atan2(dy, dx)];
    CGFloat startingAngle = [d_owner normalizedPosition:d_owner.startAngle];
    
    switch (d_owner.sliceDirection ) {
        case CPPieDirectionClockwise: {
            for ( NSUInteger currentIndex = 0; currentIndex < sampleCount; currentIndex++ ) {
                // calculate angles for this slice
                CGFloat width = [d_owner cachedDoubleForField:CPPieChartFieldSliceWidthNormalized recordIndex:currentIndex];
                if ( isnan(width) ) continue;
                CGFloat endingAngle = startingAngle - width;
                
                // offset the center point of the slice if needed
                CGFloat offsetTouchedAngle = touchedAngle;
                //CGFloat offsetDistanceSquared = distanceSquared;
                CGFloat radialOffset = 0.0;
                if ( dataSourceProvidesRadialOffsets ) {
                    radialOffset = [theDataSource radialOffsetForPieChart:d_owner recordIndex:currentIndex];
                    
                    if ( radialOffset != 0.0 ) {
                        CGPoint offsetCenter;
                        CGFloat medianAngle = M_PI * (startingAngle + endingAngle);
                        offsetCenter = CGPointMake(centerPoint.x + cg_cos(medianAngle) * radialOffset,
                                                   centerPoint.y + cg_sin(medianAngle) * radialOffset);
                        dx = plotAreaPoint.x - offsetCenter.x;
                        dy = plotAreaPoint.y - offsetCenter.y;
                        offsetTouchedAngle = [d_owner normalizedPosition:cg_atan2(dy, dx)];
                        //offsetDistanceSquared = dx * dx + dy * dy;
                    }
                }
                
                // check angles
                if ( [d_owner angle:touchedAngle betweenStartAngle:startingAngle endAngle:endingAngle] ) {
                    if ( [d_owner angle:offsetTouchedAngle betweenStartAngle:startingAngle endAngle:endingAngle] ) {
                        ret = currentIndex;
                        return ret;
                    }
                    else {
                        return NO;
                    }
                }
                
                // save angle for the next slice
                startingAngle = endingAngle;
            }
        } break;
        case CPPieDirectionCounterClockwise: {
            for ( NSUInteger currentIndex = 0; currentIndex < sampleCount; currentIndex++ ) {
                // calculate angles for this slice
                CGFloat width = [d_owner cachedDoubleForField:CPPieChartFieldSliceWidthNormalized recordIndex:currentIndex];
                if ( isnan(width) ) continue;
                CGFloat endingAngle = startingAngle + width;
                
                // offset the center point of the slice if needed
                CGFloat offsetTouchedAngle = touchedAngle;
                //CGFloat offsetDistanceSquared = distanceSquared;
                CGFloat radialOffset = 0.0;
                if ( dataSourceProvidesRadialOffsets ) {
                    radialOffset = [theDataSource radialOffsetForPieChart:d_owner recordIndex:currentIndex];
                    
                    if ( radialOffset != 0.0 ) {
                        CGPoint offsetCenter;
                        CGFloat medianAngle = M_PI * (startingAngle + endingAngle);
                        offsetCenter = CGPointMake(centerPoint.x + cg_cos(medianAngle) * radialOffset,
                                                   centerPoint.y + cg_sin(medianAngle) * radialOffset);
                        dx = plotAreaPoint.x - offsetCenter.x;
                        dy = plotAreaPoint.y - offsetCenter.y;
                        offsetTouchedAngle = [d_owner normalizedPosition:cg_atan2(dy, dx)];
                        //offsetDistanceSquared = dx * dx + dy * dy;
                    }
                }
                
                // check angles
                if ( [d_owner angle:touchedAngle betweenStartAngle:startingAngle endAngle:endingAngle] ) {
                    if ( [d_owner angle:offsetTouchedAngle betweenStartAngle:startingAngle endAngle:endingAngle] ) {
                        ret = currentIndex;
                        return ret;
                    }
                    else {
                        return NO;
                    }
                }
                
                // save angle for the next slice
                startingAngle = endingAngle;
            }
        } break;
        default: break;
    }
    
    return ret;
}

@end

@implementation UICPPieChart (WSI)

- (void)drawIndicatorsInContext:(CGContextRef)context {
    // remove old indicator
    for (CPAnnotation *anno in d_ptr.tmp_annos_indicators) {
        [self removeAnnotation:anno];
    }
    [d_ptr.tmp_annos_indicators removeAllObjects];
    
    // draw new indicator
    for (id each in d_ptr.indicators) {
        [self drawIndicatorInContext:context indicator:each];
    }
}

- (void)drawIndicatorInContext:(CGContextRef)context indicator:(UICPIndicatorLayer*)indicator{
    CPAnnotation *anno = [CPAnnotation new];
    anno.contentLayer = indicator;
    [self addAnnotation:anno];
    [anno release];
    [d_ptr.tmp_annos_indicators addObject:anno];
    
    // set position
    CGPoint pt_center = [self centerPoint:context];
    d_ptr.pt_center = pt_center;
    CGFloat radius = self.pieRadius;
    
    CGFloat x = radius * cg_cos(indicator.positionAngle);
    CGFloat y = radius * cg_sin(indicator.positionAngle);
    
    x += pt_center.x;
    y += pt_center.y;
    
    indicator.position = CGPointMake(x, y);
    
    // set direction
    CATransform3D mat = CATransform3DMakeRotation(indicator.positionAngle + M_PI_2, 0, 0, 1);
    [indicator setTransform:mat];
}

@end

@implementation UICPPieChart

@synthesize outLine, pieTotal, totalOutLine, totalRadius;
@synthesize allowInteractiveRotate;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(UICPPieChart);
    return self;
}

- (void)dealloc {
    [outLine release];
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)addIndicator:(CPIndicatorLayer *)__layer {
    [d_ptr.indicators addObject:__layer];
}

- (void)renderAsVectorInContext:(CGContextRef)context {
    CGPoint pt_center = [self centerPoint:context];
    CGFloat diameter = self.pieRadius + self.pieRadius;
    
    int pos_x = pt_center.x - self.pieRadius;
    int pos_y = pt_center.y - self.pieRadius;
    
    // super
    [super renderAsVectorInContext:context];
    
    // local
    CGContextSaveGState(context);
    
    // draw outline
    if (outLine != nil) {
        CGAffineTransform mat = CGAffineTransformMakeTranslation(pos_x, pos_y);
        CGMutablePathRef ph_outer = CGPathCreateMutable();
        CGPathAddEllipseInRect(ph_outer, &mat, CGRectMake(0, 0, diameter, diameter));
        CGContextBeginPath(context);
        CGContextAddPath(context, ph_outer);  
        CGPathCloseSubpath(ph_outer);
        [outLine setLineStyleInContext:context];
        CGContextStrokePath(context);
        CGPathRelease(ph_outer);
    }
    
    CGContextRestoreGState(context);
    
    // hit test
    for (UICPIndicatorLayer *indicator in d_ptr.indicators) {
        int sliceId = [d_ptr hitTestSlice:indicator.position];
        if (sliceId != -1) {
            id <UICPPieChartDelegate> delegate = (id <UICPPieChartDelegate>)self.delegate;
            if ([delegate respondsToSelector:@selector(pieChart:sliceWasOver:indicator:)])
                [delegate pieChart:self sliceWasOver:sliceId indicator:indicator];
        }
    }

}

-(void)setBounds:(CGRect)newBounds {
    [super setBounds:newBounds];
}

- (void)drawSliceInContext:(CGContextRef)context centerPoint:(CGPoint)centerPoint radialOffset:(CGFloat)radialOffset startingValue:(CGFloat)startingValue width:(CGFloat)sliceWidth fill:(CPFill *)sliceFill {
    
    CGContextSaveGState(context);
	
    CGFloat startingAngle = [self radiansForPieSliceValue:startingValue];
    CGFloat finishingAngle = [self radiansForPieSliceValue:startingValue + sliceWidth];
    
    CGFloat xOffset = 0.0;
    CGFloat yOffset = 0.0;
    
    if ( radialOffset != 0.0 ) {
        CGFloat medianAngle = 0.5 * (startingAngle + finishingAngle);
        xOffset = cg_round(cg_cos(medianAngle) * radialOffset);
        yOffset = cg_round(cg_sin(medianAngle) * radialOffset);
    }
    
    CGFloat centerX = centerPoint.x + xOffset;
    CGFloat centerY = centerPoint.y + yOffset;
	
	CGMutablePathRef slicePath = CGPathCreateMutable();
    [self addSliceToPath:slicePath centerPoint:CGPointMake(centerX, centerY) startingAngle:startingAngle finishingAngle:finishingAngle];
	CGPathCloseSubpath(slicePath);
	
	if ( sliceFill ) {
		CGContextBeginPath(context);
		CGContextAddPath(context, slicePath);
		[sliceFill fillPathInContext:context]; 
	}
	
	// Draw the border line around the slice
	CPLineStyle *borderStyle = self.borderLineStyle;
	if ( borderStyle ) {
		CGContextBeginPath(context);
		CGContextAddPath(context, slicePath);
		[borderStyle setLineStyleInContext:context];
		CGContextStrokePath(context);
	}
	
	CGPathRelease(slicePath);
	CGContextRestoreGState(context);
}

- (void)drawOverlayInContext:(CGContextRef)context centerPoint:(CGPoint)centerPoint {
    [super drawOverlayInContext:context centerPoint:centerPoint];

    CGContextSaveGState(context);
    
    id <UICPPieChartDataSource> source = (id <UICPPieChartDataSource>) self.dataSource;
    CGFloat radius_tl = self.totalRadius * self.pieRadius;
    CGFloat diameter_tl = radius_tl + radius_tl;
    
    // draw total pie
    if (self.pieTotal) {
        CPFill *fill_total = nil;
        if ([source respondsToSelector:@selector(totalFillForPieChart:)])
            fill_total = [source totalFillForPieChart:self];
        CGMutablePathRef ph_total = CGPathCreateMutable();
        CGAffineTransform mat = CGAffineTransformMakeTranslation(centerPoint.x - radius_tl,
                                                                 centerPoint.y - radius_tl);
        CGPathAddEllipseInRect(ph_total, &mat, CGRectMake(0, 0, diameter_tl, diameter_tl));
        if (fill_total) {
            CGContextBeginPath(context);
            CGContextAddPath(context, ph_total);
            [fill_total fillPathInContext:context];
        }
        if (self.totalOutLine) {
            CGContextBeginPath(context);
            CGContextAddPath(context, ph_total);
            [self.totalOutLine setLineStyleInContext:context];
            CGContextStrokePath(context);
        }
        CGPathRelease(ph_total);
        
        // clear
        for (CPAnnotation *anno in d_ptr.tmp_annos) {
            [self removeAnnotation:anno];
        }
        [d_ptr.tmp_annos removeAllObjects];
        
        // total label
        CPLayer *label = nil;
        if ([source respondsToSelector:@selector(totalLabelForPieChart:)])
            label = (CPLayer*)[source totalLabelForPieChart:self];
        if (label) {
            int cnt = [[label sublayers] count];
            if (cnt == 0) {
                CPAnnotation *anno = [[CPAnnotation alloc] init];
                anno.contentLayer = label;
                [self addAnnotation:anno];
                [anno release];
                // calc height
                int sum_height = 0;
                for (CPLayer *sub in [label sublayers]) {
                    sum_height += sub.frame.size.height;
                }
                int offset_x = 0, offset_y = 0;
                if (sum_height < diameter_tl) {
                    offset_y = diameter_tl - sum_height;
                    offset_y *= .5f;
                }
                // reset frame
                int pos_x = centerPoint.x - radius_tl;
                pos_x += (diameter_tl - label.frame.size.width) * .5f + offset_x;
                int pos_y = centerPoint.y - radius_tl;
                pos_y -= offset_y - label.frame.size.height * .5f;
                label.frame = CGRectMake(pos_x,
                                         pos_y,
                                         diameter_tl, 
                                         diameter_tl);
            } else {
                // calc height
                int sum_height = 0;
                for (CPLayer *sub in [label sublayers]) {
                    sum_height += sub.frame.size.height;
                }
                int offset_x = 0, offset_y = 0;
                if (sum_height < diameter_tl) {
                    offset_y = diameter_tl - sum_height;
                    offset_y *= .5f;
                }
                // reset each frame
                int const height = diameter_tl / cnt;
                int pos_x = 0;
                int pos_y = offset_y;
                int width = 0;
                NSMutableArray *annos = [NSMutableArray new];
                for (int i = cnt; i != 0; --i) {
                    CPLayer *sub = [[label sublayers] objectAtIndex:i - 1];
                    CPAnnotation *anno = [[CPAnnotation alloc] init];
                    pos_x = offset_x + (diameter_tl - sub.frame.size.width) * .5f;                    
                    width = sub.frame.size.width;
                    int t_height = MIN(height, sub.frame.size.height);
                    sub.frame = CGRectMake(centerPoint.x - radius_tl + pos_x,
                                           centerPoint.y - radius_tl + pos_y,
                                           width,
                                           t_height);
                    pos_y += t_height;
                    anno.contentLayer = sub;
                    [annos addObject:anno];
                    [anno release];
                }
                for (CPAnnotation *anno in annos) {
                    [self addAnnotation:anno];
                    [d_ptr.tmp_annos addObject:anno];
                }
                [annos release];
            }
        }
    }
    
    // draw indicators
    [self drawIndicatorsInContext:context];
    
    CGContextRestoreGState(context);
}

# pragma mark -
# pragma mark interactive

- (BOOL)pointingDeviceDownEvent:(id)event atPoint:(CGPoint)interactionPoint {
    [d_ptr.timer_animation invalidate];
    [d_ptr.timer_stopAnimation invalidate];
    d_ptr.move_speed = 0;
    
    BOOL ret = [super pointingDeviceDownEvent:event atPoint:interactionPoint];
    
    if (allowInteractiveRotate) {
        d_ptr.evtpt_rotate = interactionPoint;
    }
    
    return ret;
}

- (BOOL)pointingDeviceDraggedEvent:(id)event atPoint:(CGPoint)interactionPoint {

    BOOL ret = [super pointingDeviceDraggedEvent:event atPoint:interactionPoint];
    
    //CGFloat diameter = self.pieRadius + self.pieRadius;
    CGFloat radius = self.pieRadius;
    
    BOOL b_inpie = distance_points2d(interactionPoint.x, interactionPoint.y, d_ptr.pt_center.x, d_ptr.pt_center.y) < radius;
    id <UICPPieChartDelegate> delegate = (id <UICPPieChartDelegate>)self.delegate;
    
    // rotate
    if (allowInteractiveRotate && b_inpie) {
        CGFloat dangle = 0;
        CGFloat dangle_x = interactionPoint.x - d_ptr.evtpt_rotate.x;
        CGFloat dangle_y = interactionPoint.y - d_ptr.evtpt_rotate.y;

        if (ABS(dangle_x) > ABS(dangle_y)) {
      
            dangle = dangle_x;
            if (interactionPoint.y > d_ptr.pt_center.y){
                dangle = -dangle; 
                d_ptr.move_position = 3; //at top
            }else{
                d_ptr.move_position = 4; //at down
            }
            
            if(interactionPoint.x > d_ptr.evtpt_rotate.x){
                d_ptr.move_dirc = 1; //move right
            }
            else{
                d_ptr.move_dirc = 2; //move left
            }
   
        } else {
            dangle = dangle_y;
            if (interactionPoint.x < d_ptr.pt_center.x){
                dangle = -dangle;
                d_ptr.move_position = 2; //at left
            }else{
                d_ptr.move_position = 1; //at right
            }
            
			if(interactionPoint.y > d_ptr.evtpt_rotate.y)
				d_ptr.move_dirc = 3; //move up
			else 
				d_ptr.move_dirc = 4; //move down
        }
        
        d_ptr.move_speed = ABS(dangle); //  move speed
        
        real angle = dangle * M_PI_360;
        angle = self.startAngle + angle;
        angle = M_2PI_RESTRICT(angle);
        self.startAngle = angle;
        d_ptr.evtpt_rotate = interactionPoint;
        
        int sliceId = [d_ptr hitTestSlice:interactionPoint];
        if (sliceId != -1) {
            if ([delegate respondsToSelector:@selector(pieChart:sliceWasDragging:)]) {
                [delegate pieChart:self sliceWasDragging:sliceId];
                d_ptr.slice_lst_dragging = sliceId;
            }
        }
        
        // hit test
        for (UICPIndicatorLayer *indicator in d_ptr.indicators) {
            int sliceId = [d_ptr hitTestSlice:indicator.position];
            if (sliceId != -1) {                
                if ([delegate respondsToSelector:@selector(pieChart:sliceWasOver:indicator:)])
                    [delegate pieChart:self sliceWasOver:sliceId indicator:indicator];
            }
        }
    }
    
    return ret;
}

- (BOOL)pointingDeviceUpEvent:(id)event atPoint:(CGPoint)interactionPoint {
    BOOL ret = [super pointingDeviceUpEvent:event atPoint:interactionPoint];
    
    id <UICPPieChartDelegate> delegate = (id <UICPPieChartDelegate>)self.delegate;
    
    // if dragging
    if (d_ptr.slice_lst_dragging != -1) {
        if ([delegate respondsToSelector:@selector(pieChart:sliceWasDraggingEnd:)])
            [delegate pieChart:self sliceWasDraggingEnd:d_ptr.slice_lst_dragging];
        d_ptr.slice_lst_dragging = -1;
    }
    
    // hit test
    for (UICPIndicatorLayer *indicator in d_ptr.indicators) {
        int sliceId = [d_ptr hitTestSlice:indicator.position];
        if (sliceId != -1) {            
            if ([delegate respondsToSelector:@selector(pieChart:sliceWasOver:indicator:)])
                [delegate pieChart:self sliceWasOver:sliceId indicator:indicator];
        }
    }
    
    [d_ptr.timer_animation invalidate];
    d_ptr.timer_animation = [NSTimer scheduledTimerWithTimeInterval:(0.1) target:self selector:@selector(animationTimer) userInfo:nil repeats:YES];
    [d_ptr.timer_stopAnimation invalidate];
	d_ptr.timer_stopAnimation = [NSTimer scheduledTimerWithTimeInterval:(2) target:self selector:@selector(stop_AnimationTimer) userInfo:nil repeats:NO];

    return ret;
}

- (void)stop_AnimationTimer{
   // printf("stop...\n");
	[d_ptr.timer_animation invalidate];
    [d_ptr.timer_stopAnimation invalidate];
}

- (void) animationTimer{
    if(d_ptr.move_speed > 12){
        
        if(d_ptr.move_speed >= self.pieRadius/2){
            d_ptr.move_speed = self.pieRadius/2;
        }
        
        CGPoint interactionPoint = d_ptr.evtpt_rotate;

        CGPoint left_point = CGPointMake(d_ptr.pt_center.x - self.pieRadius, d_ptr.pt_center.y);
        CGPoint down_point = CGPointMake(d_ptr.pt_center.x, d_ptr.pt_center.y - self.pieRadius);
        CGPoint right_point = CGPointMake(d_ptr.pt_center.x + self.pieRadius, d_ptr.pt_center.y);
        CGPoint top_point = CGPointMake(d_ptr.pt_center.x, d_ptr.pt_center.y + self.pieRadius);

        switch (d_ptr.move_dirc) {
            case 1:
                interactionPoint.x += d_ptr.move_speed;
                if(interactionPoint.x >= right_point.x){
                    if(d_ptr.move_position == 4){
                        d_ptr.move_position = 1;
                        d_ptr.move_dirc = 3;
                    }else if(d_ptr.move_position == 3){
                        d_ptr.move_position = 1;
                        d_ptr.move_dirc = 4;
                    }
                }
                break;
            case 2:
                interactionPoint.x -= d_ptr.move_speed;
                if(interactionPoint.x <= left_point.x){
                    if(d_ptr.move_position ==4){
                        d_ptr.move_position = 2;
                        d_ptr.move_dirc = 3;
                    } else if(d_ptr.move_position == 3) {
                        d_ptr.move_position = 2;
                        d_ptr.move_dirc = 4;
                    }
                }
                break;
            case 3:
                interactionPoint.y += d_ptr.move_speed;
                if(interactionPoint.y >= top_point.y){
                    if(d_ptr.move_position == 1) {
                        d_ptr.move_position = 3;
                        d_ptr.move_dirc = 2;
                    } else if (d_ptr.move_position == 2) {
                        d_ptr.move_position = 3;
                        d_ptr.move_dirc = 1;
                    }
                }
                break;
            case 4:
                interactionPoint.y -= d_ptr.move_speed;
                if(interactionPoint.y <= down_point.y){
                    if(d_ptr.move_position == 1){
                        d_ptr.move_position = 4;
                        d_ptr.move_dirc = 2;
                    }else if(d_ptr.move_position == 2){
                        d_ptr.move_position = 4;
                        d_ptr.move_dirc = 1;
                    }
                }
                break;
            default:
                break;
        }
        
        d_ptr.move_speed -=2;
        
       // CGFloat radius = self.pieRadius;
        
        //BOOL b_inpie = distance_points2d(interactionPoint.x, interactionPoint.y, d_ptr.pt_center.x, d_ptr.pt_center.y) < radius;
        
        // rotate
        if (allowInteractiveRotate) {
            CGFloat dangle = 0;
            CGFloat dangle_x = interactionPoint.x - d_ptr.evtpt_rotate.x;
            CGFloat dangle_y = interactionPoint.y - d_ptr.evtpt_rotate.y;
            if (ABS(dangle_x) < ABS(dangle_y)) {
                dangle = dangle_y + 1;
                if (interactionPoint.x < d_ptr.pt_center.x)
                    dangle = -dangle;
            }
            else {
                dangle = dangle_x + 1;
                if (interactionPoint.y > d_ptr.pt_center.y)
                    dangle = -dangle;  
            }
            self.startAngle += dangle * M_PI_360;
            self.startAngle = M_2PI_RESTRICT(self.startAngle);
            d_ptr.evtpt_rotate = interactionPoint;
        }
        // hit test
        for (UICPIndicatorLayer *indicator in d_ptr.indicators) {
            int sliceId = [d_ptr hitTestSlice:indicator.position];
            if (sliceId != -1) {
                id <UICPPieChartDelegate> delegate = (id <UICPPieChartDelegate>)self.delegate;
                if ([delegate respondsToSelector:@selector(pieChart:sliceWasOver:indicator:)])
                    [delegate pieChart:self sliceWasOver:sliceId indicator:indicator];
            }
        }
	}

}

@end

WSI_END
