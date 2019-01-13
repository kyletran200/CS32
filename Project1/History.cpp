#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;


History::History(int nRows, int nCols)
	: m_Rows(nRows), m_Cols(nCols), rowIndex(0), colIndex(0)
{


}

bool History::record(int r, int c)
{
	if ((r > m_Rows || c > m_Cols) || r < 1 || c < 1)
	{
		return false;
	}
	else 
	{
		rowArr[rowIndex] = r;
		colArr[colIndex] = c; 
		rowIndex++;
		colIndex++;
		return true;
	}
}

void History::display() const
{
	char grid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < m_Rows; r++)
	{
		for (c = 0; c < m_Cols; c++)
		{
			grid[r][c] = '.';
		}
	}
	
	for (int i = 0; i < rowIndex && i < colIndex; i++)
	{
		char& hGridChar = grid[rowArr[i]-1][colArr[i]-1];
		switch (hGridChar)
		{
		case '.':
			hGridChar = 'A';
			break;
		case 'Z':
			break;
		default:
			hGridChar++;
			break;

		}

	}
	clearScreen();
	
	for (r = 0; r < m_Rows; r++)
	{
		for (c = 0; c < m_Cols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
}
