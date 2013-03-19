
# ifndef __WSI_MACH_6F08C47A2E09457FAA59B22120D1B1ED_H_INCLUDED
# define __WSI_MACH_6F08C47A2E09457FAA59B22120D1B1ED_H_INCLUDED

WSI_BEGIN_HEADER_C

extern const size_t kHostSize;

# ifdef WSI_MACH_PRIVATE

WSI_EXTERN void mem_init(void);

# endif

WSI_EXTERN natural_t mem_used_size(void);
WSI_EXTERN natural_t mem_free_size(void);
WSI_EXTERN natural_t mem_total_size(void);
WSI_EXTERN float cpu_usage(void);

WSI_END_HEADER_C

# endif