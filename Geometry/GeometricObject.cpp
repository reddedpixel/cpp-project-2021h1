#include "GeometricObject.h"

GeometricObject::GeometricObject()
{
	cout << "Object created." << endl;
}

GeometricObject::~GeometricObject()
{
	cout << "Object deleted." << endl;
}

//gets
string GeometricObject::GetName()
{
	return name;
}

int GeometricObject::GetDimensionCount()
{
	return dimensionCount;
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
void GeometricObject::SetDimensionCount(int dC)
{
	dimensionCount = dC;
}
void GeometricObject::SetAxes(vector<string> a)
{
	axes = a;
}

//axes

void GeometricObject::PrintAxes()
{
	for (int i = 0; i < axes.size(); i++)
		cout << axes[i] << "; ";
}

void GeometricObject::AddAxis(string axis)
{
	axes.push_back(axis);
}

void GeometricObject::AddAxis(int i, string axis)
{
	axes.insert(axes.begin() + i, axis);
}

void GeometricObject::DeleteAxis(int i)
{
	axes.erase(axes.begin() + i);
}

string GeometricObject::GetOneAxis(int i)
{
	return axes[i];
}

int GeometricObject::CheckAxes()
{
	int r = 0;
	r = axes.size() - dimensionCount;
	return r;
}

void GeometricObject::PrintSelf()
{
	cout << "*** OBJECT INFORMATION ***" << endl;
	cout << "Object name: " << name << endl;
	cout << "Dimensions: " << dimensionCount<<endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
}