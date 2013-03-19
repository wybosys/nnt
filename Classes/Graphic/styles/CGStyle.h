
# ifndef __WSICG_STYLE_5ABD45C0C2EB407E91EE9D10BA0BC9D2_H_INCLUDED
# define __WSICG_STYLE_5ABD45C0C2EB407E91EE9D10BA0BC9D2_H_INCLUDED

# import "WCGFill.h"
# import "../shapes/CGShape.h"
# import "CGStyleContext.h"

WSI_BEGIN_HEADER_OBJC

@interface WCGStyle : WSIObject {
    
    //! link.
    WCGStyle* _previous;
    WCGStyle* _next;
    
    //! fillable. default is YES.
    BOOL fillable;
    
    //! strokable, default is NO.
    BOOL strokable;
}

@property (nonatomic, assign) WCGStyle *previous, *next;
@property (nonatomic, assign) BOOL fillable, strokable;

- (void)drawInContext:(WCGStyleContext*)ctx;
- (void)break_previous_next;

@end

@interface WCGShapeStyle : WCGStyle {
    WCGShape* _shape;
}

@property (nonatomic, retain) WCGShape* shape;

@end

@interface WCGFillStyle : WCGStyle {
    WCGFill* _fill;
}

@property (nonatomic, retain) WCGFill* fill;

@end

@interface WCGStyleSheet : WSIObject {
    
    //! array for store all styles.
    NSMutableDictionary* _styles;
    
@protected
    WCGStyle *_root, *_last;
}

@property (nonatomic, retain, readonly) NSDictionary* styles;

//! add style.
- (void)addStyle:(WCGStyle*)style forKey:(NSString*)key;

//! find.
- (id)styleForKey:(NSString*)key;

//! remove.
- (void)removeStyleForKey:(NSString*)key;

//! draw.
- (void)drawInContext:(CGContextRef)ctx inRect:(CGRect)rect;

//! clear.
- (void)clear;

@end

WSI_END_HEADER_OBJC

# endif