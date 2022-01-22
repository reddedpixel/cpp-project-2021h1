#include "Figure3D.h"

Figure3D::Figure3D()
{
	cout << "Object is now a 3D figure." << endl;
}

Figure3D::Figure3D(int fDimensions, vector<string> fAxes) : Figure2D(fDimensions, fAxes)
{
	cout << "Object is now a 3D figure." << endl;
}

Figure3D::~Figure3D()
{
	cout << "3D figure " << name << "deleted" << endl;
	cout << endl;
}
//gets
int Figure3D::GetEdges()
{
	return edges;
}

vector<Figure2D*> Figure3D::GetFaces()
{
	return faces;
}

float Figure3D::GetMeasure()
{
	return measure;
}

//sets
void Figure3D::SetEdges(int e)
{
	edges = e;
}

void Figure3D::SetFaces(vector<Figure2D*> f)
{
	faces = f;
}

//vertices
void Figure3D::AddVertex()
{
	/*if (vertices.size() - edges + faces.size() == 2)
	{
		cout << "Unable to add vertex. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
	}
	else
	{*/
		Point* vertex = new Point(dimensions, axes);
		vertex->Fill();
		vertices.push_back(vertex);
		cout << "Vertex " << vertex->GetName() << " added." << endl;
		cout << endl;
	//}
}

void Figure3D::AddVertex(Point* vertex)
{
	/*if (vertices.size() - edges + faces.size() == 2)
	{
		cout << "Unable to add vertex. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
	}
	else
	{*/
		vertices.push_back(vertex);
		cout << "Vertex " << vertex->GetName() << " added." << endl;
		cout << endl;
	//}
}

void Figure3D::AddVertex(int i, Point* vertex)
{
	/*if (vertices.size() - edges + faces.size() == 2)
	{
		cout << "Unable to add vertex. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
	}
	else
	{*/
		vertices.insert(vertices.begin() + i, vertex);
		cout << "Vertex " << vertex->GetName() << " added at position " << i << "." << endl;
		cout << endl;
	//}
}

//faces
void Figure3D::AddFace()
{
	/*if (vertices.size() - edges + faces.size() == 2)
	{
		cout << "Unable to add face. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
	}
	else
	{*/
	bool edgesAccountedFor = 0;
	string temps;
	Figure2D* face = new Figure2D(dimensions, axes);
	int tempi = 0;
	cout << "- Filling general object information. -" << endl;
	face->GeometricObject::Fill();
	cout << "--- Filling specific 2D figure information. ---" << endl;
	cout << "Input the amount of sides to add: ";
	cin >> tempi;
	face->SetEdges(tempi);
	tempi = 0;
	if (vertices.size() != 0)
	{
			cout << "Vertices already in 3D figure: ";
			PrintVertices();
			cout << endl;
			cout << "How many vertices already added to 3D figure does this face contain? ";
			cin >> tempi;
	}
	if (tempi != 0)
	{
		for (int i = 0; i < tempi; i++)
		{
			bool foundVertex = 0;
			while (!foundVertex)
			{
				cout << "Input the name of the vertex " << i + 1 << " belonging to the new face: ";
				cin >> temps;
				for (int j = 0; j < vertices.size(); j++)
				{
					if (vertices[j]->GetName() == temps)
					{
						foundVertex = 1;
						face->AddVertex(vertices[j]);
					}
				}
				if (!foundVertex)
					cout << "Unable to find vertex with that name. Please try again." << endl;
			}
				
		}
		edges = edges + face->GetEdges() - tempi + 1;
		edgesAccountedFor = 1;
	}
	face->Fill();
	faces.push_back(face);
	vector<Point*> vertexList = vertices;
	for (int l = 0; l < face->GetVertices().size(); l++)
			vertexList.push_back(face->GetVertices()[l]);
	vertexList = RemoveDuplicateVertices(vertexList);//почему без этого добавляется один лишний?
	vertexList = SortVertices(vertexList, vertexList.size());
	SetVertices(vertexList);
	if (!edgesAccountedFor)
		edges = edges + face->GetEdges();
	cout << "New face " << face->GetName() << " added." << endl;
	cout << endl;
	//}
}

void Figure3D::Figure3D::AddFace(Figure2D* face)
{
	/*if (vertices.size() - edges + faces.size() == 2)
	{
		cout << "Unable to add face. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
	}
	else
	{*/
		faces.push_back(face);
		cout << "Face " << face->GetName() << " added." << endl;
		cout << endl;
	//}
}

void Figure3D::AddFace(int i, Figure2D* face)
{
	/*if (vertices.size() - edges + faces.size() == 2)
	{
		cout << "Unable to add face. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
	}
	else
	{*/
		faces.insert(faces.begin() + i, face);
		cout << "Face " << face->GetName() << " added at position " << i << "." << endl;
		cout << endl;
	//}
}

void Figure3D::DeleteFace(int i)
{
	faces.erase(faces.begin() + i);
	cout << "Face at position " << i << " deleted." << endl;
	cout << endl;
}

void Figure3D::PrintFaces()
{
	for (int i = 0; i < faces.size(); i++)
	{
		faces[i]->PrintVertices();
		cout << " ";
	}
	cout << endl;
}

//measure
float Figure3D::CalculateMeasure()
{
	return measure;
}

bool Figure3D::CheckEulersTheorem()
{
	bool b = 0;
	if (vertices.size() - edges + faces.size() == 2)
		b = 1;
	return b;
}

void Figure3D::PrintSelf()
{
	cout << "*** 3D FIGURE INFORMATION ***" << endl;
	cout << "Figure name: " << name << endl;
	cout << "Dimensions: " << dimensions << endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
	cout << "Edges: " << edges << endl;
	cout << "Vertices: ";
	PrintVertices();
	cout << endl;
	for (int i = 0; i < vertices.size(); i++)
		vertices[i]->PrintCoords();
	cout << "Faces: " << faces.size() << endl;
	PrintFaces();
	cout << "Volume: " << measure << endl;
	cout << endl;
}

void Figure3D::Fill()
{
	int temp;
	cout << "- Filling general object information. -" << endl;
	GeometricObject::Fill();
	cout << "---- Filling specific 3D figure information. ----" << endl;
	if (CheckEulersTheorem())
	{
		cout << "Unable to fill figure. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
	}
	else
	{
		cout << "Input the amount of faces: ";
		cin >> temp;
		for (int i = 0; i < temp; i++)
		{
			cout << "- Adding face " << i + 1 << ". -" << endl;
			AddFace();
		}
	}
	cout << "3D figure " << name << " added." << endl;
	cout << "----------------" << endl;
	cout << endl;
}