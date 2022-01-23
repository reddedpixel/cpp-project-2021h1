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

void Figure2D::EditAllVertexCoordinates()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		cout << "Editing coordinates for vertex " << vertices[i]->GetName() << "." << endl;
		vertices[i]->EditCoordinates();
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

vector<Point*> Figure2D::SortVertices(vector<Point*> vertexList, int size)//сортировка quicksort'ом
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
	vertices = SortVertices(vertices, edges);
	cout << "2D figure " << name << " added." << endl;
	cout << "----------------" << endl;
	cout << endl;
}

void Figure2D::Clear()
{
	name = "";
	dimensions = 0;
	axes.clear();
	coordinates.clear();
	edges = 0;
	vertices.clear();
	measure = 0;
}

void Figure2D::Edit()
{
	bool foundAxis = 0;
	bool foundVertex = 0;
	int tempi = 0;
	string temps = "";
	cout << "Select which field to edit (input the number):" << endl;
	cout << "  1. Name" << endl;
	cout << "  2. Dimensions" << endl;
	cout << "  3. Axes" << endl;
	cout << "  4. Edges" << endl;
	cout << "  5. Vertices" << endl;
	cout << "  6. Measure" << endl;
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
			EditAllVertexCoordinates();
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
						EditAllVertexCoordinates();
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
				EditAllVertexCoordinates();
			}
			else if (tempi > 0)
			{
				tempi--;
				AddAxis(tempi, temps);
				EditAllVertexCoordinates();
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
				EditAllVertexCoordinates();
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
		cout << "Current edges: " << edges << endl;
		cout << "Input the new amount of edges: ";
		cin >> tempi;
		SetEdges(tempi);
		if (tempi < vertices.size())
		{
			cout << "Deleting excess vertices." << endl;
			for (int s = 0; s < vertices.size() - tempi; s++)
			{
				foundVertex = 0;
				while (!foundVertex)
				{
					cout << "Input the name of the vertex you want to delete: ";
					cin >> temps;
					for (int s1 = 0; s1 < vertices.size(); s1++)
					{
						if (vertices[s1]->GetName() == temps)
						{
							foundVertex = 1;
							tempi = s1;
						}
					}
					if (foundVertex)
					{
						DeleteVertex(tempi);
					}
					else
						cout << "Unable to find a vertex with that name." << endl;
				}
			}
		}
		if (tempi > vertices.size())
		{
			for (int s2 = 0; s2 < tempi - vertices.size(); s2++)
				AddVertex();
		}
		vertices = SortVertices(vertices, edges);
		break;
	}
	case(5):
	{
		cout << "Current vertices: ";
		PrintVertices();
		cout << endl;
		cout << "Select an option (input the number):" << endl;
		cout << "  1. Add a vertex" << endl;
		cout << "  2. Delete a vertex" << endl;
		cout << "  3. Edit a vertex" << endl;
		cin >> tempi;
		switch (tempi)
		{
		case(1):
		{
			AddVertex();
			edges++;
			break;
		}
		case(2):
		{
			cout << "Input the name of the vertex: " << endl;
			cin >> temps;
			foundVertex = 0;
			for (int m = 0; m < vertices.size(); m++)
			{
				if (vertices[m]->GetName() == temps)
				{
					foundVertex = 1;
					tempi = m;
				}
			}
			if (foundVertex)
			{
				DeleteVertex(tempi);
				edges--;
			}
			else
				cout << "Unable to find a vertex with that name." << endl;
			break;
		}
		case(3):
		{
			cout << "Input the name of the vertex: " << endl;
			cin >> temps;
			foundVertex = 0;
			for (int m1 = 0; m1 < vertices.size(); m1++)
			{
				if (vertices[m1]->GetName() == temps)
				{
					foundVertex = 1;
					tempi = m1;
				}
			}
			if (foundVertex)
			{
				vertices[tempi]->Edit();
			}
			else
				cout << "Unable to find a vertex with that name." << endl;
			break;
		}
		default:
		{
			cout << "Invalid input." << endl;
			break;
		}
		}
		vertices = SortVertices(vertices, edges);
		break;
	}
	case(6):
	{
		cout << "Current measure: " << measure << endl;
		cout << "Input new measure: ";
		float tempf;
		scanf_s("%f", &tempf);
		measure = tempf;
		break;
	}
	default:
	{
		cout << "Invalid input." << endl;
		break;
	}
	}
}

void Figure2D::Save(ofstream& f)
{
	f << "<Figure2D>" << endl;
	f << "name: " << name << endl;
	f << "dimensions: " << dimensions << endl;
	f << "axes: ";
	for (int i = 0; i < axes.size(); i++)
		f << axes[i] << " ";
	f << endl;
	f << "coordinates: 0" << endl;
	f << "edges: " << edges << endl;
	f << "vertices: " << endl;
	for (int k = 0; k < vertices.size(); k++)
		vertices[k]->Save(f);
	f << "measure: " << measure << endl;
	f << "</Figure2D>" << endl;
}

void Figure2D::Load(vector<string> x)
{

}