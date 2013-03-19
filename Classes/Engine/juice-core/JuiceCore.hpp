
# ifndef __JUICE_ENGINE_913C2085BEA74362A78A1B21B0576A88_H_INCLUDED
# define __JUICE_ENGINE_913C2085BEA74362A78A1B21B0576A88_H_INCLUDED

# define JUICE_BEGIN namespace juice {
# define JUICE_END }
# define JUICEIMPL_BEGIN JUICE_BEGIN namespace impl {
# define JUICEIMPL_END } JUICE_END
# define JUICE_EXCEPTION(exp) namespace exception { class exp {}; }
# define JUICE_SUPER(cls) typedef cls super; friend class cls;
# define JUICE_FRIEND(cls) friend class cls;

# ifdef _DEBUG
#   define JUICE_DEBUG
#   define throw_class(cls) { throw cls(); }
# else
#   define throw_class(cls) {}
# endif

typedef char const* rawstr_t;

# ifndef jimpl
#   define jimpl ((implT*)this)
# endif

# endif