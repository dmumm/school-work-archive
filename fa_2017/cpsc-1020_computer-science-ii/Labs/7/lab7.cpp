#include "Date.hpp"

int main(int argc, char *argv[])
{

  int n, m, d, y, i;
  i = 0;

  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if(argc != 3) {
    cout << "USAGE ERROR:  ./executable outPutFileName";
    return -1;
  } if(input.fail())  {
    cout << argv[1] << " did not open successfully\n";
  } if(output.fail()) {
    cout << argv[2] << " did not open successfully\n";
  }


  input >> n;
  cout << n << endl;

  Date dates[n];

  for(i=0; i<n; i++)
  {
    input >> m >> d >> y;
    dates[i].set_month(m);
    dates[i].set_day(d);
    dates[i].set_year(y);
  }

  sort(dates, dates+n, Date::compare);

  for(i=0; i<n; i++)
  {
    output << dates[i].print() << endl;
  }

  input.close();
  output.close();
  return 0;
}
