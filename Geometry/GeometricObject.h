#pragma once
#include <iostream>
#include <vector>

using namespace std;

class GeometricObject
{
protected:
	string name;
	int dimensionAmount;
	vector<string> axes;
public:
	GeometricObject();
	GeometricObject(int fDimensions, vector<string> fAxes);
	~GeometricObject();

	//gets
	string GetName();
	int GetDimensionAmount();
	vector<string> GetAxes();

	//sets
	void SetName(string n);
	void SetAxes(vector<string> a);
	void SetDimensionAmount(int d);

	//axes
	void PrintAxes();
	void AddAxis();
	void AddAxis(string axis);
	void AddAxis(int i, string axis);
	void DeleteAxis(int i);
	//string GetOneAxis(int i);

	virtual void PrintSelf();
	virtual void Fill();
};