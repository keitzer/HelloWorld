//
//  HelloWorld.cpp
//  C++Projects
//
//  Created by Alex Ogorek on 9/1/14.
//  Copyright (c) 2014 Alex Ogorek. All rights reserved.
//

#include "HelloWorld.h"

//note with recursive functions, you HAVE to break it up into smaller pieces. else bad things happen
int factorial(int x)
{
	if (x <= 1)
		return x;
	else
		return x * factorial(x-1);
}

int getIndexOfElementInArray(int value, int *array, int low, int high)
{
	//not found
	if (high < low)
		return -1;
	
	//if this is the value
	int mid = (high + low) / 2;
	if (value == array[mid])
		return mid;
	
	//if the value is smaller...
	if (value < array[mid])
		return getIndexOfElementInArray(value, array, low, mid-1);
	
	//or larger...
	return getIndexOfElementInArray(value, array, mid+1, high);
}

void printSolution(int n, int *q, int **t)
{
	for (int x = 0; x < n; ++x)
	{
		for (int y = 0; y < n; ++y)
		{
			if (q[x] == y)
				std::cout << "Q";
			else
				std::cout << "x";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void changeThreats(int n, int rowValue, int colValue, int changeValue, int **t)
{
	//update the threats row by row
	for (int x = rowValue+1; x < n; ++x)
	{
		//vertically down
		t[x][colValue] += changeValue;
		
		//diagonally left down
		if (colValue - (x - rowValue) >= 0)
			t[x][colValue - (x - rowValue)] += changeValue;
		
		//diagonally right down
		if (colValue + (x - rowValue) < n)
			t[x][colValue + (x  - rowValue)] += changeValue;
	}
}

void queenSearch(int row, int n, int *q, int **t)
{
	if (row == n)
		printSolution(n,q,t);
	else
	{
		for (q[row] = 0; q[row] < n; ++q[row])
		{
			if (t[row][q[row]] == 0)
			{
				changeThreats(n, row, q[row], 1, t);
				queenSearch(row+1, n, q, t);
				changeThreats(n, row, q[row], -1, t);
			}
		}
	}
}

int main()
{
	
	/*
		Recursion (via a Factorial example)
	 */
	
	int factorialValue = 4;
	
	
	for (int x = factorialValue; x > 0; --x)
		std::cout << x << "*";
	std::cout << " should be: ";
	int result = 1;
	for (int x = 1; x <= factorialValue; ++x)
		result *= x;
	std::cout << result << std::endl;
	
	std::cout << "Result: " << factorial(factorialValue) << std::endl;
	
	
	
	/*
		Binary Search -- also recursion
	 */
	
	std::cout << "\n\n";
	
	int valueToFind = 7;
	
	int *arrayOfNumbers = new int[10];
	int sizeOfArray = 10;
	
	// = {1,2,3,4,5,6,7,8,9,10};
	for (int x = 1; x <= sizeOfArray; ++x)
		arrayOfNumbers[x-1] = x;
	
	for (int x = 0; x < sizeOfArray; ++x)
		std::cout << arrayOfNumbers[x] << ",";
	std::cout << std::endl;
	
	std::cout << "Index of " << valueToFind << " is: " << getIndexOfElementInArray(valueToFind, arrayOfNumbers, 0, sizeOfArray-1) << std::endl;
	
	
	
	
	/*
		n-Queens problem
		n*n chessboard... place a queen on the board
		place N queens, so that no 2 queens can attack each other
		implemented using an idea called "backtracking"
		
	 eg: 4x4 grid
		first, place 1 queen per row, 1st, 2nd... etc.. 
		if there's not enough room on the current row, backtrack to the previous row
		so if trying to place 3rd queen, you can't... move the 2nd queen over by 1 column
		no fourth? re-place the 3rd... no where for the 3rd? re-place the 2nd... no place for 2nd? re-place 1st
		go again...
		1st queen in 2nd column... 2nd queen, far right, 3rd queen far left, 4th queen 2nd from far right
	 */
	
	int n = 4;
	std::cout << "How many queens?: ";
	std::cin >> n;
	
	int *q = new int[n];
	int **t = new int* [n];// = new int[n][n];
	
	//init the "threats" 2D array
	for (int x = 0; x < n; ++x)
	{
		t[x] = new int[x];
		for (int y = 0; y < n; ++y)
		{
			t[x][y] = 0;
		}
	}
	
	queenSearch(1, n, q, t);
	
	//de-allocate memory
	delete [] q;
	for (int x = 0; x < n; ++x)
		delete [] t[x];
	delete [] t;
}