
# include "wsi/WSIFoundation.h"
# include "TestBoost.h"
# include "wsi/Core/Boost+WSI.h"

# include "../../../3rd/boost/mpl/vector.hpp"
# include "../../../3rd/boost/mpl/list.hpp"
# include "../../../3rd/boost/mpl/same_as.hpp"
# include "../../../3rd/boost/mpl/at.hpp"
# include "../../../3rd/boost/mpl/find.hpp"
# include "../../../3rd/boost/mpl/find_if.hpp"
# include "../../../3rd/boost/mpl/contains.hpp"
# include "../../../3rd/boost/mpl/count.hpp"

WSIAPP_BEGIN

struct CA
{
    
};

struct CB
{
    
};

typedef ::boost::mpl::vector<float,double,long double, int, CA, CA> test_types;
typedef ::boost::mpl::find<test_types, int>::type test_find;
typedef ::boost::mpl::push_back<test_types, int> test_types2;

//typedef ::boost::mpl::vector<float,double,long double> floats;
//typedef ::boost::mpl::push_back<floats,int>::type types;

//BOOST_MPL_ASSERT(( ::boost::is_same< ::boost::mpl::at_c<types,3>::type, int > ));

TestBoost::TestBoost()
{
    int xx = test_types::size();
    bool suc = ::boost::is_same< ::boost::mpl::deref<test_find>::type, int>();
    suc = ::boost::mpl::contains<test_types, double>();
    suc = ::boost::mpl::contains<test_types, CA>();
    suc = ::boost::is_same< ::boost::mpl::at_c<test_types, 3>::type, int>();
    int cnt = ::boost::mpl::count<test_types, CA>::type::value;
    
    xx = 0;
    cnt = 0;
    
    trace_msg("test boost");
}

TestBoost::~TestBoost()
{
    
}

void TestBoost::main()
{
    
}

WSIAPP_END