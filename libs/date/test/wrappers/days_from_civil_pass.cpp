#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/date/algorithm/days_from_civil.hpp>

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
	* Checking helper function
	* Pass year,month when month > 2 and when month < 2
	**/
	{
		ymd_date dt_1(jan/day(1)/year(2014));
		ymd_date dt_2(mar/day(1)/year(2014));

		/**
		* Year reduced to 2013 as algorithm starts new year from 1 March.
		**/

		BOOST_TEST(helper_function(static_cast<int>(dt_1.to_year()),static_cast<int>(dt_1.to_month()))==2013);
		BOOST_TEST(helper_function(static_cast<int>(dt_2.to_year()),static_cast<int>(dt_2.to_month()))==2014);
	}

	/**	
	* Checking era function
	* Pass year,month when year < 0 (negative era) and when year > 0
	**/
	{
		ymd_date dt_1(jan/day(1)/year(1));
		ymd_date dt_2(jan/day(1)/year(-1));
		BOOST_TEST(era_(static_cast<int>(dt_1.to_year()),static_cast<int>(dt_1.to_month()))==0);
		BOOST_TEST(era_(static_cast<int>(dt_2.to_year()),static_cast<int>(dt_2.to_month()))==-1);
	}

	/**	
	* Checking yoe_ function
	* Pass negative era and positive era the yoe should be in range [0,399]
	**/
	{
		ymd_date dt_1(jan/day(1)/year(1));
		ymd_date dt_2(jan/day(1)/year(-1));
		int x = yoe_(static_cast<int>(dt_1.to_year()),static_cast<int>(dt_1.to_month()));
		int y = yoe_(static_cast<int>(dt_2.to_year()),static_cast<int>(dt_2.to_month()));
		BOOST_TEST(x < 400 && x >= 0);
		BOOST_TEST(y < 400 && y >= 0);
	}

	/**	
	* Checking doy_ function
	* Gives the days of year in range [0,365]
	* Pass leap year and non_leap year 
	**/
	{
		ymd_date dt_1(feb/day(29)/year(2008));
		ymd_date dt_2(mar/day(1)/year(2010));
		//March 1 is 0th day and Feb 29 is 365th
		BOOST_TEST(doy_(static_cast<int>(dt_1.to_month()),static_cast<int>(dt_1.to_day()))==365);
		BOOST_TEST(doy_(static_cast<int>(dt_2.to_month()),static_cast<int>(dt_2.to_day()))==0);

	}

	/**	
	* Checking doe_ function
	* Gives the days of era in range [0,146096]
	* Pass leap year and non_leap year 
	**/
	{
		ymd_date dt_1(mar/day(1)/year(0)); //Result is 0 days of era.
		ymd_date dt_2(apr/day(1)/year(0)); //Result is now 31 days of era.
		ymd_date dt_3(feb/day(29)/year(400)); // One era is completed.
		BOOST_TEST(doe_(static_cast<int>(dt_1.to_year()),static_cast<unsigned>(dt_1.to_month()),
			static_cast<unsigned>(dt_1.to_day()))==0);
		BOOST_TEST(doe_(static_cast<int>(dt_2.to_year()),static_cast<unsigned>(dt_2.to_month()),
			static_cast<unsigned>(dt_2.to_day()))==31);
		BOOST_TEST(doe_(static_cast<int>(dt_3.to_year()),static_cast<unsigned>(dt_3.to_month()),
			static_cast<unsigned>(dt_3.to_day()))==146096);

	}
	std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl; 

	/**
	* Finally days_from_civil 
	* Constructing from ymd_date 32767/dec/31
	* 
	**/
	{


		/**
		* For boost::chrono epoch is 0000/01/01
		* But days_from_civil gives date from 1970/01/01
		* Creating a days_date and checking count against the days_date.days_since_epoch().count() 
		**/
		/*
		* Take date : 1970/01/01
		* Result  should be Oth day.
		*/
		BOOST_TEST(days_from_civil(1970,1,1)==0);

		days_date dt_1(jan/day(1)/year(1970));
		days_date dt_2(mar/day(10)/year(2014));
		int x = dt_2.days_since_epoch().count()-dt_1.days_since_epoch().count();
		BOOST_TEST(days_from_civil(static_cast<int>(dt_2.to_year()),static_cast<unsigned>(dt_2.to_month()),
			static_cast<unsigned>(dt_2.to_day()))==x);

		/**
		* Years before 1970 maps to negative days.
		**/
		ymd_date dt_3(jan/day(1)/year(1969));
		BOOST_TEST(days_from_civil(static_cast<int>(dt_3.to_year()),static_cast<unsigned>(dt_3.to_month()),
			static_cast<unsigned>(dt_3.to_day()))==-365);
	
		/**
		* 365 days of year 1970
		* BUT days_from_civil gives date from 0th day so 364 day on dec/31/1970.
		*/
		
		ymd_date dt_4(dec/day(31)/1970);
		BOOST_TEST(days_from_civil(static_cast<int>(dt_4.to_year()),static_cast<unsigned>(dt_4.to_month()),
			static_cast<unsigned>(dt_4.to_day()))==364);

		ymd_date dt(days(23947853));
		int y = days_date(dt).days_since_epoch().count()-dt_1.days_since_epoch().count();
		BOOST_TEST(days_from_civil(static_cast<int>(dt.to_year()),static_cast<unsigned>(dt.to_month()),
			static_cast<unsigned>(dt.to_day()))==y);
	}	

	return boost::report_errors();
}
