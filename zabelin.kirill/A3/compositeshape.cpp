#include "compositeshape.hpp"
#include <iostream>

CompositeShape::CompositeShape(const Shape &new_shape) :
  Shape(new_shape),
  size_(1)
{
  mass_ = new Shape*[1];
  mass_[0] = new_shape.clone();
  area_ = mass_[0]->getArea();
}

CompositeShape::~CompositeShape()
{
  for(int i = 0; i < size_; i++)
  {
    delete mass_[i];
  }
  delete [] mass_;
}

double CompositeShape::getArea() const
{
  return area_;
}

rectangle_t CompositeShape::getFrameRect() const
{
  return {pos_, getUpY() - getDownY(), getRightX() - getLeftX()};
}

void CompositeShape::printInfo(std::ostream& out) const
{
  out << "CompositeShape:\n";
  for(int i = 0; i < size_; i++)
  {
    mass_[i]->printInfo(out);
  }
}

void CompositeShape::addShape(const Shape &new_shape)
{
  Shape **new_mass = new Shape*[size_+1];
  for(int i = 0; i < size_; i++)
  {
    new_mass[i] = mass_[i];
  }
  new_mass[size_] = new_shape.clone();
  delete [] mass_;
  mass_ = new_mass;
  area_ += mass_[size_]->getArea();
  size_++;
  pos_ = {(getLeftX() + getRightX()) / 2, (getUpY() + getDownY()) / 2};  
}
void CompositeShape::scale(const double &coefficient)
{
  if(coefficient > 0 && coefficient != 1){
    point_t pos = {0, 0};
    area_ = 0;
    for(int i = 0; i < size_; i++)
    {
      pos = mass_[i]->getPos();
      mass_[i]->move((pos.x < pos_.x ? pos.x - pos_.x : pos.x - pos_.x) * (coefficient - 1),
       (pos.y < pos_.y ? pos.y - pos_.y : pos.y - pos_.y) * (coefficient - 1));
      mass_[i]->scale(coefficient);
      area_ += mass_[i]->getArea();
    }
  }
}

Shape* CompositeShape::clone() const
{
  Shape **clon = new Shape*[size_];
  for(int i = 0; i < size_; i++)
  {
    clon[i] = mass_[i];
  }
  return *clon;
}

void CompositeShape::move(const point_t &end_pos)
{
  for(int i = 0; i < size_; i++)
  {
    mass_[i]->move(end_pos.x - pos_.x, end_pos.y - pos_.y);
  }
}

void CompositeShape::move(const double &delta_x, const double &delta_y)
{
  move(pos_.x + delta_x, pos_.y + delta_y);
}

double CompositeShape::getUpY() const
{
  double up_y = mass_[0]->getUpY();
  for(int i = 1; i < size_; i++)
  {
    if(mass_[i]->getUpY() > up_y)
    {
      up_y = mass_[i]->getUpY();
    }
  }
  return up_y;
}

double CompositeShape::getDownY() const
{
  double down_y = mass_[0]->getDownY();
  for(int i = 1; i < size_; i++)
  {
    if(mass_[i]->getDownY() < down_y)
    {
      down_y = mass_[i]->getDownY();
    }
  }
  return down_y;
}

double CompositeShape::getLeftX() const
{
  double left_x = mass_[0]->getLeftX();
  for(int i = 1; i < size_; i++)
  {
    if(mass_[i]->getLeftX() < left_x)
    {
      left_x = mass_[i]->getLeftX();
    }
  }
  return left_x;
}

double CompositeShape::getRightX() const
{
  double right_x = mass_[0]->getRightX();
  for(int i = 1; i < size_; i++)
  {
    if(mass_[i]->getRightX() > right_x)
    {
      right_x = mass_[i]->getRightX();
    }
  }
  return right_x;
}

std::ostream& operator<<(std::ostream& out, const CompositeShape &out_shape)
{
  out_shape.printInfo(out);
  return out;
}
