#include<iostream>
using namespace std;

int Factorial(int n)
{
	if (n == 0) return 1;
	return n * Factorial(n - 1);
}

void main()
{
	setlocale(LC_ALL, "");

	/*
	cout << "Hello" << "\t";
	try
	{
		main();
	}
	
	//catch (const std::exception& e)
	//{
	//	std::cerr << e.what() << endl;
	//}
	
	catch (...)
	{
		std::cerr << "Somthing went wrong" << endl;
	}

	cout << "ok" << endl;
	*/

	int n;
	cout << "¬ведите число: "; cin >> n;

	cout << Factorial(n) << endl;
}