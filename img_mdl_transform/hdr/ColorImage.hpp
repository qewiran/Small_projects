#ifndef COLOR_IMAGE_HPP
#define COLOR_IMAGE_HPP
#include <vector>
#include <iostream>
#include <tuple>
#include <memory>
#include <algorithm>
#include <cstdint>
#include <cmath>
using std::vector;

template <typename T>
class Point;

template <typename T>
std::ostream& operator<< (std::ostream& os, const Point<T>& point)
{
    os << '[' << +(point.val1) << ", " << +(point.val2) << ", " << +(point.val3) << ']';
    return os;
}

template <typename T>
class Point
{
protected:
    T val1; T val2; T val3;
public:
    Point() :
        val1(static_cast<T>(0)), val2(static_cast<T>(0)), val3(static_cast<T>(0)) {}

    Point(T val1, T val2, T val3) : val1(val1), val2(val2), val3(val3) {}
    Point(const Point& other_point) : val1(other_point.val1), val2(other_point.val2), val3(other_point.val3) {}

    operator std::tuple<T, T, T>() const
    {
        return std::make_tuple(val1, val2, val3);
    }

    Point<T>& operator= (const Point& other)
    {
        if (this != &other)
        {
            val1 = other.val1;
            val2 = other.val2;
            val3 = other.val3;
        }
        return *this;
    }

    Point<T>& operator= (const std::tuple<T, T, T>& t)
    {
        val1 = std::get<0>(t);
        val2 = std::get<1>(t);
        val3 = std::get<2>(t);
        return *this;
    }

    friend std::ostream& operator << <T>(std::ostream& os, const Point<T>& point);
};

template <typename T>
class Point4;

template <typename T>
std::ostream& operator<< (std::ostream& os, const Point4<T>& point)
{
    os << '[' << +(point.val1) << ", " << +(point.val2) << ", " << +(point.val3) << ", " << +(point.val4) << ']';
    return os;
}

template <typename T>
class Point4 :protected Point<T>
{
    T val4;
public:
    Point4() : val4(static_cast<T>(0)) {}
    Point4(const Point4& other_point) :Point<T>(other_point), val4(other_point.val4) {}
    Point4(T val1, T val2, T val3, T val4) : Point<T>(val1, val2, val3), val4(val4) {}

    operator std::tuple<T, T, T, T>() const
    {
        return std::make_tuple(this->val1, this->val2, this->val3, val4);
    }
    friend std::ostream& operator << <T>(std::ostream& os, const Point4<T>& point);
};

template <typename T, template <typename> typename PointType>
class ColorImage;

template <typename T, template <typename> typename PointType>
std::ostream& operator<< (std::ostream& os, const ColorImage<T, PointType>& img)
{
    std::for_each(img.resource.begin(), img.resource.end(), [&](const vector<PointType<T>>& row)
        {
            std::for_each(row.begin(), row.end(), [&](PointType<T> point)
                {
                    os << point << ' ';
                });
            os << "\n";
        });
    return os;
}


template < typename T, template <typename> typename PointType = Point>
class ColorImage
{
protected:
    vector <vector <PointType<T>>> resource;

public:
    ColorImage() {}

    ColorImage(size_t rows, size_t cols)
    {
        resource.resize(rows, vector<PointType<T>>(cols));
        if (rows < resource.capacity() || cols < resource[0].capacity())
            resource.shrink_to_fit();
    }

    ColorImage(const vector<vector<PointType<T>>>& init_resource) : resource(init_resource) {}

    friend std::ostream& operator << <T, PointType>(std::ostream& os, const ColorImage<T, PointType>& img);
};

#endif