#ifndef BOOST_CHRONO_DATE_CIVIL_FROM_DAYS_HPP
#define BOOST_CHRONO_DATE_CIVIL_FROM_DAYS_HPP

#include <limits>
#include <boost/chrono/date/config.hpp>
#include <boost/static_assert.hpp>
#include "boost/tuple/tuple.hpp"

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
*CIVIL_FROM_DAYS returns the year/month/day triple in civil calendar from a serial date(number of days).
*Preconditions: z is number of days since 1970-01-01 and is in the range:
	[numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
**/

#if ! defined BOOST_NO_CXX14_RELAXED_CONSTEXPR

template <class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
boost::tuple<Int, unsigned, unsigned>
civil_from_days(Int z) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT_MSG(std::numeric_limits<unsigned>::digits >= 18,
             "This algorithm has not been ported to a 16 bit unsigned integer");
    BOOST_STATIC_ASSERT_MSG(std::numeric_limits<Int>::digits >= 20,
             "This algorithm has not been ported to a 16 bit signed integer");
    z += 719468;
    const Int era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
    const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
    const Int y = static_cast<Int>(yoe) + era * 400;
    const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
    const unsigned mp = (5*doy + 2)/153;                                   // [0, 11]
    const unsigned d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
    const unsigned m = mp + (mp < 10 ? 3 : -9);                            // [1, 12]
    return boost::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);

//    return std::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
}



#else

/**
* Small functions are made to use in place of temporary variables as they cannot be stored in a constexpr functions.
* A proposal is made for relaxation of constraints on constexpr functions in c++14 .
See at http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3597.html
* For full explanation of the algorithm see http://home.roadrunner.com/~hinnant/date_algorithms.html#civil_from_days
**/

/**
* Helper function for the adjustment of Z to shift the epoch from 1970-01-01 to 0000-03-01.
**/

template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
Int
helper_function(Int z){
	return z += 719468 ;
}
/**
* Helper function to get the era from the number of days.
* The first step in the computation is to shift the epoch from 1970-01-01 to 0000-03-01.
**/
template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
Int
era_(Int z) BOOST_NOEXCEPT {
	//z += 719468;
	//return z ;
	return ((helper_function(z) >= 0 ? helper_function(z) : helper_function(z) - 146096) / 146097);
}

/**
* Helper function to get the day-of-era (doe) from the number of days.
* This always results in a doe in the range [0, 146096].
**/

//Make DOE with z
template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
doe_(Int z) BOOST_NOEXCEPT {

	return static_cast<unsigned>(helper_function(z) - era_(z) * 146097);
}

/**
* Helper function to get the year-of-era (yoe) from the number of days.
* From the day-of-era (doe), the year-of-era (yoe, range [0, 399]) can be computed.
**/

template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
yoe_(Int z) BOOST_NOEXCEPT {
	return (doe_(z) - doe_(z)/1460 + doe_(z)/36524 - doe_(z)/146096) / 365;
}

/**
* Year making function from the number of days.
* Given year-of-era, and era, one can compute the year number. 
**/

template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
Int
year_(Int z) BOOST_NOEXCEPT {
	return static_cast<Int>(yoe_(z)) + era_(z) * 400;
}

/**
* Helper function to get the day-of-year (doy) from the number of days.
* The day-of-year, again with the year beginning on Mar. 1, can be computed from the day-of-era and year-of-era
**/
template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
doy_(Int z) BOOST_NOEXCEPT {
	return doe_(z) - (365*yoe_(z) + yoe_(z)/4 - yoe_(z)/100);
}

/**
* Helper function to get the month number from the day-of-year (doy) given the number of days.
**/
template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
mp_(Int z) BOOST_NOEXCEPT {
	return (5*doy_(z) + 2)/153;
}

/**
* Function to calculate day-of-month from day-of-year and month-of-year.  
* One is added to the result since the day count is 1-based instead of 0-based. 
**/
template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
day_(Int z) BOOST_NOEXCEPT {
	return doy_(z) - (153*mp_(z)+2)/5 + 1;
}

/**
* Function to transfer the month number from the [0, 11] / [Mar, Feb] system to the civil system: [1, 12].
**/
template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
month_(Int z) BOOST_NOEXCEPT {
	return mp_(z) + (mp_(z) < 10 ? 3 : -9);
}

/**
* Resultant CIVIL_FROM_DAYS function using all the above functions and return the triple year/month/day in std::tuple.
* The triple can be returned in any form desired by the user.
**/
template<class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
boost::tuple<Int,unsigned,unsigned>
civil_from_days(Int z) BOOST_NOEXCEPT {
	BOOST_STATIC_ASSERT_MSG(std::numeric_limits<unsigned>::digits >= 18,
             "This algorithm has not been ported to a 16 bit unsigned integer");
    BOOST_STATIC_ASSERT_MSG(std::numeric_limits<Int>::digits >= 20,
             "This algorithm has not been ported to a 16 bit signed integer");
    return boost::tuple<Int, unsigned, unsigned>(year_(z) + (month_(z) <= 2), month_(z), day_(z));
//	return std::tuple<Int, unsigned, unsigned>(year_(z) + (month_(z) <= 2), month_(z), day_(z));
}

#endif
} //chrono
} //boost
#endif
//BOOST_CHRONO_DATE_CIVIL_FROM_DAYS_HPP
