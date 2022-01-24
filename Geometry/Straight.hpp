#ifndef STRAIGHT_HPP
#define STRAIGHT_HPP


#include "Line.hpp"

class Straight: public Line {
public:
    Straight();
    Straight(int nDimensions, std::vector<std::string> axes,
             std::vector<Point*> points, std::vector<Line> parallelLines);
    ~Straight() = default;

    std::vector<Line> getParallelLines();
    bool isParallel(const Line& line);

private:
    std::vector<Line> _parallelLines;
};


#endif //STRAIGHT_HPP
