/*----------------------------------------------------------------
 *  Author:        Maxim Kukhtenkov
 *  Written:       10/10/2014
 *  Last updated:  10/10/2014
 *  
 *  WordGrid Class header
 *
 *----------------------------------------------------------------*/

#ifndef WORDGRID_H
#define WORDGRID_H

#include <string>

class WordGrid
{
private:
	int maxRowCount;
	int maxColCount;
	
	class Letter
	{
	public:
		Letter(char value):value(value) {};
		char value;
		Letter* neighbors[8];
		int yCoordinate;
		int xCoordinate;
	};

	Letter*** letters;


public:
	WordGrid(int, int);
	~WordGrid();
	void display();
	void initializeLetters();
	void searchWord(std::string);
	void initializeNeighbors(bool);
	void populateNeighbors(int, int, bool);

};

#endif
