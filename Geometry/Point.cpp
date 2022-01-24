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
	for (int i = 0; i < axes.size(); i++)
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
	for (int i = 0; i < axes.size(); i++)
	{
		if (i == axes.size() - 1)
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

void Point::Edit()
{
	bool foundAxis = 0;
	int tempi = 0;
	string temps = "";
	cout << "Select which field to edit (input the number):" << endl;
	cout << "  1. Name" << endl;
	cout << "  2. Dimensions" << endl;
	cout << "  3. Axes" << endl;
	cout << "  4. Coordinates" << endl;
	cin >> tempi;
	switch (tempi)
	{
	case(1):
	{
		cout << "Current name: " << name << endl;
		cout << "Input new name: ";
		cin >> temps;
		name = temps;
		cout << "Name " << name << " set";
		break;
	}
	case(2):
	{
		cout << "Current dimensions: " << dimensions << endl;
		cout << "Current axes: ";
		PrintAxes();
		cout << endl;
		cout << "Input new dimensions: ";
		cin >> tempi;
		dimensions = tempi;
		if (dimensions > axes.size())
		{
			cout << "Adding new axes." << endl;
			for (int i = 0; i < dimensions - axes.size(); i++)
				AddAxis();
			EditCoordinates();
		}
		if (dimensions < axes.size())
		{
			cout << "Deleting excess axes." << endl;
			for (int i = 0; i < axes.size() - dimensions; i++)
			{
				while (!foundAxis)
				{
					cout << "Input the name of the axis to delete: ";
					cin >> temps;
					for (int k = 0; k < axes.size(); k++)
					{
						if (axes[k] == temps)
						{
							foundAxis = 1;
							tempi = k;
						}
					}
					if (foundAxis)
					{
						DeleteAxis(tempi);
						EditCoordinates();
					}
					else
						cout << "Unable to find an axis with that name." << endl;
				}
			}
		}
		break;
	}
	case(3):
	{
		cout << "Current axes: ";
		PrintAxes();
		cout << endl;
		cout << "Select an option (input the number):" << endl;
		cout << "  1. Add axis" << endl;
		cout << "  2. Delete axis" << endl;
		cin >> tempi;
		switch (tempi)
		{
		case(1):
		{
			cout << "Input the axis name: ";
			cin >> temps;
			cout << "Input the number of the axis placement (e.g. 2 for 2nd, 3 for 3rd, 0 for at the end): ";
			cin >> tempi;
			if (tempi == 0)
			{
				AddAxis(temps);
				EditCoordinates();
			}
			else if (tempi > 0)
			{
				tempi--;
				AddAxis(tempi, temps);
				EditCoordinates();
			}
			else
			{
				cout << "Invalid input." << endl;
			}
			break;
		}
		case(2):
		{
			cout << "Input the axis name: ";
			cin >> temps;
			foundAxis = 0;
			for (int j = 0; j < axes.size(); j++)
			{
				if (axes[j] == temps)
				{
					foundAxis = 1;
					tempi = j;
				}
			}
			if (foundAxis)
			{
				DeleteAxis(tempi);
				EditCoordinates();
			}
			else
				cout << "Unable to find an axis with that name." << endl;
			break;
		}
		default:
		{
			cout << "Invalid input." << endl;
			break;
		}
		}
		break;
	}
	case(4):
	{
		EditCoordinates();
		break;
	}
	default:
	{
		cout << "Invalid input." << endl;
		break;
	}
	}
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
        // удаление лишних пробелов из конца строки buffer
        buffer.erase(std::find_if_not(buffer.rbegin(),buffer.rend(),::isspace).base(), buffer.end());
        // удаление лишних пробелов из начала строки buffer
        buffer.erase(buffer.begin(), std::find_if_not(buffer.begin(), buffer.end(), ::isspace));

        if (buffer == "<Point>") {
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
            } else if (fieldName == "coordinates" && coordinates.empty()) {
                std::istringstream stringStream(fieldValue);
                while (stringStream >> buffer) {
                    coordinates.push_back(stof(buffer));
                }
            }
        }
    }
}