#ifndef CURVE_HPP
#define CURVE_HPP


#include "Line.hpp"

class Curve: public Line {
public:
    Curve();
    Curve(int nDimensions, std::vector<std::string> axes,
          std::vector<Point*> points, std::string curveType);
    ~Curve() = default;

    std::string getCurveType();
    void setCurveType(std::string curveType);

    virtual void Fill();
    void Clear();

    void Save(ofstream& f);
    void Load(ifstream& fileStream);
private:
    std::string _curveType;
};


#endif //CURVE_HPP
