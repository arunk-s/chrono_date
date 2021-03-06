#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month_common_year.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month_leap_year.hpp>

#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/chrono/chrono.hpp>

using namespace boost::chrono;

const int Ymin = 1900;
int Ymax = Ymin+10*1000;

typedef boost::chrono::high_resolution_clock Clock;
typedef boost::chrono::duration<double> sec;


void years_last_day_of_month_common(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  int cnt = 0;
  Clock::time_point t0 = Clock::now();

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
//      bool is_leap = year(y).is_leap();
//      unsigned int day_count = m_.days_in(is_leap).count();
      cnt += last_day_of_month_common_year(m_);
      //cnt++;
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with last_day_of_month_common_year()                   " << t1-t0<< " Total Years " << ycount << " Total Count "<<cnt<<'\n';

}
/*
void years_last_day_of_month_leap(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  int cnt = 0;
  Clock::time_point t0 = Clock::now();

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
//      bool is_leap = year(y).is_leap();
//      unsigned int day_count = m_.days_in(is_leap).count();
        last_day_of_month_leap_year(m_);
        cnt++;
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with last_day_of_month_leap_year()                     " << t1-t0<< " Total Years " << ycount << " Total Count "<<cnt<<'\n';

}
*/
void years_last_day_of_month(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  int cnt = 0;
  Clock::time_point t0 = Clock::now();

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
//      bool is_leap = year(y).is_leap();
//      unsigned int day_count = m_.days_in(is_leap).count();
      cnt += last_day_of_month(y,m_);
      //cnt++;
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with last_day_of_month()                               " << t1-t0<< " Total Years " << ycount << " Total Count "<<cnt<<'\n';

}
void years_days_in_month(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  int cnt = 0;
  Clock::time_point t0 = Clock::now();

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
//      unsigned int day_count =
      cnt += m_.days_in(is_leap).count();
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with days_in().count()                                 " << t1-t0<< " Total Years " << ycount << " Total Count "<<cnt<<'\n';

}

int main(void){
  years_last_day_of_month_common();
  years_last_day_of_month();
  years_days_in_month();
  years_last_day_of_month_common();
  years_last_day_of_month();
//  years_last_day_of_month_leap();
  years_days_in_month();

  Ymax *= 10;
  years_last_day_of_month_common();
  years_last_day_of_month();
//  years_last_day_of_month_leap();
  years_days_in_month();

  return 1;
}
