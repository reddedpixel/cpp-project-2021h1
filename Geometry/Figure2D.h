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
	void EditAllVertexCoordinates();//нужно для редактирования осей/количества измерений в двумерной фигуре
	void DeleteVertex(int i);
	void PrintVertices();
	vector<Point*> RemoveDuplicateVertices(vector<Point*> vertexList);//удаление вершин с одинаковыми координатами
	vector<Point*> SortVertices(vector<Point*> vertexList, int size);//сортировка вершин quicksort'ом по имени
	//measure
	virtual float CalculateMeasure();//здесь просто возвращает значение, но для Circle считает
	
	virtual void PrintSelf();
	virtual void Fill();
	virtual void Clear();
	virtual void Edit();

	virtual void Save(ofstream& f);
	virtual void Load(ifstream& fileStream);
};