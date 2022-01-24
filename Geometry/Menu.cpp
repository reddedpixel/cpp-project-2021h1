#include "Menu.h"
Menu::Menu()
{
	cout << "Menu created." << endl;
}

Menu::~Menu()
{
	cout << "Menu deleted." << endl;
}

void Menu::AddObject()
{
	int tempi = 0;
	cout << "Currently available objects:" << endl;
	cout << "  1. General geometric object" << endl;
	cout << "  2. Point" << endl;
	cout << "  3. 2D figure" << endl;
	cout << "  4. 3D figure" << endl;
	cout << "  5. Line" << endl;
	cout << "Input the number of the object you'd like to add: ";
	cin >> tempi;
	switch (tempi)
	{
	case(1):
	{
		GeometricObject* obj = new GeometricObject;
		obj->Fill();
		objectList.push_back(obj);
		break;
	}
	case(2):
	{
		Point* point = new Point;
		point->Fill();
		objectList.push_back(point);
		break;
	}
	case(3):
	{
		cout << "Currently available 2D figures:" << endl;
		cout << " 1. General 2D figure" << endl;
		cout << " 2. Circle" << endl;
		cout << "Input the number of the object you'd like to add: ";
		cin >> tempi;
		switch (tempi)
		{
		case(1):
		{
			Figure2D* fig2d = new Figure2D;
			fig2d->Fill();
			objectList.push_back(fig2d);
			break;
		}
		case(2):
		{
			Circle* circle = new Circle;
			circle->Fill();
			objectList.push_back(circle);
			break;
		}
		default:
		{
			cout << "Invalid input." << endl;
			break;
		}
		}
		break;
	}
	case(4):
	{
		cout << "Currently available 3D figures:" << endl;
		cout << " 1. General 3D figure" << endl;
		cout << "Input the number of the object you'd like to add: ";
		cin >> tempi;
		switch (tempi)
		{
		case(1):
		{
			Figure3D* fig3d = new Figure3D;
			fig3d->Fill();
			objectList.push_back(fig3d);
			break;
		}
		default:
		{
			cout << "Invalid input." << endl;
			break;
		}
		}
		break;
	}
	case(5):
	{
		cout << "Currently available lines:" << endl;
		cout << " 1. General line" << endl;
		cout << " 2. Straight line" << endl;
		cout << " 3. Curve" << endl;
		cout << "Input the number of the object you'd like to add: ";
		cin >> tempi;
		switch (tempi)
		{
		case(1):
		{
			Line* line = new Line;
			line->Fill();
			objectList.push_back(line);
			break;
		}
		case(2):
		{
			Straight* sline = new Straight;
			sline->Fill();
			objectList.push_back(sline);
			break;
		}
		case(3):
		{
			Curve* curve = new Curve;
			curve->Fill();
			objectList.push_back(curve);
			break;
		}
		default:
		{
			cout << "Invalid input." << endl;
			break;
		}
		}
		break;
	}
	default:
	{
		cout << "Invalid input." << endl;
		break;
	}
	}
	cout << "Returning to menu." << endl;
}

int Menu::ChooseObject()
{

	string temps = "";
	vector<int> newObjList;
	cout << "Input the name of the object: ";
	cin >> temps;
	for (int i = 0; i < objectList.size(); i++) {
		if (objectList[i]->GetName() == temps)
			newObjList.push_back(i);
	}
	if (newObjList.size() == 0)
	{
		cout << "Unable to find an object with that name. Try again." << endl;
		return -1;
	}
	if (newObjList.size() == 1)
	{
		return newObjList[0];
	}
	if (newObjList.size() > 1)
	{
		cout << "Found multiple objects with that name." << endl;
		int tempi;
		for (int k = 0; k < newObjList.size(); k++)
		{
			cout << "Object " << k + 1 << ":" << endl;
			objectList[newObjList[k]]->PrintSelf();
			cout << endl;
		}
		cout << "Please input the number of the desired object: ";
		cin >> tempi;
		tempi--;
		return newObjList[tempi];
	}
	else
	{
		cout << "Something went wrong. Try again." << endl;
		return -1;
	}

}

void Menu::PrintList()
{
	if (objectList.size() == 0)
		cout << "No objects available. Returning to menu..." << endl;
	else
	{
		objectList = SortByName(objectList, objectList.size());
		cout << "*Total objects: " << objectList.size() <<"*"<< endl;
		for (int i = 0; i < objectList.size(); i++)
			objectList[i]->PrintSelf();
	}
}

void Menu::Load()
{
	char buf[201];
	ifstream f;
	f.open("database.txt");
	while (!f.eof())
	{
		f.getline(buf, 100);
		vector <string> stringList;
	}
	f.close();
}

void Menu::Save()
{
	ofstream f;
	f.open("database.txt");
	f << objectList.size() << endl;
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Save(f);
	}
	f.close();
}

void Menu::MainMenu()
{
	bool end = 0;
	string answer;
	int menuop = 0;
	while (!end)
	{
		cout << "------------------------------" << endl;
		cout << "Welcome to Geometry.exe!" << endl;
		cout << "Please select one of the options:" << endl;
		cout << "  1. Print all objects" << endl;
		cout << "  2. Print objects by dimension" << endl;
		cout << "  3. Add new object" << endl;
		cout << "  4. Delete an object" << endl;
		cout << "  5. Edit an object" << endl;
		cout << "  6. Load information from file" << endl;
		cout << "  7. Save information to file" << endl;
		cout << "  8. Exit" << endl;
		cin >> menuop;
		switch (menuop)
		{
		case(1):
		{
			PrintList();
			break;
		}
		case(2):
		{
			if (objectList.size() == 0)
				cout << "No objects available. Returning to menu..." << endl;
			else
			{
				vector<GeometricObject*> dim0;
				vector<GeometricObject*> dim1;
				vector<GeometricObject*> dim2;
				vector<GeometricObject*> dim3;
				dim0 = FilterByDimensions(objectList, 0);
				dim0 = SortByName(dim0, dim0.size());
				if (dim0.size() != 0)
				{
					cout << "***** Objects with no dimensional data *****" << endl;
					for (int c0 = 0; c0 < dim0.size(); c0++)
						dim0[c0]->PrintSelf();
				}
				dim1 = FilterByDimensions(objectList, 1);
				dim1 = SortByName(dim1, dim1.size());
				if (dim1.size() != 0)
				{
					cout << "***** 1-dimensional objects *****" << endl;
					for (int c1 = 0; c1 < dim1.size(); c1++)
						dim1[c1]->PrintSelf();
				}
				dim2 = FilterByDimensions(objectList, 2);
				dim2 = SortByName(dim2, dim2.size());
				if (dim2.size() != 0)
				{
					cout << "***** 2-dimensional objects *****" << endl;
					for (int c2 = 0; c2 < dim2.size(); c2++)
						dim2[c2]->PrintSelf();
				}
				dim3 = FilterByDimensions(objectList, 3);
				dim3 = SortByName(dim3, dim3.size());
				if (dim3.size() != 0)
				{
					cout << "***** 3-dimensional objects *****" << endl;
					for (int c3 = 0; c3 < dim3.size(); c3++)
						dim3[c3]->PrintSelf();
				}
			}
			break;
		}
		case(3):
		{
			AddObject();
			break;
		}
		case(4):
		{
			DeleteObject(ChooseObject());
			break;
		}
		case(5):
		{
			EditObject(ChooseObject());
			break;
		}
		case(6):
		{
			cout << "Loading from file database.txt..." << endl;
			Load();
			cout << "Returning to menu." << endl;
			break;
		}
		case(7):
		{
			cout << "Saving will delete all information previously stored in file. Are you sure you want to save? (y/n): ";
			cin >> answer;
			if ((answer == "y") || (answer == "yes"))
			{
				cout << "Saving to file database.txt..." << endl;
				Save();
				cout << "Returning to menu." << endl;
			}
			else
				cout << "Saving interrupted. Returning to menu." << endl;
			break;
		}
		case(8):
		{
			end = 1;
			cout << "Exiting..." << endl;
			break;
		}
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}
}

void Menu::EditObject(int i)
{
	if (i < 0)
	{
		cout << "Something went wrong. Try again." << endl;
	}
	else
	{
		int tempi;
		string temps;
		cout << "Editing options:" << endl;
		cout << "  1. Edit" << endl;
		cout << "  2. Refill" << endl;
		cout << "Input the number of the desired option: ";
		cin >> tempi;
		switch (tempi)
		{
		case(1):
		{
			objectList[i]->Edit();
			break;
		}
		case(2):
		{
			cout << "Refilling the object will delete all of its data. Do you want to proceed? (y/n): ";
			cin >> temps;
			if ((temps == "y") || (temps == "yes"))
			{
				objectList[i]->Clear();
				objectList[i]->Fill();
			}
			else
				cout << "Object not refilled." << endl;
			break;
		}
		default:
		{
			cout << "Invalid input." << endl;
			break;
		}
		}
		cout << "Returning to menu." << endl;
	}
}
void Menu::DeleteObject(int i)
{
	if (i < 0)
	{
		cout << "Something went wrong. Try again." << endl;
	}
	else
	{
		string answer;
		objectList[i]->PrintSelf();
		cout << "Are you sure you want to delete this object? (y/n): ";
		cin >> answer;
		if ((answer == "y")||(answer == "yes"))
		{
			objectList[i]->Clear();
			objectList.erase(objectList.begin() + i);
			cout << "Object deleted successfully." << endl;
		}
		else
			cout << "Object not deleted. Returning to menu." << endl;
	}
}

vector<GeometricObject*> Menu::SortByName(vector<GeometricObject*> list, int size)
{
	if (size != 0)
	{
		int i = 0;
		int j = size - 1;
		int midi = size / 2;
		GeometricObject* mid = list[midi];
		while (i <= j)
		{
			while (list[i]->GetName() < mid->GetName())
				i++;
			while (list[j]->GetName() > mid->GetName())
				j--;
			if (i <= j)
			{
				if (i != j)
				{
					GeometricObject* temp1 = list[i];
					GeometricObject* temp2 = list[j];
					list.erase(list.begin() + i);
					list.insert(list.begin() + i, temp2);
					list.erase(list.begin() + j);
					list.insert(list.begin() + j, temp1);
				}
				i++;
				j--;
			}
		}
		vector<GeometricObject*> left;
		int k1 = 0;
		while (k1 < midi)
		{
			left.push_back(list[k1]);
			k1++;
		}
		vector<GeometricObject*> right;
		int k2 = midi;
		while (k2 < size)
		{
			right.push_back(list[k2]);
			k2++;
		}
		list.clear();

		if (j > 0)
			left = SortByName(left, left.size());
		if (i < size)
			right = SortByName(right, right.size());
		int k3 = 0;
		while (k3 < left.size())
		{
			list.push_back(left[k3]);
			k3++;
		}
		k3 = 0;
		while (k3 < right.size())
		{
			list.push_back(right[k3]);
			k3++;
		}
	}
	return list;
}

vector<GeometricObject*> Menu::FilterByDimensions(vector<GeometricObject*> list, int controldimensions)
{
	if (list.size() > 0)
	{
		vector<GeometricObject*> templist;
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->GetDimensions() == controldimensions)
				templist.push_back(list[i]);
		}
		list.swap(templist);
		templist.clear();
	}
	return list;
}