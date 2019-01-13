#include "Game.h"
#include "Well.h"
#include "Piece.h"
#include "UserInterface.h"
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>


const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
 :m_well(width, height), m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_rowsleft(5), m_score(0)
{

}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
		displayPrompt("Good job!  Press the Enter key to start next level!");
		waitForEnter();
		m_screen.clear();
		m_well.clearWell();
		m_screen.clear();
		m_well.display(m_screen, WELL_X, WELL_Y);
		m_level++;
		m_rowsleft = m_level * 5;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
	
	m_screen.gotoXY(16, 8); //Print score
	m_screen.printStringClearLine("Score:           " + std::to_string(m_score));

	m_screen.gotoXY(16, 9);					//Print rows left
	m_screen.printStringClearLine("Rows left:       " + std::to_string(m_rowsleft));

	m_screen.gotoXY(16, 10);				//Print Level
	m_screen.printStringClearLine("Level:           " + std::to_string(m_level));

}


bool Game::playOneLevel()
{
	bool qPressed = false;		//Check if the player has pressed Q to quit
	queue<PieceType> pieceQueue;
	this->displayStatus();
	for(;;)  //Keep adding pieces until the well is full i.e the game is over or until the player finishes a level
	{
		if (pieceQueue.empty())			//First time through add a piece to the empty queue
		{
			pieceQueue.push(chooseRandomPieceType());
		}
		if (qPressed)		//End the game is Q is pressed
		{
			break;
		}
		switch (chooseRandomPieceType())	//Add another piece every time we loop through using a random enum PieceType
		{
		case PIECE_I:						//Push the piecetype onto our queue
			pieceQueue.push(PIECE_I);
			break;
		case PIECE_O:
			pieceQueue.push(PIECE_O);
			break;
		case PIECE_T:
			pieceQueue.push(PIECE_T);
			break;
		case PIECE_L:
			pieceQueue.push(PIECE_L);
			break;
		case PIECE_J:
			pieceQueue.push(PIECE_J);
			break;
		case PIECE_S:
			pieceQueue.push(PIECE_S);
			break;
		case PIECE_Z:
			pieceQueue.push(PIECE_Z);
			break;
		case PIECE_CRAZY:
			pieceQueue.push(PIECE_CRAZY);
			break;
		case PIECE_VAPOR:
			pieceQueue.push(PIECE_VAPOR);
			break;
		case PIECE_FOAM:
			pieceQueue.push(PIECE_FOAM);
			break;
		default:
			pieceQueue.push(PIECE_FOAM);
			break;
		}  
		

		m_well.addPiece(pieceQueue.front());	//Construct a piece based off the first piecetype added to the queue
		if (m_well.getPiece()->willEndGame())	//If the piece about to be displayed will overlap with another block in the well, end the game
		{
			break;
		}
		pieceQueue.pop();		//Remove the picetype at the front
		m_well.displayNextPiece(m_screen, pieceQueue.front());  //Use the net piecetype in the queue to ispaly our next piece

		
		

		this->displayStatus();
		m_well.getPiece()->displayPiece(m_screen); //Display the piece initially onto the screen at X = 3, Y = 0
		while (!m_well.getPiece()->isTransformed())			//While the piece has not been transformed into $ signs
		{
			Timer timer;
			while (timer.elapsed() <= max(1000 - (100 * (m_level - 1)), 100)) //Process keystrokes
			{		
				char ch;
				if (getCharIfAny(ch))
				{
					switch (ch)
					{
					case ARROW_UP:
					case 'w':
						m_well.getPiece()->clearPiece(m_screen);
						if (m_well.getPiece()->rotatePiece() && !m_well.getPiece()->isTransformed()) //If the rotation occurs changes the value of orientation
						{
							m_well.getPiece()->changeOrientationValue();	//Change the orientation value
						}
						m_well.getPiece()->displayPiece(m_screen);
						break;
					case ARROW_RIGHT:
					case 'd':
						if (!m_well.getPiece()->isTransformed())   //If the piece is not transformed we are allowd to move it left and right
						{
							m_well.getPiece()->clearPiece(m_screen);
							m_well.getPiece()->movePieceRight();
							m_well.getPiece()->displayPiece(m_screen);
						}
						break;
					case ARROW_LEFT:
					case 'a':
						if (!m_well.getPiece()->isTransformed())
						{
							m_well.getPiece()->clearPiece(m_screen);
							m_well.getPiece()->movePieceLeft();
							m_well.getPiece()->displayPiece(m_screen);
						}
						break;
					case  ' ':
						m_well.getPiece()->clearPiece(m_screen);	//Instantly clears piece and moves it to the bottom and transforms it
						m_well.getPiece()->movePieceBottom();
						m_well.getPiece()->transformPiece();
						if (m_well.getPiece()->getType() == PIECE_FOAM)  //If the piece is a foam bomb it must call the recursive function
						{
							int x_original = m_well.getPiece()->getXbound() + 1;
							int y_original = m_well.getPiece()->getYbound() + 1;
							m_well.getPiece()->foamExplodeIfPossible(m_screen, x_original, y_original, x_original, y_original);
						}
						else
						{
							m_well.getPiece()->addToWell();    //Otherwise add it to the well and display it normally
							m_well.getPiece()->displayPiece(m_screen);
						}
						break;
					case ARROW_DOWN:
					case 's':
						if (!m_well.getPiece()->isTransformed())
						{
							if (m_well.getPiece()->isAtBottom())				//If the down is pressed while at the bottom, transform the piece and update the well
							{
								m_well.getPiece()->clearPiece(m_screen);
								m_well.getPiece()->transformPiece();
								if (m_well.getPiece()->getType() == PIECE_FOAM) //If the piece is a foam bomb, call the foambomb function
								{
									int x_original = m_well.getPiece()->getXbound() + 1;
									int y_original = m_well.getPiece()->getYbound() + 1;
									m_well.getPiece()->foamExplodeIfPossible(m_screen, x_original, y_original, x_original, y_original);
								}
								else
								{
									m_well.getPiece()->addToWell();   //Otherwise add it to the well normallly and dispaly it
									m_well.getPiece()->displayPiece(m_screen);
								}
							}
							else
							{
								m_well.getPiece()->clearPiece(m_screen);  //If the piece is not at the bottom, clear it and move it down and restart the timer
								m_well.getPiece()->movePieceDown();
								m_well.getPiece()->displayPiece(m_screen);
								timer.start();
							}
						}
						break;
					}
					if ((ch == 's' || ch == ' ' || ch == ARROW_DOWN) && (m_well.getPiece()->isTransformed())) //If the down or space was pressed and the piece  is finished moving, break the timer
					{
						break;
					}
					if (ch == 'Q' || ch == 'q') //Break out of the timer if a q was pressed 
					{
						qPressed = true;
						break;
					}
				}
			}
			if (qPressed)  //Break again if q was pressed out of the outer loop
			{
				break;
			}
			if (!m_well.getPiece()->isTransformed())			//If the piece is not already transformed
			{
				m_well.getPiece()->clearPiece(m_screen);	//Once a certain time has passed, drop the piece down a row
				if (m_well.getPiece()->isAtBottom())			//If the piece is already at the bottom transform it and add it to the well
				{
					if (m_well.getPiece()->getType() == PIECE_FOAM)  //Call foam bomb recursive function if it hits the bottom
					{
						m_well.getPiece()->transformPiece();
						int x_original = m_well.getPiece()->getXbound() + 1;
						int y_original = m_well.getPiece()->getYbound() + 1;
						m_well.getPiece()->foamExplodeIfPossible(m_screen, x_original, y_original, x_original, y_original);
					}
					else
					{
						m_well.getPiece()->transformPiece();  //Otherwise transform the piece normally and add it to the well and siaply it
						m_well.getPiece()->addToWell();
						m_well.getPiece()->displayPiece(m_screen);
					}
				}
				else
				{
					m_well.getPiece()->movePieceDown();		//If the piece is not at the bottom move it down normally
					m_well.getPiece()->displayPiece(m_screen);
				}
			}
		}
		int rowsCleared = m_well.clearRows(m_screen);		//After the piece has hit the bottom check to clear rows

		m_rowsleft = m_rowsleft - rowsCleared;
	
		if (rowsCleared >= 1)
		{

			m_score = m_score + pow(2, rowsCleared - 1) * 100; //Update the score if a row was cleared
		}
		
		if (m_rowsleft <= 0)		//If we are finished clearing rows end the level and display the status
		{
			m_rowsleft = 0;
			this->displayStatus();
			return true;
		}
		this->displayStatus();

	} 
	return false;
	
}


