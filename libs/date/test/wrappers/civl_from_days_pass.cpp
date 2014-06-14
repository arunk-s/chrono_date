#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/date/algorithms/civil_from_days.hpp>

#include <boost/detail/lightweight_test.hpp>
#include <tuple>
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
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

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
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

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
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

    {
        days_date dt_1(jan/day(1)/year(1970));
        days_date dt_2(mar/day(01)/2014); 
        days_date dt_3(mar/day(23)/1998);
        days_date dt_4(jan/day(1)/year(0));

        BOOST_TEST(year_(dt_2.days_since_epoch().count()-dt_1.days_since_epoch().count())==2014);
        BOOST_TEST(year_(dt_3.days_since_epoch().count()-dt_1.days_since_epoch().count())==1998);
    }

    /** 
    * Checking doy_ function
    * Check for already built dates by days_date
    * All dates has to be subtracted from 1970-01-01 for shifting of the epoch value.
    * The day-of-year, starts with the year beginning on Mar. 1.
    * boost::chrono's epoch count starts from -32767/1/1
    **/
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

    {
        days_date dt_1(jan/day(1)/year(1970));
        days_date dt_2(mar/day(01)/2014);
        days_date dt_3(mar/day(31)/2014); 
        days_date dt_4(apr/day(30)/2014); 
        BOOST_TEST(doy_(dt_2.days_since_epoch().count()-dt_1.days_since_epoch().count())==0); //Day numbers start from 0.
        BOOST_TEST(doy_(dt_3.days_since_epoch().count()-dt_1.days_since_epoch().count())==30); 
        BOOST_TEST(doy_(dt_4.days_since_epoch().count()-dt_1.days_since_epoch().count())==60); 
    }

    /** 
    * Checking day_ function
    * Check for already built dates by days_date
    * Now the Days number starts from 1
    **/
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

    {
        days_date dt_1(jan/day(1)/year(1970));
        days_date dt_2(mar/day(01)/2014);
        days_date dt_3(sep/day(30)/2014);
        days_date dt_4(jan/day(31)/2014); 
        BOOST_TEST(day_(dt_2.days_since_epoch().count())==01); 
        BOOST_TEST(day_(dt_3.days_since_epoch().count())==30); 
        BOOST_TEST(day_(dt_4.days_since_epoch().count())==31); 

    }    
    /** 
    * Checking month_ function
    * Check for already built dates by days_date
    **/
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

    {
        days_date dt_1(jan/day(1)/year(1970));
        days_date dt_2(mar/day(01)/2014);
        days_date dt_3(sep/day(30)/2014);
        days_date dt_4(jan/day(31)/2014); 
        BOOST_TEST(month_(dt_1.days_since_epoch().count())==1); 
        BOOST_TEST(month_(dt_2.days_since_epoch().count())==3); 
        BOOST_TEST(month_(dt_3.days_since_epoch().count())==9); 
        BOOST_TEST(month_(dt_4.days_since_epoch().count())==1); 
    } 

    /** 
    * Finally checking civil_from_days function
    * All dates has to be subtracted from 1970-01-01 for shifting of the epoch value.
    * civil_from_days gives date from 1970/01/01 i.e civil_from_days(0) == 1970/01/01

    **/
    std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 
    {
        days_date dt_1(jan/day(1)/year(1970));
        days_date dt_2(mar/day(01)/2014);
        days_date dt_3(sep/day(30)/2014);
        days_date dt_4(jan/day(31)/2014); 
        days_date dt_5(jan/day(1)/year(1969));

        auto d=civil_from_days(dt_2.days_since_epoch().count()-dt_1.days_since_epoch().count());
        auto d_1=civil_from_days(dt_3.days_since_epoch().count()-dt_1.days_since_epoch().count());
        auto d_2=civil_from_days(dt_4.days_since_epoch().count()-dt_1.days_since_epoch().count());
        auto d_3= civil_from_days(dt_5.days_since_epoch().count()-dt_1.days_since_epoch().count());

        //For years ahead of 1970
        BOOST_TEST(std::get<0>(d)==2014 && std::get<1>(d)==3 && std::get<2>(d)==1);
        BOOST_TEST(std::get<0>(d_1)==2014 && std::get<1>(d_1)==9 && std::get<2>(d_1)==30);
        BOOST_TEST(std::get<0>(d_2)==2014 && std::get<1>(d_2)==1 && std::get<2>(d_2)==31);
       
        //For years less than 1970
        BOOST_TEST(std::get<0>(d_3)==1969 && std::get<1>(d_3)==1 && std::get<2>(d_3)==1);
 
        //Day 0 corresponds to year 1970-01-01
        auto d_4 = civil_from_days(0);
        BOOST_TEST(std::get<0>(d_4)==1970 && std::get<1>(d_4)==1 && std::get<2>(d_4)==1);

    }
    return boost::report_errors();
}
