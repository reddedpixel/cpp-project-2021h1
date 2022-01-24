#include "Straight.hpp"

#include <utility>
#include <cmath>

Straight::Straight(): Line() {
    _parallelLines = std::vector<Line*>();
}

Straight::Straight(int nDimensions, std::vector<std::string> axes,
                   std::vector<Point*> points,
                   std::vector<Line*> parallelLines)
                   : Line(nDimensions, std::move(axes), std::move(points)) {
    float sum = 0;
    for (int i = 0; i < nDimensions; i++) {
        float coordsDiff = _end->GetCoordinates()[i] - _start->GetCoordinates()[i];
        sum += coordsDiff * coordsDiff;
    }
    _length = int(sqrt(sum));
    _parallelLines = std::move(parallelLines);
}

std::vector<Line*> Straight::getParallelLines() {
    return _parallelLines;
}

bool Straight::isParallel(Line* line) {
    for (Line* l : _parallelLines) {
        if (l == line) {
            return true;
        }
    }
    return false;
}

void Straight::Save(ofstream& f)
{
    f << "<Straight>" << endl;
    f << "name: " << name << endl;
    f << "dimensions: " << dimensions << endl;
    f << "axes: ";
    for (int i = 0; i < axes.size(); i++)
        f << axes[i] << " ";
    f << endl;
    f << "equation: " << _equation << endl;
    f << "points: ";
    for (int j = 0; j < _points.size(); j++)
        _points[j]->Save(f);
    f << "length: " << _length << endl;
    f << "parallelLines: ";
    for (int k = 0; k < _parallelLines.size(); k++)
        _parallelLines[k]->Save(f);
    f << "</Straight>" << endl;
}

void Straight::Load(ifstream& fileStream) {
    std::string buffer, fieldName, fieldValue;
    while (getline(fileStream, buffer) && buffer != "</Straight>") {
        // удаление лишних пробелов из конца и начала строки
        buffer.erase(std::find_if_not(buffer.rbegin(), buffer.rend(), ::isspace).base(), buffer.end());
        buffer.erase(buffer.begin(), std::find_if_not(buffer.begin(), buffer.end(), ::isspace));
            fieldName = buffer.substr(0, buffer.find(':'));
            fieldValue = buffer.substr(buffer.find(':') + 1);
            // удаление лишних пробелов из начала
            fieldValue.erase(fieldValue.begin(), std::find_if_not(fieldValue.begin(), fieldValue.end(), ::isspace));
            if (fieldName == "name" && name.empty()) {
                name = fieldValue;
            }
            else if (fieldName == "dimensions" && dimensions == 0) {
                dimensions = stoi(fieldValue);
            }
            else if (fieldName == "axes" && axes.empty()) {
                std::istringstream stringStream(fieldValue);
                while (stringStream >> buffer) {
                    axes.push_back(buffer);
                }
            }
            else if (fieldName == "equation" && _equation.empty()) {
                _equation = fieldValue;
            }
            else if (fieldName == "points" && _points.empty()) {
                std::string nextLine;
                while (nextLine != "length" && !fileStream.eof()) {
                    Point* bufferPoint = new Point;
                    bufferPoint->Load(fileStream);
                    _points.push_back(bufferPoint);
                    long long pos = fileStream.tellg();
                    getline(fileStream, nextLine);
                    nextLine.erase(nextLine.begin(), std::find_if_not(nextLine.begin(), nextLine.end(), ::isspace));
                    nextLine = nextLine.substr(0, buffer.find(':')-1);
                    fileStream.seekg(pos);
                }
                _start = _points.front();
                _end = _points.back();
            }
            else if (fieldName == "length" && _length == 0) {
                _length = stoi(fieldValue);
            }
            else if (fieldName == "parallelLines" && _parallelLines.empty()) {
                std::string nextLine;
                while (nextLine != "</Straight>" && !fileStream.eof()) {
                    Line* bufferLine = new Line;
                    bufferLine->Load(fileStream);
                    _parallelLines.push_back(bufferLine);
                    long long pos = fileStream.tellg();
                    getline(fileStream, nextLine);
                    fileStream.seekg(pos);
                }
            }
    }
}