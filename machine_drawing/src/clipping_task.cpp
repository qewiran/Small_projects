#include "../hdr/shape.hpp"
#include "../hdr/clipper.hpp"
#include "../hdr/obj_parser.hpp"
#include "opencv2/highgui.hpp"
static const int WIDTH = 1280;
static const int HEIGHT = 720;

int main() {
  std::pair<cv::Point2i, cv::Point2i> lineForRect{cv::Point2i(90,200), cv::Point2i(300,200)};
  std::pair<cv::Point2i, cv::Point2i> lineForTri{cv::Point2i(525,540), cv::Point2i(500,300)};

  cv::Mat img(HEIGHT, WIDTH, CV_8UC1);
  // Rectangle<cv::Point2i> clipRect(
  //     {cv::Point2i(100, 100), cv::Point2i(400, 100), cv::Point2i(400, 400),
  //      cv::Point2i(100, 400) });
  // clipRect.draw(img,240);
  // auto normalsRect = getNormals(clipRect);
  // CBlineClip(img, clipRect, normalsRect, lineForRect.first, lineForRect.second,
  //            false);
  Polygon<3, cv::Point2i> clipTri(
      {cv::Point2i(500, 500), cv::Point2i(600, 600), cv::Point2i(550, 700)});
  clipTri.draw(img,155);
  auto normalsTri = getNormals(clipTri);
  // CBlineClip(img, clipTri, normalsTri, lineForTri.first, lineForTri.second,
  //            false);
  Polygon<3,cv::Point2i> tri(
      {cv::Point2i(550,550), cv::Point2i(600,700), cv::Point2i(400,500)}
      );
  tri.draw(img, 200);
  CBpolygonClip(img, clipTri, tri);

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}
