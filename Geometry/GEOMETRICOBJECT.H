#pragma once
#include <iostream>
#include <vector>

using namespace std;

class GeometricObject
{
private:
	string name;
	int dimensionCount;
	vector<string> axes;
public:
	GeometricObject();
	~GeometricObject();

	//gets
	string GetName();
	int GetDimensionCount();
	vector<string> GetAxes();

	//sets
	void SetName(string n);
	void SetDimensionCount(int dC);
	void SetAxes(vector<string> a);

	//axes
	void PrintAxes();
	void AddAxis(string axis);
	void AddAxis(int i, string axis);
	void DeleteAxis(int i);
	string GetOneAxis(int i);
	int CheckAxes(); //проверяет соответствие кол-ва измерений и кол-ва осей

	void PrintSelf();
};