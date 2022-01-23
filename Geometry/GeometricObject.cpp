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
		cout << "Axis " << axis << " added at position "<<i<<"." << endl;
		cout << endl;
	}
}

void GeometricObject::DeleteAxis(int i)
{
	axes.erase(axes.begin() + i);
	cout << "Axis at position " << i << " deleted.";
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
	int tempi = 0;
	string temps = "";
	cout << "Select which field to edit (input the number):" << endl;
	cout << "  1. Name" << endl;
	cout << "  2. Dimensions and axes" << endl;
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
				cout << "Input the name of the axis to delete: ";
				cin >> temps;
				for (int k = 0; k < axes.size(); k++)
				{
					if (axes[k] == temps)
						tempi = k;
				}
				DeleteAxis(tempi);
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
	cout << "Returning to menu." << endl;
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

void GeometricObject::Load(vector<string> x)
{
	//to be continued...
}