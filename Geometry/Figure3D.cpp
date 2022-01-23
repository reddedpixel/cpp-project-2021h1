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
	Point* vertex = new Point(dimensions, axes);
	vertex->Fill();
	vertices.push_back(vertex);
	cout << "Vertex " << vertex->GetName() << " added." << endl;
	cout << endl;
}

void Figure3D::AddVertex(Point* vertex)
{
	vertices.push_back(vertex);
	cout << "Vertex " << vertex->GetName() << " added." << endl;
	cout << endl;
}

void Figure3D::AddVertex(int i, Point* vertex)
{
		vertices.insert(vertices.begin() + i, vertex);
		cout << "Vertex " << vertex->GetName() << " added at position " << i << "." << endl;
		cout << endl;
}

//faces
void Figure3D::AddFace()
{
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
	else
	{
		if (!CheckEulersTheorem(vertices.size(), edges, faces.size()))
			edges = edges + face->GetEdges() - tempi + 1;
	}
	cout << "New face " << face->GetName() << " added." << endl;
	cout << endl;
}

void Figure3D::Figure3D::AddFace(Figure2D* face)
{
		faces.push_back(face);
		cout << "Face " << face->GetName() << " added." << endl;
		cout << endl;
}

void Figure3D::AddFace(int i, Figure2D* face)
{
		faces.insert(faces.begin() + i, face);
		cout << "Face " << face->GetName() << " added at position " << i << "." << endl;
		cout << endl;
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

bool Figure3D::CheckEulersTheorem(int v, int e, int f)
{
	bool b = 0;
	if (v - e + f == 2)
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
	if (CheckEulersTheorem(vertices.size(), edges, faces.size()))
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

void Figure3D::Clear()
{
	name = "";
	dimensions = 0;
	axes.clear();
	coordinates.clear();
	edges = 0;
	vertices.clear();
	measure = 0;
	faces.clear();
}

void Figure3D::Save(ofstream& f)
{
	f << "<Figure3D>" << endl;
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
	f << "faces: " << endl;
	for (int l = 0; l < faces.size(); l++)
		faces[l]->Save(f);
	f << "</Figure3D>" << endl;
}

void Figure3D::Load(vector<string> x)
{

}