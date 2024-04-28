#include "../hdr/clipper.hpp"
#include "../hdr/line_algorithm.hpp"
#include "../hdr/shape.hpp"

static const double EPS = 1e-14;
void LBclip(cv::Mat img, const Rectangle<>& clipRect, cv::Point2i point1,
            cv::Point2i point2) {
  double p1 = -(point2.x - point1.x);
  double p2 = -p1;
  double p3 = -(point1.y - point2.y);
  double p4 = -p3;

  double q1 = point1.x - clipRect.tl().x;
  double q2 = clipRect.br().x - point1.x;
  double q3 = point1.y - clipRect.br().y;
  double q4 = clipRect.tl().y - point1.y;

  std::vector<double> pos;
  std::vector<double> neg;
  pos.push_back(1.);
  neg.push_back(0.);

  if (std::abs(p1) > EPS) {
    double r1 = q1 / p1;
    double r2 = q2 / p2;
    if (p1 < 0) {
      neg.push_back(r1);
      pos.push_back(r2);
    } else {
      neg.push_back(r2);
      pos.push_back(r1);
    }
  }
  if (std::abs(p3) > EPS) {
    double r3 = q3 / p3;
    double r4 = q4 / p4;
    if (p3 < 0) {
      neg.push_back(r3);
      pos.push_back(r4);
    } else {
      neg.push_back(r4);
      pos.push_back(r3);
    }
  }

  double xn1, yn1, xn2, yn2;
  double rn1, rn2;

  rn1 = *std::max_element(neg.cbegin(), neg.cend());
  rn2 = *std::min_element(pos.cbegin(), pos.cend());

  xn1 = std::abs(point1.x + p2 * rn1);
  yn1 = std::abs(point1.y + p4 * rn1);

  xn2 = std::abs(point1.x + p2 * rn2);
  yn2 = std::abs(point1.y + p4 * rn2);
  
  bresenhamLine(img, cv::Point2i(xn1, yn1), cv::Point2i(xn2, yn2), 255);
  bresenhamLine(img, point1, cv::Point2i(xn1, yn1), 100);
  bresenhamLine(img, cv::Point2i(xn2, yn2), point2, 100);
}


