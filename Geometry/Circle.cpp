#include "Circle.h"

Circle::Circle()
{
	radius = 0;
	edges = 1;
	cout << "Object is now a circle." << endl;
}

Circle::~Circle()
{
	cout << "Circle " << name << "deleted." << endl;
}

//gets
float Circle::GetRadius()
{
	return radius;
}

//sets
void Circle::SetRadius(float r)
{
	radius = r;
}

//measure
float Circle::CalculateMeasure()
{
	float pi = 3.1415926f;
	measure = pi * (radius * radius);
	return measure;
}

void Circle::PrintSelf()
{
	cout << "*** CIRCLE INFORMATION ***" << endl;
	cout << "Circle name: " << name << endl;
	cout << "Dimensions: " << dimensions << endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
	cout << "Center: ";
	PrintVertices();
	cout << endl;
	for (int i = 0; i < edges; i++)
		vertices[i]->PrintCoords();
	cout << "Area: " << CalculateMeasure() << endl;
	cout << endl;
}

void Circle::Fill()
{

	cout << "- Filling general object information. -" << endl;
	GeometricObject::Fill();
	cout << "--- Filling specific circle information. ---" << endl;
	cout<<"- Adding circle center. -" << endl;
	AddVertex();
	cout << "Input circle radius: ";
	scanf_s("%f", &radius);
	cout << "Circle " << name << " added." << endl;
	cout << "----------------" << endl;
	cout << endl;

}

void Circle::Clear()
{
	name = "";
	dimensions = 0;
	axes.clear();
	coordinates.clear();
	edges = 0;
	vertices.clear();
	measure = 0;
	radius = 0;
}

void Circle::Edit()
{
	bool foundAxis = 0;
	bool foundVertex = 0;
	int tempi = 0;
	string temps = "";
	cout << "Select which field to edit (input the number):" << endl;
	cout << "  1. Name" << endl;
	cout << "  2. Dimensions" << endl;
	cout << "  3. Axes" << endl;
	cout << "  4. Center" << endl;
	cout << "  5. Radius" << endl;
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
			vertices[0]->EditCoordinates();
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
					{
						DeleteAxis(tempi);
						vertices[0]->EditCoordinates();
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
				vertices[0]->EditCoordinates();
			}
			else if (tempi > 0)
			{
				tempi--;
				AddAxis(tempi, temps);
				vertices[0]->EditCoordinates();
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
				vertices[0]->EditCoordinates();
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
		cout << "Current center info:" << endl;
		vertices[0]->PrintSelf();
		vertices[0]->Edit();
		break;
	}
	case(5):
	{
		cout << "Current radius: " << radius << endl;
		cout << "Input new radius: ";
		float tempf;
		scanf_s("%f", &tempf);
		radius = tempf;
		break;
	}
	default:
		cout << "Incorrect input." << endl;
	}
}

void Circle::Save(ofstream& f)
{
	f << "<Circle>" << endl;
	f << "name: " << name << endl;
	f << "dimensions: " << dimensions << endl;
	f << "axes: ";
	for (int i = 0; i < axes.size(); i++)
		f << axes[i] << " ";
	f << endl;
	f << "coordinates: 0" << endl;
	f << "edges: 1" << endl;
	f << "vertices: " << endl;
	vertices[0]->Save(f);
	f << "measure: " << measure << endl;
	f << "radius: " << radius << endl;
	f << "</Circle>" << endl;
}

void Circle::Load(ifstream& fileStream)
{
	std::string buffer, fieldName, fieldValue;
	while (getline(fileStream, buffer) && buffer != "</Circle>") {
		// удаление лишних пробелов из конца строки buffer
		buffer.erase(std::find_if_not(buffer.rbegin(), buffer.rend(), ::isspace).base(), buffer.end());
		// удаление лишних пробелов из начала строки buffer
		buffer.erase(buffer.begin(), std::find_if_not(buffer.begin(), buffer.end(), ::isspace));
		// парсим в fieldName и fieldValue название и значение поля соответственно
		fieldName = buffer.substr(0, buffer.find(':'));
		fieldValue = buffer.substr(buffer.find(':') + 1);
		// удаление лишних пробелов из начала строки fieldValue
		fieldValue.erase(fieldValue.begin(), std::find_if_not(fieldValue.begin(), fieldValue.end(), ::isspace));
		// в зависимости от названия поля обрабатываем его
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
		else if (fieldName == "edges") {
			edges = stoi(fieldValue);
		}
		else if (fieldName == "vertices") {
			std::string nextLine;
			while (nextLine != "measure" && !fileStream.eof()) {
				Point* bufferPoint = new Point;
				bufferPoint->Load(fileStream);
				vertices.push_back(bufferPoint);
				// запоминаем текущее значение курсора файла
				long long pos = fileStream.tellg();
				// читаем и парсим следующую строку файла
				getline(fileStream, nextLine);
				nextLine.erase(nextLine.begin(), std::find_if_not(nextLine.begin(), nextLine.end(), ::isspace));
				nextLine = nextLine.substr(0, buffer.find(':')-1);
				// возвращаем курсор на значение до чтения строки
				fileStream.seekg(pos);
			}
		}
		else if (fieldName == "measure") {
			measure = stof(fieldValue);
		}
		else if (fieldName == "radius") {
			radius = stof(fieldValue);
		}
	}
}