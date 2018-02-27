#include "matrixshape.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>
MatrixShape::MatrixShape(const Shape *shape) :
  matrix_(nullptr),
  columns_(1),
  lines_(1)
{
  if(shape == nullptr)
  {
    throw std::invalid_argument("Object does not exist");
  }
  matrix_ = new const Shape*[1];
  matrix_[0] = shape;
}

MatrixShape::~MatrixShape()
{
  delete [] matrix_;
}

void MatrixShape::addShape(const Shape *shape)
{
  if(shape == nullptr)
  {
    throw std::invalid_argument("Object does not exist");
  }
  
  for (size_t i = 0; i < columns_ * lines_; i++)
  {
    if(matrix_[i] == shape)
    {
      throw std::invalid_argument("This shape is already in the MatrixShape");
    }
  }

  size_t i = lines_, j = columns_ - 1;
  while((i != 0) && (!intersect(matrix_[(i - 1) * columns_ + j], shape)))
  {
    (j != 0) ? j-- : (i--, j = columns_ - 1);
  }
  
  if(i == lines_) 
  {
    lines_++;
    const Shape **new_matrix = new const Shape*[columns_ * lines_];
    i = 0;
    while(i < (lines_ - 1) * columns_)
    {
      new_matrix[i] = matrix_[i];
      i++;
    }
    new_matrix[i++] = shape;
    while(i < columns_ * lines_)
    {
      new_matrix[i++] = nullptr;
    }
    delete [] matrix_;
    matrix_ = new_matrix;
  }
  else
  {
    j = 0;
    while((j < columns_) && (matrix_[i * columns_ + j] != nullptr))
    {
      j++;
    }
    if(j == columns_)
    {
      ++columns_;
      const Shape **new_matrix = new const Shape*[columns_ * lines_];
      j = 0;      
      size_t iter = 0;
      while(j < columns_ * lines_)
      {
        if((j + 1) % columns_ == 0)
        {
          if((i + 1) == ((j + 1) / columns_))
          {
            new_matrix[j] = shape;
          }
          else
          {
            new_matrix[j] = nullptr;
          }
        }
        else
        {
          new_matrix[j] = matrix_[iter++];
        }
        j++;
      }
      delete [] matrix_;
      matrix_ = new_matrix;
    }
    else
    {
      matrix_[i * columns_ + j] = shape;
    }
  }
}

std::ostream& operator<<(std::ostream& out, const MatrixShape & matrix)
{
  for (size_t i = 0; i < matrix.lines_; i++)
  {
    for (size_t j = 0; j < matrix.columns_; j++)
    {
      if(matrix.matrix_[i * matrix.columns_ + j] == nullptr)
      {
        out << "0\t";
      }
      else
      {
        out << matrix.matrix_[i * matrix.columns_ + j]->getName() << '\t';
      }
    }
    std::cout << '\n';
  }
  return out;
}

const Shape** MatrixShape::operator[](const size_t &index) const
{
  if(index > lines_)
  {
    throw std::invalid_argument("The matrix is smaller");
  }
  return (matrix_ + index * columns_);
}

bool MatrixShape::intersect(const Shape * sh1, const Shape * sh2) const noexcept
{
  if((sh1 == nullptr) || (sh2 == nullptr))
  {
    return false;
  }
  return ((fabs(sh1->getFrameRect().pos.x - sh2->getFrameRect().pos.x) 
        < ((sh1->getFrameRect().height / 2) + (sh2->getFrameRect().height / 2))) 
      && ((fabs(sh1->getFrameRect().pos.y - sh2->getFrameRect().pos.y) 
        < ((sh1->getFrameRect().width / 2) + (sh2->getFrameRect().width / 2)))));
}
