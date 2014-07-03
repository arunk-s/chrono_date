#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/algorithms/weekday_from_days.hpp>

#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/chrono/chrono.hpp>

using namespace boost::chrono;

const int Ymin = 1900;
int Ymax = Ymin+10*1000;

typedef boost::chrono::high_resolution_clock Clock;
typedef boost::chrono::duration<double> sec;


void years_weekday_from_days(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  int cnt = 0;
  Clock::time_point t0 = Clock::now();
  days_date dt_1(jan/day(01)/1970);

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      unsigned int day_count = m_.days_in(is_leap).count();

      for(unsigned int i = 1 ; i<=day_count ;++i)
      {

        weekday_from_days(days_date(m_/day(i)/y).days_since_epoch().count()-dt_1.days_since_epoch().count());
        cnt++;
//          auto d_1 = 
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with weekday_from_days()                   " << t1-t0<< " Total Years " << ycount << " Total Count "<< cnt <<'\n';

}
void years_weekday(){
//  boost::chrono::days_rep count = 0;
  int ycount = 0;
  int cnt = 0;
  Clock::time_point t0 = Clock::now();
  days_date dt_1(jan/day(01)/1970);

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      unsigned int day_count = m_.days_in(is_leap).count();

      for(unsigned int i = 1 ; i<=day_count ;++i)
      {

        weekday(days_date(m_/day(i)/y));
//          weekday_from_days(days_date(m_/day(i)/y).days_since_epoch().count()-dt_1.days_since_epoch().count());
        cnt++;
//          auto d_1 = 
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with weekday()                             " << t1-t0<< " Total Years " << ycount << " Total Count "<< cnt <<'\n';

}
int main(void){
  years_weekday_from_days();
  years_weekday();
  years_weekday_from_days();
  years_weekday();
  years_weekday_from_days();
  years_weekday();

  return 1;
}