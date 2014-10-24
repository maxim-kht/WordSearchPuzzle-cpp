/*----------------------------------------------------------------
 *  Author:        Maxim Kukhtenkov
 *  Written:       10/10/2014
 *  Last updated:  10/10/2014
 *  
 *  Main Class for a Word Search Puzzle
 *
 *
 *----------------------------------------------------------------*/

#include <iostream>
#include <string>
#include "WordGrid.h"


int main()
{

	std::cout << "\n-------------------\n"
			    << "    Word Search    \n"
		        << "-------------------\n\n\n";

	//-------------------------------------------------------
	/* 1. Input the number of rows and columns */
	//-------------------------------------------------------

	int rows;
	int columns;

	std::cout << "Enter the number of rows: ";
	std::cin >> rows;

	std::cout << "Enter the number of columns: ";
	std::cin >> columns;

	WordGrid* grid = new WordGrid(rows, columns);

	grid->display();


	/*---------------------------------------------------------
	*  2. Chose the wrap or no wrap mode
	*-------------------------------------------------------*/

	bool wrap = false;

	int choice;
	std::cout << "Choose the mode: \n1. Wrap\n2. No wrap\n(Type 1 for wrap or 2 for no-wrap)\n";
	std::cin >> choice;

	// Validate input
	while (choice < 1 || choice > 2)
	{
		std::cout << "Please type 1 for Wrap mode or 2 for No Wrap";
		std::cin >> choice;
	}

	// Assign wrap
	switch (choice) 
	{
	case 1: wrap = true;
		std::cout << "You chose the WRAP mode\n";
		break;
	case 2: wrap = false;
		std::cout << "You chose the NO WRAP mode\n";
		break;
	}

	grid->initializeNeighbors(wrap);


	/*---------------------------------------------------------
	*  3. Insert words and search them in the grid
	*-------------------------------------------------------*/

	int numOfWords;
	std::cout << "How many words do you wish to find?\n";
	std::cin >> numOfWords;
	std::cin.ignore(); // Consume newline left over

	std::string* words = new std::string[numOfWords];

	// Enter the words
	std::cout << "Enter " << numOfWords << ((numOfWords > 1) ? " words: " : " word: ") << "\n";
	for (int i = 0; i < numOfWords; i++) 
	{
		std::getline(std::cin, words[i]);
	}

	// Search and output the result
	std::cout << "\n------------\n Output\n------------\n\n";
	for (int i = 0; i < numOfWords; i++)
	{
		grid->searchWord(words[i]);
	}

	std::cout << "Thanks for playing!\n";

    delete[] words;
	delete grid;

	return 0;
}