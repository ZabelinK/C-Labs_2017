#define BOOST_TEST_MODULE testCompositeShape

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "compositeshape.hpp"

BOOST_AUTO_TEST_CASE(not_correct_construcor)
{
  std::shared_ptr<Shape>shape = nullptr;
  BOOST_CHECK_THROW(CompositeShape comp(shape) , std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(constructor_comp_shape_rectangle)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 0, 0 }, 100, 10);
  CompositeShape comp(rect);
  BOOST_CHECK(rect->getFrameRect() == comp.getFrameRect());
}

BOOST_AUTO_TEST_CASE(constructor_comp_shape_circle)
{
  auto cir = std::make_shared<Circle>(point_t{ 10, -10 }, 11);
  CompositeShape comp(cir);
  BOOST_CHECK(cir->getFrameRect() == comp.getFrameRect());
}

BOOST_AUTO_TEST_CASE(constructor_comp_shape_tringle)
{
  auto tri = std::make_shared<Triangle>(point_t{ 0, 0 }, point_t{ 10, 8 }, point_t{ -9, 4 });
  CompositeShape comp(tri);
  BOOST_CHECK(tri->getFrameRect() == comp.getFrameRect());
}

BOOST_AUTO_TEST_CASE(compositeshape_rectangle)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 11, 13 }, 10, 1);
  CompositeShape comp(rect);
  BOOST_CHECK(comp[0] == rect);
}

BOOST_AUTO_TEST_CASE(compositeshape_circle)
{
  auto cir = std::make_shared<Circle>(point_t{ 11, 13 }, 10);
  CompositeShape comp(cir);
  BOOST_CHECK(comp[0] == cir);
}

BOOST_AUTO_TEST_CASE(compositeshape_triangle)
{
  auto tri = std::make_shared<Triangle>(point_t{ 0, 0 }, point_t{ 10, 8 }, point_t{ -9, 4 });
  CompositeShape comp(tri);
  BOOST_CHECK(comp[0] == tri);
}

BOOST_AUTO_TEST_CASE(not_correct_addShape)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 11, 13 }, 10, 1);
  CompositeShape comp(rect);
  std::shared_ptr<Shape> shape = nullptr;
  BOOST_CHECK_THROW(comp.addShape(shape), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(add_compositeshape_rectangle)
{
  auto rect_one = std::make_shared<Rectangle>(point_t{ 11, 13 }, 10, 1);
  CompositeShape comp(rect_one);
  auto rect_two = std::make_shared<Rectangle>(point_t{ 1, 1 }, 10, 1);
  comp.addShape(rect_two);
  BOOST_CHECK(comp[1] == rect_two);
}

BOOST_AUTO_TEST_CASE(add_compositeshape_circle)
{
  auto cir_one = std::make_shared<Circle>(point_t{ 11, 13 }, 10);
  CompositeShape comp(cir_one);
  auto cir_two = std::make_shared<Circle>(point_t{ 1, 1 }, 10);
  comp.addShape(cir_two);
  BOOST_CHECK(comp[1] == cir_two);
}

BOOST_AUTO_TEST_CASE(add_compositeshape_triangle)
{
  auto tri_one = std::make_shared<Triangle>(point_t{ 0, 0 }, point_t{ 10, 8 }, point_t{ -9, 4 });
  CompositeShape comp(tri_one);
  auto tri_two = std::make_shared<Triangle>(point_t{ 0, 0 }, point_t{ 10, 8 }, point_t{ -9, 4 });
  comp.addShape(tri_two);
  BOOST_CHECK(comp[1] == tri_two);
}

BOOST_AUTO_TEST_CASE(add_compositeshape_rectangle_frame_rect)
{
  auto rect_one = std::make_shared<Rectangle>(point_t{ 0,0 }, 2, 2);
  CompositeShape comp(rect_one);
  auto rect_two = std::make_shared<Rectangle>(point_t{ 2,0 }, 2, 4);
  comp.addShape(rect_two);
  rectangle_t frame_rect = { { 1,0 },4,4 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(add_compositeshape_circle_frame_rect)
{
  auto cir_one = std::make_shared<Circle>(point_t{ 0,0 }, 2);
  CompositeShape comp(cir_one);
  auto cir_two = std::make_shared<Circle>(point_t{ 2,0 }, 2);
  comp.addShape(cir_two);
  rectangle_t frame_rect = { { 1,0 },6,4 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(add_compositeshape_triangle_frame_rect)
{
  auto tri_one = std::make_shared<Triangle>(point_t{ 0,0 }, point_t{ 1,1 }, point_t{ 6,0 });
  CompositeShape comp(tri_one);
  auto tri_two = std::make_shared<Triangle>(point_t{ 0,0 }, point_t{ 1,1 }, point_t{ 0,6 });
  comp.addShape(tri_two);
  rectangle_t frame_rect = { { 3,3 },6,6 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(area_compositeshape)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  BOOST_CHECK_CLOSE(rect->getArea() + tri->getArea() + cir->getArea(), comp.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(move_absolutely_compositeshape)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);;
  rectangle_t frame_rect = comp.getFrameRect();
  comp.move({ 100, -100 });
  BOOST_CHECK_CLOSE(frame_rect.height, comp.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rect.width, comp.getFrameRect().width, 0.001);
  BOOST_CHECK(frame_rect.pos != comp.getFrameRect().pos);
}

BOOST_AUTO_TEST_CASE(move_relatively_compositeshape)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  rectangle_t frame_rect = comp.getFrameRect();
  comp.move(10, 40);
  BOOST_CHECK_CLOSE(frame_rect.height, comp.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rect.width, comp.getFrameRect().width, 0.001);
  BOOST_CHECK(frame_rect.pos != comp.getFrameRect().pos);
}

BOOST_AUTO_TEST_CASE(move_absolutely_compositeshape_area)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  comp.move({ 10, -100 });
  BOOST_CHECK_CLOSE(rect->getArea() + tri->getArea() + cir->getArea(), comp.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(move_relatively_compositeshape_area)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  comp.move(10, -100);
  BOOST_CHECK_CLOSE(rect->getArea() + tri->getArea() + cir->getArea(), comp.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(scale_compositeshape_one)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  rectangle_t frame_rect = comp.getFrameRect();
  comp.scale(10);
  BOOST_CHECK_CLOSE(frame_rect.height * 10, comp.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rect.width * 10, comp.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(scale_compositeshape_two)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  rectangle_t frame_rect = comp.getFrameRect();
  comp.scale(0.4);
  BOOST_CHECK_CLOSE(frame_rect.height * 0.4, comp.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rect.width * 0.4, comp.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(scale_compositeshape_area_one)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  double area = comp.getArea();
  comp.scale(5);
  BOOST_CHECK_CLOSE(area * 25, comp.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(scale_compositeshape_area_two)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  double area = comp.getArea();
  comp.scale(0.1);
  BOOST_CHECK_CLOSE(area * 0.01, comp.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(scale_not_correct_compositeshape)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 10, 5);
  auto cir = std::make_shared<Circle>(point_t{ -5,3 }, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 10, 2 }, point_t{ -3, 2 }, point_t{ -2, -2 });
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.addShape(tri);
  BOOST_CHECK_THROW(comp.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(relation_rectangle)
{
  auto rect1 = std::make_shared<Rectangle>(point_t{ 1,1 }, 2, 4);
  auto rect2 = std::make_shared<Rectangle>(point_t{ 2,2 }, 2, 2);
  CompositeShape comp(rect1);
  comp.addShape(rect2);
  rect2->move({ 3,3 });
  rectangle_t frame_rect = { { 2,1.5 },4,5 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(relation_circle)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 2, 4);
  auto cir = std::make_shared<Circle>(point_t{ 2,2 }, 1);
  CompositeShape comp(rect);
  comp.addShape(cir);
  cir->move({ 3,3 });
  rectangle_t frame_rect = { { 2,1.5 },4,5 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(relation_triangle)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 2, 4);
  auto tri = std::make_shared<Triangle>(point_t{ 3,3 }, point_t{ 5,3 },point_t { 5,1 });
  CompositeShape comp(rect);
  comp.addShape(tri);
  tri->move(1, 0);
  rectangle_t frame_rect = { { 3,1 },6,4 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(two_comp)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 1,1 }, 2, 4);
  CompositeShape comp1(rect);
  CompositeShape comp2(rect);
  BOOST_CHECK(comp1[0] == comp2[0]);
}
