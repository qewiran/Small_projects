
#include "../hdr/line_algorithm.hpp"

void bresenhamLineUp(cv::Mat img, cv::Point2i p1, cv::Point2i p2) {
  int dx = p2.x - p1.x;
  int dy = p2.y - p1.y;

  int x = p1.x;

  int x_step = 1;
  int y_step = 1;

  if (dx < 0) {
    x_step *= -1;
    dx *= -1;
  }

  int D = 2 * dx - dy;

  for (int y = p1.y; y < p2.y; y += y_step) {
    img.at<u_char>(y, x) = 255;
    if (D > 0) {
      x += x_step;
      D += 2 * (dx - dy);
    } else
      D += 2 * dx;
  }
}

void bresenhamLineDown(cv::Mat img, cv::Point2i p1, cv::Point2i p2) {
  int dx = p2.x - p1.x;
  int dy = p2.y - p1.y;

  int y = p1.y;

  int x_step = 1;
  int y_step = 1;

  if (dy < 0) {
    y_step *= -1;
    dy *= -1;
  }

  int D = 2 * dy - dx;

  for (int x = p1.x; x < p2.x; x += x_step) {
    img.at<u_char>(y, x) = 255;
    if (D > 0) {
      y += y_step;
      D += 2 * (dy - dx);
    } else
      D += 2 * dy;
  }
}

void bresenhamLine(cv::Mat img, cv::Point2i p1, cv::Point2i p2) {
  int y2 = p2.y;
  int y1 = p1.y;
  int x2 = p2.x;
  int x1 = p1.x;

  if (std::abs(y2 - y1) < std::abs(x2 - x1)) {
    if (x1 > x2)
      bresenhamLineDown(img, p2, p1);
    else
      bresenhamLineDown(img, p1, p2);
  } else {
    if (y1 > y2)
      bresenhamLineUp(img, p2, p1);
    else
      bresenhamLineUp(img, p1, p2);
  }
}

void dda(cv::Mat img, cv::Point2i p1, cv::Point2i p2) {
  int dx = p2.x - p1.x;
  int dy = p2.y - p1.y;

  double y = p1.y;
  double x = p1.x;

  int steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

  double x_increment = static_cast<double>(dx) / steps;
  double y_increment = static_cast<double>(dy) / steps;

  for (size_t i = 0; i < steps; ++i) {

    img.at<uchar>(std::round(y), std::round(x)) = 255;
    x += x_increment;
    y += y_increment;
  }
}
