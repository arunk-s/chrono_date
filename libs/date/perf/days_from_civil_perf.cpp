#include <boost/chrono/date.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/algorithms/days_from_civil.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/chrono/chrono.hpp>

using namespace boost::chrono;

namespace boost
{
  namespace chrono
  {
    days::rep to_days2(int y, int m, int d) BOOST_NOEXCEPT
    {
      return days_before_year(static_cast<int_least32_t>(y - 32799)) +
          days_in_year_before(is_leap(y),m-1) +
          d;
    }
  }
}

const int Ymin = 1900;
int Ymax = Ymin+10*1000;

typedef boost::chrono::high_resolution_clock Clock;
typedef boost::chrono::duration<double> sec;
/**
 * Passing days from 1900/1/1 to 4100/1/1 to the algorithm
 * directly in integer
 **/
void years_days_in_civil()
{
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  boost::chrono::days_rep prev = days_from_civil<boost::chrono::days_rep>(Ymin,1,1) - 1 ;
  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      int day_count = m_.days_in(is_leap).count();

      for(int i = 1 ; i<=day_count ;++i)
      {

          boost::chrono::days_rep serial_date = days_from_civil<boost::chrono::days_rep>(y,m,i);
          BOOST_VERIFY( serial_date==prev+1);
          prev = serial_date;
          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
  //Clock::time_point encode = t1 - t0;
  std::cout << "with days_from_civil()                   " << t1-t0<< " Total Years " << ycount << " " <<count << '\n';
}
void years_days_in_civil_f()
{
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  boost::chrono::days_rep prev = days_from_civil_f(Ymin,1,1) - 1 ;
  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      int day_count = m_.days_in(is_leap).count();

      for(int i = 1 ; i<=day_count ;++i)
      {

          boost::chrono::days_rep serial_date = days_from_civil_f(y,m,i);
          BOOST_VERIFY( serial_date==prev+1);
          prev = serial_date;
          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
  //Clock::time_point encode = t1 - t0;
  std::cout << "with days_from_civil_f()                 " << t1-t0<< " Total Years " << ycount << " " <<count << '\n';
}
/**
 * Passing days from 1900/1/1 to 4100/1/1 to the algorithm
 * directly in integer
 **/
void years_days_in_civil_opaque()
{
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  boost::chrono::days_rep prev = days_from_civil<boost::chrono::days_rep>(Ymin,1,1) - 1 ;
  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      int day_count = m_.days_in(is_leap).count();

      for(int i = 1 ; i<=day_count ;++i)
      {

          boost::chrono::days_rep serial_date = days_from_civil<boost::chrono::days_rep>(year(y), month(m, no_check),day(i,no_check));
          BOOST_VERIFY( serial_date==prev+1);
          prev = serial_date;
          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
  //Clock::time_point encode = t1 - t0;
  std::cout << "with days_from_civil() (opaque)          " << t1-t0<< " Total Years " << ycount << " " <<count << '\n';
}

/**
 *Passing the same range to the algorithms
 *but casting from ymd_date
 **/
void ymd_years_days_in_civil()
{
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  boost::chrono::days_rep prev = days_from_civil<boost::chrono::days_rep>(Ymin,1,1) - 1 ;
  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      int day_count = m_.days_in(is_leap).count();

      for(int i = 1 ; i<=day_count ;++i)
      {

        ymd_date dt1(year(y),m_,day(i, no_check));
        boost::chrono::days_rep serial_date = days_from_civil<boost::chrono::days_rep>(static_cast<int>(dt1.to_year()),static_cast<unsigned>(dt1.to_month()),
                                              static_cast<unsigned>(dt1.to_day()));
        BOOST_VERIFY( serial_date==prev+1);
        prev = serial_date;
        count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
 // Clock::time_point encode = t1 - t0;
  std::cout << "with days_from_civil() with casting      " << t1-t0 << " Total Years " << ycount << " " <<count<< '\n';
}

/**
 * Passing days from 1900/1/1 to 4100/1/1 to the algorithm
 * directly in integer
 **/
void ymd_to_days()
{
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  boost::chrono::days_rep prev = to_days(Ymin,1,1) - 1 ;
  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      int day_count = m_.days_in(is_leap).count();

      for(int i = 1 ; i<=day_count ;++i)
      {

          boost::chrono::days_rep serial_date = to_days(y,m,i);
          BOOST_VERIFY( serial_date==prev+1);
          prev = serial_date;
          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
  //Clock::time_point encode = t1 - t0;
  std::cout << "with to_days()                          " << t1-t0<< " Total Years " << ycount << " " <<count << '\n';
}

/**
 * Passing days from 1900/1/1 to 4100/1/1 to the algorithm
 * directly in integer
 **/
void ymd_to_days_inline()
{
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  boost::chrono::days_rep prev = to_days2(Ymin,1,1) - 1 ;
  for (int y = Ymin; y <=Ymax; ++y)
  {
    for (int m = 1; m <=12; ++m)
    {
      month m_ = month(m, no_check);
      bool is_leap = year(y).is_leap();
      int day_count = m_.days_in(is_leap).count();

      for(int i = 1 ; i<=day_count ;++i)
      {

          boost::chrono::days_rep serial_date = to_days2(y,m,i);
          BOOST_VERIFY( serial_date==prev+1);
          prev = serial_date;
          count+=serial_date;
      }
    }
    ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
  //Clock::time_point encode = t1 - t0;
  std::cout << "with to_days2()                         " << t1-t0<< " Total Years " << ycount << " " <<count << '\n';
}


/**
 *Calculating the same serial dates
 *but from days_date built days_since_epoch()
 **/
void serial_date_days_date()
{
  boost::chrono::days_rep count = 0;
  int ycount = 0;
  Clock::time_point t0 = Clock::now();
  days_date dt (year(Ymin),month(1, no_check),day(1, no_check));
  boost::chrono::days_rep prev = dt.days_since_epoch().count() - 1 ;
  for (int y = Ymin; y <=Ymax; ++y)
    {
    for (int m = 1; m <=12; ++m)
      {
        month m_ = month(m, no_check);
        bool is_leap = year(y).is_leap();
        boost::int_least64_t day_count = m_.days_in(is_leap).count();

        for(int i = 1 ; i<=day_count ;++i)
          {

            days_date dt1(year(y),m_,day(i, no_check));
            boost::chrono::days_rep serial_date = dt1.days_since_epoch().count();


            BOOST_VERIFY( serial_date==prev+1);
            prev = serial_date;
            count+=serial_date;
          }
      }
      ycount++;
  }
  Clock::time_point t1 = Clock::now();
  //typedef boost::chrono::duration<float, boost::nano> sec;
 // Clock::time_point encode = t1 - t0;
  std::cout << "with days_since_epoch()                  " << t1-t0 << " Total Years " << ycount << " " <<count<< '\n';
}

int main()
{
  for (int i = 0; i < 10; ++i)
  {
    Ymax = Ymin+(i+1)*1000;
    std::cout<<i<<"th"<<" Loop"<<std::endl;
    years_days_in_civil();
    years_days_in_civil_opaque();

    ymd_years_days_in_civil();
    years_days_in_civil_f();
    //ymd_to_days_inline();
    //ymd_to_days();
    serial_date_days_date();

  }
  return 1;
}
