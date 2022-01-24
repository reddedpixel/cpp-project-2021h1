#include "Line.hpp"

#include <utility>
#include <cassert>

Line::Line(): GeometricObject() {
    _points = std::vector<Point>();
    _start = _end = Point();
    _equation = "";
    _length = 0;
}

Line::Line(int nDimensions, vector<string> axes, std::vector<Point> points):
        GeometricObject(nDimensions, std::move(axes)),
           _start(points.front()), _end(points.back()) {
    // проверка на то, что количество координат каждой
    // точки совпадает с размерностью линии
    bool hasSameDimension = true;
    for (Point p : _points) {
        if (p.GetCoordinates().size() != nDimensions) {
            hasSameDimension = false;
        }
    }
    assert(hasSameDimension);

    _points = points;
    _equation = "";
    _length = 0;
}

bool Line::isPointOnLine(Point point) {
    if (_points.empty()) {
        return false;
    }
    // если количество координат данной точки не совпадает с
    // размерностью линии (числом координат любой точки,
    // уже лежащей на линии), то вернуть "ложь"
    std::vector<float> pointCoords = point.GetCoordinates();
    if (pointCoords.size() != _points[0].GetCoordinates().size()) {
        return false;
    }
    // если найдется хотя бы одна точка, совпадающая с данной,
    // то вернуть "истина"
   for (const Point& p : _points) {
        if (point == p) {
            return true;
        }
    }
    return false;
}

void Line::addPoint(const Point& point) {
    // если точка не на линии, то добавить её на линию
    if (!this->isPointOnLine(point)) {
        _points.push_back(point);
    }
}

Point Line::removePoint() {
    Point back = _points.back();
    _points.pop_back();
    if (!_points.empty()) {
        // если выброшенная точка совпадает с конечной,
        // то обновить значение конечной
        if (_end == back) {
            _end = _points.back();
        }
        // если выброшенная точка совпадает с начальной,
        // то обновить значение начальной
        if (_start == back) {
            _start = _points.front();
        }
    }
    return back;
}

void Line::setStartPoint(const Point& start) {
    // если точка start не на линии, то добавить её на линию
    if (!this->isPointOnLine(start)) {
        _points.push_back(start);
    }
    _start = start;
}

Point Line::getStartPoint() {
    return _start;
}

void Line::setEndPoint(const Point& end) {
    // если точка end не на линии, то добавить её на линию
    if (!this->isPointOnLine(end)) {
        _points.push_back(end);
    }
    _end = end;
}

Point Line::getEndPoint() {
    return _end;
}

void Line::setLength(int length) {
    assert(length >= 0);
    _length = length;
}

int Line::getLength() const {
    return _length;
}

void Line::setEquation(std::string equation) {
    _equation = std::move(equation);
}

std::string Line::getEquation() {
    return _equation;
}

void Line::Clear() {
    GeometricObject::Clear();
    _equation = "";
    _points = std::vector<Point>();
    _start = _end = Point();
    _length = 0;
}

void Line::Load(ifstream& fileStream) {
    std::string buffer, fieldName, fieldValue;
    bool foundStart = false;
    while (getline(fileStream, buffer) && buffer != "</Line>") {
        // удаление лишних пробелов из конца и начала строки
        buffer.erase(std::find_if_not(buffer.rbegin(),buffer.rend(),::isspace).base(), buffer.end());
        buffer.erase(buffer.begin(), std::find_if_not(buffer.begin(), buffer.end(), ::isspace));
        if (buffer == "<Line>") {
            foundStart = true;
        } else if (foundStart) {
            fieldName = buffer.substr(0, buffer.find(':'));
            fieldValue = buffer.substr(buffer.find(':') + 1);
            // удаление лишних пробелов из начала
            fieldValue.erase(fieldValue.begin(), std::find_if_not(fieldValue.begin(), fieldValue.end(), ::isspace));
            if (fieldName == "name" && name.empty()) {
                name = fieldValue;
            } else if (fieldName == "dimensions" && dimensions == 0) {
                dimensions = stoi(fieldValue);
            } else if (fieldName == "axes" && axes.empty()) {
                std::istringstream stringStream(fieldValue);
                while (stringStream >> buffer) {
                    axes.push_back(buffer);
                }
            } else if (fieldName == "equation" && _equation.empty()) {
                _equation = fieldValue;
            } else if (fieldName == "points" && _points.empty()) {
                std::string nextLine;
                while (nextLine != "length" && !fileStream.eof()) {
                    Point bufferPoint;
                    bufferPoint.Load(fileStream);
                    _points.push_back(bufferPoint);
                    bufferPoint.Clear();
                    long long pos = fileStream.tellg();
                    getline(fileStream, nextLine);
                    nextLine.erase(nextLine.begin(), std::find_if_not(nextLine.begin(), nextLine.end(), ::isspace));
                    nextLine = nextLine.substr(0, buffer.find(':'));
                    fileStream.seekg(pos);
                }
                _start = _points.front();
                _end = _points.back();
            } else if (fieldName == "length" && _length == 0) {
                _length = stoi(fieldValue);
            }
        }
    }
}

bool Line::operator==(const Line& other) {
    for (int i = 0; i < _points.size(); i++) {
        if (!(_points[i] == other._points[i])) {
            return false;
        }
    }
    return true;
}
