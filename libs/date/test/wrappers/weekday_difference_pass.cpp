#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/date/algorithms/weekday_difference.hpp>

#include <boost/detail/lightweight_test.hpp>
int main()
{
    using std::cout ;
    using std::endl ;
    using namespace boost ;
    using namespace boost::chrono ;
 
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

//    days_date dt_1(jan/day(01)/1970); 

    BOOST_CONSTEXPR unsigned a[7][7] =
    {// -    Sun Mon Tue Wed Thu Fri Sat
     /*Sun*/ {0,  6,  5,  4,  3,  2,  1},
     /*Mon*/ {1,  0,  6,  5,  4,  3,  2},
     /*Tue*/ {2,  1,  0,  6,  5,  4,  3},
     /*Wed*/ {3,  2,  1,  0,  6,  5,  4},
     /*Thu*/ {4,  3,  2,  1,  0,  6,  5},
     /*Fri*/ {5,  4,  3,  2,  1,  0,  6},
     /*Sat*/ {6,  5,  4,  3,  2,  1,  0}
    };
    for (unsigned x = 0; x < 7; ++x)
        for (unsigned y = 0; y < 7; ++y)
            BOOST_TEST(weekday_difference(x, y) == a[x][y]);

    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 
    return boost::report_errors();

}