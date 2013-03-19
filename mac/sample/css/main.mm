
# import <Foundation/Foundation.h>
# import <wsi/WSIFoundation.h>
# import <wsi/CSSParser.h>

int main (int argc, const char * argv[])
{    
    WSI_AUTORELEASEPOOL_BEGIN
    
    wsi::CSSParser css;
	wsi::core::string str = "body { background-color:#ff9900; } body { text-color: #ff9900; } h1 { img:url('img.pn g');} body { text-color:#000000 }";
    //str = "backgroud-color:#00ff00; text-color:#0000ff";
	if (css.parse(str))
	{
		trace_msg(@"success");
        
		// print all class.
		wsi::css::classes_type const& classes = css.classes();
		for (wsi::css::classes_type::const_iterator each = classes.begin();
             each != classes.end();
             ++each)
		{
            std::cout << each->first << std::endl;
			for (wsi::css::attributes_type::const_iterator attr = each->second->attributes.begin();
                 attr != each->second->attributes.end();
                 ++attr)
			{
				std::cout << attr->second->name << " = " << attr->second->value << std::endl;
			}
		}
        
        // print all attributes.
        wsi::css::attributes_type const& attrs = css.attributes();
        for (wsi::css::attributes_type::const_iterator each = attrs.begin();
             each != attrs.end();
             ++each)
        {
            std::cout << each->second->name << " = " << each->second->value << std::endl;
        }
	}
	else
	{
		trace_msg(@"failed");
	}
    
	getchar();
    WSI_AUTORELEASEPOOL_END
    return 0;
}

