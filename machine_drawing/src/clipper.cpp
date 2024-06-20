#include <clipper.hpp>
#include <line_algorithm.hpp>
#include <shape.hpp>

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
static const double EPS = 1e-14;
// this function gives the maximum
float maxi(float arr[],int n) {
  float m = 0;
  for (int i = 0; i < n; ++i)
    if (m < arr[i])
      m = arr[i];
  return m;
}

// this function gives the minimum
float mini(float arr[], int n) {
  float m = 1;
  for (int i = 0; i < n; ++i)
    if (m > arr[i])
      m = arr[i];
  return m;
}
void LBclip(cv::Mat img, const Rectangle<> &clipRect, cv::Point2i pointOut,
            cv::Point2i point2) {
//   double p1 = -(point2.x - pointOut.x);
//   double p2 = -p1;
//   double p3 = -(point2.y - pointOut.y);
//   double p4 = -p3;
//
//   double q1 = pointOut.x - clipRect.tl().x;
//   double q2 = clipRect.br().x - pointOut.x;
//   double q3 = pointOut.y - clipRect.tl().y;
//   double q4 = clipRect.tl().y - pointOut.y;
//
//   std::vector<double> pos(5);
// std::vector<double> neg(5);
//   int posind = 1, negind = 1;
//   pos[0] = 1;
//   neg[0] = 0;
  // pos.push_back(1.);
  // neg.push_back(0.);
  //
  // if (std::abs(p1) > EPS) {
  //   double r1 = q1 / p1;
  //   double r2 = q2 / p2;
  //   if (p1 < 0) {
  //     neg.push_back(r1);
  //     pos.push_back(r2);
  //   } else {
  //     neg.push_back(r2);
  //     pos.push_back(r1);
  //   }
  // }
  // if (std::abs(p3) > EPS) {
  //   double r3 = q3 / p3;
  //   double r4 = q4 / p4;
  //   if (p3 < 0) {
  //     neg.push_back(r3);
  //     pos.push_back(r4);
  //   } else {
  //     neg.push_back(r4);
  //     pos.push_back(r3);
  //   }
  // }
  //
  //


  // double xn1, yn1, xn2, yn2;
  // double rn1, rn2;
  //
  // rn1 = *std::max_element(neg.cbegin(), neg.cend());
  // rn2 = *std::min_element(pos.cbegin(), pos.cend());
  //
  // xn1 = (pointOut.x + p2 * rn1);
  // yn1 = (pointOut.y + p4 * rn1);
  //
  // xn2 = (pointOut.x + p2 * rn2);
  // yn2 = (pointOut.y + p4 * rn2);
  // 
  // std::cout << pointOut.x << ' ' << pointOut.y << " " << point2.x << ' '
  //           << point2.y << '\n';
  // std::cout << xn1 << " " << yn1 << '\n';
  // std::cout<<xn2<<" "<<yn2<<'\n';
  // bresenhamLine(img,pointOut,point2, 100);
  // bresenhamLine(img, cv::Point2i(xn1, yn1), cv::Point2i(xn2, yn2), 255);
  int x2 = point2.x;
  int x1 = pointOut.x;
  int y2 = point2.y;
  int y1 = pointOut.y;
  int xmin = clipRect.tl().x;
  int ymin = clipRect.tl().y;
  int xmax = clipRect.br().x;
  int ymax = clipRect.br().y;
  float p1 = -(x2 - x1);
  float p2 = -p1;
  float p3 = -(y2 - y1);
  float p4 = -p3;

  float q1 = x1 - xmin;
  float q2 = xmax - x1;
  float q3 = y1 - ymin;
  float q4 = ymax - y1;

  float posarr[5], negarr[5];
  int posind = 1, negind = 1;
  posarr[0] = 1;
  negarr[0] = 0;

  if (p1 != 0) {
    float r1 = q1 / p1;
    float r2 = q2 / p2;
    if (p1 < 0) {
      negarr[negind++] = r1; // for negative p1, add it to negative array
      posarr[posind++] = r2; // and add p2 to positive array
    } else {
      negarr[negind++] = r2;
      posarr[posind++] = r1;
    }
  }
  if (p3 != 0) {
    float r3 = q3 / p3;
    float r4 = q4 / p4;
    if (p3 < 0) {
      negarr[negind++] = r3;
      posarr[posind++] = r4;
    } else {
      negarr[negind++] = r4;
      posarr[posind++] = r3;
    }
  }

  float xn1, yn1, xn2, yn2;
  float rn1, rn2;
  rn1 = maxi(negarr, negind); // maximum of negative array
  rn2 = mini(posarr, posind); // minimum of positive array


  xn1 = x1 + p2 * rn1;
  yn1 = y1 + p4 * rn1; // computing new points

  xn2 = x1 + p2 * rn2;
  yn2 = y1 + p4 * rn2;

  std::cout<<xn1<<' '<<yn1<<'\n';
  bresenhamLine(img, pointOut, point2, 100);
  bresenhamLine(img,cv::Point2i(xn1,yn1),cv::Point2i(xn2,yn2), 255);
}

int computeCode(cv::Point2i p, const Rectangle<cv::Point2i> &clipRect) {
  int x_left = clipRect.tl().x;
  int x_right = clipRect.br().x;
  int y_top = clipRect.tl().y;
  int y_bot = clipRect.br().y;
  int code = INSIDE;

  if (p.x < x_left) // to the left of rectangle
    code |= LEFT;
  else if (p.x > x_right) // to the right of rectangle
    code |= RIGHT;
  if (p.y < y_bot) // below the rectangle
    code |= BOTTOM;
  else if (p.y > y_top) // above the rectangle
    code |= TOP;

  return code;
}
bool CSclip(cv::Mat img, const Rectangle<cv::Point2i> &clipRect, cv::Point2i p1,
            cv::Point2i p2) {
  int x_left = clipRect.tl().x;
  int x_right = clipRect.br().x;
  int y_top = clipRect.br().y;
  int y_bot = clipRect.tl().y;
  int code1 = computeCode(p1, clipRect);
  int code2 = computeCode(p2, clipRect);
  bresenhamLine(img, p1, p2, 100);
  std::cout<<"["<<p1.x<<", "<<p1.y<<"]"<<' ';
  std::cout<<"["<<p2.x<<", "<<p2.y<<"]"<<'\n';

  bool visible = false;
  while (1) {
    if (code1 == 0 && code2 == 0) {
      visible = true;
      break;
    } else if ((code1 & code2)!=0) {
      break;
    } else {
      int code_out;
      double x, y;
      if (code1 != 0)
        code_out = code1;
      else
        code_out = code2;

      if (code_out & TOP) {
        x = p1.x + (p2.x - p1.x) * (y_top - p1.y) / (p2.y - p1.y);
        y = y_top;
      } else if (code_out & BOTTOM) {
        x = p1.x + (p2.x - p1.x) * (y_bot - p1.y) / (p2.y - p1.y);
        y = y_bot;
      } else if (code_out & LEFT) {
        y = p1.y + (p2.y - p1.y) * (x_left - p1.x) / (p2.x - p1.x);
        x = x_left;
      } else if (code_out & RIGHT) {
        y = p1.y + (p2.y - p1.y) * (x_right - p1.x) / (p2.x - p1.x);
        x = x_right;
      }
      if (code_out == code1) {
        p1 = cv::Point2i(x, y);
        code1 = computeCode(p1, clipRect);
      } else {
        p2 = cv::Point2i(x, y);
        code2 = computeCode(p2, clipRect);
      }
    }
  }
  std::cout<<"["<<p1.x<<", "<<p1.y<<"]"<<' ';
  std::cout<<"["<<p2.x<<", "<<p2.y<<"]"<<'\n';
    bresenhamLine(img, p1,p2 , 255);
  return visible;
}

CBlineParams CBclip(cv::Point2i p1, cv::Point2i p2, cv::Point2i windowPoint,
                    cv::Point2i normal, double tIn, double tOut) {

  double Q = (p1 - windowPoint).dot(normal);
  double P = (p2 - p1).dot(normal);
  bool visible = true;
  if (std::abs(P) < eps) {
    if (Q < eps)
      return {-1., -1., false};

  } else {
    double t = -Q / P;
    if (P < 0.) {

      if (t < tIn) {
        visible = false;
        return {tIn, tOut, visible};
      }
      tOut = std::min(t, tOut);
    } else {

      if (t > tOut) {
        visible = false;
        return {tIn, tOut, visible};
      }
      tIn = std::max(t, tIn);
    }
  }
  return {tIn, tOut, visible};
};
