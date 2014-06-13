#ifndef BOOST_CHRONO_DATE_DAYS_FROM_CIVIL_HPP
#define BOOST_CHRONO_DATE_DAYS_FROM_CIVIL_HPP
#include <limits>
#include <boost/chrono/date/config.hpp>
#include <boost/static_assert.hpp>

#if ! defined BOOST_NO_CXX14_RELAXED_CONSTEXPR
#if defined __clang__
#if ! __has_feature(cxx_relaxed_constexpr)
#define BOOST_NO_CXX14_RELAXED_CONSTEXPR
#endif
#else
#define BOOST_NO_CXX14_RELAXED_CONSTEXPR
#endif
#endif

namespace boost {

	namespace chrono {

	  /**
	    * Converts a ymd_date to serial_day number starting from 1970/01/01
	    * Gives negative days for prior to 1970/01/01
	    * y-m-d represents a date in the civil (Gregorian) calendar
	    * m is in [1, 12]
	    * d is in [1, last_day_of_month(y, m)]
	    * y is "approximately" in
	     [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
	    * Exact range of validity is:
	    [civil_from_days(numeric_limits<Int>::min()),
	    civil_from_days(numeric_limits<Int>::max()-719468)]
	   **/

#if ! defined BOOST_NO_CXX14_RELAXED_CONSTEXPR

template <class Int>
constexpr
Int
days_from_civil(int y, int m, int d) noexcept
{
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
             "This algorithm has not been ported to a 16 bit unsigned integer");
    static_assert(std::numeric_limits<Int>::digits >= 20,
             "This algorithm has not been ported to a 16 bit signed integer");
    y -= m <= 2;
    const Int era = (y >= 0 ? y : y-399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
    const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;  // [0, 365]
    const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
    return era * 146097 + static_cast<Int>(doe) - 719468;
}

template <class Int>
constexpr
Int
days_from_civil2(int y, unsigned m, unsigned d) noexcept
{
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
             "This algorithm has not been ported to a 16 bit unsigned integer");
    static_assert(std::numeric_limits<Int>::digits >= 20,
             "This algorithm has not been ported to a 16 bit signed integer");
    y -= m <= 2;
    const Int era = (y >= 0 ? y : y-399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
    const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;  // [0, 365]
    const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
    return era * 146097 + static_cast<Int>(doe) - 719468;
}

#else
	  /**
	    * Helper functions are made because temporary variables cannot be stored in a constexpr functions.
	    * A proposal is made for relaxation of constraints on constexpr functions in c++14 .
	        See at http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3597.html
	  **/

	  /**
		* Helper function to set the year start from March 01 and end of last day of February.
		* Transform the year to an internal one for Months January and February.
	  **/

	  template<class Int>
	  BOOST_CONSTEXPR
	  BOOST_FORCEINLINE
	  Int
	  helper_function(Int y,unsigned m) BOOST_NOEXCEPT {
	    return y-=m <= 2 ;
	  }

	  /**
	    * Gives era(A 400 years time period)
	  */

	  template<class Int>
	  BOOST_CONSTEXPR
	  BOOST_FORCEINLINE
	  Int
	  era_(Int y,unsigned m) BOOST_NOEXCEPT {
	    return (helper_function(y,m) > 0 ? helper_function(y,m) : helper_function(y,m)-399)/400 ;
	  }


	  /*
	     Gives Year of Era which lies in Range [0,399]
	   */
	  template<class Int>
	  BOOST_CONSTEXPR
	  BOOST_FORCEINLINE
	  unsigned
	  yoe_(Int y,unsigned m) BOOST_NOEXCEPT {
	    return static_cast<unsigned>(helper_function(y,m) - era_(y,m) * 400 ); // Range between [0,399]
	  }

	  /*
	    Gives Days of year calculate from months and days and in Range [0,365]
	   */

	  BOOST_CONSTEXPR
	  BOOST_FORCEINLINE
	  unsigned
	  doy_(unsigned m,unsigned d) BOOST_NOEXCEPT {
	    return  (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1 ; //Range between [0, 365]
	  }

	  /**
	    * Gives The days of era. It is simply 365 days for every year,
	    	plus another day for every 4 years, minus a day for every hundred years, plus the day-of-year.
	   **/

	  template<class Int>
	  BOOST_CONSTEXPR
	  BOOST_FORCEINLINE
	  unsigned
	  doe_(Int y , unsigned m, unsigned d) BOOST_NOEXCEPT {
	    return  yoe_(y,m)*365 + yoe_(y,m)/4 - yoe_(y,m)/100 + doy_(m,d) ; //Range between [0, 146096]
	  }

	  /**
		* Finally construct the serial date from era and the days of era.
		* It gives the number of days, before, or after, 0000-03-01
		* Subtraction of 719468 is to align the algoritm with implementation of std::chrono::system_clock.
		* Makes serial date 0 equivalent to 1970/01/01 instead of 0000-03-01.
	  **/

	  template<class Int>
	  BOOST_CONSTEXPR
	  BOOST_FORCEINLINE
	  Int
	  days_from_civil(Int y,unsigned m,unsigned d) BOOST_NOEXCEPT {
	    BOOST_STATIC_ASSERT_MSG(std::numeric_limits<unsigned>::digits >= 18,
				    "This algorithm has not been ported to a 16 bit unsigned integer");
	    BOOST_STATIC_ASSERT_MSG(std::numeric_limits<Int>::digits >= 20,
				  "This algorithm has not been ported to a 16 bit signed integer");
	    return era_(y,m) * 146097 + static_cast<Int>(doe_(y,m,d)) - 719468;

	  }

#endif


constexpr
days_rep
days_from_civil(year y, month m, day d) noexcept
{
  return days_from_civil<days_rep>(y.value(),m.value(),d.value());
}
	}   //chrono
}       //boost


#endif
//BOOST_CHRONO_DATE_DAYS_FROM_CIVIL_HPP
