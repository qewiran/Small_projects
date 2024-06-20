#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include <opencv2/core/mat.hpp>
#include <fstream>
#include <string>

class ObjParser {

  std::ifstream input;
  std::ofstream output;

public:
  std::vector<cv::Point3i> vertices;
  std::vector<cv::Point2i> vertDraw;
  std::vector<std::array<size_t,3>> connectIdx;

  void parse(cv::Mat, const std::string&, size_t, size_t, size_t);
  void draw(cv::Mat);
};
#endif // OBJ_PARSER_HPP
