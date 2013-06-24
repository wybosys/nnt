
# include <nnt/Foundation+NNT.h>
# include <nnt/Parser/JsonObjParser.h>

NNTAPP_BEGIN

core::string objstr = \
"{ \
\"CA\" \
: { \
\"name\" : \"test\", \
\"value\" : 123.421, \
} \
}";

class CA
: public lang::Object
{
public:
    
    CA()
    : value(0)
    {
        cls.name = "CA";
        cls.instance = INSTANCE;        
    }
    
    static lang::Object* INSTANCE()
    {
        return new CA;
    }
    
    core::string name;
    double value;
  
    lang::Class cls;
};

void test_json()
{    
    parser::JsonDocument jdoc;
    jdoc.parse(core::type_cast<core::data>(objstr));
    parser::JsonObj jobj(jdoc);
}

NNTAPP_END

int main(int argc, const char * argv[])
{
    if (1) ::nntapp::test_json();
    return 0;
}

