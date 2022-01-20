#include "Point.h"

Point::Point()
{
	cout << "Object is now a point." << endl;
}

Point::Point(int fDimensions, vector<string> fAxes)
{
	dimensionAmount = fDimensions;
	axes = fAxes;
	cout << "Object is now a point." << endl;
}

Point::~Point()
{
	cout << "Point " << name <<" deleted." << endl;
	cout << endl;
}

//gets
vector<float> Point::GetCoords()
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
	for (int i = 0; i < dimensionAmount; i++)
	{
		cout << "Input coordinate value on axis " << axes[i] << " : ";
		scanf_s("%f", &temp);
		coordinates.push_back(temp);
	}
	PrintCoords();
}

void Point::PrintCoords()
{
	cout << "Point " << name << " has coordinates (";
	int i = 0;
	for (int i = 0; i < dimensionAmount; i++)
	{
		if (i == dimensionAmount - 1)
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
	cout << "Dimensions: " << dimensionAmount << endl;
	cout << "Axes: ";
	PrintAxes();
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