#ifndef H_BASE_TYPES
#define H_BASE_TYPES
struct point_t {
  double x, y;
};
  
struct rectangle_t {
  point_t pos;
  double height, width;
};
#endif
