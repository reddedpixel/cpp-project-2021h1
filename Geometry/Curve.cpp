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

void Curve::Clear() {
    Line::Clear();
    _curveType = "";
}

void Curve::Load(ifstream &fileStream) {
    std::string buffer, fieldName, fieldValue;
    bool foundStart = false;
    while (getline(fileStream, buffer) && buffer != "</Curve>") {
        // удаление лишних пробелов из конца и начала строки
        buffer.erase(std::find_if_not(buffer.rbegin(),buffer.rend(),::isspace).base(), buffer.end());
        buffer.erase(buffer.begin(), std::find_if_not(buffer.begin(), buffer.end(), ::isspace));
        if (buffer == "<Curve>") {
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
            } else if (fieldName == "curveType" && _curveType.empty()) {
                _curveType = fieldValue;
            }
        }
    }
}