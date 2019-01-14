#include <queue>
#include <iostream>
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
	queue<Coord> coordQueue;
	Coord a(sr, sc);
	coordQueue.push(a); //Push the starting coordinate onto the queue
	maze[sr][sc] = 'D';
	while (!coordQueue.empty())
	{
		Coord current = coordQueue.front();
		coordQueue.pop();
		if (current.r() == er && current.c() == ec)
		{
			return true;
		}
		if (current.r() != 0 && maze[current.r() - 1][current.c()] != 'D' && maze[current.r()][current.c() - 1] != 'X') //Check if slot to the north is undiscovered and can move there
		{
			Coord newCoord(current.r() - 1, current.c());
			coordQueue.push(newCoord);
			maze[current.r() - 1][current.c()] = 'D';
		}
		if (current.c() != 0 && maze[current.r()][current.c() - 1] != 'D' && maze[current.r()][current.c() - 1] != 'X') //Check if slot to the west is undisocvered and can move there
		{
			Coord newCoord(current.r(), current.c() - 1);
			coordQueue.push(newCoord);
			maze[current.r()][current.c() - 1] = 'D';
		}
		if (current.r() != 9 && maze[current.r() + 1][current.c()] != 'D' && maze[current.r() + 1][current.c()] != 'X') //Check if slot to the south is undiscovered and can move there
		{
			Coord newCoord(current.r() + 1, current.c());
			coordQueue.push(newCoord);
			maze[current.r() + 1][current.c()] = 'D';
		}
		if (current.r() != 9 && maze[current.r()][current.c() + 1] != 'D' && maze[current.r()][current.c() + 1] != 'X') //Check if slot to the east is undiscovered and can move there
		{
			Coord newCoord(current.r(), current.c() + 1);
			coordQueue.push(newCoord);
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
	{ 'X','.','X','X','X','.','X','X','X','X' }, /*5*/
	{ 'X','X','X','.','.','.','.','X','.','X' },
	{ 'X','.','X','X','.','X','X','X','.','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};					  /*5*/

	if (pathExists(maze, 6, 5, 1, 8)) {
		cout << "Solvable!" << endl;
	}
	else
	{
		cout << "Out of luck!" << endl;
	}
}

