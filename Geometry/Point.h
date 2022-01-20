#pragma once
#include "GEOMETRICOBJECT.H"

class Point : public GeometricObject
{
protected:
	vector<float> coordinates;
public:
	Point();
	Point(int fDimensions, vector<string> fAxes);
	~Point();
	//gets
	vector<float> GetCoords();
	//sets
	void SetCoords(vector<float> v);

	//coordinates
	void EditCoordinates();
	void PrintCoords();

	virtual void PrintSelf();
	virtual void Fill();
};