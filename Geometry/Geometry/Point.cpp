#include "Point.h"

Point::Point()
{
	cout << "Object" << name <<" upgraded to point." << endl;
}
Point::~Point()
{
	cout << "Point " << name<<" deleted." << endl;
}

//gets
vector<double> Point::GetCoords()
{
	return coordinates;
}

//sets
void Point::SetCoords(vector<double> v)
{
	coordinates = v;
}
void Point::SetCoords()
{
	cout << "Setting point coordinates." << endl;
	double temp = 0;
	for (int i = 0; i < dimensionAmount; i++)
	{
		cout << "Input coordinate on axis " << axes[i] << ": ";
		cin >> temp;
		//cout << endl;
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
	cout << "Filling general object information." << endl;
	GeometricObject::Fill();
	cout << "Filling specific point information." << endl;
	SetCoords();
	cout << "Point " << name << " added." << endl;
}