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

void Curve::Clear() {
    Line::Clear();
    _curveType = "";
}

void Curve::Load(ifstream &fileStream) {
    std::string buffer, fieldName, fieldValue;
    bool foundStart = false;

    while (getline(fileStream, buffer) && buffer != "</Curve>") {
        // удаление лишних пробелов из конца строки buffer
        buffer.erase(std::find_if_not(buffer.rbegin(), buffer.rend(),
                                      ::isspace).base(), buffer.end());
        // удаление лишних пробелов из начала строки buffer
        buffer.erase(buffer.begin(),
                     std::find_if_not(buffer.begin(), buffer.end(), ::isspace));

        if (buffer == "<Curve>") {
            foundStart = true;
        } else if (foundStart) {
            // парсим в fieldName и fieldValue название и значение поля соответственно
            fieldName = buffer.substr(0, buffer.find(':'));
            fieldValue = buffer.substr(buffer.find(':') + 1);

            // удаление лишних пробелов из начала строки fieldValue
            fieldValue.erase(fieldValue.begin(),
                             std::find_if_not(fieldValue.begin(),
                                              fieldValue.end(), ::isspace));

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
                    nextLine.erase(nextLine.begin(),
                                   std::find_if_not(nextLine.begin(),
                                                    nextLine.end(), ::isspace));
                    nextLine = nextLine.substr(0, buffer.find(':'));
                    // возвращаем курсор на значение до чтения строки
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