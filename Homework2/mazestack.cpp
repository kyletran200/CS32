#include <iostream>
#include <stack>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;
	Coord a(sr, sc);
	coordStack.push(a); //Push the starting coordinate onto the stack
	maze[sr][sc] = 'D';
	while (!coordStack.empty())
	{
		Coord current = coordStack.top();
		coordStack.pop();
		if (current.r() == er && current.c() == ec)
		{
			return true;
		}
		if (current.r() != 0 && maze[current.r() - 1][current.c()] != 'D' && maze[current.r()][current.c() - 1] != 'X') //Check if slot to the north is undiscovered and can move there
		{
			Coord newCoord(current.r() - 1, current.c());
			coordStack.push(newCoord);
			maze[current.r() - 1][current.c()] = 'D';
		}
		if (current.c() != 0 && maze[current.r()][current.c() - 1] != 'D' && maze[current.r()][current.c() - 1] != 'X') //Check if slot to the west is undisocvered and can move there
		{
			Coord newCoord(current.r(), current.c() - 1);
			coordStack.push(newCoord);
			maze[current.r()][current.c() - 1] = 'D';
		}
		if (current.c() != 9 && maze[current.r() + 1][current.c()] != 'D' && maze[current.r() + 1][current.c()] != 'X') //Check if slot to the south is undiscovered and can move there
		{
			Coord newCoord(current.r() + 1, current.c());
			coordStack.push(newCoord);
			maze[current.r() + 1][current.c()] = 'D';
		}
		if (current.c() != 9 && maze[current.r()][current.c() + 1] != 'D' && maze[current.r()][current.c() + 1] != 'X') //Check if slot to the east is undiscovered and can move there
		{
			Coord newCoord(current.r(), current.c() + 1);
			coordStack.push(newCoord);
			maze[current.r()][current.c() + 1] = 'D';
		}
	}
	return false;
}

int main()
{
	char maze[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','.','.','.','.','.','.','.','X' },
	{ 'X','X','X','X','X','.','X','.','X','X' },
	{ 'X','.','.','.','X','.','X','.','.','X' },
	{ 'X','.','X','.','.','.','X','.','.','X' },
	{ 'X','.','X','X','X','.','X','X','X','X' }, 
	{ 'X','X','X','.','.','.','.','X','.','X' },
	{ 'X','.','X','X','.','X','X','X','.','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 6, 5, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}




