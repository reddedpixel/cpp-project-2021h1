#include "Straight.hpp"

#include <utility>
#include <cmath>

Straight::Straight(): Line() {
    _parallelLines = std::vector<Line>();
}

Straight::Straight(int nDimensions, std::vector<std::string> axes,
                   std::vector<Point> points,
                   std::vector<Line> parallelLines)
                   : Line(nDimensions, std::move(axes), std::move(points)) {
    float sum = 0;
    for (int i = 0; i < nDimensions; i++) {
        float coordsDiff = _end.GetCoordinates()[i] - _start.GetCoordinates()[i];
        sum += coordsDiff * coordsDiff;
    }
    _length = int(sqrt(sum));
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

void Straight::Load(ifstream& fileStream) {
    std::string buffer, fieldName, fieldValue;
    bool foundStart = false;

    while (getline(fileStream, buffer) && buffer != "</Straight>") {
        // удаление лишних пробелов из конца строки buffer
        buffer.erase(std::find_if_not(buffer.rbegin(),buffer.rend(),::isspace).base(), buffer.end());
        // удаление лишних пробелов из начала строки buffer
        buffer.erase(buffer.begin(), std::find_if_not(buffer.begin(), buffer.end(), ::isspace));

        if (buffer == "<Straight>") {
            foundStart = true;
        } else if (foundStart) {
            // парсим в fieldName и fieldValue название и значение поля соответственно
            fieldName = buffer.substr(0, buffer.find(':'));
            fieldValue = buffer.substr(buffer.find(':') + 1);

            // удаление лишних пробелов из начала строки fieldValue
            fieldValue.erase(fieldValue.begin(), std::find_if_not(fieldValue.begin(), fieldValue.end(), ::isspace));

            // в зависимости от названия поля обрабатываем его
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
                    // запоминаем текущее значение курсора файла
                    long long pos = fileStream.tellg();
                    // читаем и парсим следующую строку файла
                    getline(fileStream, nextLine);
                    nextLine.erase(nextLine.begin(), std::find_if_not(nextLine.begin(), nextLine.end(), ::isspace));
                    nextLine = nextLine.substr(0, buffer.find(':'));
                    // возвращаем курсор на значение до чтения строки
                    fileStream.seekg(pos);
                }
                _start = _points.front();
                _end = _points.back();
            } else if (fieldName == "length" && _length == 0) {
                _length = stoi(fieldValue);
            } else if (fieldName == "parallelLines" && _parallelLines.empty()) {
                std::string nextLine;
                while (nextLine != "</Straight>" && !fileStream.eof()) {
                    Line bufferLine;
                    bufferLine.Load(fileStream);
                    _parallelLines.push_back(bufferLine);
                    bufferLine.Clear();
                    // запоминаем текущее значение курсора файла
                    long long pos = fileStream.tellg();
                    // читаем следующую строку файла
                    getline(fileStream, nextLine);
                    // возвращаем курсор на значение до чтения строки
                    fileStream.seekg(pos);
                }
            }
        }
    }
}
