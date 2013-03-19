
# ifndef __NNT_NNTCG_DEFINES_87F262A7DFF4456186EBC03347D2FF27_H_INCLUDED
# define __NNT_NNTCG_DEFINES_87F262A7DFF4456186EBC03347D2FF27_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

typedef enum  _NgNumericType {
    NgNumericTypeInteger,	//! Integer
    NgNumericTypeFloat,    //! Float
    NgNumericTypeDouble    //! Double
} NgNumericType;

typedef struct _NgRGBAColor {
	CGFloat red;	//! The red component (0 ≤ red ≤ 1).
	CGFloat green;	//! The green component (0 ≤ green ≤ 1).
	CGFloat blue;	//! The blue component (0 ≤ blue ≤ 1).
	CGFloat alpha;	//! The alpha component (0 ≤ alpha ≤ 1).
} NgRGBAColor;

//! @brief Enumeration of label positioning offset directions
typedef enum _NgSign {
	NgSignNone     =  0, //! No offset
	NgSignPositive = +1, //! Positive offset
	NgSignNegative = -1  //! Negative offset
} NgSign;

//! @brief Enumeration of constraint types used in spring and strut model.
typedef enum _NgConstraint {
    NgConstraintNone,   //! No constraint. Free movement, equivalent to "spring".
    NgConstraintFixed	 //! Distance is fixed. Equivalent to a "strut".
} NgConstraint;

//! @brief Constraints for a relative position.
typedef struct _NgConstraints {
	NgConstraint lower;	//! The constraint on the lower range.
	NgConstraint upper;	//! The constraint on the upper range.
} NgConstraints;

//! @brief Enumeration of alignments.
typedef enum _NgAlignment {
    NgAlignmentLeft = 1,
    NgAlignmentRight = 2,
    NgAlignmentCenterH = 4,
    NgAlignmentCenterV = 8,
    NgAlignmentCenter = NgAlignmentCenterH | NgAlignmentCenterV,
    NgAlignmentTop = 0x10,
    NgAlignmentBottom = 0x20
} NgAlignment;

//! @brief Enumeration of direction.
typedef enum _NgDirection {
    NgDirectionLeft   = 0,
    NgDirectionRight  = 1,
    NgDirectionTop    = 2,
    NgDirectionBottom = 3,
    NgDirectionWest = NgDirectionLeft,
    NgDirectionEast = NgDirectionRight,
    NgDirectionNorth = NgDirectionTop,
    NgDirectionSouth = NgDirectionBottom
} NgDirection;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cg)

# ifdef NNT_TARGET_MAC

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif