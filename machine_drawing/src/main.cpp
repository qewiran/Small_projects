#include "../hdr/shape.hpp"
#include "../hdr/clipper.hpp"
#include "../hdr/obj_parser.hpp"
static const int WIDTH = 1280;
static const int HEIGHT = 720;

int main() {

  cv::Mat img(HEIGHT, WIDTH, CV_8UC1);

  Rectangle<cv::Point2i> clipRect(
      {cv::Point2i(100, 100), cv::Point2i(100, 400), cv::Point2i(400, 400),
       cv::Point2i(400, 100) });
  clipRect.draw(img,240);
  auto normalsRect = getNormals(clipRect);
  CBclip(img, clipRect, normalsRect, cv::Point2i(0,0), cv::Point2i(200,700));

  Polygon<3,cv::Point2i> clipTri(
      {cv::Point2i(500, 500), cv::Point2i(500, 700), cv::Point2i(600, 600)});
  clipTri.draw(img,240);
  auto normalsTri = getNormals(clipTri);
  CBclip(img,clipTri, normalsTri,cv::Point2i(200,300), cv::Point2i(700,700));

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}
