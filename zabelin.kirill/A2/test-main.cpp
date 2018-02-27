#define BOOST_TEST_MODULE mytest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

BOOST_AUTO_TEST_CASE(test_invalid_argument_rectangle)
{
  BOOST_CHECK_THROW(Rectangle rect({2, 2},-1, 3), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_circle)
{
  BOOST_CHECK_THROW(Circle cir({2, 2}, -10), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_invalid_argument_triangle)
{
  BOOST_CHECK_THROW(Triangle tri({0, 0}, {5, 5}, {10, 10}), std::invalid_argument);
};

BOOST_AUTO_TEST_CASE(test_move_point_rectange)
{
  Rectangle rect({1,1}, 10, 14.5);
  const rectangle_t frame_rect = rect.getFrameRect();
  rect.move({100, -100});
  BOOST_CHECK_CLOSE(frame_rect.height, rect.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rect.width, rect.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_circle)
{
  Circle cir({0,0}, 7);
  const rectangle_t frame_cir = cir.getFrameRect();
  cir.move({100, -100});
  BOOST_CHECK_CLOSE(frame_cir.width, cir.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_triangle)
{
  Triangle tri({1,1}, {2,10}, {0,0});
  const point_t tri_vertex[3] = { tri.getPosVertexA(), tri.getPosVertexB(), tri.getPosVertexC() };
  tri.move({100, -100});
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[0].x - tri_vertex[1].x) * (tri_vertex[0].x - tri_vertex[1].x) 
        + (tri_vertex[0].y - tri_vertex[1].y) * (tri_vertex[0].y - tri_vertex[1].y)), 
      sqrt((tri.getPosVertexA().x - tri.getPosVertexB().x) * (tri.getPosVertexA().x - tri.getPosVertexB().x) 
        + (tri.getPosVertexA().y - tri.getPosVertexB().y) * (tri.getPosVertexA().y - tri.getPosVertexB().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[1].x - tri_vertex[2].x) * (tri_vertex[1].x - tri_vertex[2].x) 
        + (tri_vertex[1].y - tri_vertex[2].y) * (tri_vertex[1].y - tri_vertex[2].y)), 
      sqrt((tri.getPosVertexB().x - tri.getPosVertexC().x) * (tri.getPosVertexB().x - tri.getPosVertexC().x) 
        + (tri.getPosVertexB().y - tri.getPosVertexC().y) * (tri.getPosVertexB().y - tri.getPosVertexC().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[2].x - tri_vertex[0].x) * (tri_vertex[2].x - tri_vertex[0].x) 
        + (tri_vertex[2].y - tri_vertex[0].y) * (tri_vertex[2].y - tri_vertex[0].y)), 
      sqrt((tri.getPosVertexA().x - tri.getPosVertexC().x) * (tri.getPosVertexA().x - tri.getPosVertexC().x) 
        + (tri.getPosVertexA().y - tri.getPosVertexC().y) * (tri.getPosVertexA().y - tri.getPosVertexC().y)), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_rectange_area)
{
  Rectangle rect({1,1}, 10, 14.5);
  const double area_rect = rect.getArea();
  rect.move({1,1});
  BOOST_CHECK_CLOSE(area_rect, rect.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_circle_area)
{
  Circle cir({0,0}, 7);
  const double area_cir = cir.getArea();
  cir.move({1,1});
  BOOST_CHECK_CLOSE(area_cir, cir.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_point_triangle_area)
{
  Triangle tri({1,1}, {2,10}, {0,0});
  const double area_tri = tri.getArea();
  tri.move({1,1});
  BOOST_CHECK_CLOSE(area_tri, tri.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_rectange)
{
  Rectangle rect({1,1}, 10, 14.5);
  const rectangle_t frame_rect = rect.getFrameRect();
  rect.move(-11, 4);
  BOOST_CHECK_CLOSE(frame_rect.height, rect.getFrameRect().height, 0.001);
  BOOST_CHECK_CLOSE(frame_rect.width, rect.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_circle)
{
  Circle cir({0,0}, 7);
  const rectangle_t frame_cir = cir.getFrameRect();
  cir.move(10, -6);
  BOOST_CHECK_CLOSE(frame_cir.width, cir.getFrameRect().width, 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_triangle)
{
  Triangle tri({1,1}, {2,10}, {0,0});
  const point_t tri_vertex[3] = { tri.getPosVertexA(), tri.getPosVertexB(), tri.getPosVertexC() };
  tri.move(-1,0);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[0].x - tri_vertex[1].x) * (tri_vertex[0].x - tri_vertex[1].x) 
        + (tri_vertex[0].y - tri_vertex[1].y) * (tri_vertex[0].y - tri_vertex[1].y)), 
      sqrt((tri.getPosVertexA().x - tri.getPosVertexB().x) * (tri.getPosVertexA().x - tri.getPosVertexB().x) 
        + (tri.getPosVertexA().y - tri.getPosVertexB().y) * (tri.getPosVertexA().y - tri.getPosVertexB().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[1].x - tri_vertex[2].x) * (tri_vertex[1].x - tri_vertex[2].x) 
        + (tri_vertex[1].y - tri_vertex[2].y) * (tri_vertex[1].y - tri_vertex[2].y)), 
      sqrt((tri.getPosVertexB().x - tri.getPosVertexC().x) * (tri.getPosVertexB().x - tri.getPosVertexC().x) 
        + (tri.getPosVertexB().y - tri.getPosVertexC().y) * (tri.getPosVertexB().y - tri.getPosVertexC().y)), 0.001);
  BOOST_CHECK_CLOSE(sqrt((tri_vertex[2].x - tri_vertex[0].x) * (tri_vertex[2].x - tri_vertex[0].x) 
        + (tri_vertex[2].y - tri_vertex[0].y) * (tri_vertex[2].y - tri_vertex[0].y)), 
      sqrt((tri.getPosVertexA().x - tri.getPosVertexC().x) * (tri.getPosVertexA().x - tri.getPosVertexC().x) 
        + (tri.getPosVertexA().y - tri.getPosVertexC().y) * (tri.getPosVertexA().y - tri.getPosVertexC().y)), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_rectange_area)
{
  Rectangle rect({1,1}, 10, 14.5);
  const double area_rect = rect.getArea();
  rect.move(1,1);
  BOOST_CHECK_CLOSE(area_rect, rect.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_circle_area)
{
  Circle cir({0,0}, 7);
  const double area_cir = cir.getArea();
  cir.move(1,1);
  BOOST_CHECK_CLOSE(area_cir, cir.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_move_delta_triangle_area)
{
  Triangle tri({1,1}, {2,10}, {0,0});
  const double area_tri = tri.getArea();
  tri.move(1,1);
  BOOST_CHECK_CLOSE(area_tri, tri.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_scale_rectangle_area)
{
  Rectangle rect({1,1}, 10, 14.5);
  const double area_rect = rect.getArea(), scale = 2;
  rect.scale(scale);
  BOOST_CHECK_CLOSE(area_rect * scale * scale, rect.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_scale_circle_area)
{
  Circle cir({0,0}, 7);
  const double area_cir = cir.getArea(), scale = 0.3;
  cir.scale(scale);
  BOOST_CHECK_CLOSE(area_cir * scale * scale, cir.getArea(), 0.001);
}

BOOST_AUTO_TEST_CASE(test_scale_triangle_area)
{
  Triangle tri({1,1}, {2,10}, {0,0});
  const double area_tri = tri.getArea(), scale = 10;
  tri.scale(scale);
  BOOST_CHECK_CLOSE(area_tri * scale * scale, tri.getArea(), 0.001);
}
