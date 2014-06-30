#ifndef BOOST_CHRONO_DATE_LAST_DAY_MONTH_HPP
#define BOOST_CHRONO_DATE_LAST_DAY_MONTH_HPP

#include <limits>
#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/static_assert.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month_common_year.hpp>

namespace boost {

namespace chrono {

// Preconditions: m is in [1, 12]
// Returns: The number of days in the month m of year y
// The result is always in the range [28, 31].
template <class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
last_day_of_month(Int y, unsigned m) BOOST_NOEXCEPT
{
    return m != 2 || !is_leap(y) ? last_day_of_month_common_year(m) : 29u;
}

} //chrono
} //boost
#endif
//BOOST_CHRONO_DATE_LAST_DAY_MONTH_HPP