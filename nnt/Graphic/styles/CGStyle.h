
# ifndef __NNTCG_STYLE_5ABD45C0C2EB407E91EE9D10BA0BC9D2_H_INCLUDED
# define __NNTCG_STYLE_5ABD45C0C2EB407E91EE9D10BA0BC9D2_H_INCLUDED

# import "NGFill.h"
# import "../shapes/CGShape.h"
# import "CGStyleContext.h"

NNT_BEGIN_HEADER_OBJC

@interface NgStyle : NNTObject {
    
    //! link.
    NgStyle* _previous;
    NgStyle* _next;
    
    //! fillable. default is YES.
    BOOL fillable;
    
    //! strokable, default is NO.
    BOOL strokable;
}

@property (nonatomic, assign) NgStyle *previous, *next;
@property (nonatomic, assign) BOOL fillable, strokable;

- (void)drawInContext:(NgStyleContext*)ctx;
- (void)break_previous_next;

@end

@interface NgShapeStyle : NgStyle {
    NgShape* _shape;
}

@property (nonatomic, retain) NgShape* shape;

@end

@interface NgFillStyle : NgStyle {
    NgFill* _fill;
}

@property (nonatomic, retain) NgFill* fill;

@end

@interface NgStyleSheet : NNTObject {
    
    //! array for store all styles.
    NSMutableDictionary* _styles;
    
@protected
    NgStyle *_root, *_last;
}

@property (nonatomic, retain, readonly) NSDictionary* styles;

//! add style.
- (void)addStyle:(NgStyle*)style forKey:(NSString*)key;

//! find.
- (id)styleForKey:(NSString*)key;

//! remove.
- (void)removeStyleForKey:(NSString*)key;

//! draw.
- (void)drawInContext:(CGContextRef)ctx inRect:(CGRect)rect;

//! clear.
- (void)clear;

@end

NNT_END_HEADER_OBJC

# endif