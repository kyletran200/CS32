
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec)
	{
		return true;
	}
	maze[sr][sc] = 'D';
	if (sr != 0 && maze[sr - 1][sc] != 'X' && maze[sr - 1][sc] != 'D') //Location to the north
	{
		if (pathExists(maze, sr - 1, sc, er, ec))
		{
			return true;
		}
	}
	if (sc != 0 && maze[sr][sc - 1] != 'X' && maze[sr ][sc - 1] != 'D') //Location to the west
	{
		if (pathExists(maze, sr, sc - 1, er, ec))
		{
			return true;
		}
	}
	if (sr != 9 && maze[sr + 1][sc] != 'X' && maze[sr + 1][sc] != 'D') //Location to the south
	{
		if (pathExists(maze, sr + 1, sc, er, ec))
		{
			return true;
		}
	}
	if (sc != 9 && maze[sr][sc + 1] != 'X' && maze[sr][sc + 1] != 'D') //Location to the east
	{
		if (pathExists(maze, sr, sc + 1, er, ec))
		{
			return true;
		}
	}
	return false;
}

