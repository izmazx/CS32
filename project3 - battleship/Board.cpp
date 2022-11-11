#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>


using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;

  private:
    const Game& m_game;
    char grid[MAXROWS][MAXCOLS];
};

BoardImpl::BoardImpl(const Game& g): m_game(g)
{
    for(int i = 0; i < m_game.rows(); i++)
    {
        for(int j = 0; j < m_game.cols(); j++)
        {
            grid[i][j] = '.';
        }
    }

}

void BoardImpl::clear()
{
    for(int i = 0; i < m_game.rows(); i++)
    {
        for(int j = 0; j < m_game.cols(); j++)
        {
            grid[i][j] = '.';
        }
    }

}

void BoardImpl::block()
{
      // Block 50% of cells
    int i = 0;
    int numToBlock = (m_game.rows()*m_game.cols())/2;
    while (i < numToBlock)
    {
        int r = randInt(m_game.rows());
        int c = randInt(m_game.cols());
        if (grid[r][c] == '.')
        {
            grid[r][c] = 'X';
            i++;
        }
    }
}



void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
    {
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (grid[r][c] == 'X')
                grid[r][c] = '.';
        }
    }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    int shiplength = m_game.shipLength(shipId);
    int row = topOrLeft.r;
    int col = topOrLeft.c;
    
    //testing for invalid
    if (shipId < 0 || shipId >= m_game.nShips()) //invalid id
        return false;
    for (int r = 0; r < m_game.rows(); r++) //ship already placed
    {
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (grid[r][c] == m_game.shipSymbol(shipId))
                return false;
        }
    }
    if (dir == HORIZONTAL && topOrLeft.c + shiplength > m_game.cols()) //extends past bounds
        return false;
    if (dir == VERTICAL && topOrLeft.r + shiplength > m_game.rows())
        return false;
    if (dir == HORIZONTAL) //ship is being placed somewhere that has other ship/block
    {
        for(int i = 0; i < shiplength; i++)
        {
            if (grid[row][col+i] != '.')
                return false;
        }
    }
    if (dir == VERTICAL)
    {
        for(int i = 0; i < shiplength; i++)
        {
            if (grid[row+i][col] != '.')
                return false;
        }
    }
    
    //placing of ship
    for (int i = 0; i < shiplength; i++)
    {
        if (dir == HORIZONTAL)
            grid[row][col+i] = m_game.shipSymbol(shipId);
        if (dir == VERTICAL)
            grid[row+i][col] = m_game.shipSymbol(shipId);
    }
    return true;
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    int shiplength = m_game.shipLength(shipId);

    if(shipId < 0 || shipId >= m_game.nShips()) //invalid id
        return false;
    if (dir == HORIZONTAL) //entire ship is not contained
    {
        for(int i = 0; i < shiplength; i++)
        {
            if (grid[topOrLeft.r][topOrLeft.c+i] != m_game.shipSymbol(shipId))
                return false;
        }
    }
    if (dir == VERTICAL)
    {
        for(int i = 0; i < shiplength; i++)
        {
            if (grid[topOrLeft.r+i][topOrLeft.c] != m_game.shipSymbol(shipId))
                return false;
        }
    }
    
    //unplace ship
    for (int i = 0; i < shiplength; i++)
    {
        if (dir == HORIZONTAL)
            grid[topOrLeft.r][topOrLeft.c+i] = '.';
        if (dir == VERTICAL)
            grid[topOrLeft.r+i][topOrLeft.c] = '.';
    }
    
    return true;
}

void BoardImpl::display(bool shotsOnly) const
{
    cout << "  ";
    for (int i = 0; i < m_game.cols(); i++)
    {
        cout << i;
    }
    cout << '\n'; //first line
    
    for (int i = 0; i < m_game.rows(); i++) //each row
    {
        cout << i << " ";
        for (int j = 0; j < m_game.cols(); j++)
        {
            if(shotsOnly && (grid[i][j] != 'X' && grid[i][j] != 'o'))
                cout << ".";
            else
                cout << grid[i][j];
        }
        cout << '\n';
    }
    
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    if(p.r < 0 || p.c < 0 || p.r >= m_game.rows() || p.c >= m_game.cols()) //outside bounds
        return false;
    if(grid[p.r][p.c] == 'o' || grid[p.r][p.c] == 'X') //prev attacked location
        return false;
    
    if(grid[p.r][p.c] == '.') //shot missed
    {
        grid[p.r][p.c] = 'o';
        shotHit = false;
        shipDestroyed = false;
    }
    else //shot hit
    {
        shotHit = true;
        char x = grid[p.r][p.c];
        grid[p.r][p.c] = 'X';
        for(int r = 0; r < m_game.rows(); r++)
        {
            for(int c = 0; c < m_game.cols(); c++)
            {
                if(grid[r][c] == x) //doesnt work
                {
                    shipDestroyed = false;
                    return true;
                }
            }
        }
        
        shipDestroyed = true;
        for(int i = 0; i < m_game.nShips(); i++) //loop thru ships and find id that matches s
        {
            if(m_game.shipSymbol(i) == x)
            {
                shipId = i;
                return true;
            }
        }
    }
    
    return true; 
}

bool BoardImpl::allShipsDestroyed() const
{
    for(int r = 0; r < m_game.rows(); r++)
    {
        for(int c = 0; c < m_game.cols(); c++)
        {
            if (grid[r][c] != '.' && grid[r][c] != 'o' && grid[r][c] != 'X')
                return false;
        }
    }
    return true;
}


//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
