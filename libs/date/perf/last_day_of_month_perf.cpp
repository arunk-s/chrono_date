#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/algorithms/last_day_of_month_common_year.hpp>
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
  days_date dt_1(jan/day(01)/1970);
//  boost::chrono::days_rep serial_date = dt_2.days_since_epoch().count() - dt_1.days_since_epoch().count() ;

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (unsigned int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      unsigned int day_count = m_.days_in(is_leap).count();
      last_day_of_month_common_year(m_);
      cnt++;
/*
      for(unsigned int i = 1 ; i<=day_count ;++i)
      {

          civil_from_days(days_date(m_/day(i)/y).days_since_epoch().count()-dt_1.days_since_epoch().count());
      }
*/      
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  std::cout << "with civil_from_days()                   " << t1-t0<< " Total Years " << ycount << " Total Count "<<cnt<<'\n';
 
}

int main(void){
  years_last_day_of_month_common();
}