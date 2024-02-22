#include "../hdr/ColorSystemTypes.hpp"

using std::vector;

static const double EPS = 1e-10;

double f(double t)
{
    return (t >= 0.008856 + EPS) ? std::pow(t, 1. / 3.) : 7.787 * t + 16. / 116.;
}

double gamma_correction(double t)
{
    return (t <= 0.04045) ? t / 12.92 : std::pow((t + 0.055) / 1.055, 2.4);
}

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

            r = gamma_correction(r / 255.);
            g = gamma_correction(g / 255.);
            b = gamma_correction(b / 255.);

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

RGB::operator HLS() const
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

            double v_max = std::max(r, std::max(g, b));
            double v_min = std::min(r, std::min(g, b));
            double l = (v_max + v_min) / 2.;

            double s = l <= 0.5 + EPS && std::abs(v_max + v_min) < EPS ? (v_max - v_min) / (v_max + v_min) : (v_max - v_min) / (2 - (v_max + v_min));

            double h = -1.;

            if (std::abs(g - r) < EPS && std::abs(g - b) < EPS)
                h = 0.;
            else
            {
                if (std::abs(v_max - r) < EPS)
                {
                    h = 60. * (g - b) / (v_max - v_min);
                }
                else if (std::abs(v_max - g) < EPS)
                {
                    h = 120. + 60. * (b - r) / (v_max - v_min);
                }
                else if (std::abs(v_max - b) < EPS)
                {
                    h = 240. + 60. * (r - g) / (v_max - v_min);
                }
            }
            if (h < 0.) h += 360.;
            newRow.emplace_back(h / 2., s * 255., l * 255.);
            });
        newValuesResource.emplace_back(newRow);
        });
    return HLS(newValuesResource);
}

RGB::operator Lab() const
{
    return static_cast<Lab>(static_cast<XYZ>(*this));
}

XYZ::operator Lab() const
{
    vector<vector<Point<double>>> newValuesResource;
    newValuesResource.reserve(resource.size());

    const double Z_n = 1.088754;
    const double X_n = 0.950456;

    std::for_each(resource.begin(), resource.end(), [&](const std::vector<Point<double>> row) {
        vector<Point<double>> newRow; newRow.reserve(row.size());

        std::for_each(row.begin(), row.end(), [&](Point<double> point) {

            std::tuple<double, double, double> point_tuple = static_cast<std::tuple<double, double, double>>(point);

            double x = std::get<0>(point_tuple); ;
            double y = std::get<1>(point_tuple); ;
            double z = std::get<2>(point_tuple); ;

            x /= X_n;
            z /= Z_n;
            double l = (y >= 0.008856 + EPS) ? 116. * std::pow(y, 1. / 3.) - 16. : 903.3 * y;
            double a = 500. * (f(x) - f(y)) + 128.;
            double b = 200. * (f(y) - f(z)) + 128.;

            newRow.emplace_back(l * 2.55, a, b);
            });
        newValuesResource.emplace_back(newRow);
        });
    return Lab(newValuesResource);

}

XYZ::operator RGB() const
{
    vector<vector<Point<u_char>>> newValuesResource;
    newValuesResource.reserve(resource.size());

    std::for_each(resource.begin(), resource.end(), [&](const std::vector<Point<double>> row) {
        vector<Point<u_char>> newRow; newRow.reserve(row.size());

        std::for_each(row.begin(), row.end(), [&](Point<double> point) {

            std::tuple<double, double, double> point_tuple = static_cast<std::tuple<double, double, double>>(point);

            double x = std::get<0>(point_tuple);
            double y = std::get<1>(point_tuple);
            double z = std::get<2>(point_tuple);

            double r = 3.240479 * x - 1.53715 * y - 0.498535 * z;
            double g = -0.969256 * x + 1.875991 * y + 0.041556 * z;
            double b = 0.055648 * x - 0.204043 * y + 1.057311 * z;

            newRow.emplace_back(static_cast<u_char>(static_cast<u_int32_t>(std::round(r))),
                static_cast<u_char>(static_cast<u_int32_t>(std::round(g))),
                static_cast<u_char>(static_cast<u_int32_t>(std::round(b))));
            });
        newValuesResource.emplace_back(newRow);
        });
    return RGB(newValuesResource);
}

XYZ::operator HLS() const
{
    return static_cast<HLS>(static_cast<RGB>(*this));
}

XYZ::operator HSV() const
{
    return static_cast<HSV>(static_cast<RGB>(*this));
}

HSV::operator RGB() const
{
    vector<vector<Point<u_char>>> newValuesResource;
    newValuesResource.reserve(resource.size());

    std::for_each(resource.begin(), resource.end(), [&](const std::vector<Point<double>> row) {
        vector<Point<u_char>> newRow; newRow.reserve(row.size());

        std::for_each(row.begin(), row.end(), [&](Point<double> point) {

            std::tuple<double, double, double> point_tuple = static_cast<std::tuple<double, double, double>>(point);

            double h = std::get<0>(point_tuple)/255.;
            double s = std::get<1>(point_tuple)/255.;
            double v = std::get<2>(point_tuple)/255.;

            double r = -1.;
            double g = -1.;
            double b = -1.;

            int i = static_cast<int>(std::floor(h * 6.));
            double f = h * 6. - i;
            double p = v * (1 - s);
            double q = v * (1 - f * s);
            double t = v * (1 - (1 - f) * s);

            switch (i % 6)
            {
            case 0:
                r = v; g = t; b = p;
                break;
            case 1:
                r = q; g = v; b = t;
                break;
            case 2:
                r = p; g = v; b = t;
                break;
            case 3:
                r = p; g = q; b = v;
                break;
            case 4:
                r = t; g = p; b = v;
                break;
            case 5:
                r = v; g = p; b = q;
                break;
            }
            newRow.emplace_back(static_cast<u_char>(static_cast<u_int32_t>(std::round(r * 255.))),
                static_cast<u_char>(static_cast<u_int32_t>(std::round(g * 255.))),
                static_cast<u_char>(static_cast<u_int32_t>(std::round(b * 255.))));
            });
        newValuesResource.emplace_back(newRow);
        });
    return RGB(newValuesResource);
}

HSV::operator HLS() const
{
    return static_cast<HLS>(static_cast<RGB>(*this));
}

HSV::operator XYZ() const
{
    return static_cast<XYZ>(static_cast<RGB>(*this));
}

HSV::operator Lab() const
{
    return static_cast<Lab>(static_cast<RGB>(*this));
}

// HLS::operator RGB() const
// {
    
// }