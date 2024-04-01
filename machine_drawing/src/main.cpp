
#include "../hdr/clipper.hpp"
#include "../hdr/obj_parser.hpp"
#include <array>
#include <iostream>
static const int WIDTH = 800;
static const int HEIGHT = 800;

int main() {

  cv::Mat img(HEIGHT, WIDTH, CV_8UC1);

  // ObjParser parser;
  // parser.parse(img, "african_head.obj", "test.obj");

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}