#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class GeometricObject
{
protected:
	string name;
	int dimensions;
	vector<string> axes;
public:
	GeometricObject();
	GeometricObject(int fDimensions, vector<string> fAxes);
	~GeometricObject();

	//gets
	string GetName();
	int GetDimensions();
	vector<string> GetAxes();

	//sets
	void SetName(string n);
	void SetAxes(vector<string> a);
	void SetDimensions(int d);

	//axes
	void PrintAxes();
	void AddAxis();
	void AddAxis(string axis);
	void AddAxis(int i, string axis);
	void DeleteAxis(int i);
	//string GetOneAxis(int i);

	virtual void PrintSelf();
	virtual void Fill();
	virtual void Clear();
	virtual void Edit();

	virtual void Save(ofstream& f);
	virtual void Load(ifstream& fileStream);
};