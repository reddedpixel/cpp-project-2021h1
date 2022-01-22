#include "Figure2D.h"
Figure2D::Figure2D()
{
	edges = 0;
	measure = 0;
	cout << "Object is now a 2D figure." << endl;
}

Figure2D::Figure2D(int fDimensions, vector<string> fAxes) : Point(fDimensions, fAxes)
{
	edges = 0;
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

int Figure2D::GetEdges()
{
	return edges;
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

void Figure2D::SetEdges(int e)
{
	edges = e;
}

//vertices
void Figure2D::AddVertex()
{
	if (vertices.size() + 1 > edges)
	{
		cout << "Unable to add vertex. There cannot be more vertices than sides." << endl;
	}
	else
	{
		Point* vertex = new Point(dimensions, axes);
		vertex->Fill();
		vertices.push_back(vertex);
		cout << "Vertex " << vertex->GetName() << " added." << endl;
		cout << endl;
	}
}

void Figure2D::AddVertex(Point* vertex)
{
	if (vertices.size() + 1 > edges)
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
	if (vertices.size() + 1 > edges)
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
	edges -= 1;
	cout << "Vertex at position " << i << " deleted." << endl;
	cout << endl;
}

void Figure2D::PrintVertices()
{
	for (int i = 0; i < vertices.size(); i++)
			cout << vertices[i]->GetName()<<" ";
}

vector<Point*> Figure2D::RemoveDuplicateVertices(vector<Point*> vertexList)
{
	for (int i = 0; i < vertexList.size()-1; i++)
	{
		for (int j = i + 1; j < vertexList.size(); j++)
		{
			if (vertexList[i]->GetCoordinates() == vertexList[j]->GetCoordinates())
			{
				vertexList.erase(vertexList.begin() + j);
				j--;
			}
		}
	}
	return vertexList;
}

vector<Point*> Figure2D::SortVertices(vector<Point*> vertexList, int size)
{
	int i = 0;
	int j = size - 1;
	int midi = size / 2;
	Point* mid = vertexList[midi];
	while (i <= j)
	{
		while (vertexList[i]->GetName() < mid->GetName())
			i++;
		while (vertexList[j]->GetName() > mid->GetName())
			j--;
		if (i <= j)
		{
			if (i != j)
			{
				Point* temp1 = vertexList[i];
				Point* temp2 = vertexList[j];
				vertexList.erase(vertexList.begin() + i);
				vertexList.insert(vertexList.begin() + i, temp2);
				vertexList.erase(vertexList.begin() + j);
				vertexList.insert(vertexList.begin() + j, temp1);
			}
			i++;
			j--;
		}
	}
	vector<Point*> left;
	int k1 = 0;
	while (k1 < midi)
	{
		left.push_back(vertexList[k1]);
		k1++;
	}
	vector<Point*> right;
	int k2 = midi;
	while (k2 < size)
	{
		right.push_back(vertexList[k2]);
		k2++;
	}
	vertexList.clear();

	if (j > 0)
		left = SortVertices(left, left.size());
	if (i < size)
		right = SortVertices(right, right.size());
	int k3 = 0;
	while (k3 < left.size())
	{
		vertexList.push_back(left[k3]);
		k3++;
	}
	k3 = 0;
	while (k3 < right.size())
	{
		vertexList.push_back(right[k3]);
		k3++;
	}

	return vertexList;

}

//measure
float Figure2D::CalculateMeasure()
{
	return measure;
}

void Figure2D::PrintSelf()
{
	cout << "*** 2D FIGURE INFORMATION ***" << endl;
	cout << "Figure name: " << name << endl;
	cout << "Dimensions: " << dimensions << endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
	cout << "Sides: " << edges << endl;
	cout << "Vertices: ";
	PrintVertices();
	cout << endl;
	for (int i = 0; i < edges; i++)
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
	if (edges == 0)
	{
		cout << "Input the amount of sides: ";
		cin >> temp;
		SetEdges(temp);
	}
	for (int i = vertices.size(); i < edges; i++)
	{
		cout << "- Adding new vertex " << i + 1 << ". -" << endl;
		AddVertex();
	}
	cout << "2D figure " << name << " added." << endl;
	cout << "----------------" << endl;
	cout << endl;
}