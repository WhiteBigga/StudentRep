// openmpProj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <vector>
using namespace std;

// функци€ дл€ случайного расположени€ клада
int random(int a, int b)
{
	srand(time(NULL));
	if (a > 0) return a + rand() % (b - a);
	else return a + rand() % (abs(a) + b);
}

int main()
{
	cout << "You need to know the size of Treasure Island" << endl;
	// ввод длины острова
	cout << "Enter the length of the Island: ";
	int length;
	cin >> length;
	// ввод ширина острова
	cout << "Enter the width of the Island: ";
	int width;
	cin >> width;
	if (length <= 0 || width <= 0) {
		cout << "Impossible length or width...";
		exit(0);
	}
	// ввод числа групп
	cout << "Enter number of groups you need for treasure searching: ";
	int numberOfGroups;
	cin >> numberOfGroups;
	if (numberOfGroups <= 0) {
		cout << "Impossible number of groups...";
		exit(0);
	}
	int area = length * width; // считаем площадь острова
	int g_numCompareWith = random(0, area);
	vector<int> arr; //создаем вектор дл€ хранени€ всех возможных позиций с кладом
	for (int i = 0; i < area; i++){
		arr.push_back(i); //заполн€ем эти позиции целыми числами от 0 до максимального индекса (<значение площади - 1>)
	}
	// ”станавливаем желаемое количество потоков
	// ÷икл будет выполн€тьс€ в g_nNumberOfThreads потоков.
	// ѕараметры цикла будут автоматически распределены между потоками.
#pragma omp parallel num_threads(numberOfGroups)
	{
#pragma omp for
		for (int i = 0; i < area; i++)
		{
			//если группа нашла клад, то она сообщает об этом капитану
			if (arr[i] == g_numCompareWith)
			{
				cout << "Group number: " << omp_get_thread_num() << " found the treasure" << "\n";
				cout << omp_get_thread_num() << " group came back to John Silver and told him where the tresure is!" << endl;
				cout << "Good Job, pirate!" << endl;
				exit(0);
			}
		}
	}
}

