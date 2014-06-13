//
//  (C) Copyright Howard Hinnant
//  (C) Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//

#ifndef BOOST_CHRONO_DATE_IO_DURATION_UNITS_HPP
#define BOOST_CHRONO_DATE_IO_DURATION_UNITS_HPP

#include <boost/chrono/config.hpp>
#include <boost/ratio/ratio_io.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/io/duration_style.hpp>
#include <boost/chrono/io/ios_base_state.hpp>
#include <string>
#include <ios>
#include <locale>
#include <algorithm>

namespace boost
{
  namespace chrono
  {


    /**
     * This class is used to define the strings for the default English
     *
     */
    template <typename CharT = char>
    class date_duration_units_default: public duration_units_default<CharT>
    {
    public:
      /**
       * Type of character the facet is instantiated on.
       */
      typedef CharT char_type;
      /**
       * Type of character string passed to member functions.
       */
      typedef std::basic_string<CharT> string_type;

      /**
       * Construct a @c duration_units_default facet.
       * @param refs
       * @Effects Construct a @c duration_units_default facet.
       * If the @c refs argument is @c 0 then destruction of the object is
       * delegated to the @c locale, or locales, containing it. This allows
       * the user to ignore lifetime management issues. On the other had,
       * if @c refs is @c 1 then the object must be explicitly deleted;
       * the @c locale will not do so. In this case, the object can be
       * maintained across the lifetime of multiple locales.
       */
      explicit date_duration_units_default(size_t refs = 0) :
        duration_units_default<CharT> (date_valid_units_, refs)
      {
        string_type* it = init_valid_units(date_valid_units_);
        it = fill_units(it, ratio<86400> ());
      }
      /**
       * Destroys the facet.
       */
      ~date_duration_units_default()
      {
      }

    protected:
      typedef duration_units_default<CharT> base_type;

      /**
       * @param k the found pointer to the unit.
       * @Effects @c rt is set to the valid Period when the @c k matches a valid unit.
       * @return true if @c k matches a valid unit.
       */
      bool do_match_valid_unit(const string_type* k, rt_ratio& rt) const
      {
        if ( this->base_type::do_match_valid_unit(k,rt) ) return true;

        std::size_t index = (k - valid_units_) / (pfs_ + 1);
        switch (index)
        {
        case 19:
          rt = rt_ratio(ratio<86400> ());
          return rue;
        default:
          std::cerr << __FILE__ << ":" << __LINE__ << std::endl;
          return false;
        }

//        std::size_t index = (k - valid_units_) / (pfs_ + 1);
//        switch (index)
//        {
//        case 0:
//          rt = rt_ratio(atto());
//          break;
//        case 1:
//          rt = rt_ratio(femto());
//          break;
//        case 2:
//          rt = rt_ratio(pico());
//          break;
//        case 3:
//          rt = rt_ratio(nano());
//          break;
//        case 4:
//          rt = rt_ratio(micro());
//          break;
//        case 5:
//          rt = rt_ratio(milli());
//          break;
//        case 6:
//          rt = rt_ratio(centi());
//          break;
//        case 7:
//          rt = rt_ratio(deci());
//          break;
//        case 8:
//          rt = rt_ratio(deca());
//          break;
//        case 9:
//          rt = rt_ratio(hecto());
//          break;
//        case 10:
//          rt = rt_ratio(kilo());
//          break;
//        case 11:
//          rt = rt_ratio(mega());
//          break;
//        case 12:
//          rt = rt_ratio(giga());
//          break;
//        case 13:
//          rt = rt_ratio(tera());
//          break;
//        case 14:
//          rt = rt_ratio(peta());
//          break;
//        case 15:
//          rt = rt_ratio(exa());
//          break;
//        case 16:
//          rt = rt_ratio(ratio<1> ());
//          break;
//        case 17:
//          rt = rt_ratio(ratio<60> ());
//          break;
//        case 18:
//          rt = rt_ratio(ratio<3600> ());
//          break;
//        case 19:
//          rt = rt_ratio(ratio<86400> ());
//          break;
//        default:
//          std::cerr << __FILE__ << ":" << __LINE__ << std::endl;
//          return false;
//        }
//        return true;
      }


      /**
       * @return pointer to the start of valid units.
       */
      const string_type* do_get_valid_units_start() const
      {
        return date_valid_units_;
      }
      /**
       * @return pointer to the end of valid units.
       */
      const string_type* do_get_valid_units_end() const
      {
        return date_valid_units_ + 20 * (pfs_ + 1);
      }

      /**
       *
       * This facet names the units associated to the following periods:
       * atto,femto,pico,nano,micro,milli,centi,deci,ratio<1>,deca,hecto,kilo,mega,giga,tera,peta,exa,ratio<60> and ratio<3600>.
       * @return true if the unit associated to the given Period is named, false otherwise.
       */
      bool do_is_named_unit(rt_ratio rt) const
      {

        if ( this->base_type::do_is_named_unit(rt) ) return true;
        return (rt==ratio<86400>());

//        if (rt.num==1) {
//          switch (rt.den)
//          {
//          case BOOST_RATIO_INTMAX_C(1):
//          case BOOST_RATIO_INTMAX_C(10):
//          case BOOST_RATIO_INTMAX_C(100):
//          case BOOST_RATIO_INTMAX_C(1000):
//          case BOOST_RATIO_INTMAX_C(1000000):
//          case BOOST_RATIO_INTMAX_C(1000000000):
//          case BOOST_RATIO_INTMAX_C(1000000000000):
//          case BOOST_RATIO_INTMAX_C(1000000000000000):
//          case BOOST_RATIO_INTMAX_C(1000000000000000000):
//            return true;
//          default:
//            return false;
//          }
//        } else if (rt.den==1) {
//          switch (rt.num)
//          {
//          case BOOST_RATIO_INTMAX_C(10):
//          case BOOST_RATIO_INTMAX_C(60):
//          case BOOST_RATIO_INTMAX_C(100):
//          case BOOST_RATIO_INTMAX_C(1000):
//          case BOOST_RATIO_INTMAX_C(3600):
//          case BOOST_RATIO_INTMAX_C(86400):
//          case BOOST_RATIO_INTMAX_C(1000000):
//          case BOOST_RATIO_INTMAX_C(1000000000):
//          case BOOST_RATIO_INTMAX_C(1000000000000):
//          case BOOST_RATIO_INTMAX_C(1000000000000000):
//          case BOOST_RATIO_INTMAX_C(1000000000000000000):
//            return true;
//          default:
//            return false;
//          }
//        }
//        return false;

      }

      /**
       * @return the unit associated to this duration if it is named, "" otherwise.
       */
      std::string do_get_unit(duration_style::type style, rt_ratio rt, intmax_t v) const
      {

        if (rt.num==1) {
          this->base_type::do_get_unit(style,rt,v);
//          switch (rt.den)
//          {
//          case BOOST_RATIO_INTMAX_C(1):
//            return do_get_unit(style, ratio<1>(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(10):
//            return do_get_unit(style, deci(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(100):
//            return do_get_unit(style, centi(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(1000):
//            return do_get_unit(style, milli(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(1000000):
//            return do_get_unit(style, micro(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(1000000000):
//            return do_get_unit(style, nano(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(1000000000000):
//            return do_get_unit(style, pico(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(1000000000000000):
//            return do_get_unit(style, femto(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(1000000000000000000):
//            return do_get_unit(style, atto(), do_get_plural_form(v));
//          default:
//            ;
//          }
        } else if (rt.den==1) {
          switch (rt.num)
          {
          case BOOST_RATIO_INTMAX_C(86400):
            return do_get_unit(style, ratio<86400>(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(10):
//             return do_get_unit(style, deca(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(60):
//            return do_get_unit(style, ratio<60>(), do_get_plural_form(v));
//          case BOOST_RATIO_INTMAX_C(100):
//             return do_get_unit(style, hecto(), do_get_plural_form(v));
//           case BOOST_RATIO_INTMAX_C(1000):
//             return do_get_unit(style, kilo(), do_get_plural_form(v));
//           case BOOST_RATIO_INTMAX_C(3600):
//             return do_get_unit(style, ratio<3600>(), do_get_plural_form(v));
//           case BOOST_RATIO_INTMAX_C(1000000):
//             return do_get_unit(style, mega(), do_get_plural_form(v));
//           case BOOST_RATIO_INTMAX_C(1000000000):
//             return do_get_unit(style, giga(), do_get_plural_form(v));
//           case BOOST_RATIO_INTMAX_C(1000000000000):
//             return do_get_unit(style, tera(), do_get_plural_form(v));
//           case BOOST_RATIO_INTMAX_C(1000000000000000):
//             return do_get_unit(style, peta(), do_get_plural_form(v));
//           case BOOST_RATIO_INTMAX_C(1000000000000000000):
//             return do_get_unit(style, exa(), do_get_plural_form(v));
           default:
             this->base_type::do_get_unit(style,rt,v);
             ;
           }
        }

        return "";

      }

      /**
       * @param style the duration style.
       * @param period the period associated to the duration days.
       * @param pf the requested plural form.
       * @return if style is symbol returns "d", otherwise if pf is 0 return "day", if pf is 1 "days"
       */
      virtual string_type do_get_unit(duration_style style, ratio<86400> , std::size_t pf) const
      {
        static const CharT t[] =
        { 'd' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 'd', 'a', 'y' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 'd', 'a', 'y', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol) return symbol;
        if (pf == 0) return singular;
        if (pf == 1) return plural;
        // assert
        //throw "exception";
      }

      string_type date_valid_units_[20 * 3];

    };

  } // chrono

} // boost

#endif  // header
