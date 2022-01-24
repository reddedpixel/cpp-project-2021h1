#pragma once
#include "Figure2D.h"

class Figure3D : public Figure2D
{
protected:
	vector<Figure2D*> faces;
public:
	Figure3D();
	Figure3D(int fDimensions, vector<string> fAxes);
	~Figure3D();
	//gets
	int GetEdges();
	vector<Figure2D*> GetFaces();
	virtual float GetMeasure();
	//sets
	void SetEdges(int e);
	void SetFaces(vector<Figure2D*> f);
	//vertices
	virtual void AddVertex();
	virtual void AddVertex(Point* vertex);
	virtual void AddVertex(int i, Point* vertex);
	//edges
	virtual int RecountEdges();
	//faces
	void AddFace();
	void AddFace(Figure2D* face);
	void AddFace(int i, Figure2D* face);
	void DeleteFace(int i);
	void PrintFaces();
	//measure
	virtual float CalculateMeasure();//здесь просто возвращает объем.  ласс Sphere с подсчЄтом объема реализовать € не успел :/

	bool CheckEulersTheorem(int v, int e, int f);//проверка на выполнение теоремы Ёйлера дл€ выпуклых многогранников
	virtual void PrintSelf();
	virtual void Fill();
	virtual void Clear();
	virtual void Edit();

	virtual void Save(ofstream& f);
	virtual void Load(ifstream& fileStream);
};