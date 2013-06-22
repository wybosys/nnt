
# ifndef __NNT_MACH_6F08C47A2E09457FAA59B22120D1B1ED_H_INCLUDED
# define __NNT_MACH_6F08C47A2E09457FAA59B22120D1B1ED_H_INCLUDED

NNT_BEGIN_HEADER_C

extern const size_t kHostSize;

# ifdef NNT_MACH_PRIVATE

NNT_EXTERN void mem_init(void);

# endif

NNT_EXTERN natural_t mem_used_size(void);
NNT_EXTERN natural_t mem_free_size(void);
NNT_EXTERN natural_t mem_total_size(void);
NNT_EXTERN float cpu_usage(void);

NNT_END_HEADER_C

# endif