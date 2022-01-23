#include "Point.h"

Point::Point()
{
	cout << "Object is now a point." << endl;
}

Point::Point(int fDimensions, vector<string> fAxes) : GeometricObject(fDimensions, fAxes)
{
	cout << "Object is now a point." << endl;
}

Point::~Point()
{
	cout << "Point " << name <<" deleted." << endl;
	cout << endl;
}

//gets
vector<float> Point::GetCoordinates()
{
	return coordinates;
}

//sets
void Point::SetCoords(vector<float> v)
{
	coordinates = v;
}

//coordinates
void Point::EditCoordinates()
{
	coordinates.clear();
	float temp;
	for (int i = 0; i < dimensions; i++)
	{
		cout << "Input coordinate value on axis " << axes[i] << ": ";
		scanf_s("%f", &temp);
		coordinates.push_back(temp);
	}
	PrintCoords();
}

void Point::PrintCoords()
{
	cout << "Point " << name << " has coordinates (";
	int i = 0;
	for (int i = 0; i < dimensions; i++)
	{
		if (i == dimensions - 1)
			cout << coordinates[i];
		else
			cout << coordinates[i] << ";";
	}
	cout << ")." << endl;
}

void Point::PrintSelf()
{
	cout << "*** POINT INFORMATION ***" << endl;
	cout << "Point name: " << name << endl;
	cout << "Dimensions: " << dimensions << endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
	PrintCoords();
	cout << endl;
}

void Point::Fill()
{
	cout << "- Filling general object information. -" << endl;
	GeometricObject::Fill();
	cout << "-- Filling specific point information. --" << endl;
	cout << "Setting point coordinates." << endl;
	float temp = 0;
	EditCoordinates();
	cout << "Point " << name << " added." << endl;
	cout << "----------------" << endl;
	cout << endl;
}

void Point::Clear()
{
	name = "";
	dimensions = 0;
	axes.clear();
	coordinates.clear();
}

bool Point::operator==(Point other) 
{
	return coordinates == other.coordinates;
}

void Point::Save(ofstream& f)
{
	f << "<Point>" << endl;
	f << "name: " << name << endl;
	f << "dimensions: " << dimensions << endl;
	f << "axes: ";
	for (int i = 0; i < axes.size(); i++)
		f << axes[i] << " ";
	f << endl;
	f << "coordinates: ";
	for (int k = 0; k < coordinates.size(); k++)
		f << coordinates[k] << " ";
	f << endl;
	f << "</Point>" << endl;
}

void Point::Load(ifstream& fileStream) {
    std::string buffer, fieldName, fieldValue;
    bool foundStart = false;
    while (getline(fileStream, buffer) && buffer != "</Point>") {
        // удаление лишних пробелов из конца и начала строки
        buffer.erase(std::find_if_not(buffer.rbegin(),buffer.rend(),::isspace).base(), buffer.end());
        buffer.erase(buffer.begin(), std::find_if_not(buffer.begin(), buffer.end(), ::isspace));
        if (buffer == "<Point>") {
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
            } else if (fieldName == "coordinates" && coordinates.empty()) {
                std::istringstream stringStream(fieldValue);
                while (stringStream >> buffer) {
                    coordinates.push_back(stof(buffer));
                }
            }
        }
    }
}