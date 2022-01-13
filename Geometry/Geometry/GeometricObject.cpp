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

int GeometricObject::GetDimensionAmount()
{
	dimensionAmount = axes.size();
	return dimensionAmount;
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

void GeometricObject::SetDimensionAmount(int d)
{
	dimensionAmount = d;
}

//axes
void GeometricObject::PrintAxes()
{
	for (int i = 0; i < axes.size(); i++)
		cout << axes[i] << "; ";
}
void GeometricObject::AddAxis()
{
	if (axes.size() + 1 > dimensionAmount)
	{
		cout << "Unable to add axis. There are less dimensions than axes." << endl;
	}
	else
	{
		string str;
		cout << "Input axis name: ";
		cin >> str;
		axes.push_back(str);
		cout << "Axis " << str << " added." << endl;
	}
}
void GeometricObject::AddAxis(string axis)
{
	if (axes.size() + 1 > dimensionAmount)
	{
		cout << "Unable to add axis. There are less dimensions than axes." << endl;
	}
	else
	{
		axes.push_back(axis);
		cout << "Axis " << axis << " added." << endl;
	}
}

void GeometricObject::AddAxis(int i, string axis)
{
	if (axes.size() + 1 > dimensionAmount)
	{
		cout << "Unable to add axis. There are less dimensions than axes." << endl;
	}
	else
	{
		axes.insert(axes.begin() + i, axis);
		cout << "Axis " << axis << " added at position "<<i<<"." << endl;
	}
}

void GeometricObject::DeleteAxis(int i)
{
	axes.erase(axes.begin() + i);
}

string GeometricObject::GetOneAxis(int i)
{
	return axes[i];
}

void GeometricObject::PrintSelf()
{
	cout << "*** OBJECT INFORMATION ***" << endl;
	cout << "Object name: " << name << endl;
	cout << "Dimensions: " << dimensionAmount<<endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
}

void GeometricObject::Fill()
{
	int tempi;
	string temps;
	double tempd;

	cout << "Input name: ";
	cin >> temps;
	name = temps;
	cout << "Input the amount of dimensions: ";
	cin >> tempi;
	dimensionAmount = tempi;
	for (int i = 0; i < dimensionAmount; i++)
	{
		cout << "Inputting axis " << i+1 << "."<<endl;
		AddAxis();
	}
	cout << "Object " << name << " with " << dimensionAmount << " dimensions and axes ";
	for (int k = 0; k < dimensionAmount; k++)
		cout << axes[k] <<" ";
	cout << "added." << endl;
}