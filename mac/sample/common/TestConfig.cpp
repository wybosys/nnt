
# include <wsi/WSIFoundation.h>
# include "TestConfig.h"
# include <wsi/Store/WSIConfiguration.h>

WSIAPP_BEGIN

void TestConfig::main()
{
    ::wsi::store::Configuration* config = ::wsi::store::Configuration::getInstance();
    config->add((void*)"K", 1, (void*)"A", 1);
    config->add((void*)"K", 1, (void*)"B", 1);
    config->add((void*)"M", 1, (void*)"N", 1);
    config->set((void*)"K", 1, (void*)"C", 1);
    
    ::wsi::core::data data;
    ::wsi::core::list< ::wsi::core::data> datas;
    config->find((void*)"K", 1, data);
    config->find((void*)"K", 1, datas);
    
    ::wsi::core::list< ::wsi::core::data>::iterator iter = datas.begin();
    while (iter != datas.end())
    {
        ::wsi::core::data& each = *iter;
        ::wsi::core::string str = ::wsi::core::type_cast< ::wsi::core::string>(each);        
        trace_msg(str);
        ++iter;
    }
}

WSIAPP_END