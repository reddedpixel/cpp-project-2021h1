#pragma once
#include "GEOMETRICOBJECT.H"

class Point : public GeometricObject
{
private:
	vector<double> coordinates;
public:
	Point();
	~Point();
	//gets
	vector<double> GetCoords();
	//sets
	void SetCoords(vector<double> v);
	void SetCoords();

	void PrintCoords();

	virtual void PrintSelf();
	virtual void Fill();
};