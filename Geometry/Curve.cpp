#include "Curve.hpp"

#include <utility>

Curve::Curve(): Line() {
    _curveType = "";
}

Curve::Curve(int nDimensions, std::vector<std::string> axes,
             std::vector<Point> points,
             std::string curveType): Line(nDimensions, std::move(axes), std::move(points)) {
    _curveType = std::move(curveType);
}

std::string Curve::getCurveType() {
    return _curveType;
}

void Curve::setCurveType(std::string curveType) {
    _curveType = std::move(curveType);
}
