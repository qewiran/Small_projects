#ifndef COLORED_IMAGE_HPP
#define COLORED_IMAGE_HPP
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
class ColorImage;

template <typename T>
std::ostream& operator<< (std::ostream& os, const ColorImage<T>& img)
{
    std::for_each(img.resource.begin(), img.resource.end(), [&](const vector<Point<T>>& row)
        {
            std::for_each(row.begin(), row.end(), [&](Point<T> point)
                {
                    os << point << ' ';
                });
            os << "\n";
        });
    return os;
}


template <typename T>
class ColorImage
{
protected:
    vector <vector <Point<T>>> resource;

public:
    ColorImage() = default;

    ColorImage(size_t rows, size_t cols)
    {
        resource.resize(rows, vector<Point<T>>(cols));
        if (rows < resource.capacity() || cols < resource[0].capacity())
            resource.shrink_to_fit();
    }

    ColorImage(const vector<vector<Point<T>>>& init_resource) : resource(init_resource) {}

    friend std::ostream& operator << <T>(std::ostream& os, const ColorImage<T>& img);
};




#endif