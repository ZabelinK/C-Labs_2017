
#define BOOST_TEST_MODULE testPolygonAndMatrixShape

#define _USE_MATH_DEFINES
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "compositeshape.hpp"
#include "polygon.hpp"
#include "matrixshape.hpp"

BOOST_AUTO_TEST_CASE(polygon_throw_null)
{
  point_t *points = nullptr;
  BOOST_CHECK_THROW(Polygon pol(points, 2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(polygon_throw_size)
{
  point_t points[] = { { 2,5 },{ 10,3 } };
  BOOST_CHECK_THROW(Polygon pol(points, 2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(polygon_throw_convex)
{
  point_t points[] = { { 2,1 },{ 3,5 },{ 5,6 },{ 9,5 },{ 5,4 },{ 3,3 } };
  BOOST_CHECK_THROW(Polygon pol(points, 6), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(polygon_throw_zero_area)
{
  point_t points[] = { { 1,1 },{ 2,2 },{ 3,3 },{ 4,4 },{ 5,5 } };
  BOOST_CHECK_THROW(Polygon pol(points, 5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(polygon_construcor_out_of_order)
{
  point_t points[] = { { 2,1 },{ 5,6 },{ 3,5 },{ 9,5 },{ 4,1 } };
  BOOST_CHECK_NO_THROW(Polygon pol(points, 5));
}

BOOST_AUTO_TEST_CASE(polygon_construcor_temp)
{
  point_t points[] = { { 2,1 },{ 3,5 },{ 5,6 },{ 9,5 },{ 4,1 } };
  BOOST_CHECK_NO_THROW(Polygon pol(points));
}

BOOST_AUTO_TEST_CASE(polygon_construcor_order)
{
  point_t points[] = { { 2,1 },{ 3,5 },{ 5,6 },{ 9,5 },{ 4,1 } };
  BOOST_CHECK_NO_THROW(Polygon pol(points, 5));
}

BOOST_AUTO_TEST_CASE(polygon_construcor_copy)
{
  point_t points[] = { { 2,1 },{ 3,5 },{ 5,6 },{ 9,5 },{ 4,1 } };
  Polygon pol_c(points, 5);
  BOOST_CHECK_NO_THROW(Polygon pol(pol_c));
}

BOOST_AUTO_TEST_CASE(polygon_construcor_oper_copy)
{
  point_t points_c[] = { { 2,1 },{ 3,5 },{ 5,6 },{ 9,5 },{ 4,1 } };
  Polygon pol_c(points_c, 5);
  point_t points[] = { { 1,1 },{ 1,5 },{ 5,5 },{ 5,1 } };
  Polygon pol(points, 4);
  BOOST_CHECK_NO_THROW(pol = pol_c);
}


BOOST_AUTO_TEST_CASE(polygon_area)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  BOOST_CHECK_CLOSE(pol.getArea(), 34, 0.001);
}

BOOST_AUTO_TEST_CASE(polygon_frameRect)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  rectangle_t frame_rect = { { 5,4 },6,6 };
  BOOST_CHECK(pol.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(polygon_scale_throw)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  BOOST_CHECK_THROW(pol.scale(-3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(polygon_scale_more_one)
{
  point_t points[] = { { 4,3 },{ 4,7 },{ 8,8 },{ 8,2 } };
  Polygon pol(points, 4);
  rectangle_t frame_rect = { { 6,5 }, 12, 18 };
  pol.scale(3);
  BOOST_CHECK(pol.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(polygon_scale_more_one_area)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  pol.scale(3);
  BOOST_CHECK_CLOSE(pol.getArea(), 34 * 3 * 3, 0.001);
}

BOOST_AUTO_TEST_CASE(polygon_scale_less_one)
{
  point_t points[] = { { 4,3 },{ 4,7 },{ 8,8 },{ 8,2 } };
  Polygon pol(points, 4);
  rectangle_t frame_rect = { { 6,5 }, 2, 3 };
  pol.scale(0.5);
  BOOST_CHECK(pol.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(polygon_scale_less_one_area)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  pol.scale(0.5);
  BOOST_CHECK_CLOSE(pol.getArea(), 34 * 0.5 * 0.5, 0.001);
}

BOOST_AUTO_TEST_CASE(polygon_move_abs)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  pol.move({ 10,20 });
  BOOST_CHECK_CLOSE(pol.getFrameRect().height, 6, 0.001);
  BOOST_CHECK_CLOSE(pol.getFrameRect().width, 6, 0.001);
  BOOST_CHECK_CLOSE(pol.getArea(), 34, 0.001);
}

BOOST_AUTO_TEST_CASE(polygon_move_rel)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  pol.move(10, 2);
  BOOST_CHECK_CLOSE(pol.getFrameRect().height, 6, 0.001);
  BOOST_CHECK_CLOSE(pol.getFrameRect().width, 6, 0.001);
  BOOST_CHECK_CLOSE(pol.getArea(), 34, 0.001);
}

BOOST_AUTO_TEST_CASE(rectangle_turn_counter_clockwise)
{
  Rectangle rect({ 3,3 }, 4, 4);
  rect.turn(45);
  rectangle_t frame_rect = { { 3,3 }, 8 * sin(45 * M_PI / 180), 8 * sin(45 * M_PI / 180) };
  BOOST_CHECK(rect.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(rectangle_turn_clockwise)
{
  Rectangle rect({ 3,3 }, 4, 4);
  rect.turn(-45);
  rectangle_t frame_rect = { { 3,3 }, 8 * sin(45 * M_PI / 180), 8 * sin(45 * M_PI / 180) };
  BOOST_CHECK(rect.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(rectangle_turn_area)
{
  Rectangle rect({ 3,3 }, 4, 4);
  double area = rect.getArea();
  rect.turn(45);
  BOOST_CHECK_CLOSE(area, rect.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(circle_turn_counter_clockwise)
{
  Circle cir({ 2,2 }, 7);
  rectangle_t frame_rect = cir.getFrameRect();
  cir.turn(33);
  BOOST_CHECK(cir.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(circle_turn_clockwise)
{
  Circle cir({ 2,2 }, 7);
  rectangle_t frame_rect = cir.getFrameRect();
  cir.turn(-40);
  BOOST_CHECK(cir.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(circle_turn_area)
{
  Circle cir({ 3,3 }, 4);
  double area = cir.getArea();
  cir.turn(60);
  BOOST_CHECK_CLOSE(area, cir.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(triangle_turn_counter_clockwise)
{
  Triangle tri({ 3,1 }, { 6,1 }, { 6,7 });
  tri.turn(90);
  rectangle_t frame_rect = { { 4, 2.5 },6,3 };
  BOOST_CHECK(tri.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(triangle_turn_clockwise)
{
  Triangle tri({ 3,1 }, { 6,1 }, { 6,7 });
  tri.turn(-90);
  rectangle_t frame_rect = { { 6, 3.5 },6,3 };
  BOOST_CHECK(tri.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(triangle_turn_area)
{
  Triangle tri({ 2,1 }, { 4,1 }, { 4,5 });
  double area = tri.getArea();
  tri.turn(-45);
  BOOST_CHECK_CLOSE(area, tri.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(polygon_turn_counter_clockwise)
{
  point_t points[] = { { 4,3 },{ 4,7 },{ 8,8 },{ 8,2 } };
  Polygon pol(points, 4);
  rectangle_t frame_rect = { { 6,5 }, 6, 4 };
  pol.turn(90);
  BOOST_CHECK(pol.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(polygon_turn_clockwise)
{
  point_t points[] = { { 4,3 },{ 4,7 },{ 8,8 },{ 8,2 } };
  Polygon pol(points, 4);
  rectangle_t frame_rect = { { 6,5 }, 6, 4 };
  pol.turn(-90);
  BOOST_CHECK(pol.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(polygon_turn_area)
{
  point_t points[] = { { 2,1 },{ 2,5 },{ 4,7 },{ 8,7 },{ 8,1 } };
  Polygon pol(points, 5);
  double area = pol.getArea();
  pol.turn(60);
  BOOST_CHECK_CLOSE(area, pol.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(compositeshape_turn_counter_clockwise)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 6,3 }, 4, 2);
  auto cir = std::make_shared<Circle>(point_t{ 3,3 }, 1);
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.turn(90);
  rectangle_t frame_rect = { { 5,3 },2,6 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(compositeshape_turn_clockwise)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 6,3 }, 4, 2);
  auto cir = std::make_shared<Circle>(point_t{ 3,3 }, 1);
  CompositeShape comp(rect);
  comp.addShape(cir);
  comp.turn(-90);
  rectangle_t frame_rect = { { 5,3 },2,6 };
  BOOST_CHECK(comp.getFrameRect() == frame_rect);
}

BOOST_AUTO_TEST_CASE(compositeshape_turn_area)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 6,3 }, 4, 2);
  auto cir = std::make_shared<Circle>(point_t{ 3,3 }, 1);
  CompositeShape comp(rect);
  comp.addShape(cir);
  double area = comp.getArea();
  comp.turn(490);
  BOOST_CHECK_CLOSE(area, comp.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(matrixshape_constructor)
{
  Rectangle rect({ 6,3 }, 4, 2);
  MatrixShape mat(&rect);
  BOOST_CHECK(mat[0][0] == &rect);
}

BOOST_AUTO_TEST_CASE(matrixshape_new_lines)
{
  Rectangle rect({ 6,3 }, 4, 2);
  Triangle tri({ 7, 1 }, { 7, 5 }, { 10, 3 });
  MatrixShape mat(&rect);
  mat.addShape(&tri);
  BOOST_CHECK(mat[1][0] == &tri);
}

BOOST_AUTO_TEST_CASE(matrixshape_new_columns)
{
  Rectangle rect({ 6,3 }, 4, 2);
  Triangle tri({ 7, 1 }, { 7, 5 }, { 10, 3 });
  point_t points[] = { { 2,1 },{ 2,5 },{ 6,6 },{ 4,1 } };
  Polygon pol(points, 4);
  MatrixShape mat(&rect);
  mat.addShape(&tri);
  mat.addShape(&pol);
  BOOST_CHECK(mat[1][1] == &pol);
}

BOOST_AUTO_TEST_CASE(matrixshape_null)
{
  Rectangle rect({ 6,3 }, 4, 2);
  Triangle tri({ 7, 1 }, { 7, 5 }, { 10, 3 });
  point_t points[] = { { 2,1 },{ 2,5 },{ 6,6 },{ 4,1 } };
  Polygon pol(points, 4);
  MatrixShape mat(&rect);
  mat.addShape(&tri);
  mat.addShape(&pol);
  BOOST_CHECK(mat[0][1] == nullptr);
}

BOOST_AUTO_TEST_CASE(matrixshape_new_shape)
{
  Rectangle rect({ 6,3 }, 4, 2);
  Circle cir({ -10,-5 }, 1);
  Triangle tri({ 7, 1 }, { 7, 5 }, { 10, 3 });
  point_t points[] = { { 2,1 },{ 2,5 },{ 6,6 },{ 4,1 } };
  Polygon pol(points, 4);
  MatrixShape mat(&rect);
  mat.addShape(&tri);
  mat.addShape(&pol);
  mat.addShape(&cir);
  BOOST_CHECK(mat[0][1] == &cir);
}

BOOST_AUTO_TEST_CASE(matrixshape_composite)
{
  auto rect = std::make_shared<Rectangle>(point_t{ 6,3 }, 4, 2);
  auto cir = std::make_shared<Circle>(point_t{ 3,3 }, 1);
  CompositeShape comp(rect);
  comp.addShape(cir);
  MatrixShape mat(&comp);
  BOOST_CHECK(&comp == mat[0][0]);
}
