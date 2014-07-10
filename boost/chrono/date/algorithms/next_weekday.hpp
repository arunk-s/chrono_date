#ifndef BOOST_CHRONO_DATE_NEXT_WEEKDAY_HPP
#define BOOST_CHRONO_DATE_NEXT_WEEKDAY_HPP

#include <limits>
#include <boost/chrono/date/config.hpp>
#include <boost/static_assert.hpp>

namespace boost {

namespace chrono {
// Preconditions: wd <= 6
// Returns: The weekday following wd
// The result is always in the range [0, 6].
BOOST_CONSTEXPR
BOOST_FORCEINLINE
unsigned
next_weekday(unsigned wd) BOOST_NOEXCEPT
{
    return wd < 6 ? wd+1 : 0;
}

} //chrono
} //boost

#endif
//BOOST_CHRONO_DATE_NEXT_WEEKDAY_HPP