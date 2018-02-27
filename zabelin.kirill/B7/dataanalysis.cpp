#include "dataanalysis.h"

DataAnalysis::DataAnalysis():
  begin_(0),
  max_(0),
  min_(0),
  numbPositive_(0),
  numbNegative_(0),
  numbZero_(0),
  sumOdd_(0),
  sumEven_(0),
  beginEqualEnd_(false),
  emptyData_(true)
{}

void DataAnalysis::operator()(long long int i)
{
  if(emptyData_)
  {
    begin_ = i;
    max_ = i;
    min_ = i;
    emptyData_ = false;
  }

  if(i > max_)
  {
    max_ = i;
  }
  else if(i < min_)
  {
    min_ = i;
  }

  i > 0 ? ++numbPositive_
      : i == 0 ? ++numbZero_ : ++numbNegative_;

  i % 2 == 0 ? sumEven_ += i : sumOdd_ += i;

  beginEqualEnd_ = i == begin_;
}

long long DataAnalysis::getMax() const
{
  return max_;
}

long long DataAnalysis::getMin() const
{
  return min_;
}

double DataAnalysis::getMean() const
{
  return static_cast<double>(sumOdd_ + sumEven_) / (numbNegative_ + numbPositive_ + numbZero_);
}

size_t DataAnalysis::getNumbPositive() const
{
  return numbPositive_;
}

size_t DataAnalysis::getNumbNegative() const
{
  return numbNegative_;
}

long long DataAnalysis::getSumOdd() const
{
  return sumOdd_;
}

long long DataAnalysis::getSumEven() const
{
  return sumEven_;
}

bool DataAnalysis::checkFirstEqLast() const
{
  return beginEqualEnd_;
}

bool DataAnalysis::empty() const
{
  return emptyData_;
}
