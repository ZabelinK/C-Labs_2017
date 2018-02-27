#define _USE_MATH_DEFINES

#include "compositeshape.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "detail.hpp"

class CompositeShape::Impl 
{
public:
  Impl();
  Impl(const Impl&);
  Impl & operator=(const Impl&);
  detail::TempArray<ptr_shape> array_;
};

CompositeShape::Impl::Impl() :
  array_(1)
{}

CompositeShape::Impl::Impl(const CompositeShape::Impl& imp) :
  array_(1)
{
  *this = imp;
}

CompositeShape::Impl& CompositeShape::Impl::operator=(const CompositeShape::Impl& imp)
{
  if (this == &imp)
  {
    return *this;
  }

  array_ = imp.array_;
  for (size_t i = 0; i < array_.getSize(); i++)
  {
    array_[i] = imp.array_[i];
  }

  return *this;
}

CompositeShape::CompositeShape(const std::shared_ptr<Shape> &shape) :
  impl_ptr_(std::make_unique<Impl>())
{
  if(!shape)
  {
    throw std::invalid_argument("Object does not exist");
  }
  
  impl_ptr_->array_[0] = shape;
}

CompositeShape::CompositeShape(const CompositeShape &comp) :
  impl_ptr_(nullptr)
{
  *this = comp;
}

CompositeShape & CompositeShape::operator=(const CompositeShape &comp)
{
  if(this == &comp)
  {
    return *this;
  }
  
  if (!comp.impl_ptr_)
  {
    impl_ptr_.reset();
  }
  else if(!impl_ptr_)
  {
    impl_ptr_ = std::make_unique<Impl>(*comp.impl_ptr_);
  }
  else
  {
    *impl_ptr_ = *comp.impl_ptr_;
  }

  return *this;
}

CompositeShape::~CompositeShape() = default;
CompositeShape::CompositeShape(CompositeShape&&) = default;
CompositeShape& CompositeShape::operator=(CompositeShape&&) = default;

void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if(!shape)
  {
    throw std::invalid_argument("Object does not exist");
  }
  
  for (size_t i = 0; i < impl_ptr_->array_.getSize(); i++)
  {
    if (shape == impl_ptr_->array_[i])
    {
      throw std::invalid_argument("This shape is already in the CompositeShape");
    }
  }
  
  impl_ptr_->array_.add(&shape);

}

double CompositeShape::getArea() const
{
  double area = impl_ptr_->array_[0]->getArea();
  
  for(size_t i = 1; i < impl_ptr_->array_.getSize(); i++)
  {
    area += impl_ptr_->array_[i]->getArea();
  }
  
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t frame_rect = impl_ptr_->array_[0]->getFrameRect();
  
  for(size_t i = 1; i < impl_ptr_->array_.getSize(); i++)
  {
    rectangle_t frame = impl_ptr_->array_[i]->getFrameRect();
    frame_rect.expandRect({(frame.pos.x + frame.height / 2),
        (frame.pos.y + frame.width / 2)});
    frame_rect.expandRect({(frame.pos.x - frame.height / 2),
        (frame.pos.y - frame.width / 2)});
  }

  return frame_rect;
}

void CompositeShape::scale(double coefficient)
{
  point_t centre = CompositeShape::getFrameRect().pos;
  if((coefficient > 0) && (coefficient != 1))
  {
    for(size_t i = 0; i < impl_ptr_->array_.getSize(); i++)
    {
      point_t centre_shape = impl_ptr_->array_[i]->getFrameRect().pos;
      impl_ptr_->array_[i]->move({centre.x + (centre_shape.x - centre.x) * coefficient,
          centre.y + (centre_shape.y - centre.y) * coefficient});
      impl_ptr_->array_[i]->scale(coefficient);
    }
  }
  else if(coefficient != 1)
  {
    throw std::invalid_argument("Not correct arguments for scale (CompositeShape)");
  }
}

void CompositeShape::move(const point_t &end_pos)
{
  point_t centre = CompositeShape::getFrameRect().pos;
  CompositeShape::move(end_pos.x - centre.x, end_pos.y - centre.y);
}

void CompositeShape::move(double dx, double dy)
{
  for(size_t i = 0; i < impl_ptr_->array_.getSize(); i++)
  {
    impl_ptr_->array_[i]->move(dx, dy);
  }
}

void CompositeShape::turn(double angle)
{
  point_t centre = CompositeShape::getFrameRect().pos;
  double sin_angle = sin((angle * M_PI) / 180), 
      cos_angle = cos((angle * M_PI) / 180);
  
  for(size_t i = 0; i < impl_ptr_->array_.getSize(); i++)
  {
    point_t centre_shape = impl_ptr_->array_[i]->getFrameRect().pos;
    impl_ptr_->array_[i]->move({centre.x + (centre_shape.x - centre.x) * cos_angle
          - (centre_shape.y - centre.y) * sin_angle,
        centre.y + (centre_shape.y - centre.y) * cos_angle
          + (centre_shape.x - centre.x) * sin_angle });
    impl_ptr_->array_[i]->turn(angle);
  }
}

void CompositeShape::remove(const size_t& index)
{
  impl_ptr_->array_.remove(index);
}

void CompositeShape::print(std::ostream& out) const
{
  out << "CompositeShape:\n";
  for(size_t i = 0; i < impl_ptr_->array_.getSize(); i++)
  {
    impl_ptr_->array_[i]->print(out);
    out << '\n';
  }  
}

size_t CompositeShape::getSize() const noexcept
{
  return impl_ptr_->array_.getSize();
}

std::string CompositeShape::getName() const
{
  return "CompositeShape";
}

std::shared_ptr<Shape> CompositeShape::operator[](const size_t &index) const
{
  if (index > impl_ptr_->array_.getSize())
  {
    throw std::invalid_argument("CompositeShape smaller");
  }
  return impl_ptr_->array_[index];
}

bool operator==(const CompositeShape & comp1, const CompositeShape & comp2)
{
  if(comp1.impl_ptr_->array_.getSize() == comp2.impl_ptr_->array_.getSize())
  { 
    for(size_t i = (comp1.impl_ptr_->array_.getSize() - 1);
      comp1.impl_ptr_->array_[i] == comp2.impl_ptr_->array_[i]; 
      i--)
    {
      if(i == 0)
      {
       return true; 
      }
    }
    return false;
  }
  else
  {
    return false;
  }
}

std::ostream& operator<<(std::ostream& out, const CompositeShape &out_shape)
{
  out_shape.print(out);
  return out;
}
