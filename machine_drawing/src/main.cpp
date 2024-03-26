
#include "../hdr/Triangle.hpp"
#include "../hdr/bresenhamLine.hpp"
#include "../hdr/objParser.hpp"

static const int WIDTH = 800;
static const int HEIGHT = 800;

int main() {

  std::ifstream input("african_head.obj");
  std::ofstream output("test.obj");
  cv::Mat img(HEIGHT, WIDTH, CV_8UC1);

  if (input.is_open()) {
    std::vector<cv::Point2i> vertices;
    vertices.emplace_back(0, 0);

    std::string kindOfInfo;

    std::string coordinate_x;
    std::string coordinate_y;

    std::string index_v1;
    std::string index_v2;
    std::string index_v3;

    int x, y;

    int v1_idx;
    int v2_idx;
    int v3_idx;

    std::string line;
    while (std::getline(input, line)) {
      std::istringstream iss(line);
      iss >> kindOfInfo;

      if (kindOfInfo == "v") {
        iss >> coordinate_x >> coordinate_y;

        double x_ = std::stod(coordinate_x) * WIDTH / 2.;
        double y_ = std::stod(coordinate_y) * HEIGHT / 2.;

        x = WIDTH / 2 + std::round(x_);
        y = HEIGHT - (HEIGHT / 2 + std::round(y_));
        vertices.emplace_back(x, y);

      }
      if (kindOfInfo == "f") {

        iss >> index_v1 >> index_v2 >> index_v3;

        v1_idx = std::stoi(index_v1.substr(0, index_v1.find_first_of('/')));
        v2_idx = std::stoi(index_v2.substr(0, index_v2.find_first_of('/')));
        v3_idx = std::stoi(index_v3.substr(0, index_v3.find_first_of('/')));

        drawTriangle(img, Triangle(vertices[v1_idx], vertices[v2_idx],
                                   vertices[v3_idx]));
                                   
        output << Triangle(vertices[v1_idx], vertices[v2_idx], vertices[v3_idx])
               << '\n';
      }
    }
  }
  input.close();
  output.close();

  cv::namedWindow("TEST", cv::WINDOW_GUI_NORMAL);
  cv::imshow("TEST", img);
  cv::waitKey(0);
}