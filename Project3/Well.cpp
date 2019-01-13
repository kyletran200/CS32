#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"



Well::~Well()
{
	for (unsigned int i = 0; i < m_piece.size(); i++) //Destroy all piece pointers in destructor
	{
		delete m_piece[i];
	}
}


Well::Well(int width, int height)
	: m_height(height), m_width(width)
{
	m_well.resize(m_height, vector<char>(m_width + 2));

	for (int i = 0; i < m_height; i++)  //Loop through height and set values to @ and print
	{

		m_well[i][0] = '@';
		if (i >= 0 && i < m_height - 1)
		{
			m_well[i][m_width + 1] = '@';
		}
		if (i == m_height - 1)					
		{
			for (int j = 0; j < m_width + 2; j++)
			{
				m_well[i][j] = '@';
			}
		}
	}  //Also set the bottom row and right column

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width + 2; j++)  
		{
			if (m_well[i][j] != '@')
			{
				m_well[i][j] = ' ';
			}
		}
	}
}




void Well::display(Screen& screen, int x, int y)
{
	screen.clear();				//Loop through the well and display it

	for (int i = x; i < m_height; i++)
	{
		for (int j = y; j < m_width + 2; j++)
		{
			screen.gotoXY(j, i);
			screen.printChar(m_well[i][j]);
		}
	}
	screen.gotoXY(16, 3); //Print next piece
	screen.printString("Next piece:");
}

void Well::displayNextPiece(Screen& screen, PieceType type) const
{
	std::vector< std::vector<char> > nextPiece;

	switch (type)   //Decide what piece to display based off the type given
	{
	case PIECE_I:
		nextPiece = {
		{ ' ',' ',' ',' ' }, //0
		{ '#','#','#','#' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_O:
		nextPiece = {
			{ '#','#',' ',' ' }, //0
		{ '#','#',' ',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_T:
		nextPiece = {
			{ ' ','#',' ',' ' }, //0
		{ '#','#','#',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
		break;
	case PIECE_L:
		nextPiece = {
			{ ' ',' ',' ',' ' }, //0
		{ '#','#','#',' ' }, //1
		{ '#',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_J:
		nextPiece = {
			{ ' ',' ',' ',' ' }, //0
		{ ' ','#','#','#' }, //1
		{ ' ',' ',' ','#' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_S:
		nextPiece = {
			{ ' ',' ',' ',' ' }, //0
		{ ' ','#','#',' ' }, //1
		{ '#','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_Z:
		nextPiece = {
			{ ' ',' ',' ',' ' }, //0
		{ '#','#',' ',' ' }, //1
		{ ' ','#','#',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_CRAZY:
		nextPiece = {
		{ '#',' ',' ','#' }, //0
		{ ' ','#','#',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_VAPOR:
		nextPiece = {
		{ ' ','#','#',' ' }, //0
		{ ' ',' ',' ',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	case PIECE_FOAM:
		nextPiece = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ','#',' ',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	default:
		nextPiece = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ','#',' ',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		};
		break;
	}
	for (int i = 0; i < 4; i++)			//Print the next piece
	{
		for (int j = 0; j < 4; j++)
		{
			screen.gotoXY(16 + j, 4 + i);
			screen.printChar(nextPiece[i][j]);
		}
	}
}


void Well::setCoordinate(int row, int col, char val)
{
	m_well[row][col] = val;  //Set value of well
}

Piece* Well::getPiece() const
{
	return m_piece.back();  //Return the back piece added to the vector
}



char Well::getValueAtCoordinate(int row, int col) const
{
	return m_well[row][col];
}

void Well::addPiece(PieceType type)
{
	if (type == PIECE_O)		//Decide what piece to add to the vector based off of type given
	{
		m_piece.push_back(new Piece_O(this));
	}
	else if (type == PIECE_I)
	{
		m_piece.push_back(new Piece_I(this));
	}
	else if (type == PIECE_T)
	{
		m_piece.push_back(new Piece_T(this));
	}
	else if (type == PIECE_L)
	{
		m_piece.push_back(new Piece_L(this));
	}
	else if (type == PIECE_J)
	{
		m_piece.push_back(new Piece_J(this));
	}
	else if (type == PIECE_S)
	{
		m_piece.push_back(new Piece_S(this));
	}
	else if (type == PIECE_Z)
	{
		m_piece.push_back(new Piece_Z(this));
	}
	else if (type == PIECE_CRAZY)
	{
		m_piece.push_back(new CrazyShape(this));
	}
	else if (type == PIECE_VAPOR)
	{
		m_piece.push_back(new VaporBomb(this));
	}
	else if (type == PIECE_FOAM)
	{
		m_piece.push_back(new FoamBomb(this));
	}
	else
	{
		m_piece.push_back(new Piece_I(this));
	}

}




int Well::getWidth() const
{
	return m_width;
}

int Well::getHeight() const
{
	return m_height;
}


int Well::clearRows(Screen& screen)
{
	int rowsRemoved = 0;
	int i = m_height - 2;
	while (i > 0)
	{
		if (isRowFull(i))  //Check if any rows are full on the creen
		{
			rowsRemoved++;  //Increment the number of rows removed
			for (int k = i; k > 0; k--)
			{
				for (int j = 1; j < m_width + 1; j++)			//Loop through the row and set it equal to the row on top of it
				{
					m_well[k] = m_well[k - 1];
					screen.gotoXY(j, k);
					screen.printChar(m_well[k][j]);
				}
			}
		}
		else
		{
			i--;
		}
	}
	return rowsRemoved;  //Return the number of rows removed
} 

bool Well::isRowFull(int row) const	//Checks if a certain row is full or not
{
	bool full = true;
	for (int i = 1; i <= m_width; i++)  //Loop through the row
	{
		if (m_well[row][i] != '$' && m_well[row][i] != '*')		//If the row does not contain a '$' or a '*' at any point break and return false
		{
			full = false;
			break;
		}
	}
	return full;
}

void Well::clearWell()
{
	for (int i = 0; i < m_height; i++)
	{

		for (int j = 0; j < m_width + 2; j++)
		{
			if (m_well[i][j] == '$' || m_well[i][j] == '*')  //Replace all $ and * in the well with spaces
			{
				m_well[i][j] = ' ';
			}
		}

	}
}

