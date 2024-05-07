#include "../hdr/transform.hpp"
#include "opencv2/core.hpp"
#include <iostream>
static const size_t WIDTH = 1280;
static const size_t HEIGHT = 720;
int main() {
  TransformColVec<double, 4> vec({1., 0., 0.}, 1.);
  std::cout<<axonometricProj(vec, ProjCategory::AXON_DIMETRIC);

  // cv::Mat img(WIDTH, HEIGHT, CV_8UC1);
  // cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  // cv::imshow("TEST", img);
  // cv::waitKey(0);
}
