#ifndef DETAIL_HPP
#define DETAIL_HPP
#include <stdexcept>
#include <cstdlib>
#include <memory>
namespace detail
{
  unsigned long long int fact(long long int);

  template<typename T>
  class TempArray
  {
  public:
    TempArray(const TempArray<T>&);
    TempArray(TempArray<T>&&) = default;
    TempArray(const size_t& size);
    template<size_t size>
    TempArray(const T (&)[size]);
    TempArray<T> & operator=(const TempArray<T>&);
    TempArray<T> & operator=(TempArray<T>&&) = default;
    T& operator[](const size_t&) const;
    void add(const T*);
    void remove(const size_t &size);
    size_t getSize() const noexcept;
  private:
    std::unique_ptr<T[]> arr_;
    size_t size_;
  };

  template<typename T>
  template<size_t size>
  TempArray<T>::TempArray(const T (&arr)[size]) :
    arr_(nullptr),
    size_(size)
  {
    arr_.reset(std::make_unique<T[]>(size_));
    for (size_t i = 0; i < size_; i++)
    {
      arr_[i] = arr[i];
    }
  }

  template<typename T>
  TempArray<T>::TempArray(const TempArray<T> &arr) :
    arr_(nullptr),
    size_(0)
  {
    *this = arr;
  }

  template<typename T>
  TempArray<T>::TempArray(const size_t& size) :
    arr_(std::make_unique<T[]>(size)),
    size_(size)
  {}

  template<typename T>
  TempArray<T> & TempArray<T>::operator=(const TempArray<T> &arr)
  {
    if (this == &arr)
    {
      return *this;
    }

    size_ = arr.size_;
    arr_ = std::make_unique<T[]>(size_);
    for (size_t i = 0; i < size_; i++)
    {
      arr_[i] = arr.arr_[i];
    }

    return *this;
  }

  template<typename T>
  T& TempArray<T>::operator[](const size_t &index) const
  {
    if (index >= size_)
    {
      throw std::invalid_argument("Array less");
    }

    return arr_[index];
  }

  template<typename T>
  void TempArray<T>::add(const T *elem)
  {
    if (!elem)
    {
      throw std::invalid_argument("Ptr = nullptr");
    }

    std::unique_ptr<T[]> new_arr(std::make_unique<T[]>(size_ + 1));

    for (size_t i = 0; i < size_; i++)
    {
      new_arr[i] = arr_[i];
    }

    new_arr[size_++] = *elem;

    arr_.swap(new_arr);
  }

  template<typename T>
  void TempArray<T>::remove(const size_t &size)
  {
    if ((size >= size_) || (size < 0))
    {
      throw std::invalid_argument("Going out of the array");
    }

    std::unique_ptr<T[]> new_arr(std::make_unique<T[]>(size_ - 1));

    size_t i = 0, j = 0;

    while (i != size_)
    {
      if (i != size)
      {
        new_arr[j++] = arr_[i++];
      }
      else
      {
        i++;
      }
    }

    size_--;

    arr_.swap(new_arr);
  }

  template<typename T>
  size_t TempArray<T>::getSize() const noexcept
  {
    return size_;
  }
}

#endif
