#include <fill.hpp>
#include <obj_parser.hpp>
#include <shape.hpp>
#include <sstream>
#include <string>

void ObjParser::parse(cv::Mat img, const std::string &inPath, size_t HEIGHT,
                      size_t WIDTH, size_t DEPTH) {
  input.open(inPath);

  if (input.is_open()) {
    vertices.clear();
    vertices.emplace_back(-1, -1, -1);
    vertDraw.emplace_back(-1, -1);

    std::string kindOfInfo;

    std::string coordinate_x;
    std::string coordinate_y;
    std::string coordinate_z;

    std::string index_v1;
    std::string index_v2;
    std::string index_v3;

    int x_d, y_d, z_d;

    size_t v1_idx;
    size_t v2_idx;
    size_t v3_idx;

    std::string line;
    while (std::getline(input, line)) {
      std::istringstream iss(line);
      iss >> kindOfInfo;

      if (kindOfInfo == "v") {
        iss >> coordinate_x >> coordinate_y >> coordinate_z;

        double x_ = std::stod(coordinate_x) * WIDTH / 2;
        double y_ = std::stod(coordinate_y) * HEIGHT / 2;
        double z_ = std::stod(coordinate_z) * DEPTH / 2;

        x_d = WIDTH / 2. + std::round(x_);
        y_d = HEIGHT / 2. - std::round(y_);
        vertices.emplace_back(x_, y_, z_);
        vertDraw.emplace_back(x_d, y_d);
      }
      if (kindOfInfo == "f") {

        iss >> index_v1 >> index_v2 >> index_v3;

        v1_idx = std::stoi(index_v1.substr(0, index_v1.find_first_of('/')));
        v2_idx = std::stoi(index_v2.substr(0, index_v2.find_first_of('/')));
        v3_idx = std::stoi(index_v3.substr(0, index_v3.find_first_of('/')));
        connectIdx.push_back({v1_idx, v2_idx, v3_idx});
      }
    }
    input.close();
  }
}

void ObjParser::draw(cv::Mat img) {

  for (auto idxs : connectIdx) {
    size_t v1_idx = idxs[0], v2_idx = idxs[1], v3_idx = idxs[2];

    Polygon<3, cv::Point2i> tmp({vertDraw[v1_idx],vertDraw[v2_idx],vertDraw[v3_idx],});
    tmp.draw(img, 255);
    // fill(img,tmp,std::rand()%255);
  }
}
