#include "Curve.hpp"
#include <utility>

Curve::Curve()
{
    _curveType = "";
    cout << "Object is now a curve." << endl;
}

Curve::Curve(int nDimensions, std::vector<std::string> axes,
             std::vector<Point*> points,
             std::string curveType): Line(nDimensions, std::move(axes), std::move(points)) {
    _curveType = std::move(curveType);
}

std::string Curve::getCurveType() {
    return _curveType;
}

void Curve::setCurveType(std::string curveType) {
    _curveType = std::move(curveType);
}

void Curve::Fill()
{
    int tempi;
    string temps;
    cout << "- Filling general object information. -" << endl;
    GeometricObject::Fill();
    cout << "--- Filling specific curve information. ---" << endl;
    cout << "Input equation: ";
    cin >> temps;
    _equation = temps;
    cout << "- Adding start point. -" << endl;
    Point* spoint = new Point(dimensions, axes);
    spoint->Fill();
    _start = spoint;
    cout << "- Adding end point. -" << endl;
    Point* epoint = new Point(dimensions, axes);
    epoint->Fill();
    cout << "Input length: ";
    cin >> tempi;
    _length = tempi;
    cout << "Input curve type: ";
    cin >> temps;
    _curveType = temps;
    cout << "Curve " << name << " (" << _curveType << ") with equation " << _equation << " added." << endl;
    cout << "----------------" << endl;
    cout << endl;
}