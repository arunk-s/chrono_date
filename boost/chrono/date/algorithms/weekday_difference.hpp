#ifndef BOOST_CHRONO_DATE_WEEKDAY_DIFFERCENCE_HPP
#define BOOST_CHRONO_DATE_WEEKDAY_HPP

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
// Preconditions: x <= 6 && y <= 6
// Returns: The number of days from the weekday y to the weekday x.
// The result is always in the range [0, 6].
#if ! defined BOOST_NO_CXX14_RELAXED_CONSTEXPR
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
weekday_difference(unsigned x, unsigned y) BOOST_NOEXCEPT
{
    x -= y;
    return x <= 6 ? x : x + 7;
}

#else

BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
helper(unsigned x, unsigned y) BOOST_NOEXCEPT
{
    return x-y;
}

BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
weekday_difference(unsigned x, unsigned y) BOOST_NOEXCEPT
{
//    x -= y;
//    return x <= 6 ? x : x + 7;
	return helper(x,y) <=6 ? helper(x,y) : helper(x,y) + 7 ;
}

#endif
} //chrono
} //boost

#endif
//BOOST_CHRONO_DATE_WEEKDAY_DIFFERCENCE_HPP