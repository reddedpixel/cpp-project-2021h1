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

//edges
int Figure3D::RecountEdges()
{
	vector<Point*> checkedvertl;
	edges = faces[0]->GetEdges();//выбираем любую сторону в качестве начальной
	for (int i = 0; i < faces[0]->GetEdges(); i++)
		checkedvertl.push_back(faces[0]->GetVertices()[i]);//добавляем в список учтенных вершин её вершины
	for (int j = 1; j < faces.size(); j++)
	{
		vector<Point*> templist = faces[j]->GetVertices();
		int sharedvertices = 0;
		for (int j1 = 0; j1 < checkedvertl.size(); j1++)
		{
			for (int j2 = 0; j2 < templist.size(); j2++)
			{
				if (templist[j2] == checkedvertl[j1])
					sharedvertices++;
			}
		}
		edges = edges + faces[j]->GetEdges() - sharedvertices;
		if (j != faces.size() - 1)
			edges++;
	}
	return edges;
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
	vertexList = RemoveDuplicateVertices(vertexList);
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

void Figure3D::Edit()
{
	bool foundAxis = 0;
	bool foundVertex = 0;
	bool foundFace = 0;
	int tempi = 0;
	string temps = "";
	cout << "Select which field to edit (input the number):" << endl;
	cout << "  1. Name" << endl;
	cout << "  2. Dimensions" << endl;
	cout << "  3. Axes" << endl;
	cout << "  4. Faces" << endl;
	cout << "  5. Measure" << endl;
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
		cout << "Current faces: " << faces.size() << endl;
		PrintFaces();
		cout << "Select an option (input the number):" << endl;
		cout << "  1. Add face" << endl;
		cout << "  2. Delete face" << endl;
		cin >> tempi;
		switch (tempi)
		{
		case(1):
		{
			if (!CheckEulersTheorem(vertices.size(), edges, faces.size()))
			{
				AddFace();
			}
			else
				cout << "Unable to add face. 3D figure must obey Euler's theorem: V - E + F = 2." << endl;
			break;
		}
		case(2):
		{
			cout << "How many vertices does this face contain? ";
			cin >> tempi;
			vector<string> vertstr;
			foundFace = 0;
			foundVertex = 1;
			for (int j1 = 0; j1 < tempi; j1++)
			{
				cout << "Input the name of vertex " << j1 + 1 << ": ";
				cin >> temps;
				vertstr.push_back(temps);
			}
			for (int j2 = 0; j2 < faces.size(); j2++)
			{
				if (faces[j2]->GetEdges() == tempi)
				{
					for (int j3 = 0; j3 < tempi; j3++)
					{
						if (faces[j2]->GetVertices()[j3]->GetName() != vertstr[j3])
							foundVertex = 0;
					}
					if (foundVertex)
					{
						foundFace = 1;
						tempi = j2;
						break;
					}
				}
			}
			if (foundFace)
			{
				DeleteFace(tempi);
				for (int j4 = 0; j4 < vertstr.size(); j4++)
				{
					foundVertex = 0;
					for (int j5 = 0; j5 < faces.size(); j5++)
					{
						for (int j6 = 0; j6 < faces[j5]->GetEdges(); j6++)
						{
							if (faces[j5]->GetVertices()[j6]->GetName() == vertstr[j4])
							{
								foundVertex = 1;
								break;
							}
						}
						if (foundVertex)
							break;
						else
						{
							for (int j7 = 0; j7 < vertices.size(); j7++)
							{
								if (vertices[j7]->GetName() == vertstr[j4])
								{
									foundVertex = 1;
									tempi = j7;
								}
							}
							if (foundVertex)
								DeleteVertex(tempi);
						}
					}
				}
			}
			else
				cout << "Unable to find a face with these vertices." << endl;
			RecountEdges();
			break;
		}
		default:
			cout << "Invalid input." << endl;
		}
		break;
	}
	case(5):
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