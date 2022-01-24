#ifndef LINE_HPP
#define LINE_HPP


#include "Point.h"
#include <string>

class Line: public GeometricObject {
public:
    Line();
    Line(int nDimensions, vector<string> axes, std::vector<Point*> points);
    ~Line() = default;
    //gets
    Point* getStartPoint();
    Point* getEndPoint();
    int getLength() const;
    std::string getEquation();
    //sets
    void setStartPoint(Point* start);
    void setEndPoint(Point* end);
    void setLength(int length);
    void setEquation(std::string equation);
    //points
    bool isPointOnLine(Point* point);
    void addPoint(Point* point);
    Point* removePoint();

    virtual void Clear();
    virtual void Save(ofstream& f);
    virtual void Load(ifstream& fileStream);
    virtual void Fill();

    bool operator==(const Line& other);

protected:
    std::string _equation;
    std::vector<Point*> _points;
    Point* _start;
    Point* _end;
    int _length;
};


#endif //LINE_HPP
