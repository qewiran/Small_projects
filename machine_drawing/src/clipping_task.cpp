#include "../hdr/shape.hpp"
#include "../hdr/clipper.hpp"
// #include "../hdr/obj_parser.hpp"
#include "opencv2/highgui.hpp"
#include <fill.hpp>
static const int WIDTH = 1280;
static const int HEIGHT = 720;

int main() {
  cv::Mat img(HEIGHT, WIDTH, CV_8UC1);
  Rectangle<cv::Point2i> clipRect(
      {cv::Point2i(100, 400), cv::Point2i(400, 400), cv::Point2i(400, 100),
       cv::Point2i(100, 100) });
  clipRect.draw(img, 155);
  auto normalsRect = getNormals(clipRect);
 Polygon<5, cv::Point2i> polygon({cv::Point2i(300, 300), cv::Point2i(500, 300),
                                   cv::Point2i(500, 150), cv::Point2i(300, 150),
                                   cv::Point2i(440, 230)});
  CBpolygonClip(img, clipRect, polygon );

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}
