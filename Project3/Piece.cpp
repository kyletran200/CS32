#include "Piece.h"
#include "Well.h"


Piece::Piece(PieceType type, Well* well)
	:x_bound(4), y_bound(0), m_well(well), m_type(type), m_orientation(0)
{

}

Piece::~Piece()
{}

void Piece::displayPiece(Screen& screen) const
{

	for (int i = 0; i < 4; i++)			//Loop through rows
	{
		for (int j = 0; j < 4; j++)		//Loop through columns
		{
			if (m_piece[i][j] != ' ')  //Print the parts that are not spaces
			{
				screen.gotoXY(x_bound + j, y_bound + i); 
				screen.printChar(m_piece[i][j]);
			}
		}
	}
}



void Piece::clearPiece(Screen& screen) const
{
	screen.gotoXY(x_bound, y_bound);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '#')	//Loop through and remove the # chars from the screen
			{
				screen.gotoXY(x_bound + j, y_bound + i);
				screen.printChar(' ');
			}
		}
	}
}

void Piece::transformPiece()			
{
				
	for (int i = 0; i < 4; i++)		//In general, transform the pieces to $
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '#')
			{
				m_piece[i][j] = '$';
			}
		}
	}
}


bool Piece::isTransformed() const //Check if the piece has been converted to $
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '$')
			{
				return true;
			}
		}
	}
	return false;
}

void Piece::addToWell() const  //Find the location of the $ and add it to the well
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '$')
			{
				m_well->setCoordinate(y_bound + i, x_bound + j, '$');
			}
		}
	}
}



PieceType Piece::getType() const
{
	return m_type;
}


void Piece::movePieceDown()
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)		//Finds the # in the piece and makes sure that the area below it is not a $ so it can increment the y bound
		{
			if (m_piece[i][j] == '#')
			{
				if (m_well->getValueAtCoordinate(y_bound + i + 1, x_bound + j) == '$' || (m_well->getValueAtCoordinate(y_bound + i + 1, x_bound + j) == '@') || (m_well->getValueAtCoordinate(y_bound + i + 1, x_bound + j) == '*'))
				{
					return;
				}
			}
		}
	}
	y_bound++;
}

void Piece::movePieceLeft()
{
	bool moveOk = true;			//Checks if the piece can move left by checking all blocks left of the #
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '#')
			{
				if (m_well->getValueAtCoordinate(y_bound + i, x_bound + j - 1) == '$' || (m_well->getValueAtCoordinate(y_bound + i, x_bound + j - 1) == '@') || (m_well->getValueAtCoordinate(y_bound + i, x_bound + j - 1) == '*'))
				{
					moveOk = false;
				}
			}
		}
	}
	if (moveOk)
	{
		x_bound--;  //Decrement the xbound so it moves left
	}
}

void Piece::movePieceRight()
{
	bool moveOk = true;			//Also checks if move right is possible
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '#')
			{
				if (m_well->getValueAtCoordinate(y_bound + i, x_bound + j + 1) == '$' || (m_well->getValueAtCoordinate(y_bound + i, x_bound + j + 1) == '@') || (m_well->getValueAtCoordinate(y_bound + i, x_bound + j + 1) == '*'))
				{
					moveOk = false;
				}
			}
		}
	}
	if (moveOk)
	{ 
		x_bound++;  //Increment x bound to move right if the move is good
	}
}

void Piece::movePieceBottom()
{
	while (!this->isAtBottom())  //Increment the y_bound until the piece is at the bottom
	{
		y_bound++;
	}
	
}

bool Piece::isAtBottom() const
{
	for (int i = 0; i < 4; i++)		//Loop through and find all # and if the block below that is a $ or an @ return true
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '#')
			{
				if (m_well->getValueAtCoordinate(y_bound + i + 1, x_bound + j) == '$' || (m_well->getValueAtCoordinate(y_bound + i + 1, x_bound + j) == '@') || (m_well->getValueAtCoordinate(y_bound + i + 1, x_bound + j) == '*'))
				{
					return true;
				}
			}
		}
	}
	return false;
}


bool Piece::rotatePiece()
{
	std::vector < std::vector<char> > temp = this->nextOrientation();
	for (int i = 0; i < 4; i++)			//Loop through the possible next orientation
	{
		for (int j = 0; j < 4; j++)
		{
			if (temp[i][j] == '#')
			{									//Check for overlap between the next possible orientation and the well
				if (m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '@' || m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '$' || m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '*')
				{
					return false;		//If there is overlap, return false and dont change the piece
				}
			}
		}
	}
	m_piece = temp;		//If there is no overlap return true and rotate the piece
	return true;

}

int Piece::getOrientation() const
{
	return m_orientation;
}

void Piece::changeOrientationValue()		//Change the value of orientation
{
	if (m_orientation < 3)
	{
		m_orientation++;
	}
	else
	{
		m_orientation = 0;
	}
}


bool Piece::willEndGame() const
{
	for (int i = 0; i < 4; i++)		//Checks if the piece about to be displayed will be overlapped with current blocks
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '#')
			{
				if (m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '$' || m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '*')
				{
					return true;
				}
					
			}
		}
	}
	return false;

}


void Piece::foamExplodeIfPossible(Screen& screen, int x, int y, int x_original, int y_original)
{
	if (x > x_bound + 3 || x < x_bound - 1 || y > y_bound + 3 || y < y_bound - 1)	//Base case that checks we arent out of bounds of the 5x5
	{
		return;
	}
	m_well->setCoordinate(y, x, '*');		//Set the value to * and print it
	screen.gotoXY(x, y);
	screen.printChar('*');
	if (m_well->getValueAtCoordinate(y, x + 1) == ' ')		//Recursively check for all directions outwards
	{
		foamExplodeIfPossible(screen, x + 1, y, x_original, y_original);
	}
	if (m_well->getValueAtCoordinate(y + 1, x) == ' ')
	{
		foamExplodeIfPossible(screen,x, y + 1, x_original, y_original);
	}
	if (m_well->getValueAtCoordinate(y, x - 1) == ' ')
	{
		foamExplodeIfPossible(screen, x - 1, y, x_original, y_original);
	}
	if (m_well->getValueAtCoordinate(y - 1, x) == ' ')
	{
		foamExplodeIfPossible(screen, x, y - 1, x_original, y_original);
	}

}




int Piece::getXbound() const
{
	return x_bound;
}

int Piece::getYbound() const
{
	return y_bound;
}





//============================= O Piece

Piece_O::Piece_O(Well* well)
	:Piece(PIECE_O, well)
{
	m_piece = { 
	{'#','#',' ',' '}, //0
	{'#','#',' ',' '}, //1
	{' ',' ',' ',' '}, //2
	{' ',' ',' ',' '}, //3
//    0,  1   2   3
	};

}

//For all nextOrientation functions, return a 2D vector that reprents the nextOrientation based off of the orientation value


std::vector< std::vector<char> > Piece_O::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	nextOrientation = {
	{ '#','#',' ',' ' }, //0
	{ '#','#',' ',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
						 //    0,  1   2   3
	};
	return nextOrientation;
}





//====================== I Piece  ===================/

Piece_I::Piece_I(Well* well)
	:Piece(PIECE_I,well)
{
	m_piece = {
	{ ' ',' ',' ',' ' }, //0
	{ '#','#','#','#' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	// 0,  1   2   3
	};
}




std::vector< std::vector<char> > Piece_I::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	if (this->getOrientation() == 1 || this->getOrientation() == 3)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ '#','#','#','#' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
		 // 0,  1   2   3
		};
	}
	else
	{
		nextOrientation= {
		{ ' ','#',' ',' ' }, //0
		{ ' ','#',' ',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ','#',' ',' ' }, //3
		 // 0,  1   2   3
		};
	}
	return nextOrientation;
}




//======== T PIECE ========= //


Piece_T::Piece_T(Well* well)
	:Piece(PIECE_T, well)
{
	m_piece = {
	{ ' ','#',' ',' ' }, //0
	{ '#','#','#',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	 // 0,  1   2   3
	};
}


std::vector< std::vector<char> > Piece_T::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	if (this->getOrientation() == 0)
	{
		nextOrientation = {
		{ ' ','#',' ',' ' }, //0
		{ ' ','#','#',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 1)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ '#','#','#',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 2)
	{
		nextOrientation = {
		{ ' ','#',' ',' ' }, //0
		{ '#','#',' ',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else
	{
		nextOrientation = {
		{ ' ','#',' ',' ' }, //0
		{ '#','#','#',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};

	}

	return nextOrientation;
}


//=== L PIECE ====== //


Piece_L::Piece_L(Well* well)
	:Piece(PIECE_L, well)
{
	m_piece = {
	{ ' ',' ',' ',' ' }, //0
	{ '#','#','#',' ' }, //1
	{ '#',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
						 // 0,  1   2   3
	};
}


std::vector< std::vector<char> > Piece_L::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	if (this->getOrientation() == 0)
	{
		nextOrientation = {
		{ ' ','#','#',' ' }, //0
		{ ' ',' ','#',' ' }, //1
		{ ' ',' ','#',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 1)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ',' ','#',' ' }, //1
		{ '#','#','#',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 2)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ','#',' ',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ','#','#',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ '#','#','#',' ' }, //1
		{ '#',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};

	}

	return nextOrientation;
}


//=== J PIECE ====== //


Piece_J::Piece_J(Well* well)
	:Piece(PIECE_J, well)
{
	m_piece = {
	{ ' ',' ',' ',' ' }, //0
	{ ' ','#','#','#' }, //1
	{ ' ',' ',' ','#' }, //2
	{ ' ',' ',' ',' ' }, //3
						 // 0,  1   2   3
	};
}


std::vector< std::vector<char> > Piece_J::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	if (this->getOrientation() == 0)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ',' ','#',' ' }, //1
		{ ' ',' ','#',' ' }, //2
		{ ' ','#','#',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 1)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ','#',' ',' ' }, //1
		{ ' ','#','#','#' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 2)
	{
		nextOrientation = {
		{ ' ','#','#',' ' }, //0
		{ ' ','#',' ',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else
	{

		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ','#','#','#' }, //1
		{ ' ',' ',' ','#' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};

	}

	return nextOrientation;
}


// ======== S PIECE ======= //

Piece_S::Piece_S(Well* well)
	:Piece(PIECE_S, well)
{
	m_piece = {
	{ ' ',' ',' ',' ' }, //0
	{ ' ','#','#',' ' }, //1
	{ '#','#',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	};
}


std::vector< std::vector<char> > Piece_S::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	if (this->getOrientation() == 0)
	{
		nextOrientation = {
		{ ' ','#',' ',' ' }, //0
		{ ' ','#','#',' ' }, //1
		{ ' ',' ','#',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 1)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ','#','#',' ' }, //1
		{ '#','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 2)
	{
		nextOrientation = {
		{ ' ',' ','#',' ' }, //0
		{ ' ',' ','#','#' }, //1
		{ ' ',' ',' ','#' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else
	{

		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ','#','#',' ' }, //1
		{ '#','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};

	}

	return nextOrientation;
}

// ======= PIECE Z ========== //


Piece_Z::Piece_Z(Well* well)
	:Piece(PIECE_Z, well)
{
	m_piece = {
	{ ' ',' ',' ',' ' }, //0
	{ '#','#',' ',' ' }, //1
	{ ' ','#','#',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	};
}


std::vector< std::vector<char> > Piece_Z::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	if (this->getOrientation() == 0)
	{
		nextOrientation = {
		{ ' ',' ','#',' ' }, //0
		{ ' ','#','#',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 1)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ '#','#',' ',' ' }, //1
		{ ' ','#','#',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 2)
	{
		nextOrientation = {
		{ ' ',' ','#',' ' }, //0
		{ ' ','#','#',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else
	{

		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ '#','#',' ',' ' }, //1
		{ ' ','#','#',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};

	}
	return nextOrientation;
}

// ===== CRAZY SHAPE ======= //

CrazyShape::CrazyShape(Well* well)
	:Piece(PIECE_CRAZY, well)
{
	m_piece = {
	{ '#',' ',' ','#' }, //0
	{ ' ','#','#',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
						 // 0,  1   2   3
	};
}
bool CrazyShape::rotatePiece()
{
	std::vector < std::vector<char> > temp = this->nextOrientation();
	for (int i = 0; i < 4; i++)			//Loop through the possible next orientation
	{
		for (int j = 0; j < 4; j++)
		{
			if (temp[i][j] == '#')
			{			
				//Check for overlap between the next possible orientation and the well
				if (this->getOrientation() == 3 && m_well->getValueAtCoordinate(y_bound + 2, x_bound + 2) == '@' || m_well->getValueAtCoordinate(y_bound + 2, x_bound + 2) == '$')
				{
					return false;
				}
				if (m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '@' || m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '$' || m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '*')
				{
					return false;		//If there is overlap, return false and dont change the piece
				}
			}
		}
	}
	m_piece = temp;		//If there is no overlap return true and rotate the piece
	return true;

}


std::vector< std::vector<char> > CrazyShape::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;

	if (this->getOrientation() == 0)
	{
		nextOrientation = {
		{ ' ',' ',' ','#' }, //0
		{ ' ',' ','#',' ' }, //1
		{ ' ',' ','#',' ' }, //2
		{ ' ',' ',' ','#' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 1)
	{
		nextOrientation = {
		{ ' ',' ',' ',' ' }, //0
		{ ' ',' ',' ',' ' }, //1
		{ ' ','#','#',' ' }, //2
		{ '#',' ',' ','#' }, //3
							 // 0,  1   2   3
		};
	}
	else if (this->getOrientation() == 2)
	{
		nextOrientation = {
		{ '#',' ',' ',' ' }, //0
		{ ' ','#',' ',' ' }, //1
		{ ' ','#',' ',' ' }, //2
		{ '#',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};
	}
	else
	{

		nextOrientation = {
		{ '#',' ',' ','#' }, //0
		{ ' ','#','#',' ' }, //1
		{ ' ',' ',' ',' ' }, //2
		{ ' ',' ',' ',' ' }, //3
							 // 0,  1   2   3
		};

	}
	return nextOrientation;
}

void CrazyShape::movePieceLeft()
{
	Piece::movePieceRight();  //Call the opoosite move function for the crazy shape
}

void CrazyShape::movePieceRight()
{
	Piece::movePieceLeft();
}

// ===== Vapor Bomb ======= //

VaporBomb::VaporBomb(Well* well)
	:Piece(PIECE_VAPOR, well)
{
	m_piece = {
	{ ' ','#','#',' ' }, //0
	{ ' ',' ',' ',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	};
}

std::vector< std::vector<char> > VaporBomb::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;
	nextOrientation = {
	{ ' ','#','#',' ' }, //0
	{ ' ',' ',' ',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	};
	return nextOrientation;
}

void VaporBomb::transformPiece()	//Vapor bomb turns into nothing when transformed
{
	m_piece = {
	{ ' ',' ',' ',' ' }, //0
	{ ' ',' ',' ',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	};
} 

bool VaporBomb::isTransformed() const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] != ' ') //Check if the piece is empty
			{
				return false;
			}
		}
	}
	return true;
}
void VaporBomb::addToWell() const
{
	for (int i = 1; i < 3; i++)			//Set value of well to ' ' to the top 2 rows above the vapor bomb
	{
		for (int j = 1; j < 3; j++)
		{
			m_well->setCoordinate(y_bound - i, x_bound + j, ' ');
		}
	}

	for (int i = 1; i < 3; i++)			//Set value of well to ' ' to bottom 2 rows below the vapor bomb
	{
		for (int j = 1; j < 3; j++)
		{
			if (m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '@')
			{
				return;
			}
			else
			{
				m_well->setCoordinate(y_bound + i, x_bound + j, ' ');
			}
		}
	}
}

void VaporBomb::displayPiece(Screen& screen)  const
{
	if (this->isTransformed())
	{
		for (int i = 1; i < 3; i++)			//Clear the top two rows on the screen
		{
			for (int j = 1; j < 3; j++)
			{
				if (m_well->getValueAtCoordinate(y_bound - i, x_bound + j) != '@')
				{
					screen.gotoXY(x_bound + j, y_bound - i);
					screen.printChar(' ');
				}
			}
		}
		for (int i = 1; i < 3; i++)			//Bottom two rows on screen
		{
			for (int j = 1; j < 3; j++)
			{
				if (m_well->getValueAtCoordinate(y_bound + i, x_bound + j) == '@')
				{
					return;
				}
				else
				{
					screen.gotoXY(x_bound + j, y_bound + i);
					screen.printChar(' ');
				}
			}
		}
		
	}
	else  //Dispaly it normally if it is not at the bottom
	{
		for (int i = 0; i < 4; i++)			//Loop through rows
		{
			for (int j = 0; j < 4; j++)		//Loop through columns
			{
				if (m_piece[i][j] != ' ')
				{
					screen.gotoXY(x_bound + j, y_bound + i);
					screen.printChar(m_piece[i][j]);
				}

			}
		}
	}
}

//====== FOAM BOMB =========== //


FoamBomb::FoamBomb(Well* well)
	:Piece(PIECE_FOAM, well)
{
	m_piece = {
	{ ' ',' ',' ',' ' }, //0
	{ ' ','#',' ',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	};
}

std::vector< std::vector<char> > FoamBomb::nextOrientation()
{
	std::vector< std::vector<char> > nextOrientation;
	nextOrientation = {
	{ ' ',' ',' ',' ' }, //0
	{ ' ','#',' ',' ' }, //1
	{ ' ',' ',' ',' ' }, //2
	{ ' ',' ',' ',' ' }, //3
	};
	return nextOrientation;
}

void FoamBomb::transformPiece()  //Transform the # to a *
{
	m_piece[1][1] = '*';
}

bool FoamBomb::isTransformed() const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_piece[i][j] == '*')  //Return true if it is a *
			{
				return true;
			}
		}
	}
	return false;
}































