#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include "../hdr/shape.hpp"
#include "../hdr/line_algorithm.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <fstream>
#include <sstream>
#include <string>

class ObjParser {

  std::ifstream input;
  std::ofstream output;

public:
  std::vector<cv::Point2i> vertices;

  // ObjParser(const std::string &inPath, const std::string &outPath)
  //     : input(inPath), output(outPath) {}

  void parse(cv::Mat, const std::string &, const std::string &);
};
#endif