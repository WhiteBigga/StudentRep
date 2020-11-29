// openmpProj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <vector>
using namespace std;

// function for the random treasure position
int random(int a, int b)
{
	srand(time(NULL));
	if (a > 0) return a + rand() % (b - a);
	else return a + rand() % (abs(a) + b);
}

int main()
{
	cout << "You need to know the size of Treasure Island" << endl;
	// island length input
	cout << "Enter the length of the Island: ";
	int length;
	cin >> length;
	// island width input
	cout << "Enter the width of the Island: ";
	int width;
	cin >> width;
	if (length <= 0 || width <= 0) {
		cout << "Impossible length or width...";
		exit(0);
	}
	// groups number input
	cout << "Enter number of groups you need for treasure searching: ";
	int numberOfGroups;
	cin >> numberOfGroups;
	if (numberOfGroups <= 0) {
		cout << "Impossible number of groups...";
		exit(0);
	}
	int area = length * width; // calculating area of the island
	int g_numCompareWith = random(0, area);
	vector<int> arr; //vector for all posible treasure positions
	for (int i = 0; i < area; i++){
		arr.push_back(i); // put 0 to <area - 1> numbers into this vector
	}
	// set thread number
	// cycle executes in <numberOfGroups> threads.
	// cycle parameters automatically spread between threads.
#pragma omp parallel num_threads(numberOfGroups)
	{
#pragma omp for
		for (int i = 0; i < area; i++)
		{
			//if group finds a treasure, it will return to the captain and tell him where it is
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

