#include "line_algorithm.hpp"
#include "shape.hpp"
#include <boost/multi_index/indexed_by.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/composite_key.hpp>
// #include <sys/types.h>

using boost::multi_index_container;
using namespace boost::multi_index;

static double eps = 1e-14;

void LBclip(cv::Mat img, const Rectangle<cv::Point2i> &clipRect, cv::Point2i p1,
            cv::Point2i p2);

struct CBlineParams {
  double tIn, tOut;
  bool out;
};

CBlineParams CBclip(cv::Point2i p1, cv::Point2i p2, cv::Point2i windowPoint,
                    cv::Point2i normal, double tIn, double tOut);

template <size_t winVertCount>
std::array<cv::Point2i, winVertCount>
getNormals(const Polygon<winVertCount> &window) {
  std::array<cv::Point2i, winVertCount> result{};

  for (size_t i = 1; i <= winVertCount; ++i) {
    cv::Point2i dp;
    if (i != winVertCount) {
      dp = window.at(i) - window.at(i - 1);
    } else {
      dp = -window.at(i - 1) + window.at(0);
    }
      result.at(i - 1) = cv::Point2i(-dp.y, dp.x);
  }

  return result;
};

template <size_t winVertCount>
CBlineParams
CBlineClip(cv::Mat img, const Polygon<winVertCount, cv::Point2i> &window,
           const std::array<cv::Point2i, winVertCount> &normals, cv::Point2i p1,
           cv::Point2i p2, bool needIntersection = false) {
  double tIn = 0;
  double tOut = 1;
  auto windowPointIt = window.cbegin();
  auto polyEnd = window.cend();
  auto normalIt = normals.cbegin();

  for (; windowPointIt != polyEnd; ++windowPointIt, ++normalIt) {
    auto params = CBclip(p1, p2, *windowPointIt, *normalIt, tIn, tOut);
    if (params.tIn < -eps  || params.tOut < -eps)
      break;
    tIn = params.tIn;
    tOut = params.tOut;
  }
  bresenhamLine(img,p1,p2,255);
  if (!needIntersection)
    bresenhamLine(img, p1 + tIn * (p2 - p1), p1 + tOut * (p2 - p1), 255);
  return {tIn, tOut};
};

template <size_t winVertCount, size_t polyVertCount>
void CBpolygonClip(cv::Mat img,
                   const Polygon<winVertCount, cv::Point2i> &window,
                   const Polygon<polyVertCount, cv::Point2i> &polygon) {
  auto normals = getNormals(window);
  auto polygonPoint1It = polygon.cbegin();
  auto polygonPoint2It = polygon.cbegin() + 1;
  auto polyEnd = polygon.cend();
  multi_index_container<
      cv::Point2i,
      indexed_by<random_access<>,
                 ordered_unique<composite_key<
                     cv::Point2i, member<cv::Point2i, int, &cv::Point2i::x>,
                     member<cv::Point2i, int, &cv::Point2i::y>>>>>
      polygonList;
  for (; polygonPoint1It != polyEnd; ++polygonPoint1It, ++polygonPoint2It) {
    if (polygonPoint2It==polyEnd)
    {
      polygonPoint2It=polygon.cbegin();
    }
    auto params = CBlineClip(img, window, normals, *polygonPoint1It,
                             *polygonPoint2It, true);
    auto tIn = params.tIn;
    auto tOut = params.tOut;

    polygonList.push_back(*polygonPoint1It);
    polygonList.push_back(cv::Point2i(
        *polygonPoint1It + tIn * (*polygonPoint2It - *polygonPoint1It)));
    polygonList.push_back(cv::Point2i(
        *polygonPoint1It + tOut * (*polygonPoint2It - *polygonPoint1It)));
  }
  
  for (auto v : polygonList)
    std::cout << '[' << v.x << " , " << v.y << ']' << '\n';
};
