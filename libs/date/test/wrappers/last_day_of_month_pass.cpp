#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month_common_year.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month_leap_year.hpp>

#include <boost/detail/lightweight_test.hpp>
int main()
{
    using std::cout ;
    using std::endl ;
    using namespace boost ;
    using namespace boost::chrono ;
 
    {
        std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

        days_date dt_1(jan/day(01)/1970); //A starting Date
        days_date dt_2(feb/day(01)/1970);
        days_date dt_3(mar/day(01)/1970);
        days_date dt_4(apr/day(01)/1970);
        days_date dt_5(may/day(01)/1970);
        days_date dt_6(jun/day(01)/1970);
        days_date dt_7(jul/day(01)/1970);
        days_date dt_8(aug/day(01)/1970);
        days_date dt_9(sep/day(01)/1970);
        days_date dt_10(oct/day(01)/1970);
        days_date dt_11(nov/day(01)/1970);
        days_date dt_12(dec/day(01)/1970);

        BOOST_TEST(last_day_of_month_common_year(dt_1.to_month()) == 31);
        BOOST_TEST(last_day_of_month_common_year(dt_2.to_month()) == 28);
        BOOST_TEST(last_day_of_month_common_year(dt_3.to_month()) == 31);
        BOOST_TEST(last_day_of_month_common_year(dt_4.to_month()) == 30);
        BOOST_TEST(last_day_of_month_common_year(dt_5.to_month()) == 31);
        BOOST_TEST(last_day_of_month_common_year(dt_6.to_month()) == 30);  
        BOOST_TEST(last_day_of_month_common_year(dt_7.to_month()) == 31);
        BOOST_TEST(last_day_of_month_common_year(dt_8.to_month()) == 31);
        BOOST_TEST(last_day_of_month_common_year(dt_9.to_month()) == 30);
        BOOST_TEST(last_day_of_month_common_year(dt_10.to_month()) == 31);
        BOOST_TEST(last_day_of_month_common_year(dt_11.to_month()) == 30);        
        BOOST_TEST(last_day_of_month_common_year(dt_12.to_month()) == 31);

    }
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

    {
        days_date dt_1(jan/day(01)/1970); //A starting Date
        days_date dt_2(feb/day(01)/1970);
        days_date dt_3(mar/day(01)/1970);
        days_date dt_4(apr/day(01)/1970);
        days_date dt_5(may/day(01)/1970);
        days_date dt_6(jun/day(01)/1970);
        days_date dt_7(jul/day(01)/1970);
        days_date dt_8(aug/day(01)/1970);
        days_date dt_9(sep/day(01)/1970);
        days_date dt_10(oct/day(01)/1970);
        days_date dt_11(nov/day(01)/1970);
        days_date dt_12(dec/day(01)/1970);

        BOOST_TEST(last_day_of_month(dt_1.to_year(),dt_1.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_2.to_year(),dt_2.to_month()) == 28);
        BOOST_TEST(last_day_of_month(dt_3.to_year(),dt_3.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_4.to_year(),dt_4.to_month()) == 30);
        BOOST_TEST(last_day_of_month(dt_5.to_year(),dt_5.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_6.to_year(),dt_6.to_month()) == 30);  
        BOOST_TEST(last_day_of_month(dt_7.to_year(),dt_7.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_8.to_year(),dt_8.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_9.to_year(),dt_9.to_month()) == 30);
        BOOST_TEST(last_day_of_month(dt_10.to_year(),dt_10.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_11.to_year(),dt_11.to_month()) == 30);        
        BOOST_TEST(last_day_of_month(dt_12.to_year(),dt_12.to_month()) == 31);        
    }
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 
   {
        days_date dt_1(jan/day(01)/2012); //A starting Date
        days_date dt_2(feb/day(01)/2012);
        days_date dt_3(mar/day(01)/2012);
        days_date dt_4(apr/day(01)/2012);
        days_date dt_5(may/day(01)/2012);
        days_date dt_6(jun/day(01)/2012);
        days_date dt_7(jul/day(01)/2012);
        days_date dt_8(aug/day(01)/2012);
        days_date dt_9(sep/day(01)/2012);
        days_date dt_10(oct/day(01)/2012);
        days_date dt_11(nov/day(01)/2012);
        days_date dt_12(dec/day(01)/2012);

        BOOST_TEST(last_day_of_month(dt_1.to_year(),dt_1.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_2.to_year(),dt_2.to_month()) == 29);
        BOOST_TEST(last_day_of_month(dt_3.to_year(),dt_3.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_4.to_year(),dt_4.to_month()) == 30);
        BOOST_TEST(last_day_of_month(dt_5.to_year(),dt_5.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_6.to_year(),dt_6.to_month()) == 30);  
        BOOST_TEST(last_day_of_month(dt_7.to_year(),dt_7.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_8.to_year(),dt_8.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_9.to_year(),dt_9.to_month()) == 30);
        BOOST_TEST(last_day_of_month(dt_10.to_year(),dt_10.to_month()) == 31);
        BOOST_TEST(last_day_of_month(dt_11.to_year(),dt_11.to_month()) == 30);        
        BOOST_TEST(last_day_of_month(dt_12.to_year(),dt_12.to_month()) == 31);        
    }
   {
        days_date dt_1(jan/day(01)/2012); //A starting Date
        days_date dt_2(feb/day(01)/2012);
        days_date dt_3(mar/day(01)/2012);
        days_date dt_4(apr/day(01)/2012);
        days_date dt_5(may/day(01)/2012);
        days_date dt_6(jun/day(01)/2012);
        days_date dt_7(jul/day(01)/2012);
        days_date dt_8(aug/day(01)/2012);
        days_date dt_9(sep/day(01)/2012);
        days_date dt_10(oct/day(01)/2012);
        days_date dt_11(nov/day(01)/2012);
        days_date dt_12(dec/day(01)/2012);

        BOOST_TEST(last_day_of_month_leap_year(dt_1.to_month()) == 31);
        BOOST_TEST(last_day_of_month_leap_year(dt_2.to_month()) == 29);
        BOOST_TEST(last_day_of_month_leap_year(dt_3.to_month()) == 31);
        BOOST_TEST(last_day_of_month_leap_year(dt_4.to_month()) == 30);
        BOOST_TEST(last_day_of_month_leap_year(dt_5.to_month()) == 31);
        BOOST_TEST(last_day_of_month_leap_year(dt_6.to_month()) == 30);  
        BOOST_TEST(last_day_of_month_leap_year(dt_7.to_month()) == 31);
        BOOST_TEST(last_day_of_month_leap_year(dt_8.to_month()) == 31);
        BOOST_TEST(last_day_of_month_leap_year(dt_9.to_month()) == 30);
        BOOST_TEST(last_day_of_month_leap_year(dt_10.to_month()) == 31);
        BOOST_TEST(last_day_of_month_leap_year(dt_11.to_month()) == 30);        
        BOOST_TEST(last_day_of_month_leap_year(dt_12.to_month()) == 31);        
    }

    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 
    return 1;
}