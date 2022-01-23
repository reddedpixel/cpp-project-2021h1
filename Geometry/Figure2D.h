#pragma once
#include "Point.h"

class Figure2D : virtual public Point
{
protected:
	int edges;
	vector<Point*> vertices;
	float measure;
public:
	Figure2D();
	Figure2D(int fDimensions, vector<string> fAxes);
	~Figure2D();
	//gets
	vector<Point*> GetVertices();
	virtual float GetMeasure();
	int GetEdges();
	//setss
	void SetVertices(vector<Point*> verts);
	void SetMeasure(float m);
	void SetEdges(int e);
	//vertices
	virtual void AddVertex();
	virtual void AddVertex(Point* vertex);
	virtual void AddVertex(int i, Point* vertex);
	void EditAllVertexCoordinates();
	void DeleteVertex(int i);
	void PrintVertices();
	vector<Point*> RemoveDuplicateVertices(vector<Point*> vertexList);
	vector<Point*> SortVertices(vector<Point*> vertexList, int size);
	//measure
	virtual float CalculateMeasure();
	
	virtual void PrintSelf();
	virtual void Fill();
	virtual void Clear();
	virtual void Edit();

	virtual void Save(ofstream& f);
	virtual void Load(vector<string> x);
};