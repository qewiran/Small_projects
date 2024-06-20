#include <opencv2/core/matx.hpp>
#include <transform.hpp> 
#include <line_algorithm.hpp>
#include <opencv2/highgui.hpp>
#include <obj_parser.hpp>
#include <shape.hpp>
#include <fill.hpp>
static const size_t WIDTH = 1000;
static const size_t HEIGHT = 1000;
static const size_t DEPTH = 1000;
int main() {
  cv::Mat img(HEIGHT,WIDTH, CV_8UC1);
  ObjParser parser;
  std::string inpath = "/home/qewiran/Documents/repos/math_uni_projects/machine_drawing/src/african_head.obj";
  parser.parse(img, inpath, HEIGHT, WIDTH, DEPTH);

  auto itV = std::next(parser.vertices.begin());
  auto itDraw = std::next(parser.vertDraw.begin()); 
  auto end = parser.vertices.end();


  for (; itV != end; ++itV, ++itDraw) {
    cv::Matx<double, 3, 1> tmp(itV->x, itV->y, itV->z);
    TransformMatx<double, 4, 1> vec(tmp, 1);
    // std::cout<<vec<<" \n";
    vec = perspectiveProj(vec, ProjCategory::PERSPECTIVE_1P, 2 ,  500. );
    // vec = vec.scale({1, 0.7 ,0.5});
    vec *= 1 / (1+ vec(3));
    itV->x = vec(0);
    itV->y = vec(1);
    itV->z = vec(2);

    // vec = vec.rotate(30,0,2);
    // itV->x = vec(0);
    // itV->y = vec(1);
    // itV->z = vec(2);
    // std::cout<<vec<<"\n ---- \n";

    // std::cout<<itDraw->x<<' '<<itDraw->y<<"\n ---- \n";
    itDraw->x = WIDTH / 2. + itV->x;
    itDraw->y = HEIGHT / 2. - itV->y;

    if (itDraw->x > 1000 || itDraw->y>1000 || itDraw->x<0 || itDraw->y<0)
    {
      std::cout<<itDraw->x<<' '<<itDraw->y<<'\n';
      return 0;
    }
  }
  parser.draw(img);

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}
