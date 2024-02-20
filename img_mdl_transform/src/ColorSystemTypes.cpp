#include "../hdr/ColorSystemTypes.hpp"

using std::vector;

static const double EPS = 1e-6;

RGB::operator XYZ () const
{
    vector<vector<Point<double>>> newValuesResource;
    newValuesResource.reserve(resource.size());

    std::for_each(resource.begin(), resource.end(), [&](const std::vector<Point<u_char>> row) {
        vector<Point<double>> newRow; newRow.reserve(row.size());

        std::for_each(row.begin(), row.end(), [&](Point<u_char> point) {

            std::tuple<u_char, u_char, u_char> point_tuple = static_cast<std::tuple<u_char, u_char, u_char>>(point);

            double r = static_cast<double>(std::get<0>(point_tuple));
            double g = static_cast<double>(std::get<1>(point_tuple));
            double b = static_cast<double>(std::get<2>(point_tuple));

            double x = 0.412453 * r + 0.357780 * g + 0.180423 * b;
            double y = 0.212671 * r + 0.715160 * g + 0.072169 * b;
            double z = 0.019334 * r + 0.119193 * g + 0.950227 * b;

            newRow.emplace_back(x, y, z);
            });
        newValuesResource.emplace_back(newRow);
        });
    return XYZ(newValuesResource);
}

RGB::operator HSV () const
{
    vector<vector<Point<double>>> newValuesResource;
    newValuesResource.reserve(resource.size());

    std::for_each(resource.begin(), resource.end(), [&](const std::vector<Point<u_char>> row) {
        vector<Point<double>> newRow; newRow.reserve(row.size());

        std::for_each(row.begin(), row.end(), [&](Point<u_char> point) {

            std::tuple<u_char, u_char, u_char> point_tuple = static_cast<std::tuple<u_char, u_char, u_char>>(point);

            double r = static_cast<double>(std::get<0>(point_tuple)); r /= 255.;
            double g = static_cast<double>(std::get<1>(point_tuple)); g /= 255.;
            double b = static_cast<double>(std::get<2>(point_tuple)); b /= 255.;

            double v = std::max(r, std::max(g, b));

            double c = std::min(r, std::min(g, b));
            double s = (std::abs(v - EPS) > 0.) && v > EPS ? (v - c) / v : 0.;

            double h = -1.;

            if (std::abs(g - r) < EPS && std::abs(g - b) < EPS)
                h = 0.;
            else
            {
                if (std::abs(v - r) < EPS)
                {
                    h = 60. * (g - b) / (v - c);
                }
                else if (std::abs(v - g) < EPS)
                {
                    h = 120. + 60. * (b - r) / (v - c);
                }
                else if (std::abs(v - b) < EPS)
                {
                    h = 240. + 60. * (r - g) / (v - c);
                }
            }
            if (h < 0.) h += 360.;
            newRow.emplace_back(h / 2., s * 255., v * 255.);
            });
        newValuesResource.emplace_back(newRow);
        });
    return HSV(newValuesResource);
}