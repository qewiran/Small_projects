#include "../hdr/shape.hpp"
#include "../hdr/line_algorithm.hpp"

std::ostream &operator<<(std::ostream &stream, const Triangle &t) {
  stream << t.v1 << " " << t.v2 << " " << t.v3;
  return stream;
}

void drawTriangle(cv::Mat img, const Triangle &t) {
  bresenhamLine(img, t.v1, t.v2);
  bresenhamLine(img, t.v2, t.v3);
  bresenhamLine(img, t.v1, t.v3);

  // dda(img, t.v1, t.v2);
  // dda(img, t.v2, t.v3);
  // dda(img, t.v1, t.v3);
}

void drawRectangle(cv::Mat img, const cv:: Rect &r){
  bresenhamLine(img, r.br(),r.br()-cv::Point2i(r.width,0));
  bresenhamLine(img, r.br()-cv::Point(r.width,0),r.tl());
  bresenhamLine(img, r.tl(), r.tl()+cv::Point2i(r.width,0));
  bresenhamLine(img, r.tl()+cv::Point2i(r.width,0), r.br());
}