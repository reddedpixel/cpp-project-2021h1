#pragma once
#include "GEOMETRICOBJECT.H"

class Point : public GeometricObject
{
protected:
	vector<float> coordinates;
public:
	Point();
	Point(int fDimensions, vector<string> fAxes) ;
	~Point();
	//gets
	vector<float> GetCoordinates();
	//sets
	void SetCoords(vector<float> v);

	//coordinates
	void EditCoordinates();
	void PrintCoords();

	virtual void PrintSelf();
	virtual void Fill();

	bool operator==(Point other);

	virtual void Save(FILE* F);
	virtual void Load(FILE* F);
};