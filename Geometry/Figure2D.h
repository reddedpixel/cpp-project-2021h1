#pragma once
#include "Point.h"

class Figure2D : virtual public Point
{
protected:
	int sides;
	vector<Point*> vertices;
	float measure;
public:
	Figure2D();
	Figure2D(int fDimensions, vector<string> fAxes);
	~Figure2D();
	//gets
	vector<Point*> GetVertices();
	virtual float GetMeasure();
	int GetSides();
	//setss
	void SetVertices(vector<Point*> verts);
	void SetMeasure(float m);
	void SetSides(int s);
	//vertices
	void AddVertex();
	void AddVertex(int fDimensions, vector<string> fAxes);
	void AddVertex(Point* vertex);
	void AddVertex(int i, Point* vertex);
	void DeleteVertex(int i);
	void PrintVertices();
	
	virtual void PrintSelf();
	virtual void Fill();
};