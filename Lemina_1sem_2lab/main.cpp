#include <iostream>
#include<fstream>
#include<string>
#include "TREE.h"

Tree Build_Formula(std::ifstream& file)
{
	char c = file.get();
	Tree t = new NODE();
	if (c >= '0' && c <= '9')
		t->info = c;
	else
	{
		t->left = Build_Formula(file);
		t->info = file.get();
		t->right = Build_Formula(file);
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
		}

	}

	return result;
}

int main()
{
	std::ifstream file("data.txt");
	Tree t = Build_Formula(file);
	std::cout<<Print_to_string(t);

}