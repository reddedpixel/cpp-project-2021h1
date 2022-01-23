#include "Circle.h"

Circle::Circle()
{
	radius = 0;
	edges = 1;
	cout << "Object is now a circle." << endl;
}

Circle::~Circle()
{
	cout << "Circle " << name << "deleted." << endl;
}

//gets
float Circle::GetRadius()
{
	return radius;
}

//sets
void Circle::SetRadius(float r)
{
	radius = r;
}

//measure
float Circle::CalculateMeasure()
{
	float pi = 3.1415926f;
	measure = pi * (radius * radius);
	return measure;
}

void Circle::PrintSelf()
{
	cout << "*** CIRCLE INFORMATION ***" << endl;
	cout << "Circle name: " << name << endl;
	cout << "Dimensions: " << dimensions << endl;
	cout << "Axes: ";
	PrintAxes();
	cout << endl;
	cout << "Center: ";
	PrintVertices();
	cout << endl;
	for (int i = 0; i < edges; i++)
		vertices[i]->PrintCoords();
	cout << "Area: " << CalculateMeasure() << endl;
	cout << endl;
}

void Circle::Fill()
{

	cout << "- Filling general object information. -" << endl;
	GeometricObject::Fill();
	cout << "--- Filling specific circle information. ---" << endl;
	cout<<"- Adding circle center. -" << endl;
	AddVertex();
	cout << "Input circle radius: ";
	scanf_s("%f", &radius);
	cout << "Circle " << name << " added." << endl;
	cout << "----------------" << endl;
	cout << endl;

}

void Circle::Clear()
{
	name = "";
	dimensions = 0;
	axes.clear();
	coordinates.clear();
	edges = 0;
	vertices.clear();
	measure = 0;
	radius = 0;
}

void Circle::Save(ofstream& f)
{
	f << "<Circle>" << endl;
	f << "name: " << name << endl;
	f << "dimensions: " << dimensions << endl;
	f << "axes: ";
	for (int i = 0; i < axes.size(); i++)
		f << axes[i] << " ";
	f << endl;
	f << "coordinates: 0" << endl;
	f << "edges: 1" << endl;
	f << "vertices: " << endl;
	vertices[0]->Save(f);
	f << "measure: " << measure << endl;
	f << "radius: " << radius << endl;
	f << "</Circle>" << endl;
}

void Circle::Load(vector<string> x)
{

}