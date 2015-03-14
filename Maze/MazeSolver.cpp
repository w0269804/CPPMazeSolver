#include "MazeSolver.h"

MazeSolver::MazeSolver(char * fileName, char * outFileName)
{
    rows = getRows(fileName); 
    cols = getCols(fileName);
    
	outFile = outFileName;

	std::cout << "Attempting to solve: " << fileName << std::endl;
    std::cout << rows << "<- Rows\n";
    std::cout << cols << "<- Cols\n";

    // dynamically size the maze
    maze = new char * [rows];
    for(int i=0; i<rows; i++)
    {
        maze[i] = new char[cols];
    }

    loadMaze(fileName);  // load maze into char array
    solve();
    print();

	std::cout << "Writing results to: " << outFileName << std::endl;
	writeMaze();
}

// destructor
MazeSolver::~MazeSolver()
{
    for(int i=0; i<rows; i++)
    {
        delete[] maze[i];
    }

    delete[] maze;
}

// print()
// ===============================
// Display the maze to the console
// replacing all visited locations
// with an empty space.
// ===============================
void MazeSolver::print()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(maze[i][j] == visited)
                std::cout << emptyPath;
            else
                std::cout << maze[i][j];
        }

        std::cout << std::endl;
    }
}

// showTruePath()
// ===========================
// Get the true path from the stack
// and show within the grid.
// ===========================
void MazeSolver::showTruePath()
{
    while(path.size() != 0) {
        maze[path.top().row][path.top().col] = pathMarker;
        path.pop();

    }

}

// loadMaze()
// ===========================
// Load the maze from a text file
// into the class level char array
// for solving / printing.
// ===========================
void MazeSolver::loadMaze(char* fileName)
{
    ifstream inStream;
    inStream.open(fileName);

    char * line = new char[cols + 1];

    int r = 0;


    if(inStream.good())
    {
        while(!inStream.eof())
        {
            inStream.getline(line, cols+1);
            for(int i = 0; i < cols; i++)
                maze[r][i] = line[i];
            r++;
        }
    } else

    {
        throw FileException();
    }

}

// solve()
// ======================
// Pushes the co-ordinates of the correct
// path into a stack. Returns true if a
// correct path can be found, false if not.
// ======================
void MazeSolver::solve()
{

    // TODO Move this into a method to
    // dyanmically search the maze for
    // the entry point rather than hard
    // hard coding it.

	int curRow = 0;// = 1; // first cell
	int curCol = 0; //= 0;

    Cell firstCell;
    firstCell.row = 1;
    firstCell.col = 0;

    path.push(firstCell); // add first cell


	while (!((curRow == rows - 2) && (curCol == cols - 1)) && path.size() != 0)
    {
        Cell nextMove;
		bool moved = false;

		curRow = path.top().row;
		curCol = path.top().col;
		maze[curRow][curCol] = visited; // set mark

        if(moved = (curCol > 0 && maze[curRow][curCol-1] == emptyPath))
            curCol--;
        else if(moved = (curCol < cols -1 && maze[curRow][curCol + 1] == emptyPath))
            curCol++;
        else if(moved = (curRow > 0 && maze[curRow - 1][curCol] == emptyPath))
            curRow--;
        else if(moved = (curRow < rows - 1 && maze[curRow + 1][curCol] == emptyPath))
            curRow++;

        if(moved)
        {
            nextMove.col = curCol;
            nextMove.row = curRow;
            maze[curRow][curCol] = visited;

            path.push(nextMove);
        } else {
            path.pop();
        }

		if (path.size() == 0)
			throw FileException("Unsolvable Maze provided or invalid file.");

		//print();

    } 

    showTruePath();

}

// getCols()
// ===================================
// Returns the number of columns in the
// first line of the text file for sizing
// the char array which holds the maze
// ===================================
int MazeSolver::getCols(char * fileName)
{
    ifstream inStream; // stream to read file
    inStream.open(fileName); // open the file

    if(inStream.good() && inStream.is_open())
    {
        char line[1024];
        inStream.getline(line, 1024);

        inStream.close();
        return std::strlen(line);
    } else {
          inStream.close(); // close he stream
        throw FileException("Unable to read file.");
    }

    inStream.close(); // close he stream

    return 0;
}

// getRows()
// ===================================
// Returns the number of rows in the
// the text file for sizing the char array
// which holds the maze
// ===================================
int MazeSolver::getRows(char * fileName)
{
    ifstream inStream; // stream to read file
    inStream.open(fileName); // open the file

    if(inStream.good() && inStream.is_open())
    {

        char line[1024];
        int numLines = 0;

        while(!inStream.eof())
        {
            inStream.getline(line, 1024);
            numLines++;
        }

        inStream.close();

        return numLines;
    } else
    {
      inStream.close(); // close he stream
      throw FileException();
    }
    
    return 0;
}

void MazeSolver::writeMaze()
{
	std::ofstream outFileStream;
	outFileStream.open(outFile);


	if (outFileStream.good())
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (maze[i][j] == visited)
					outFileStream << emptyPath;
				else
					outFileStream << maze[i][j];
			}


			outFileStream << std::endl;
		}
	}

	else
		throw FileException("Unable to write to file.");


	
}

