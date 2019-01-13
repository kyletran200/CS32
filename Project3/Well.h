#ifndef WELL_INCLUDED
#define WELL_INCLUDED
#include <string>
#include <vector>
#include "Piece.h"

using namespace std;

class Screen;
class Piece;

class Well
{
public:
    void display(Screen& screen, int x, int y);
	Well(int width, int height);
	~Well();
	void setCoordinate(int row, int col, char val);  //Use to change well
	void addPiece(PieceType type);  //Add a new piece to the well
	void displayNextPiece(Screen& screen, PieceType type) const;
	char getValueAtCoordinate(int row, int col) const;
	Piece* getPiece() const;
	int getWidth() const;
	int getHeight() const;
	void clearWell();
	bool isRowFull(int row) const;
	int clearRows(Screen& screen);
private:
	int m_height;
	int m_width;
	std::vector <std::vector<char>> m_well; //2D vector to represent well
	std::vector<Piece*> m_piece; //Vector of piece pointers to represent pieces in well

};

#endif // WELL_INCLUDED
