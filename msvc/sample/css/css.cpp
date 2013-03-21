// css.cpp : Defines the entry point for the console application.
//

# include <nnt/Foundation+NNT.h>
# include <nnt/Parser/CSSParser.h>

NNTAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
        CSSParser css;
        core::string str = "body { background-color:#ff9900; } body { text-color:#ff9900; } h1 { img:url('img.pn g'); }";
        if (css.parse(str))
        {
            trace_msg("success");

            // print all class.
            css::classes_type const& classes = css.classes();
            for (css::classes_type::const_iterator each = classes.begin();
                each != classes.end();
                ++each)
            {
                for (css::attributes_type::const_iterator attr = each->second->attributes.begin();
                    attr != each->second->attributes.end();
                    ++attr)
                {
                    ::std::cout << attr->second->name << " = " << attr->second->value << ::std::endl;
                }
            }
        }
        else
        {
            trace_msg("failed");
        }
    }

};

NNTAPP_END

int main(int argc, char* argv[])
{
    ::nntapp::App app;
    return app.execute(argc, argv);	
}
