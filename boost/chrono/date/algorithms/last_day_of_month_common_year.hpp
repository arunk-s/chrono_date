#ifndef BOOST_CHRONO_DATE_LAST_DAY_MONTH_COMMON_HPP
#define BOOST_CHRONO_DATE_LAST_DAY_MONTH_COMMON_HPP

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
#if ! defined BOOST_NO_CXX14_RELAXED_CONSTEXPR
// Preconditions: m is in [1, 12]
// Returns: The number of days in the month m of common year
// The result is always in the range [28, 31].

BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
last_day_of_month_common_year(unsigned m) BOOST_NOEXCEPT
{
    BOOST_CONSTEXPR unsigned char a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return a[m-1];
}

#else
BOOST_CONSTEXPR unsigned char a[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
last_day_of_month_common_year(unsigned m) BOOST_NOEXCEPT
{
    return a[m-1];
}

#endif
} //chrono
} //boost
#endif
//BOOST_CHRONO_DATE_LAST_DAY_MONTH_COMMON_HPP