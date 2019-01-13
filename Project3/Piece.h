#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include "UserInterface.h"
#include <vector>

class Well;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
}; 

PieceType chooseRandomPieceType();

class Piece			//Create an abstract class piece 
{
public:
	Piece(PieceType type, Well* well);
	virtual ~Piece();
	virtual void displayPiece(Screen& screen) const;		//Virtual because vapor bomb displays diferently
	void clearPiece(Screen& screen) const;					//Clearing piece always works the same
	virtual void transformPiece();  //Make virtual for special pieces		
	virtual bool isTransformed() const;	//Virtual becasue speical pieces transform differently
	virtual void addToWell() const; //Special piecces also add to the well differently

	bool willEndGame() const;	//Overlap check same for all pieces

	void changeOrientationValue();		//Changing orientation value same for all pieces

	virtual bool rotatePiece();   //Rotation same for all pieces
	virtual std::vector< std::vector<char> > nextOrientation() = 0;   //This one will not be universal


	void movePieceDown(); //All pieces will move down the same way
	virtual void movePieceLeft();  //Move left and right are virtual becasue of the crazy piece
	virtual void movePieceRight();   
	void movePieceBottom();    //Moving piece to the bottom same for all pieces
	bool isAtBottom() const;  //Checks at bottom same for all pieces

	virtual void foamExplodeIfPossible(Screen& screen, int x, int y, int x_original, int y_original); //This is only to be used by the foam bomb
	

	PieceType getType() const;
	int getOrientation() const;

	int getXbound() const;
	int getYbound() const;

protected:
	std::vector< std::vector<char> > m_piece;
	int x_bound;
	int y_bound;
	Well* m_well;

private:
	PieceType m_type;
	int m_orientation; //use this to determine which orientation the piece is in
	
};



class Piece_O : public Piece
{
public:
	Piece_O(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();
};

// ====== PIECE I ======== //
class Piece_I : public Piece
{
public:
	Piece_I(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();

};

//====== T PIECE ======== /

class Piece_T : public Piece
{
public:
	Piece_T(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();

};


//====== L PIECE ======== /

class Piece_L : public Piece
{
public:
	Piece_L(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();
};

//====== J PIECE ===== //

class Piece_J : public Piece
{
public:
	Piece_J(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();
};


//====== S PIECE ===== //

class Piece_S : public Piece
{
public:
	Piece_S(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();
};

//====== Z PIECE ====== //

class Piece_Z : public Piece
{
public:
	Piece_Z(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();
};

// ===== CRAZY SHAPE ====== //

class CrazyShape : public Piece
{
public:
	CrazyShape(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();
	virtual bool rotatePiece();
	virtual void movePieceLeft();  //Crazy shape will have different move left and right functions
	virtual void movePieceRight();   
};

//===== VAPOR BOMB ======= //

class VaporBomb : public Piece
{
public:
	VaporBomb(Well* well);		//The vapor bomb will inherit all the move functions
	virtual std::vector< std::vector<char> > nextOrientation();	//Vapor bomb doesnt transform
	virtual void transformPiece();		
	virtual void addToWell() const;	//Add to well will destroy the surrounding blocks
	virtual void displayPiece(Screen& screen) const;  //Vapor Bomb displays differnetly because it clears the well
	virtual bool isTransformed() const;
};

// ===== FOAM BOMB ======= //

class FoamBomb : public Piece
{
public:
	FoamBomb(Well* well);
	virtual std::vector< std::vector<char> > nextOrientation();
	virtual bool isTransformed() const;
	virtual void transformPiece();

};



#endif // PIECE_INCLUDED
