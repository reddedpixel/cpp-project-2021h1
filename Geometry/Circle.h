#pragma once
#include"Figure2D.h"

class Circle : public Figure2D
{
private:
	float radius;
public:
	Circle();
	~Circle();
	//gets
	float GetRadius();
	//sets
	void SetRadius(float r);
	//measure
	virtual float CalculateMeasure();

	virtual void PrintSelf();
	virtual void Fill();

};