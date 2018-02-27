#ifndef QUEUEWITHPRIORITY_H
#define QUEUEWITHPRIORITY_H

#include <list>
#include <algorithm>
#include <stdexcept>

template <typename T>
class QueueWithPriority
{
public:
  enum ElementPriority 
  {
    LOW,
    NORMAL,
    HIGH
  };
  
  void put(const T & element, ElementPriority priority);
  void accelerate();
  void pop();
  
  template <typename Operation>
  bool process(Operation operation);

private:
  std::list<T> list_[3];
  
  int getNumberNotEmptyList() const;
};

template <typename T>
void QueueWithPriority<T>::put(const T &element, ElementPriority priority)
{
  list_[priority].push_back(element);
}

template <typename T>
void QueueWithPriority<T>::accelerate()
{
  list_[HIGH].splice(list_[HIGH].end(), list_[LOW]);
}

template <typename T>
void QueueWithPriority<T>::pop()
{
  int priority = QueueWithPriority<T>::getNumberNotEmptyList();
  if(priority < 0)
  {
    throw std::out_of_range("Queue empty.");
  }
  list_[priority].pop_front();
}

template <typename T>
template <typename Operation>
bool QueueWithPriority<T>::process(Operation operation)
{
  int priority = QueueWithPriority<T>::getNumberNotEmptyList();
  if(priority < 0)
  {
    return false;
  }
 
  T tmp = list_[priority].front();
  list_[priority].pop_front();
  operation(tmp);

  return true;
}

template <typename T>
int QueueWithPriority<T>::getNumberNotEmptyList() const
{
  int priority = HIGH;
  while((priority >= 0) && list_[priority].empty())
  {
    --priority;
  }
  return priority;
}

#endif // QUEUEWITHPRIORITY_H
