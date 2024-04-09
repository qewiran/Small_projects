#include "../hdr/shape.hpp"
#include "../hdr/line_algorithm.hpp"

std::ostream &operator<<(std::ostream &stream, const Triangle &t) {
  stream << t.v1 << " " << t.v2 << " " << t.v3;
  return stream;
}

void drawTriangle(cv::Mat img, const Triangle &t) {
  bresenhamLine(img, t.v1, t.v2, 255);
  bresenhamLine(img, t.v2, t.v3, 255);
  bresenhamLine(img, t.v1, t.v3, 255);

}

void drawRectangle(cv::Mat img, const cv::Rect &r) {
  bresenhamLine(img, r.br(), r.br() - cv::Point2i(r.width, 0), 255);
  bresenhamLine(img, r.br() - cv::Point(r.width, 0), r.tl(), 255);
  bresenhamLine(img, r.tl(), r.tl() + cv::Point2i(r.width, 0), 255);
  bresenhamLine(img, r.tl() + cv::Point2i(r.width, 0), r.br(), 255);
}