
# import "Core.h"
# import "URLCodec.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(ns)

ns::String URLEncode::encode(ns::String const& str)
{
    return [str urlencode];
}

ns::String URLEncode::encode(ns::Dictionary const& dict, bool encoded)
{
    ns::String ret;
    ns::Array keys = dict.allkeys();
    const uint len = keys.count();
    
    for (uint i = 1; i <= len; ++i)
    {
        ns::String key = keys[i - 1];
        ns::String value = dict[key];
        
        if (encoded == false)
            value = URLEncode::encode(value);
        
        ns::String str = key + @"=" + value;
        if (i != len)
            str += @"&";
        
        ret += str;
    }
    
    return ret;
}

URLDecode::URLDecode()
{
    PASS;
}

URLDecode::URLDecode(String const& str)
{
    decode(str);
}

void URLDecode::clear()
{
    _data.clear();
}

void URLDecode::decode(String const& str)
{
    ns::Regex re_base(@"(\\S+)\\?(\\S+)");
    ns::Array res = re_base.capture(str);
    if (res.size() != 3)
        return;
    
    _base = res[1];
    ns::String str_pams = res[2];
    
    // get parameters.
    ns::Regex re_pam(@"([a-zA-Z0-9]+)=([a-zA-Z0-9%#\"']*)");
    ns::Array res_pams = re_pam.captures(str_pams);
    
    for (id each in res_pams())
    {
        ns::Array data(each);
        
        ns::String key = data[1];
        ns::String value = data[2];
        
        id obj = _data.find(key);
        if (obj == nil)
        {
            _data[key] = value;
        }
        else
        {
            if ([obj isKindOfClass:[NSArray class]])
            {
                ns::MutableArray values(obj);
                values.add(value);
            }
            else
            {
                ns::MutableArray values;
                values.add(obj);
                values.add(value);
                _data[key] = values;
            }
        }
    }
}

bool URLDecode::is_array(String const& key) const
{
    id obj = _data[key];
    return [obj isKindOfClass:[NSArray class]];
}

String URLDecode::value(String const& key) const
{
    return String((id)_data[key]);
}

Array URLDecode::array(String const& key) const
{
    return Array((id)_data[key]);
}

WSI_END_NS
WSI_END_CXX
