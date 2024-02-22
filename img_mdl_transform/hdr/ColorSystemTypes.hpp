#ifndef COLOR_SYSTEM_TYPES_HPP
#define COLOR_SYSTEM_TYPES_HPP
#include "ColorImage.hpp"

using std::vector;

const std::vector<double>
D65_StandartIlluminant = { 95.04f, 100.f, 108.883f };


class XYZ;
class Lab;
class HSV;
class HLS;

class RGB : public ColorImage<u_char>
{
public:
    RGB() = default;
    RGB(const vector<vector<Point<u_char>>>& init_resource) :
        ColorImage<u_char>(init_resource) {}

    explicit operator XYZ() const;
    explicit operator HSV() const;
    explicit operator HLS() const;
    explicit operator Lab() const;
};


class XYZ : public ColorImage<double>
{
public:
    XYZ() = default;
    XYZ(const vector<vector<Point<double>>>& init_resource) :
        ColorImage<double>(init_resource) {}
    explicit operator RGB() const;
    explicit operator HSV() const;
    explicit operator HLS() const;
    explicit operator Lab() const;

};

class HLS : public ColorImage <double>
{
public:
    HLS() = default;
    HLS(const vector<vector<Point<double>>>& init_resource) :
        ColorImage<double>(init_resource) {}
    explicit operator RGB() const;
    explicit operator HSV() const;
    explicit operator XYZ() const;
    explicit operator Lab() const;
};

class HSV : public ColorImage<double>
{
public:
    HSV() = default;
    HSV(const vector<vector<Point<double>>>& init_resource) :
        ColorImage<double>(init_resource) {}
    explicit operator RGB() const;
    explicit operator XYZ() const;
    explicit operator HLS() const;
    explicit operator Lab() const;
};

class Lab : public ColorImage<double>
{
public:
    Lab() = default;
    Lab(const vector<vector<Point<double>>>& init_resource) :
        ColorImage<double>(init_resource) {}
    explicit operator RGB() const;
    explicit operator HSV() const;
    explicit operator HLS() const;
    explicit operator XYZ() const;
};

#endif