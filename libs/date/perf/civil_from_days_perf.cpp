#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/algorithms/civil_from_days.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/chrono/date/tuples.hpp>
#include <boost/chrono/chrono.hpp>
#include <tuple>

using namespace boost::chrono;

const int Ymin = 1900;
int Ymax = Ymin+10*1000;

typedef boost::chrono::high_resolution_clock Clock;
typedef boost::chrono::duration<double> sec;


void years_civil_from_days(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  days_date dt_1(jan/day(01)/1970);
//  days_date dt_2(jan/day(01)/0001);
//  boost::chrono::days_rep serial_date = dt_2.days_since_epoch().count() - dt_1.days_since_epoch().count() ;
//  auto d = civil_from_days(serial_date);

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      unsigned int day_count = m_.days_in(is_leap).count();

      for(unsigned int i = 1 ; i<=day_count ;++i)
      {

          auto d_1 = civil_from_days(days_date(m_/day(i)/y).days_since_epoch().count()-dt_1.days_since_epoch().count());
          BOOST_VERIFY(std::get<0>(d_1) == y);
          BOOST_VERIFY(std::get<1>(d_1) == m);
          BOOST_VERIFY(std::get<2>(d_1) == i);
//          prev = serial_date;
//          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with days_from_civil()                   " << t1-t0<< " Total Years " << ycount << '\n';
 

//  std::cout<<std::get<0>(d)<<" "<<std::get<1>(d)<<" "<<std::get<2>(d)<<std::endl;

}

void years_to_ymd(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
//  days_date dt_1(jan/day(01)/0001);
//  boost::chrono::days serial_date = dt_1.days_since_epoch() ;//- dt_1.days_since_epoch();
//  year_month_day ymd = to_ymd(serial_date);
//  year y(ymd);
//  month m_
//  std::cout<<y<<std::endl;
//  auto d = civil_from_days(serial_date);

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      unsigned int day_count = m_.days_in(is_leap).count();

      for(unsigned i = 1 ; i<=day_count ;++i)
      {

          year_month_day ymd = to_ymd(days_date(m_/day(i)/y).days_since_epoch());
          BOOST_VERIFY(year(ymd) == y);
          BOOST_VERIFY(month(ymd) == m_);
          BOOST_VERIFY(day(ymd) == i);
//          prev = serial_date;
//          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with to_ymd()                            " << t1-t0<< " Total Years " << ycount << '\n';

}

void years_to_ymd_f(){
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  int y__;
  int m__,d__;

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      unsigned int day_count = m_.days_in(is_leap).count();

      for(unsigned i = 1 ; i<=day_count ;++i)
      {

          boost::chrono::days_rep serial_date = days_date(m_/day(i)/y).days_since_epoch().count(); //- dt_1.days_since_epoch().count() ;
          to_ymd(serial_date,y__,m__,d__);
          BOOST_VERIFY(y__ == y);
          BOOST_VERIFY(m__ == m);
          BOOST_VERIFY(d__ == i);
//          prev = serial_date;
//          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with to_ymd(y&,m&,d&)                    " << t1-t0<< " Total Years " << ycount << '\n';

}
int main(){
	years_civil_from_days();
	years_to_ymd();
  years_to_ymd_f();
  return 1;
}