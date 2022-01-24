// Geometry.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include "Menu.h"

void test()
{
	/*GeometricObject* test1 = new GeometricObject;
	test1->Fill();
	cout << endl;
	Point* test2 = new Point;
	test2->Fill();
	cout << endl;
	Figure2D* test3 = new Figure2D;
	test3->Fill();
	cout << endl;
	test3->PrintSelf();
	Figure3D* test4 = new Figure3D;
	test4->Fill();
	test4->PrintSelf();
	test4->Fill();
	test4->PrintSelf();
	Figure2D* test5 = new Figure2D;
	test5->Fill();
	test5->PrintSelf();
	test5->SetVertices(test5->SortVertices(test5->GetVertices(), test5->GetVertices().size()));
	test5->PrintSelf();*/
	Circle* test6 = new Circle;
	test6->Fill();
	test6->PrintSelf();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu newmenu;
	newmenu.MainMenu();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
