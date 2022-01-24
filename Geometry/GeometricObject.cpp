#include "GeometricObject.h"

GeometricObject::GeometricObject()
{
	dimensions = 0;
	name = "";
	cout << "Object created." << endl;
}

GeometricObject::GeometricObject(int fDimensions, vector<string> fAxes)
{
	dimensions = fDimensions;
	axes = fAxes;
	cout << "Object created." << endl;
}

GeometricObject::~GeometricObject()
{
	cout << "Object deleted." << endl;
	cout << endl;
}

//gets
string GeometricObject::GetName()
{
	return name;
}

int GeometricObject::GetDimensions()
{
	return dimensions;
}

vector<string> GeometricObject::GetAxes()
{
	return axes;
}

//sets
void GeometricObject::SetName(string n)
{
	name = n;
}

void GeometricObject::SetAxes(vector<string> a)
{
	axes = a;
}

void GeometricObject::SetDimensions(int d)
{
	dimensions = d;
}

//axes
void GeometricObject::PrintAxes()
{
	for (int i = 0; i < axes.size(); i++)
	{
		if (i != axes.size() - 1)
			cout << axes[i] << "; ";
		else
			cout << axes[i];
	}
}
void GeometricObject::AddAxis()
{
	if (axes.size() + 1 > dimensions)
	{
		cout << "Unable to add axis. There cannot be more axes than dimensions." << endl;
		cout << endl;
	}
	else
	{
		string str;
		cout << "Input axis name: ";
		cin >> str;
		axes.push_back(str);
		cout << "Axis " << str << " added." << endl;
		cout << endl;
	}
}
void GeometricObject::AddAxis(string axis)
{
	if (axes.size() + 1 > dimensions)
	{
		cout << "Unable to add axis. There cannot be more axes than dimensions." << endl;
		cout << endl;
	}
	else
	{
		axes.push_back(axis);
		cout << "Axis " << axis << " added." << endl;
		cout << endl;
	}
}

void GeometricObject::AddAxis(int i, string axis)
{
	if (axes.size() + 1 > dimensions)
	{
		cout << "Unable to add axis. There cannot be more axes than dimensions." << endl;
		cout << endl;
	}
	else
	{
		axes.insert(axes.begin() + i, axis);
		cout << "Axis " << axis << " added at position "<<i+1<<"." << endl;
		cout << endl;
	}
}

void GeometricObject::DeleteAxis(int i)
{
	axes.erase(axes.begin() + i);
	cout << "Axis at position " << i+1 << " deleted.";
	cout << endl;
}

void GeometricObject::PrintSelf()
{
	cout << "*** OBJECT INFORMATION ***" << endl;
	cout << "Object name: " << name << endl;
	cout << "Dimensions: " << dimensions << endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
}

void GeometricObject::Fill()
{
	int tempi;
	string temps;

	if (name == "")
	{
		cout << "Input name: ";
		cin >> temps;
		name = temps;
	}
	if (dimensions == 0)
	{
		cout << "Input the amount of dimensions: ";
		cin >> tempi;
		dimensions = tempi;
	}
	if (axes.size() == 0)
	{
		for (int i = 0; i < dimensions; i++)
		{
			cout << "Inputting axis " << i + 1 << "." << endl;
			AddAxis();
		}
	}
	cout << "Object " << name << " with " << dimensions << " dimensions and axes ";
	for (int k = 0; k < dimensions; k++)
		cout << axes[k] <<" ";
	cout << "added." << endl;
	cout << "----------------"<<endl;
	cout << endl;
}

void GeometricObject::Clear()
{
	name = "";
	dimensions = 0;
	axes.clear();
}

void GeometricObject::Edit()
{
	bool foundAxis = 0;
	int tempi = 0;
	string temps = "";
	cout << "Select which field to edit (input the number):" << endl;
	cout << "  1. Name" << endl;
	cout << "  2. Dimensions" << endl;
	cout << "  3. Axes" << endl;
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
		}
		if (dimensions < axes.size())
		{
			cout << "Deleting excess axes." << endl;
			for (int i = 0; i < axes.size() - dimensions; i++)
			{
				foundAxis = 0;
				while (!foundAxis)
				{
					cout << "Input the name of the axis to delete: ";
					cin >> temps;
					for (int k = 0; k < axes.size(); k++)
					{
						if (axes[k] == temps)
						{
							tempi = k;
							foundAxis = 1;
						}
					}
					if (foundAxis)
						DeleteAxis(tempi);
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
				AddAxis(temps);
			else if (tempi > 0)
			{
				tempi--;//������ ��� �� ������� �� 0, � ������������ �� 1
				AddAxis(tempi, temps);
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
				DeleteAxis(tempi);
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
	default:
	{
		cout << "Invalid input." << endl;
		break;
	}
	}
}

void GeometricObject::Save(ofstream& f)
{
	f << "<GeometricObject>" << endl;
	f << "name: " << name << endl;
	f << "dimensions: " << dimensions << endl;
	f << "axes: ";
	for (int i = 0; i < axes.size(); i++)
		f << axes[i] << " ";
	f << endl;
	f << "</GeometricObject>" << endl;
}

void GeometricObject::Load(ifstream& fileStream) {
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
            }
        }
    }
}