// MP2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

const int dataBaseSize = 15; // size of data base
int dataBase[dataBaseSize]; //data base
int front = 0; //index for reading from DB
int rear = 0; //index for writing to DB
int count = 0; //number of occupied lines in DB
unsigned int seed = 101; // used initializer

pthread_mutex_t mutex; // mutex for conditional variables
// this conditional variable blocks writer's thread  
// when the number of occupied lines in DB becomes equal to {dataBaseSize}
pthread_cond_t notFull;

// this conditional variable blocks reader's thread  
// when the number of occupied lines in DB becomes equal to 0
pthread_cond_t notEmpty;

//Function for writers with Threads
void* Writer(void* param) {
	int pNum = *((int*)param);
	int data, i;
	int k = 0;
	while (1) {
		//making a random integer element for data base (for each line) 
		data = rand() * 100 - 40;
		pthread_mutex_lock(&mutex); //protection for writing
		//thread sleeps if number of occupied lines eqals to size of the data base
		while (count == dataBaseSize) {
			pthread_cond_wait(&notFull, &mutex);
		}
		//write to line of data base
		dataBase[rear] = data;
		rear = (rear + 1) % dataBaseSize;
		//need to increase a number of occupied lines
		count++;
		//end of critical section
		pthread_mutex_unlock(&mutex);
		//calls readers after adding line to data base
		pthread_cond_broadcast(&notEmpty);
		//action output
		printf("Writer %d: Writes value = %d to line in Data Base with number [%d]\n", pNum, data, rear);
		//controlls an infinite cycle based on output (not time)
		k++;
		if (k >= 300)
			exit(0);
	}
	return NULL;
}

//Function for readers with Threads
void* Reader(void* param) {
	int cNum = *((int*)param);
	int result;
	int k = 0;
	while (1) {
		//need to read line in data base
		pthread_mutex_lock(&mutex); //reading protection
		//thread sleeps if number of occupied lines equals to 0
		while (count == 0) {
			pthread_cond_wait(&notEmpty, &mutex);
		}
		//take a line from data base
		//starting the critical section
		result = dataBase[front];
		front = (front + 1) % dataBaseSize; //critical section
		//need to decrease a number of occupied lines
		count--;
		//end of critical section
		pthread_mutex_unlock(&mutex);
		//after reading smth from data base calls writers
		pthread_cond_broadcast(&notFull);
		//action output
		printf("Reader %d: Reads value = %d from line in Data Base with number [%d]\n", cNum, result, front);
		//controlls an infinite cycle based on output (not time)
		k++;
		if (k >= 300)
			exit(0);
	}
	return NULL;
}

int main() {
	srand(seed);
	int i;
	//this is the initialization of mutex and semaphore
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&notFull, NULL);
	pthread_cond_init(&notEmpty, NULL);

	//Creation of 4 writers
	pthread_t threadWriter[4];
	int writers[4];
	for (i = 0; i < 4; i++) {
		writers[i] = i + 1;
		pthread_create(&threadWriter[i], NULL, Writer, (void*)(writers + i));		
	}

	//Creation of 5 readers
	pthread_t threadReader[5];
	int readers[5];
	for (i = 0; i < 5; i++) {
		readers[i] = i + 1;
		pthread_create(&threadReader[i], NULL, Reader, (void*)(readers + i));
	}

	//as usual let main thread be a reader
	int mNum = 0;
	Reader((void*)&mNum);
	return 0;
}


