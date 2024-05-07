#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include "opencv2/core/mat.hpp"
#include <fstream>
#include <string>

class ObjParser {

  std::ifstream input;
  std::ofstream output;

public:
  std::vector<cv::Point2i> vertices;

  void parse(cv::Mat, const std::string &, const std::string &);
};
#endif // OBJ_PARSER_HPP
