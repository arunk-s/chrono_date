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
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  days_date dt_1(jan/day(01)/1970);
  days_date dt_2(jan/day(01)/0001);
  boost::chrono::days_rep serial_date = dt_2.days_since_epoch().count() - dt_1.days_since_epoch().count() ;
  auto d = civil_from_days(serial_date);

  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      int day_count = m_.days_in(is_leap).count();

      for(int i = 1 ; i<=day_count ;++i)
      {

          auto d_1 = civil_from_days(days_date(m_/day(i)/y).days_since_epoch().count()-dt_1.days_since_epoch().count());

//          BOOST_VERIFY( serial_date==prev+1);
//          prev = serial_date;
//          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
  //Clock::time_point encode = t1 - t0;	
  std::cout << "with days_from_civil()                   " << t1-t0<< " Total Years " << ycount << " " <<count << '\n';
 

//  std::cout<<std::get<0>(d)<<" "<<std::get<1>(d)<<" "<<std::get<2>(d)<<std::endl;

}

int main(){
	temp();
	return 1;
}