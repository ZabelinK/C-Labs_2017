#ifndef H_MATRIX_SHAPE
#define H_MATRIX_SHAPE
#include <iostream>
#include <memory>
#include <cstdlib>
#include "shape.hpp"

class MatrixShape
{
public:
  MatrixShape(const MatrixShape&) = default;
  MatrixShape(MatrixShape&&) = default;
  MatrixShape(const Shape *);
  ~MatrixShape();
  MatrixShape &operator=(const MatrixShape&) = default;
  MatrixShape &operator=(MatrixShape&&) = default;
  friend std::ostream& operator<<(std::ostream&, const MatrixShape &);
  void addShape(const Shape *);
  const Shape** operator[](const size_t&) const;
  
private:
  const Shape **matrix_;
  size_t columns_, lines_;
  bool intersect(const Shape*, const Shape*) const noexcept;
};

std::ostream& operator<<(std::ostream&, const MatrixShape &);

#endif
