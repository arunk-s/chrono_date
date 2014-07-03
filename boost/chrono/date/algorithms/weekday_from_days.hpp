#ifndef BOOST_CHRONO_DATE_WEEKDAY_FROM_DAYS_HPP
#define BOOST_CHRONO_DATE_WEEKDAY_FROM_DAYS_HPP

#include <limits>
#include <boost/chrono/date/config.hpp>
#include <boost/static_assert.hpp>


namespace boost {

namespace chrono {
// Returns day of week in civil calendar [0, 6] -> [Sun, Sat]
// Preconditions:  z is number of days since 1970-01-01 and is in the range:
//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-4].
template <class Int>
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
weekday_from_days(Int z) BOOST_NOEXCEPT
{
    return static_cast<unsigned>(z >= -4 ? (z+4) % 7 : (z+5) % 7 + 6);
}

} //chrono
} //boost

#endif
//BOOST_CHRONO_DATE_WEEKDAY_FROM_DAYS_HPP