#include <fstream>
#include <sstream>
#include <string>

#include "../hdr/bresenhamLine.hpp"

static const int WIDTH = 800;
static const int HEIGHT = 600;

int main() {
  std::ifstream input("african_head.obj");
  std::ofstream output("test.obj");
  cv::Mat img(HEIGHT, WIDTH, CV_8UC1);

  if (input.is_open()) {
    std::string kindOfInfo;
    std::string coordinate_x1;
    std::string coordinate_y1;
    std::string coordinate_x2;
    std::string coordinate_y2;
    int x1 = WIDTH + 1;
    int y1 = HEIGHT + 1;
    int x2 = WIDTH + 1;
    int y2 = HEIGHT + 1;
    std::string line;
    while (std::getline(input, line)) {
      std::istringstream iss(line);
      iss >> kindOfInfo;

      if (kindOfInfo == "v") {
        iss >> coordinate_x2 >> coordinate_y2;

        double x2_ = std::stod(coordinate_x2) * WIDTH / 2;
        double y2_ = std::stod(coordinate_y2) * HEIGHT / 2;
        x2 = std::round(x2_);
        y2 = std::round(y2_);

        if (x1 != WIDTH + 1) {
          bresenhamLine(
              img, cv::Point2i(WIDTH / 2 + x1, HEIGHT - (HEIGHT / 2 + y1)),
              cv::Point2i(WIDTH / 2 + x2, HEIGHT - (HEIGHT / 2 + y2)));
        }
        std::cout << x2 << " " << y2 << "\n";
        x1 = x2;
        y1 = y2;

      } else
        break;
    }
  }
  input.close();
  output.close();

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}