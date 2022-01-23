#pragma once
#include "Figure3D.h"
#include "Circle.h"
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
private:
	vector<GeometricObject*> objectList;
};