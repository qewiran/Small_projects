#include "../hdr/shape.hpp"
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
  // 
  cv::Rect2i clipRect(cv::Point2i(100,100), cv::Point(400,400));
  
  drawRectangle(img, clipRect);
  LBclip(img, clipRect, cv::Point2i(0,0), cv::Point2i(300,600));
  // bresenhamLine(img,  cv::Point2i(0,0), cv::Point2i(600,600));
  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}
