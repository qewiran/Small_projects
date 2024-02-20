#ifndef COLOR_SYSTEM_TYPES_HPP
#define COLOR_SYSTEM_TYPES_HPP
#include "ColoredImage.hpp"

using std::vector;

const std::vector<double>
D65_StandartIlluminant = { 95.04f, 100.f, 108.883f };


class XYZ;
class Lab;
class HSV;
class HSL;

class RGB : public ColoredImage<u_char>
{
public:
    RGB() = default;
    RGB(const vector<vector<Point<u_char>>>& init_resource) :
        ColoredImage<u_char>(init_resource) {}

    operator XYZ() const;
    operator HSV() const;
    operator HSL() const;
    operator Lab() const;
};


class XYZ : public ColoredImage<double>
{
public:
    XYZ() = default;
    XYZ(const vector<vector<Point<double>>>& init_resource) :
        ColoredImage<double>(init_resource) {}
    operator RGB() const;
    operator HSV() const;
    operator HSL() const;
    operator Lab() const;

};

class HSL : public ColoredImage <double>
{
public:
    HSL() = default;
    HSL(const vector<vector<Point<double>>>& init_resource) :
        ColoredImage<double>(init_resource) {}
    operator RGB() const;
    operator HSV() const;
    operator XYZ() const;
    operator Lab() const;
};

class HSV : public ColoredImage<double>
{
public:
    HSV() = default;
    HSV(const vector<vector<Point<double>>>& init_resource) :
        ColoredImage<double>(init_resource) {}
    operator RGB() const;
    operator XYZ() const;
    operator HSL() const;
    operator Lab() const;
};

class Lab : public ColoredImage<double>
{
public:
    Lab() = default;
    Lab(const vector<vector<Point<double>>>& init_resource) :
        ColoredImage<double>(init_resource) {}
    operator RGB() const;
    operator HSV() const;
    operator HSL() const;
    operator XYZ() const;
};

#endif