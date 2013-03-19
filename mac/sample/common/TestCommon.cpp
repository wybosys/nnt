
# include "wsi/WSIFoundation.h"
# include "TestCommon.h"
# include "wsi/Core/Directory+WSI.h"
# include "wsi/Core/App.h"

WSIAPP_BEGIN

void TestCommon::main()
{
    ::wsi::core::string path = "\\abc\\\\cde\\";
    ::wsi::core::string path2 = "c:\\abc\\cde\\efg";
    ::wsi::core::string tmp = ::wsi::core::dot(path);
    tmp = ::wsi::core::dot(path2);
    tmp = ::wsi::core::dotdot(path);
    tmp = ::wsi::core::dotdot(path2);
    
    ::wsi::core::string dir = wsi::Application::getInstance()->working_directory();
    dir += "test";
    ::wsi::core::mkdir(dir);
    dir += "xx//yy";
    ::wsi::core::mkdir(dir);
    ::wsi::core::mkdirs(dir);
}

WSIAPP_END