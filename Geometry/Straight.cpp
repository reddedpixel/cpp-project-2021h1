#include "Straight.hpp"

#include <utility>

Straight::Straight(int nDimensions, std::vector<std::string> axes,
                   std::vector<Point> points,
                   std::vector<Line> parallelLines)
                   : Line(nDimensions, std::move(axes), std::move(points)) {
    _parallelLines = std::move(parallelLines);
}

std::vector<Line> Straight::getParallelLines() {
    return _parallelLines;
}

bool Straight::isParallel(const Line& line) {
    for (Line l : _parallelLines) {
        if (l == line) {
            return true;
        }
    }
    return false;
}
