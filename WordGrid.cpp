/*----------------------------------------------------------------
 *  Author:        Maxim Kukhtenkov
 *  Written:       10/10/2014
 *  Last updated:  11/12/2014
 *  
 *  WordGrid Class for a Word Search Puzzle. Used to create a
 *  word grid object.
 *
 *----------------------------------------------------------------*/

#include <iostream>
#include "WordGrid.h"


WordGrid::WordGrid(int maxRowCount, int maxColCount)
{
	letters = new Letter**[maxRowCount];

	for (int y = 0; y < maxRowCount; y++)
	{
		letters[y] = new Letter*[maxColCount];
	}
		

	int numOfLetters = 0;
	for (int y = 0; y < maxRowCount; y++)
	{
		for (int x = 0; x < maxColCount; x++)
		{
			letters[y][x] = new Letter('A' + numOfLetters);
			letters[y][x]->yCoordinate = y;
			letters[y][x]->xCoordinate = x;
			numOfLetters++;
			if (numOfLetters == 26)
			{
				numOfLetters = 0;
			}
				
		}
	}
	
	this->maxRowCount = maxRowCount;
	this->maxColCount = maxColCount;
}


WordGrid::~WordGrid()
{
	/* Delete the wordGrid */
	for (int y = 0; y < maxRowCount; y++)
		delete[] letters[y];
	delete[] letters;
}



void WordGrid::display()
{
	std::cout << "\n\n";

	for (int y = 0; y < maxRowCount; y++)
	{
		std::cout << y << " |\t";
		for (int x = 0; x < maxColCount; x++)
		{
			std::cout << letters[y][x]->value << "  ";
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "\n\n";
}


void WordGrid::searchWord(std::string word) {
	int startY = 0;
	int startX = 0;
	int endY = 0;
	int endX = 0;

	bool wordFound = false;

	for (int y = 0; y < maxRowCount && !wordFound; y++)
		for (int x = 0; x < maxColCount && !wordFound; x++)
		{
			// If first letter is found
			if (toupper(word[0]) == letters[y][x]->value)
			{
				startY = y;
				startX = x;

				// Search all neighbors
				for (int i = 0; i < 8 && !wordFound; i++)
				{
					bool nextLetterFound = true;
					int count = 1;
					Letter* currentLetter = letters[y][x]->neighbors[i];

					while (count < word.length() && nextLetterFound && !wordFound && currentLetter->value != '0')
					{
						if (toupper(word[count]) != currentLetter->value)
						{
							nextLetterFound = false;
						}
						else if (count == word.length() - 1 && toupper(word[count]) == currentLetter->value)
						{
							wordFound = true;
							endY = currentLetter->yCoordinate;
							endX = currentLetter->xCoordinate;
						}
						else
						{
							count++;
							currentLetter = currentLetter->neighbors[i];
						}
					}
				} // End-search all neighbors

			} // End-if first letter is found
			
		}

	if (wordFound) 
	{
		std::cout << "(" << startX << ", " << startY << "), (" << endX << ", " << endY << ")\n";
	}
	else 
	{
		std::cout << "Not Found\n";
	}
}


// Initializes neighbors of each Letter
void WordGrid::initializeNeighbors(bool wrap) 
{
	for (int y = 0; y < maxRowCount; y++) 
	{
		for (int x = 0; x < maxColCount; x++) 
		{
			populateNeighbors(y, x, wrap);
		}
	}
}


void WordGrid::populateNeighbors(int y, int x, bool wrap) {
	int maxRow = maxRowCount - 1;
	int maxCol = maxColCount - 1;

	bool northLimit = (y == 0);
	bool southLimit = (y == maxRow);
	bool westLimit = (x == 0);
	bool eastLimit = (x == maxCol);

	// North-West
	if (!northLimit && !westLimit) 
		letters[y][x]->neighbors[0] = letters[y - 1][x - 1];
	else if (!wrap)
		letters[y][x]->neighbors[0] = new Letter('0');
	else if (northLimit && westLimit)
		letters[y][x]->neighbors[0] = letters[maxRow][maxCol];
	else if (northLimit)
		letters[y][x]->neighbors[0] = letters[maxRow][x - 1];
	else if (westLimit)
		letters[y][x]->neighbors[0] = letters[y - 1][maxCol];

	// North
	if (!northLimit)
		letters[y][x]->neighbors[1] = letters[y - 1][x];
	else if (!wrap)
		letters[y][x]->neighbors[1] = new Letter('0');
	else if (northLimit)
		letters[y][x]->neighbors[1] = letters[maxRow][x];

	//North-East
	if (!northLimit && !eastLimit)
		letters[y][x]->neighbors[2] = letters[y - 1][x + 1];
	else if (!wrap)
		letters[y][x]->neighbors[2] = new Letter('0');
	else if (northLimit && eastLimit)
		letters[y][x]->neighbors[2] = letters[maxRow][0];
	else if (northLimit)
		letters[y][x]->neighbors[2] = letters[maxRow][x + 1];
	else if (eastLimit)
		letters[y][x]->neighbors[2] = letters[y - 1][0];

	//East
	if (!eastLimit)
		letters[y][x]->neighbors[3] = letters[y][x + 1];
	else if (!wrap)
		letters[y][x]->neighbors[3] = new Letter('0');
	else if (eastLimit)
		letters[y][x]->neighbors[3] = letters[y][0];

	//South-East
	if (!southLimit && !eastLimit)
		letters[y][x]->neighbors[4] = letters[y + 1][x + 1];
	else if (!wrap)
		letters[y][x]->neighbors[4] = new Letter('0');
	else if (southLimit && eastLimit)
		letters[y][x]->neighbors[4] = letters[0][0];
	else if (southLimit)
		letters[y][x]->neighbors[4] = letters[0][x + 1];
	else if (eastLimit)
		letters[y][x]->neighbors[4] = letters[y + 1][0];

	//South
	if (!southLimit)
		letters[y][x]->neighbors[5] = letters[y + 1][x];
	else if (!wrap)
		letters[y][x]->neighbors[5] = new Letter('0');
	else if (southLimit)
		letters[y][x]->neighbors[5] = letters[0][x];

	//South-West
	if (!southLimit && !westLimit)
		letters[y][x]->neighbors[6] = letters[y + 1][x - 1];
	else if (!wrap)
		letters[y][x]->neighbors[6] = new Letter('0');
	else if (westLimit && southLimit)
		letters[y][x]->neighbors[6] = letters[0][maxCol];
	else if (westLimit)
		letters[y][x]->neighbors[6] = letters[y + 1][maxCol];
	else if (southLimit)
		letters[y][x]->neighbors[6] = letters[0][x - 1];

	//West
	if (!westLimit)
		letters[y][x]->neighbors[7] = letters[y][x - 1];
	else if (!wrap)
		letters[y][x]->neighbors[7] = new Letter('0');
	else if (westLimit)
		letters[y][x]->neighbors[7] = letters[y][maxCol];
}
