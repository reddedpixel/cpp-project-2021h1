#include "Menu.h"

void Menu()
{
	bool end = 0;
	int menuop = 0;
	vector<GeometricObject*> objectList;
	while (!end)
	{
		cout << "------------------------------" << endl;
		cout << "Welcome to Geometry.exe!" << endl;
		cout << "Please select one of the options:" << endl;
		cout << "\t1. Print all objects" << endl;
		cout << "\t2. Add new object" << endl;
		cout << "\t3. Delete an object" << endl;
		cout << "\t4. Edit an object" << endl;
		cout << "\t5. Load information from file" << endl;
		cout << "\t6. Save information to file" << endl;
		cout << "\t7. Exit" << endl;
		cin >> menuop;
		switch (menuop)
		{
		case(1):
		{
			if (objectList.size() == 0)
				cout << "No objects available. Returning to menu..." << endl;
			else
			{
				cout << "Total objects: " << objectList.size() << endl;
				for (int i = 0; i < objectList.size(); i++)
					objectList[i]->PrintSelf();
			}
			break;
		}
		case(7):
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