#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <cstdio>
#include <memory>

class DataAnalysis
{
public:
  DataAnalysis();

  void operator()(long long);

  long long getMax()           const;
  long long getMin()           const;
  double    getMean()          const;
  size_t    getNumbPositive()  const;
  size_t    getNumbNegative()  const;
  long long getSumOdd()        const;
  long long getSumEven()       const;
  bool      checkFirstEqLast() const;
  bool      empty()            const;
private:
  long long begin_;
  long long max_;
  long long min_;
  size_t    numbPositive_;
  size_t    numbNegative_;
  size_t    numbZero_;
  long long sumOdd_;
  long long sumEven_;
  bool      beginEqualEnd_;
  bool      emptyData_;         
};

#endif // DATAANALYSIS_H
