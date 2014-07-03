#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/date/algorithms/weekday_from_days.hpp>

#include <boost/detail/lightweight_test.hpp>
int main()
{
    using std::cout ;
    using std::endl ;
    using namespace boost ;
    using namespace boost::chrono ;
 
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

    days_date dt_1(jan/day(01)/1970); 

    //cout<<weekday_from_days(0)<<endl;
//        cout<<weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count())<<endl;

    {
        days_date dt(oct/day(23)/2011);
        BOOST_TEST(weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count()) == 0 );
        //Subtraction is because weekday_from_days takes days from 1970-01-01.
//        BOOST_TEST( weekday(dt)==sun );
    }

    {
        days_date dt(oct/day(24)/2011);
        BOOST_TEST(weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count())== 1 );
//        BOOST_TEST( weekday(dt)==mon );
    }

    {
      days_date dt(oct/day(25)/2011);
      BOOST_TEST(weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count()) == 2);
//    BOOST_TEST( weekday(dt)==tue );
    }

    {
      days_date dt(oct/day(26)/2011);
      BOOST_TEST(weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count()) == 3 );
//    BOOST_TEST( weekday(dt)==wed );
    }

    {
      days_date dt(oct/day(27)/2011);
      BOOST_TEST(weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count()) == 4 );      
//    BOOST_TEST( weekday(dt)==thu );
    }

    {
      days_date dt(oct/day(28)/2011);
      BOOST_TEST(weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count()) == 5 );
//    BOOST_TEST( weekday(dt)==fri );
    }

    {
      days_date dt(oct/day(29)/2011);
      BOOST_TEST(weekday_from_days(dt.days_since_epoch().count()-dt_1.days_since_epoch().count()) == 6 );
//    BOOST_TEST( weekday(dt)==sat );
    }
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 
    return boost::report_errors();

}