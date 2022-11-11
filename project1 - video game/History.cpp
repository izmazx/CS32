//
//  History.cpp
//  project1
//
//  Created by Izma Zuberi on 4/3/22.
//

#include "History.h"
#include "Mesa.h"

History::History(int nRows, int nCols)
{
    rows = nRows;
    cols = nCols;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if ( r < 1 || r > rows || c < 1 || c > cols)
    {
        return false;
    }
    
    grid[r-1][c-1]++;
    return true;
}

void History::display() const
{

    clearScreen();
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == 0)
            {
                cout << ".";
            }
            else if (grid[r][c] >= 1 && grid[r][c] <= 26)
            {
                char letter = 'A' + grid[r][c] - 1;
                cout << letter;
            }
            else if (grid[r][c] > 26)
            {
                cout << 'Z';
            }
                
        }
        cout << endl;
    }
    cout << endl;
}
