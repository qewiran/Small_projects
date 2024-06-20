#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <line_algorithm.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <shape.hpp>

using boost::multi_index_container;
using namespace boost::multi_index;

enum class PointType { in, out, vertex };

struct Point {
  int x;
  int y;
  PointType type;
};

using MultiIndexList = multi_index_container<
    Point,
    indexed_by<random_access<>, ordered_unique<composite_key<
                                    Point, key<&Point::x>, key<&Point::y>>>>>;
static double eps = 1e-14;

void LBclip(cv::Mat img, const Rectangle<cv::Point2i> &clipRect, cv::Point2i p1,
            cv::Point2i p2);

struct CBlineParams {
  double tIn, tOut;
  bool visible;
};

bool CSclip(cv::Mat img, const Rectangle<cv::Point2i> &clipRect, cv::Point2i p1, cv::Point2i p2);
CBlineParams CBclip(cv::Point2i p1, cv::Point2i p2, cv::Point2i windowPoint,
                    cv::Point2i normal, double tIn, double tOut);

template <size_t winVertCount>
std::array<cv::Point2i, winVertCount>
getNormals(const Polygon<winVertCount> &window) {
  std::array<cv::Point2i, winVertCount> result{};

  for (size_t i = 1; i <= winVertCount; ++i) {
    cv::Point2i dp;
    if (i != winVertCount) {
      dp = -window.at(i) + window.at(i - 1);
    } else {
      dp = window.at(i - 1) - window.at(0);
    }
    result.at(i - 1) = cv::Point2i(-dp.y, dp.x);
  }

  return result;
};

template <size_t winVertCount, typename Cont>
CBlineParams CBlineClip(cv::Mat img, const Cont &window,
                        const std::array<cv::Point2i, winVertCount> &normals,
                        cv::Point2i p1, cv::Point2i p2,
                        bool needToDraw = false) {
  double tIn = 0;
  double tOut = 1;
  bool visible = true;
  auto windowPointIt = window.cbegin();
  auto windowEnd = window.cend();
  auto normalIt = normals.cbegin();

  for (; windowPointIt != windowEnd; ++windowPointIt, ++normalIt) {
    auto params = CBclip(p1, p2, *windowPointIt, *normalIt, tIn, tOut);
    visible = params.visible;
    if (params.visible == false) {
      break;
    }
    tIn = params.tIn;
    tOut = params.tOut;
  }
  bresenhamLine(img, p1, p2, 100);
  if (visible && needToDraw)
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
  auto windowIt = window.cbegin();

  MultiIndexList polygonList;
  MultiIndexList windowList;
  for (; polygonPoint1It != polyEnd; ++polygonPoint1It, ++polygonPoint2It) {
    if (polygonPoint2It == polyEnd) {
      polygonPoint2It = polygon.cbegin();
    }
    auto params = CBlineClip(img, window, normals, *polygonPoint1It,
                             *polygonPoint2It, false);
    auto tIn = params.tIn;
    auto tOut = params.tOut;
    polygonList.push_back(
        {polygonPoint1It->x, polygonPoint1It->y, PointType::vertex});
    windowList.push_back({windowIt->x, windowIt->y, PointType::vertex});
    auto pIn = *polygonPoint1It + tIn * (*polygonPoint2It - *polygonPoint1It);
    auto pOut = *polygonPoint1It + tOut * (*polygonPoint2It - *polygonPoint1It);
    if (tIn > eps) {
      polygonList.push_back({pIn.x, pIn.y, PointType::in});
      windowList.push_back({pIn.x, pIn.y, PointType::in});
    }
    if (tIn < 1.) {
      polygonList.push_back({pOut.x, pOut.y, PointType::out});
      windowList.push_back({pOut.x, pOut.y, PointType::out});
    }
    if (windowIt != window.cend())
      ++windowIt;
  }

  auto winListIt = windowList.cbegin();
  auto winListEnd = windowList.cend();
  auto polyListIt = polygonList.cbegin();
  auto polyListEnd = polygonList.cend();
  bool change = false;
  while (polyListIt != polyListEnd) {
    if (polyListIt->type == PointType::in) {
      change = true;
    }
    if (winListIt->type == PointType::in) {
      change = false;
      bresenhamLine(img, {polyListIt->x, polyListIt->y},
                    {winListIt->x, winListIt->y}, 255);
    }
    if (change) {
      ++winListIt;
    } else
      ++polyListIt;
  }
  for (auto v : polygonList)
    std::cout << '[' << v.x << " , " << v.y << ']' << '\n';
  std::cout << "\n";
  for (auto v : windowList)
    std::cout << '[' << v.x << " , " << v.y << ']' << '\n';
};
