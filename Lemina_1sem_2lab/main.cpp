#include <iostream>
#include<fstream>
#include<string>
#include <functional>
#include "TREE.h"
#include<Windows.h>

const int ALPHABET_SIZE = 26;


Tree Build_Formula(std::ifstream& file,int* arr)
{
	char c = file.get();
	Tree t = new NODE();
	if (c >= '0' && c <= '9')
		t->info = c;
	else
		if (c >= 'a' && c <= 'z')
		{
			int k = c - 'a';
			t->info = arr[k];
		}
		else
		{
			t->left = Build_Formula(file, arr);
			t->info = file.get();
			t->right = Build_Formula(file, arr);
			c = file.get();
		}
	return t;
}

std::string Print_to_string(const Tree& t)
{
	std::string result{};
	if (!t->left && !t->right)
	{
		result += t->info;
	}
	else
		result = '(' + Print_to_string(t->left) + Print_to_string(t->right) + ')';
	return result;
}

int Calculate(const Tree& t)
{
	int result{};
	if (!t->left && !t->right)
		result = t->info - '0';
	else
	{
		int leftF{ Calculate(t->left) };
		int rightF{ Calculate(t->right) };
		switch (t->info)
		{
		case '+':
			result = leftF + rightF;
			break;
		case '*':
			result = leftF * rightF;
			break;
		case '-':
			result = leftF - rightF;
			break;
		case '/':
			result = leftF / rightF;
		}

	}

	return result;
}

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
	std::cout << message << "\n>>> ";
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!" << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}
}
	int main_menu()
	{
		std::cout << "\nМеню Бинарного дерева\n";
		std::cout << "\n-----------------------------------------------------\n";
		std::cout << "1. Заполнить из файла\n";
		std::cout << "2. Печать\n";
		std::cout << "3. Очистить\n";
		std::cout << "4. Решить задачу\n";
		std::cout << "5. Выйти из программы\n";
		std::cout << "-----------------------------------------------------\n";

		std::function<bool(int)> foo;
		foo = [](int x)->bool {return x >= 1 && x <= 5; };
		int choice;
		validation(choice, foo, "");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		return choice;
	}

	void fill_array(int* arr,std::ifstream& file)
	{
		for (int i = 0; i < ALPHABET_SIZE; ++i)
		{
			file >> arr[i];
		}
	}
	
	void print_array(int* arr)
	{
		for (int i = 0; i < ALPHABET_SIZE; ++i)
		{
			std::cout << arr[i] << ' ';
		}
		std::cout << '\n';
	}

int main()
{
	SetConsoleOutputCP(1251);
	std::ifstream file("data.txt");
	std::ifstream file_test("test_data.txt");
	std::ifstream file_arr("peremInfo.txt");
	int* arr = new int [ALPHABET_SIZE];

	fill_array(arr,file_arr);
	

	int choice;
	TREE t;
	Tree root{};
	int n = 0;
	do {
		choice = main_menu();
		switch (choice)
		{
		case 1:
			file_test.clear();           
			file_test.seekg(0, std::ios::beg);
			file_test >> n;
			root =t.fillFromFile(n, file_test);
			break;
		case 2:
			t.print(root, 0);
			break;
		case 3:
			t.clear(root);
			break;
		case 4:
			Tree tr = Build_Formula(file,arr);
			std::cout << "\nРезультат формулы: " << Calculate(tr)<<'\n';
		}


	} while (choice != 5);

	delete[] arr;
}