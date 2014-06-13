#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/date/algorithm/civil_from_days.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
    using std::cout ;
    using std::endl ;
    using namespace boost ;
    using namespace boost::chrono ;
    /**
    *Gives smth like this : dates/days/days_date_pass.cpp:31 
    **/
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

    /** 
    * Checking era function
    * For the algorithm the epoch is 1970-01-01 but for boost::chrono epoch is 0000-01-01
    * era is 400 year period
    **/
    {
        days_date dt_1(jan/day(01)/1970); //A starting Date
        days_date dt_2(jan/day(01)/2014); //A date in the same era of the above date
        days_date dt_3(jan/day(01)/2371); //A date ahead 400 years of the starting date      
//        days_date dt_4(jan/day(1)/year(1));
        BOOST_TEST(era_(dt_1.days_since_epoch().count())==era_(dt_2.days_since_epoch().count()));
        BOOST_TEST(era_(dt_1.days_since_epoch().count())!=era_(dt_3.days_since_epoch().count()));

    }
    /** 
    * Checking doe_ function
    * Passing continous dates of the same era 
    * Check for the ranges of the days-of-era
    **/

    {
        days_date dt_4(jan/day(1)/year(1));
        days_date dt_2(jan/day(01)/2014); //A date in the same era of the above date
        days_date dt_3(jan/day(02)/2014); //A date ahead 400 years of the starting date      
 //       cout<<doe_(dt_4.days_since_epoch().count())<<endl;
        BOOST_TEST(doe_(dt_3.days_since_epoch().count())==1+doe_(dt_2.days_since_epoch().count()));
        BOOST_TEST(doe_(dt_3.days_since_epoch().count()) <= 146096 && doe_(dt_3.days_since_epoch().count())  > 0); //doe in range [0,146096]
    }
    /** 
    * Checking yoe_ function
    * Check for the ranges of the years-of-era for both positive as well as negative era
    **/
    {
        days_date dt_1(jan/day(1)/year(1));
        days_date dt_2(jan/day(1)/year(-1));
        int x = yoe_(dt_1.days_since_epoch().count());
        int y = yoe_(dt_2.days_since_epoch().count());
        BOOST_TEST(x < 400 && x >= 0);
        BOOST_TEST(y < 400 && y >= 0);
   
    }

    /** 
    * Checking year_ function
    * Check for already built dates by days_date
    * All dates has to be subtracted from 1970-01-01 for shifting of the epoch value.
    **/
    {
        days_date dt_1(jan/day(1)/year(1970));
        days_date dt_2(mar/day(01)/2014); 
        days_date dt_3(mar/day(23)/1998);
        days_date dt_4(jan/day(1)/year(0));

        BOOST_TEST(year_(dt_2.days_since_epoch().count()-dt_1.days_since_epoch().count())==2014);
        BOOST_TEST(year_(dt_3.days_since_epoch().count()-dt_1.days_since_epoch().count())==1998);
//        cout<<year_(dt_2.days_since_epoch().count()-dt_4.days_since_epoch().count())<<endl;
    }

    /** 
    * Checking doy_ function
    * Check for already built dates by days_date
    * All dates has to be subtracted from 1970-01-01 for shifting of the epoch value.
    * The day-of-year, starts with the year beginning on Mar. 1.
    **/
    {
        days_date dt_1(jan/day(1)/year(1970));
        days_date dt_2(mar/day(01)/2014);
        days_date dt_3(mar/day(31)/2014); 
        BOOST_TEST(doy_(dt_2.days_since_epoch().count()-dt_1.days_since_epoch().count())==0); //Day numbers start from 0.
        BOOST_TEST(doy_(dt_3.days_since_epoch().count()-dt_1.days_since_epoch().count())==30); 
    }

    
    return boost::report_errors();
}
