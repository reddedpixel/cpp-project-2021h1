#ifndef CURVE_HPP
#define CURVE_HPP


#include "Line.hpp"

class Curve: Line {
public:
    Curve();

    Curve(int nDimensions, std::vector<std::string> axes,
          std::vector<Point> points, std::string curveType);

    ~Curve() = default;

    std::string getCurveType();

    void setCurveType(std::string curveType);

private:
    std::string _curveType;
};


#endif //CURVE_HPP
