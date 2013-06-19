
# include <nnt/Foundation+NNT.h>
# include <nnt/Math/Statistic.h>

NNTAPP_BEGIN

void test_statistic()
{
    core::vector<int> d;
    d << 2 << 2 << 3 << 2 << 2;
    double dev = sqrt(stat::deviation<double, core::vector<int>::const_iterator>::o(d.begin(), d.end()));
    trace_fmt("dev %f", dev);
}

NNTAPP_END

int main(int argc, const char * argv[])
{
    ::nntapp::test_statistic();
    return 0;
}

