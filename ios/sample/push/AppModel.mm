
# include "Foundation+NNT.h"
# include "AppModel.h"
# include "HttpRequest.h"
# include "TextObjParser.h"
# include "BaseN+WSI.h"

NNTAPP_BEGIN

MAddDeviceToken::MAddDeviceToken()
{
    set_rpc(cross::HttpGetRequest::getClass());
    set_url(@"http://wybo-work.local/wsi/Service/apns/index.py/add?");
    tog_cache(false);
    set_parser(parser::TextObject());
}

ns::URL MAddDeviceToken::url() const
{
    ns::String da = core::type_cast<ns::String>(base64::encode(core::type_cast<core::data>(dt)));
    return ns::URL::UTF8(_url() + @"dt=" + da);
}

NNTAPP_END
