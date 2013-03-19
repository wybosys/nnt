
# include "WSIFoundation.h"
# include "MainModel.h"
# include "HttpRequest.h"
# include "TextObjParser.h"

WSIAPP_BEGIN

ByPayModel::ByPayModel()
{
    set_rpc(cross::HttpPostRequest::getClass());
    set_parser(parser::TextObject());
    set_update(true);
    set_url(@"http://t.bypay.cn/wapGateWay/wap.order!plusMerPay.ac");
}

bool ByPayModel::process(id ret)
{
    result = ns::String::As(ret);
    return true;
}

WSIAPP_END
