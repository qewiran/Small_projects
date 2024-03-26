#include "../hdr/Triangle.hpp"
#include "../hdr/bresenhamLine.hpp"

std::ostream &operator<<(std::ostream &stream, const Triangle &t) {
  stream << t.v1 << " " << t.v2 << " " << t.v3;
  return stream;
}


void drawTriangle(cv::Mat img, const Triangle &t) {
  bresenhamLine(img, t.v1, t.v2);
  bresenhamLine(img, t.v2, t.v3);
  bresenhamLine(img, t.v1, t.v3);
}