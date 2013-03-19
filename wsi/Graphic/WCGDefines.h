
# ifndef __WSI_WSICG_DEFINES_87F262A7DFF4456186EBC03347D2FF27_H_INCLUDED
# define __WSI_WSICG_DEFINES_87F262A7DFF4456186EBC03347D2FF27_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

typedef enum  _WCGNumericType {
    WCGNumericTypeInteger,	//! Integer
    WCGNumericTypeFloat,    //! Float
    WCGNumericTypeDouble    //! Double
} WCGNumericType;

typedef struct _WCGRGBAColor {
	CGFloat red;	//! The red component (0 ≤ red ≤ 1).
	CGFloat green;	//! The green component (0 ≤ green ≤ 1).
	CGFloat blue;	//! The blue component (0 ≤ blue ≤ 1).
	CGFloat alpha;	//! The alpha component (0 ≤ alpha ≤ 1).
} WCGRGBAColor;

//! @brief Enumeration of label positioning offset directions
typedef enum _WCGSign {
	WCGSignNone     =  0, //! No offset
	WCGSignPositive = +1, //! Positive offset
	WCGSignNegative = -1  //! Negative offset
} WCGSign;

//! @brief Enumeration of constraint types used in spring and strut model.
typedef enum _WCGConstraint {
    WCGConstraintNone,   //! No constraint. Free movement, equivalent to "spring".
    WCGConstraintFixed	 //! Distance is fixed. Equivalent to a "strut".
} WCGConstraint;

//! @brief Constraints for a relative position.
typedef struct _WCGConstraints {
	WCGConstraint lower;	//! The constraint on the lower range.
	WCGConstraint upper;	//! The constraint on the upper range.
} WCGConstraints;

//! @brief Enumeration of alignments.
typedef enum _WCGAlignment {
    WCGAlignmentLeft = 1,
    WCGAlignmentRight = 2,
    WCGAlignmentCenterH = 4,
    WCGAlignmentCenterV = 8,
    WCGAlignmentCenter = WCGAlignmentCenterH | WCGAlignmentCenterV,
    WCGAlignmentTop = 0x10,
    WCGAlignmentBottom = 0x20
} WCGAlignment;

//! @brief Enumeration of direction.
typedef enum _WCGDirection {
    WCGDirectionLeft   = 0,
    WCGDirectionRight  = 1,
    WCGDirectionTop    = 2,
    WCGDirectionBottom = 3,
    WCGDirectionWest = WCGDirectionLeft,
    WCGDirectionEast = WCGDirectionRight,
    WCGDirectionNorth = WCGDirectionTop,
    WCGDirectionSouth = WCGDirectionBottom
} WCGDirection;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cg)

# ifdef WSI_TARGET_MAC

# if __LP64__ || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64
#   define CG_IS_NS
# endif

# ifndef CG_IS_NS

template <typename nst, typename cgt>
inline_impl nst const& _conv(cgt const& obj)
{
    return *(nst const*)&obj;
}

inline_impl NSRect const& conv(CGRect const& rc)
{
    return _conv<NSRect>(rc);
}

inline_impl CGRect const& conv(NSRect const& rc)
{
    return _conv<CGRect>(rc);
}

inline_impl NSSize const& conv(CGSize const& sz)
{
    return _conv<NSSize>(sz);
}

inline_impl CGSize const& conv(NSSize const& sz)
{
    return _conv<CGSize>(sz);
}

inline_impl NSPoint const& conv(CGPoint const& pt)
{
    return _conv<NSPoint>(pt);
}

inline_impl CGPoint const& conv(NSPoint const& pt)
{
    return _conv<CGPoint>(pt);
}

# else

template <typename t>
inline_impl t const& conv(t const& obj)
{
    return obj;
}

# endif

# else

template <typename t>
inline_impl t const& conv(t const& obj)
{
    return obj;
}

# endif

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif