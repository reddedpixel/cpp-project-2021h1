#pragma once
#include "GeometricObject.h"
#include "Point.h"
#include "Figure2D.h"
#include "Figure3D.h"
#include "Circle.h"
#include "Line.hpp"
#include "Straight.hpp"
#include "Curve.hpp"

class Menu
{
public:
	Menu();
	~Menu();
	void AddObject();
	int ChooseObject();
	void PrintList();
	void Load();
	void Save();
	void MainMenu();
	void EditObject(int i);
	void DeleteObject(int i);
	vector<GeometricObject*> SortByName(vector<GeometricObject*> list, int size);
	vector<GeometricObject*> FilterByDimensions(vector<GeometricObject*> list, int controldimensions);

private:
	vector<GeometricObject*> objectList;
};