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

/*string GeometricObject::GetOneAxis(int i)
{
	return axes[i]; 
}*/

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

void GeometricObject::Save(FILE* F)
{

}

void GeometricObject::Load(FILE* F)
{
	fprintf(F, "%s\n", "GeometricObject");
	fprintf(F, "%s", "name :");
	
}