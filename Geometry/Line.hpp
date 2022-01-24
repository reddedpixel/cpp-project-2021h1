#ifndef LINE_HPP
#define LINE_HPP


#include "Point.h"
#include <string>

class Line: public GeometricObject {
public:
    Line();

    Line(int nDimensions, vector<string> axes, std::vector<Point> points);

    ~Line() = default;

    bool isPointOnLine(Point point);

    void addPoint(const Point& point);

    Point removePoint();

    void setStartPoint(const Point& start);

    Point getStartPoint();

    void setEndPoint(const Point& end);

    Point getEndPoint();

    void setLength(int length);

    int getLength() const;

    void setEquation(std::string equation);

    std::string getEquation();

    virtual void Clear();

    virtual void Load(ifstream& fileStream);

    bool operator==(const Line& other);

protected:
    std::string _equation;
    std::vector<Point> _points;
    Point _start;
    Point _end;
    int _length;
};


#endif //LINE_HPP
