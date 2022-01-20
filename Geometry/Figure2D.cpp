#include "Figure2D.h"
Figure2D::Figure2D()
{
	sides = 0;
	measure = 0;
	cout << "Object is now a 2D figure." << endl;
}

Figure2D::Figure2D(int fDimensions, vector<string> fAxes)
{
	dimensionAmount = fDimensions;
	axes = fAxes;
	sides = 0;
	measure = 0;
	cout << "Object is now a 2D figure." << endl;
}

Figure2D::~Figure2D()
{
	cout << "2D figure " << name << " deleted." << endl;
	cout << endl;
}

//gets
vector<Point*> Figure2D::GetVertices()
{
	return vertices;
}

float Figure2D::GetMeasure()
{
	return measure;
}

int Figure2D::GetSides()
{
	return sides;
}

//sets
void Figure2D::SetVertices(vector<Point*> verts)
{
	vertices = verts;
}

void Figure2D::SetMeasure(float m)
{
	measure = m;
}

void Figure2D::SetSides(int s)
{
	sides = s;
}

//vertices
void Figure2D::AddVertex()
{
	if (vertices.size() + 1 > sides)
	{
		cout << "Unable to add vertex. There cannot be more vertices than sides." << endl;
	}
	else
	{
		Point* vertex = new Point;
		vertex->Fill();
		vertices.push_back(vertex);
		cout << "Vertex " << vertex->GetName() << " added." << endl;
		cout << endl;
	}
}

void Figure2D::AddVertex(int fDimensions, vector<string> fAxes)
{
	if (vertices.size() + 1 > sides)
	{
		cout << "Unable to add vertex. There cannot be more vertices than sides." << endl;
		cout << endl;
	}
	else
	{
		Point* vertex = new Point(fDimensions, fAxes);
		vertex->Fill();
		vertices.push_back(vertex);
		cout << "Vertex " << vertex->GetName() << " added." << endl;
		cout << endl;
	}
}

void Figure2D::AddVertex(Point* vertex)
{
	if (vertices.size() + 1 > sides)
	{
		cout << "Unable to add vertex. There cannot be more vertices than sides." << endl;
		cout << endl;
	}
	else
	{
		vertices.push_back(vertex);
		cout << "Vertex " << vertex->GetName() << " added." << endl;
		cout << endl;
	}
}

void Figure2D::AddVertex(int i, Point* vertex)
{
	if (vertices.size() + 1 > sides)
	{
		cout << "Unable to add vertex. There cannot be more vertices than sides." << endl;
		cout << endl;
	}
	else
	{
		vertices.insert(vertices.begin() + i, vertex);
		cout << "Vertex " << vertex->GetName() << " added at position " << i << "." << endl;
		cout << endl;
	}
}

void Figure2D::DeleteVertex(int i)
{
	vertices.erase(vertices.begin() + i);
	cout << "Vertex at position " << i << " deleted." << endl;
	cout << endl;
}

void Figure2D::PrintVertices()
{
	for (int i = 0; i < vertices.size(); i++)
			cout << vertices[i]->GetName();
}

void Figure2D::PrintSelf()
{
	cout << "*** 2D FIGURE INFORMATION ***" << endl;
	cout << "Figure name: " << name << endl;
	cout << "Dimensions: " << dimensionAmount << endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
	cout << "Sides: " << sides << endl;
	cout << "Vertices: ";
	PrintVertices();
	cout << endl;
	for (int i = 0; i < sides; i++)
		vertices[i]->PrintCoords();
	cout << "Area: " << measure << endl;
	cout << endl;
}

void Figure2D::Fill()
{
	int temp;
	cout << "- Filling general object information. -" << endl;
	GeometricObject::Fill();
	cout << "--- Filling specific 2D figure information. ---" << endl;
	cout << "Input the amount of sides: ";
	cin >> temp;
	SetSides(temp);
	for (int i = 0; i < sides; i++)
	{
		cout << "- Adding vertex " << i + 1 << ". -" << endl;
		AddVertex(dimensionAmount, axes);
	}
	cout << "2D figure " << name << " added." << endl;
	cout << "----------------" << endl;
	cout << endl;
}