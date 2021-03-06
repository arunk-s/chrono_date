//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_TUPLES_HPP
#define BOOST_CHRONO_DATE_TUPLES_HPP

#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/weekday.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/day_of_year.hpp>
#include <boost/chrono/date/week.hpp>
#include <boost/chrono/date/nth_tag.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {
    namespace chrono_detail
    {
#ifndef  BOOST_NO_CXX11_CONSTEXPR
      BOOST_STATIC_CONSTEXPR day_rep leap_days_in_year_before_[13] =
          { -1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

      BOOST_FORCEINLINE static BOOST_CONSTEXPR
      day_rep leap_days_in_year_before(int d) BOOST_NOEXCEPT { return leap_days_in_year_before_[d]; }

      BOOST_STATIC_CONSTEXPR day_rep normal_days_in_year_before_[13] =
          { -1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364 };
      BOOST_FORCEINLINE static BOOST_CONSTEXPR
      day_rep normal_days_in_year_before(int d) BOOST_NOEXCEPT { return normal_days_in_year_before_[d]; }
#else
      extern  day_rep leap_days_in_year_before_[];
      BOOST_FORCEINLINE
      day_rep leap_days_in_year_before(int d) BOOST_NOEXCEPT { return leap_days_in_year_before_[d]; }
      extern  day_rep normal_days_in_year_before_[];
      BOOST_FORCEINLINE
      day_rep normal_days_in_year_before(int d) BOOST_NOEXCEPT { return normal_days_in_year_before_[d]; }

#endif

    }

    namespace unchecked
    {
      /**
       * Class year_month is a tuple-like class of year-month.
       *
       * It is CopyConstructible, CopyAssignable, and Destructible.
       *
       * In addition to construction and getters it provides the number of days in this year/month.
       */
      class year_month
      {
        year y_;
        month m_;
      public:
        BOOST_FORCEINLINE BOOST_CONSTEXPR year_month(year y, month m) BOOST_NOEXCEPT
        : y_(y),
        m_(m)
        {
        }

        /**
         * @Return the year stored component.
         */
        //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
        BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR  operator chrono::year() const BOOST_NOEXCEPT
        {
          return y_;
        }

        /**
         * @Return the month stored component.
         */
        //BOOST_CONSTEXPR chrono::month month() const BOOST_NOEXCEPT
        BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR  operator month() const BOOST_NOEXCEPT
        {
          return m_;
        }

        BOOST_FORCEINLINE BOOST_CONSTEXPR  bool is_leap_year() const BOOST_NOEXCEPT
        {
          return y_.is_leap();
        }

        // @todo make it possible to have BOOST_CONSTEXPR days_in
        /**
         * @Return the number of days of this month in this year.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR chrono::days days_in() const BOOST_NOEXCEPT
        {
          return y_.days_in_month(m_);
        }
        /**
         * @Returns the number of days since the epoch until the first day of this year/month.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR days days_since_start_of_year() const BOOST_NOEXCEPT
        {
          return (y_.is_leap())
              ? days(chrono_detail::leap_days_in_year_before(m_)+1)
              : days(chrono_detail::normal_days_in_year_before(m_)+1)
              ;        }
        /**
         * @Returns the number of days since the epoch until the first day of this year/month.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR days days_since_epoch() const BOOST_NOEXCEPT
        {
          return y_.days_since_epoch() + days_since_start_of_year();
        }
        year_month& operator+=(months m) BOOST_NOEXCEPT;
        BOOST_FORCEINLINE year_month& operator++() BOOST_NOEXCEPT
        {
          return *this += months(1);
        }
        BOOST_FORCEINLINE year_month operator++(int) BOOST_NOEXCEPT
        {
          year_month tmp(*this);
          ++(*this);
          return tmp;
        }
        BOOST_FORCEINLINE year_month& operator-=(months m) BOOST_NOEXCEPT
        {
          return *this += -m;
        }

        BOOST_FORCEINLINE year_month& operator+=(years y) BOOST_NOEXCEPT
        {
          y_ = chrono::year(y_ + y.count());
          return *this;
        }
        BOOST_FORCEINLINE year_month& operator-=(years y) BOOST_NOEXCEPT
        {
          return *this += years(-y.count());
        }

        BOOST_FORCEINLINE year_month& operator--() BOOST_NOEXCEPT
        {
          return *this -= months(1);
        }
        BOOST_FORCEINLINE year_month operator--(int) BOOST_NOEXCEPT
        {
          year_month tmp(*this);
          --(*this);
          return tmp;
        }
        friend BOOST_FORCEINLINE months operator-(year_month x, year_month y) BOOST_NOEXCEPT;


      };

      BOOST_FORCEINLINE year_month operator+(year_month ym, months m) BOOST_NOEXCEPT
      {
        ym += m;
        return ym;
      }
      BOOST_FORCEINLINE year_month operator+(months m, year_month ym) BOOST_NOEXCEPT
      {
        ym += m;
        return ym;
      }
      BOOST_FORCEINLINE year_month operator-(year_month ym, months m) BOOST_NOEXCEPT
      {
        ym -= m;
        return ym;
      }
      BOOST_FORCEINLINE months operator-(year_month x, year_month y) BOOST_NOEXCEPT
      {
        int32_t y1 = x.y_;
        int32_t m1 = x.m_;
        int32_t y2 = y.y_;
        int32_t m2 = y.m_;
        return months(y1*12 + m1 - (y2*12 + m2));
      }

      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator+(year_month ym, years y) BOOST_NOEXCEPT
      {
        return year_month(year(ym+y), month(ym));
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator+(years y, year_month ym) BOOST_NOEXCEPT
      {
        return year_month(year(ym+y), month(ym));
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator-(year_month ym, years y) BOOST_NOEXCEPT
      {
        return year_month(year(ym-y), month(ym));
      }

      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(year y, month m) BOOST_NOEXCEPT
      {
        return year_month(y, m);
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(month m, year y) BOOST_NOEXCEPT
      {
        return year_month(y, m);
      }
  //    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(chrono::year y, int m) BOOST_NOEXCEPT
  //    {
  //      return year_month(y, chrono::month(m));
  //    }
  //    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(int m, chrono::year y) BOOST_NOEXCEPT
  //    {
  //      return year_month(y, chrono::month(m));
  //    }
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(int y, chrono::month m) BOOST_NOEXCEPT
      {
        return year_month(chrono::year(y), m);
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(chrono::month m, int y) BOOST_NOEXCEPT
      {
        return year_month(chrono::year(y), m);
      }
    }

    /**
     * Class year_month is a tuple-like class of year-month.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     *
     * In addition to construction and getters it provides the number of days in this year/month.
     */
    class year_month
    {
      year y_;
      month m_;
    public:
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month(year y, month m) BOOST_NOEXCEPT
      : y_(y),
      m_(m)
      {
      }

      /**
       * @Return the year stored component.
       */
      //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR  operator chrono::year() const BOOST_NOEXCEPT
      {
        return y_;
      }

      /**
       * @Return the month stored component.
       */
      //BOOST_CONSTEXPR chrono::month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR  operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }

      BOOST_FORCEINLINE BOOST_CONSTEXPR  bool is_leap_year() const BOOST_NOEXCEPT
      {
        return y_.is_leap();
      }

      // @todo make it possible to have BOOST_CONSTEXPR days_in
      /**
       * @Return the number of days of this month in this year.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR chrono::days days_in() const BOOST_NOEXCEPT
      {
        return y_.days_in_month(m_);
      }

      year_month& operator+=(months m) BOOST_NOEXCEPT;
      BOOST_FORCEINLINE year_month& operator++() BOOST_NOEXCEPT
      {
        return *this += months(1);
      }
      BOOST_FORCEINLINE year_month operator++(int) BOOST_NOEXCEPT
      {
        year_month tmp(*this);
        ++(*this);
        return tmp;
      }
      BOOST_FORCEINLINE year_month& operator-=(months m) BOOST_NOEXCEPT
      {
        return *this += -m;
      }

      BOOST_FORCEINLINE year_month& operator+=(years y) BOOST_NOEXCEPT
      {
        y_ = chrono::year(y_ + y.count());
        return *this;
      }
      BOOST_FORCEINLINE year_month& operator-=(years y) BOOST_NOEXCEPT
      {
        return *this += years(-y.count());
      }

      BOOST_FORCEINLINE year_month& operator--() BOOST_NOEXCEPT
      {
        return *this -= months(1);
      }
      BOOST_FORCEINLINE year_month operator--(int) BOOST_NOEXCEPT
      {
        year_month tmp(*this);
        --(*this);
        return tmp;
      }
      friend BOOST_FORCEINLINE months operator-(year_month x, year_month y) BOOST_NOEXCEPT;


    };

    BOOST_FORCEINLINE year_month operator+(year_month ym, months m) BOOST_NOEXCEPT
    {
      ym += m;
      return ym;
    }
    BOOST_FORCEINLINE year_month operator+(months m, year_month ym) BOOST_NOEXCEPT
    {
      ym += m;
      return ym;
    }
    BOOST_FORCEINLINE year_month operator-(year_month ym, months m) BOOST_NOEXCEPT
    {
      ym -= m;
      return ym;
    }
    BOOST_FORCEINLINE months operator-(year_month x, year_month y) BOOST_NOEXCEPT
    {
      int32_t y1 = x.y_;
      int32_t m1 = x.m_;
      int32_t y2 = y.y_;
      int32_t m2 = y.m_;
      return months(y1*12 + m1 - (y2*12 + m2));
    }

    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator+(year_month ym, years y) BOOST_NOEXCEPT
    {
      return year_month(year(ym+y), month(ym));
    }
    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator+(years y, year_month ym) BOOST_NOEXCEPT
    {
      return year_month(year(ym+y), month(ym));
    }
    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator-(year_month ym, years y) BOOST_NOEXCEPT
    {
      return year_month(year(ym-y), month(ym));
    }

    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(year y, month m) BOOST_NOEXCEPT
    {
      return year_month(y, m);
    }
    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(month m, year y) BOOST_NOEXCEPT
    {
      return year_month(y, m);
    }
//    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(chrono::year y, int m) BOOST_NOEXCEPT
//    {
//      return year_month(y, chrono::month(m));
//    }
//    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(int m, chrono::year y) BOOST_NOEXCEPT
//    {
//      return year_month(y, chrono::month(m));
//    }
    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(int y, chrono::month m) BOOST_NOEXCEPT
    {
      return year_month(chrono::year(y), m);
    }
    BOOST_FORCEINLINE BOOST_CONSTEXPR year_month operator/(chrono::month m, int y) BOOST_NOEXCEPT
    {
      return year_month(chrono::year(y), m);
    }


    /**
     * Class year_week is a tuple-like class of year-week.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     */
    class year_week
    {
      year y_;
      week w_;
    public:
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_week(year y, week w) BOOST_NOEXCEPT
      : y_(y),
      w_(w)
      {
      }
//      BOOST_FORCEINLINE BOOST_CONSTEXPR year_week(year y, week w, check_t) BOOST_NOEXCEPT
//      : y_(y, check),
//      w_(w, check)
//      {
//      }

      /**
       * @Return the year stored component.
       */
      //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      /**
       * @Return the week stored component.
       */
      //BOOST_CONSTEXPR chrono::week week() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::week() const BOOST_NOEXCEPT
      {
        return w_;
      }

    };

    BOOST_FORCEINLINE BOOST_CONSTEXPR year_week operator/(year y, week w) BOOST_NOEXCEPT
    {
      return year_week(y, w);
    }

    BOOST_FORCEINLINE BOOST_CONSTEXPR year_week operator/(week w, year y) BOOST_NOEXCEPT
    {
      return year_week(y, w);
    }
    namespace unchecked
    {
      /**
       * Class month_day is a tuple-like class of month-day.
       *
       * It is CopyConstructible, CopyAssignable, and Destructible.
       *
       * This class is useful while generating dates, allowing to generate dates
       * that are quasi literals (e.g. jan_01/2012).
       */
      class month_day
      {
        month m_;
        day d_;

        BOOST_FORCEINLINE static BOOST_CHRONO_DATE_CONSTEXPR
        bool is_valid_(month m, day d)
        {
            return (d<=m.days_in(true).count());
        }
      public:
        BOOST_FORCEINLINE BOOST_CONSTEXPR month_day(month m, day d) BOOST_NOEXCEPT
        : m_(m),
        d_(d)
        {
          // check validity of day relative to month.
        }

        /**
         * @Return the month stored component.
         */
        //BOOST_CONSTEXPR chrono::month month() const BOOST_NOEXCEPT
        BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator unchecked::month() const BOOST_NOEXCEPT
        {
          return m_;
        }
        /**
         * @Return the day stored component.
         */
        //BOOST_CONSTEXPR chrono::day day() const BOOST_NOEXCEPT
        BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator unchecked::day() const BOOST_NOEXCEPT
        {
          return d_;
        }
        /**
         *
         * @Returns whether the @c month()/day() is a valid proleptic Gregorian date.
         */
        // @todo BOOST_CONSTEXPR
        BOOST_FORCEINLINE BOOST_CHRONO_DATE_CONSTEXPR bool is_valid() const BOOST_NOEXCEPT
        {
          return month(m_).is_valid() && day(d_).is_valid() && is_valid_(month(m_), day(d_));
        }
      };

      BOOST_FORCEINLINE BOOST_CONSTEXPR month_day operator/(month m, day d) BOOST_NOEXCEPT
      {
        return month_day(m, d);
      }
//      BOOST_FORCEINLINE BOOST_CONSTEXPR month_day operator/(month m, chrono::day d) BOOST_NOEXCEPT
//      {
//        return month_day(m, d);
//      }
//      BOOST_FORCEINLINE BOOST_CONSTEXPR month_day operator/(chrono::month m, day d) BOOST_NOEXCEPT
//      {
//        return month_day(m, d);
//      }


      BOOST_FORCEINLINE BOOST_CONSTEXPR month_day operator/(day d, month m) BOOST_NOEXCEPT
      {
        return month_day(m, d);
      }
//      BOOST_FORCEINLINE BOOST_CONSTEXPR month_day operator/(day d, chrono::month m) BOOST_NOEXCEPT
//      {
//        return month_day(m, d);
//      }
//      BOOST_FORCEINLINE BOOST_CONSTEXPR month_day operator/(chrono::day d, month m) BOOST_NOEXCEPT
//      {
//        return month_day(m, d);
//      }

    }
    /**
     * Class month_day is a tuple-like class of month-day.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     *
     * This class is useful while generating dates, allowing to generate dates
     * that are quasi literals (e.g. jan_01/2012).
     */
    class month_day
    {
      month m_;
      day d_;

      BOOST_FORCEINLINE static BOOST_CHRONO_DATE_CONSTEXPR
      bool is_valid_(month m, day d)
      {
          return (d<=m.days_in(true).count());
      }

#ifndef  BOOST_NO_CXX11_CONSTEXPR
      BOOST_FORCEINLINE static BOOST_CHRONO_DATE_CONSTEXPR
      day check_invariants(month m, day d)
      {
          return is_valid_(m,d)
                  ? d
                  : throw bad_date("day " + to_string(d) + " is out of range for month " + to_string(m))
                ;
      }
#else
      BOOST_FORCEINLINE static
      day check_invariants(month m, day d)
      {
          if ( is_valid_(m,d) )
              return d;
          else throw bad_date("day " + to_string(d) + " is out of range for month " + to_string(m));
      }
#endif
    public:
      BOOST_FORCEINLINE BOOST_CHRONO_DATE_CONSTEXPR month_day(month m, day d)
      : m_(m),
      d_(check_invariants(m,d))
      {
      }
      BOOST_FORCEINLINE BOOST_CHRONO_DATE_CONSTEXPR month_day(month::rep m, day::rep d, check_t)
      : m_(m),
      d_(check_invariants(month(m),day(d)))
      {
      }

      BOOST_FORCEINLINE BOOST_CONSTEXPR month_day(month m, day d, no_check_t)BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
      }

      // conversions

      BOOST_FORCEINLINE BOOST_CHRONO_DATE_CONSTEXPR explicit month_day(unchecked::month_day md)
          : m_(unchecked::month(md),no_check),
          d_(check_invariants(month(unchecked::month(md)), day(unchecked::day(md))))
      {
      }

      BOOST_FORCEINLINE BOOST_CONSTEXPR operator unchecked::month_day() const
      {
        return unchecked::month_day(m_, d_);
      }

      // Observers
      /**
       * @Return the month stored component.
       */
      //BOOST_CONSTEXPR chrono::month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      /**
       * @Return the day stored component.
       */
      //BOOST_CONSTEXPR chrono::day day() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::day() const BOOST_NOEXCEPT
      {
        return d_;
      }

      /**
       *
       * @Returns whether the @c month()/day() is a valid proleptic Gregorian date.
       */
      // @todo BOOST_CONSTEXPR
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_valid() const BOOST_NOEXCEPT
      {
        //return month(m_).is_valid() && day(d_).is_valid() && is_valid_(year(y_), month(m_), day(d_));
        return true;
      }
    };

    BOOST_FORCEINLINE BOOST_CHRONO_DATE_CONSTEXPR month_day operator/(month m, day d) BOOST_NOEXCEPT
    {
      return month_day(m, d);
    }


    BOOST_FORCEINLINE BOOST_CHRONO_DATE_CONSTEXPR month_day operator/(day d, month m) BOOST_NOEXCEPT
    {
      return month_day(m, d);
    }


//    /**
//     * month_day pseudo-literals.
//     */
//    extern const month_day
//        jan_01, jan_02, jan_03, jan_04, jan_05, jan_06, jan_07,
//        jan_08, jan_09, jan_10, jan_11, jan_12, jan_13, jan_14,
//        jan_15, jan_16, jan_17, jan_18, jan_19, jan_20, jan_21,
//        jan_22, jan_23, jan_24, jan_25, jan_26, jan_27, jan_28, jan_29, jan_30, jan_31,
//        feb_01, feb_02, feb_03, feb_04, feb_05, feb_06, feb_07,
//        feb_08, feb_09, feb_10, feb_11, feb_12, feb_13, feb_14,
//        feb_15, feb_16, feb_17, feb_18, feb_19, feb_20, feb_21,
//        feb_22, feb_23, feb_24, feb_25, feb_26, feb_27, feb_28, feb_29,
//        mar_01, mar_02, mar_03, mar_04, mar_05, mar_06, mar_07,
//        mar_08, mar_09, mar_10, mar_11, mar_12, mar_13, mar_14,
//        mar_15, mar_16, mar_17, mar_18, mar_19, mar_20, mar_21,
//        mar_22, mar_23, mar_24, mar_25, mar_26, mar_27, mar_28, mar_29, mar_30, mar_31,
//        apr_01, apr_02, apr_03, apr_04, apr_05, apr_06, apr_07,
//        apr_08, apr_09, apr_10, apr_11, apr_12, apr_13, apr_14,
//        apr_15, apr_16, apr_17, apr_18, apr_19, apr_20, apr_21,
//        apr_22, apr_23, apr_24, apr_25, apr_26, apr_27, apr_28, apr_29, apr_30,
//        may_01, may_02, may_03, may_04, may_05, may_06, may_07,
//        may_08, may_09, may_10, may_11, may_12, may_13, may_14,
//        may_15, may_16, may_17, may_18, may_19, may_20, may_21,
//        may_22, may_23, may_24, may_25, may_26, may_27, may_28, may_29, may_30, may_31,
//        jun_01, jun_02, jun_03, jun_04, jun_05, jun_06, jun_07,
//        jun_08, jun_09, jun_10, jun_11, jun_12, jun_13, jun_14,
//        jun_15, jun_16, jun_17, jun_18, jun_19, jun_20, jun_21,
//        jun_22, jun_23, jun_24, jun_25, jun_26, jun_27, jun_28, jun_29, jun_30,
//        jul_01, jul_02, jul_03, jul_04, jul_05, jul_06, jul_07,
//        jul_08, jul_09, jul_10, jul_11, jul_12, jul_13, jul_14,
//        jul_15, jul_16, jul_17, jul_18, jul_19, jul_20, jul_21,
//        jul_22, jul_23, jul_24, jul_25, jul_26, jul_27, jul_28, jul_29, jul_30, jul_31,
//        aug_01, aug_02, aug_03, aug_04, aug_05, aug_06, aug_07,
//        aug_08, aug_09, aug_10, aug_11, aug_12, aug_13, aug_14,
//        aug_15, aug_16, aug_17, aug_18, aug_19, aug_20, aug_21,
//        aug_22, aug_23, aug_24, aug_25, aug_26, aug_27, aug_28, aug_29, aug_30, aug_31,
//        sep_01, sep_02, sep_03, sep_04, sep_05, sep_06, sep_07,
//        sep_08, sep_09, sep_10, sep_11, sep_12, sep_13, sep_14,
//        sep_15, sep_16, sep_17, sep_18, sep_19, sep_20, sep_21,
//        sep_22, sep_23, sep_24, sep_25, sep_26, sep_27, sep_28, sep_29, sep_30,
//        oct_01, oct_02, oct_03, oct_04, oct_05, oct_06, oct_07,
//        oct_08, oct_09, oct_10, oct_11, oct_12, oct_13, oct_14,
//        oct_15, oct_16, oct_17, oct_18, oct_19, oct_20, oct_21,
//        oct_22, oct_23, oct_24, oct_25, oct_26, oct_27, oct_28, oct_29, oct_30, oct_31,
//        nov_01, nov_02, nov_03, nov_04, nov_05, nov_06, nov_07,
//        nov_08, nov_09, nov_10, nov_11, nov_12, nov_13, nov_14,
//        nov_15, nov_16, nov_17, nov_18, nov_19, nov_20, nov_21,
//        nov_22, nov_23, nov_24, nov_25, nov_26, nov_27, nov_28, nov_29, nov_30,
//        dec_01, dec_02, dec_03, dec_04, dec_05, dec_06, dec_07,
//        dec_08, dec_09, dec_10, dec_11, dec_12, dec_13, dec_14,
//        dec_15, dec_16, dec_17, dec_18, dec_19, dec_20, dec_21,
//        dec_22, dec_23, dec_24, dec_25, dec_26, dec_27, dec_28, dec_29, dec_30, dec_31
//    ;

    /**
     * Class week_weekday is a tuple-like class of week-weekday.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     *
     * It is useful when generation week based dates.
     */
    class week_weekday
    {
      week w_;
      weekday wd_;
    public:
      BOOST_FORCEINLINE BOOST_CONSTEXPR week_weekday(week w, weekday wd)BOOST_NOEXCEPT
      : w_(w),
      wd_(wd)
      {
      }

      BOOST_FORCEINLINE BOOST_CONSTEXPR week_weekday(week::rep w, weekday::rep wd, check_t)
      : w_(w, check),
      wd_(wd, check)
      {
      }
      //BOOST_CONSTEXPR chrono::week week() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::week() const BOOST_NOEXCEPT
      {
        return w_;
      }
      //BOOST_CONSTEXPR chrono::weekday weekday() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::weekday() const BOOST_NOEXCEPT
      {
        return wd_;
      }

    };

    BOOST_FORCEINLINE BOOST_CONSTEXPR week_weekday operator/(week w, weekday wd) BOOST_NOEXCEPT
    {
      return week_weekday(w, wd);
    }

    BOOST_FORCEINLINE BOOST_CONSTEXPR week_weekday operator/(weekday wd, week w) BOOST_NOEXCEPT
    {
      return week_weekday(w, wd);
    }

    /**
     * Class year_month_day is a tuple-like class of year-month-day.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     * In addition to construction and getters it provides validation of the year-month-day tuple.
     */
    class year_month_day
    {
      year y_;
      month m_;
      day d_;
    public:
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month_day(year y, month m, day d)BOOST_NOEXCEPT
      : y_(y),
      m_(m),
      d_(d)
      {
      }

//      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month_day(year::rep y, month::rep m, day::rep d, check_t)
//      : y_(y, check),
//      m_(m, check),
//      d_(d, check)
//      {
//      }
      //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      //BOOST_CONSTEXPR chrono::month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      //BOOST_CONSTEXPR chrono::day day() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::day() const BOOST_NOEXCEPT
      {
        return d_;
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_valid() const
      {
        // @todo implement this function
        return true;
      }
    };

    /**
     * Class year_month_day is a tuple-like class of year-month-day-bool.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     * In addition to construction and getters it provides validation of the year-month-day-bool tuple.
     */
    class year_month_day_leap
    {
      year y_;
      month m_;
      day d_;
      bool leap_;
    public:
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month_day_leap(year y, month m, day d, bool leap)BOOST_NOEXCEPT
      : y_(y),
      m_(m),
      d_(d),
      leap_(leap)
      {
      }

      // @todo remove this overload
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_month_day_leap(year::rep y, month::rep m, day::rep d, bool leap) BOOST_NOEXCEPT
      : y_(y),
      m_(m),
      d_(d),
      leap_(leap)
      {
      }
      //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      //BOOST_CONSTEXPR chrono::month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      //BOOST_CONSTEXPR chrono::day day() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::day() const BOOST_NOEXCEPT
      {
        return d_;
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }
      BOOST_CONSTEXPR bool is_valid() const
      {
        // @todo implement this function
        return true;
      }
    };
    /**
     * Class year_day_of_year is a tuple-like class of year-day_of_year.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     * In addition to construction and getters it provides validation of the year-day_of_year tuple.
     */
    class year_day_of_year
    {
      year y_;
      day_of_year d_;
    public:
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_day_of_year(year y, day_of_year d)BOOST_NOEXCEPT
      : y_(y),
      d_(d)
      {
      }
//      BOOST_FORCEINLINE BOOST_CONSTEXPR year_day_of_year(year::rep y, day_of_year::rep d, check_t)
//      : y_(y, check),
//      d_(d, check)
//      {
//      }
      //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      //BOOST_CONSTEXPR chrono::day_of_year day_of_year() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::day_of_year() const BOOST_NOEXCEPT
      {
        return d_;
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_valid() const
      {
        // @todo implement this function
        return true;
      }
    };


    /**
     * Class year_week_weekday is a tuple-like class of year-week-weekday.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     * In addition to construction and getters it provides validation of the year-week-weekday tuple.
     *
     */
    class year_week_weekday
    {
      year y_;
      week w_;
      weekday wd_;
    public:
      BOOST_FORCEINLINE BOOST_CONSTEXPR year_week_weekday(year y, week w, weekday wd)BOOST_NOEXCEPT
      : y_(y),
      w_(w),
      wd_(wd)
      {
      }

//      BOOST_FORCEINLINE BOOST_CONSTEXPR year_week_weekday(year::rep y, week::rep w, weekday::rep wd, check_t)
//      : y_(y, check),
//      w_(w, check),
//      wd_(wd, check)
//      {
//      }
      //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      //BOOST_CONSTEXPR chrono::week week() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::week() const BOOST_NOEXCEPT
      {
        return w_;
      }
      //BOOST_CONSTEXPR chrono::weekday weekday() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::weekday() const BOOST_NOEXCEPT
      {
        return wd_;
      }
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_valid() const
      {
        // @todo implement this function
        return true;
      }
    };


  } // chrono

} // boost

#endif  // header
