
# ifndef __WSI_BSE_APPENGINEMODEL_INFORMATION_7B426E13BEF846BC8019FA2F0CAAF3A4_H_INCLUDED
# define __WSI_BSE_APPENGINEMODEL_INFORMATION_7B426E13BEF846BC8019FA2F0CAAF3A4_H_INCLUDED

# include "AEModel.h"

WSI_BEGIN_HEADER_OBJC

@interface AEModel : AppEngineModel

@end

@interface AEMInfoLaunchCounterIncrease : AEModel

@property (nonatomic, copy) IN NEED NSString *app_name, *app_id;

@end

@interface AEMInfoLaunchDeviceCounterIncrease : AEModel

@property (nonatomic, copy) IN NEED NSString *app_name, *app_id, *dev_id;

@end

WSI_END_HEADER_OBJC

# endif
