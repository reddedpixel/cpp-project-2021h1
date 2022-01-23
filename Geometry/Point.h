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
	virtual void Clear();
	virtual void Edit();

	bool operator==(Point other);

	virtual void Save(ofstream& f);
	virtual void Load(vector<string> x);
};