#ifndef BOOST_CHRONO_DATE_PREV_WEEKDAY_HPP
#define BOOST_CHRONO_DATE_PREV_WEEKDAY_HPP

#include <limits>
#include <boost/chrono/date/config.hpp>
#include <boost/static_assert.hpp>

namespace boost {

// Preconditions: wd <= 6
// Returns: The weekday prior to wd
// The result is always in the range [0, 6].
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
prev_weekday(unsigned wd) BOOST_NOEXCEPT
{
    return wd > 0 ? wd-1 : 6;
}

} //chrono
} //boost

#endif
//BOOST_CHRONO_DATE_PREV_WEEKDAY_HPP