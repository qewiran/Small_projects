#include "../hdr/shape.hpp"
#include "../hdr/clipper.hpp"
// #include "../hdr/obj_parser.hpp"
#include "opencv2/highgui.hpp"
static const int WIDTH = 1280;
static const int HEIGHT = 720;

int main() {
  std::pair<cv::Point2i, cv::Point2i> lineForRect{cv::Point2i(90,200), cv::Point2i(300,225)};
  std::pair<cv::Point2i, cv::Point2i> lineForTri{cv::Point2i(525,540), cv::Point2i(500,300)};
  std::pair<cv::Point2i, cv::Point2i> lineForTri2{cv::Point2i(450,450), cv::Point2i(475,700)};

  cv::Mat img(HEIGHT, WIDTH, CV_8UC1);
  Rectangle<cv::Point2i> clipRect(
      {cv::Point2i(100, 100), cv::Point2i(100, 400), cv::Point2i(400, 400),
       cv::Point2i(400, 100) });
  clipRect.draw(img, 155);
  auto normalsRect = getNormals(clipRect);
  for (auto n : normalsRect)
    std::cout << n << "\n";
  CBlineClip(img, clipRect, normalsRect, lineForRect.first, lineForRect.second,
             false);

  // Polygon<5, cv::Point2i> polygon({cv::Point2i(300, 300), cv::Point2i(500, 300),
  //                                  cv::Point2i(500, 150), cv::Point2i(300, 150),
  //                                  cv::Point2i(440, 230)});
  // polygon.draw(img,255);
  // CBpolygonClip(img, clipRect, polygon );
  Polygon<3, cv::Point2i> clipTri(
      {cv::Point2i(500, 500), cv::Point2i(600, 600), cv::Point2i(500, 700)});
  clipTri.draw(img,155);
  auto normalsTri = getNormals(clipTri);
  for (auto n:normalsTri) std::cout<< n<< "\n";
  CBlineClip(img, clipTri, normalsTri, lineForTri.first, lineForTri.second,
             false);
  CBlineClip(img, clipTri, normalsTri, lineForTri2.first, lineForTri2.second,
             false);
  // Polygon<3,cv::Point2i> tri(
  //     {cv::Point2i(500,500), cv::Point2i(600,600), cv::Point2i(400,500)}
  //     );
  // tri.draw(img, 200);
  // CBpolygonClip(img, clipTri, tri);

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}
