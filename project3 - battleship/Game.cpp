#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;

class GameImpl
{
  public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
  private:
    int m_rows;
    int m_cols;
    struct Ship {int slength; char ssymbol; string sname;};
    vector<Ship> myships;
};

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols): m_rows(nRows), m_cols(nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cerr << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cerr << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
}

int GameImpl::rows() const
{
    return m_rows;
}

int GameImpl::cols() const
{
    return m_cols;  
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cerr << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cerr << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cerr << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cerr << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cerr << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cerr << "Board is too small to fit all ships" << endl;
        return false;
    }
    
    Ship s = {length, symbol, name};
    myships.push_back(s);
    
    return true;  // needs testing
}

int GameImpl::nShips() const
{
    return myships.size();
}

int GameImpl::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return myships[shipId].slength;
}

char GameImpl::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return myships[shipId].ssymbol;
}

string GameImpl::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return myships[shipId].sname;
}


Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    
    b1.clear();
    b2.clear();

    if (!p1->placeShips(b1) || !p2->placeShips(b2)) //unable to place ships
    {
        cerr << "player couldnt place ships" << endl;
        return nullptr;
    }
    
    while(!b1.allShipsDestroyed() && !b2.allShipsDestroyed())
    {
        bool validShot;
        bool shotHit;
        bool shipDestroyed;
        int shipID;
        //p1 turn
        cout << p1->name() << "'s turn. Board for " << p2->name() << ":" << endl;
        b2.display(p1->isHuman());
        
        Point p = p1->recommendAttack();
        validShot = b2.attack(p, shotHit, shipDestroyed, shipID);
        p1->recordAttackResult(p, validShot, shotHit, shipDestroyed, shipID);
        p2->recordAttackByOpponent(p);
        
        if (!validShot)
            cout << p1->name() << " wasted a shot at (" << p.r << "," << p.c << ")." << endl;
        else if (shotHit && shipDestroyed)
            cout << p1->name() << " attacked (" << p.r << "," << p.c << ") and destroyed the " << shipName(shipID) << ", resulting in: " << endl;
        else if (shotHit)
            cout << p1->name() << " attacked (" << p.r << "," << p.c << ") and hit something, resulting in: " << endl;
        else
            cout << p1->name() << " attacked (" << p.r << "," << p.c << ") and missed, resulting in: " << endl;
        b2.display(p1->isHuman());
        
        if (b2.allShipsDestroyed())
        {
            cout << p1->name() << " wins!" << endl;
            return p1;
        }
        
        if (shouldPause)
            waitForEnter();
        
        
        
        //p2 turn, same thing w p2 version of parameters and switch p1 and p2
        bool validShot2;
        bool shotHit2;
        bool shipDestroyed2;
        int shipID2;

        cout << p2->name() << "'s turn. Board for " << p1->name() << ":" << endl;
        b1.display(p2->isHuman());
        
        Point p_2 = p2->recommendAttack();
        validShot2 = b1.attack(p_2, shotHit2, shipDestroyed2, shipID2);
        p2->recordAttackResult(p_2, validShot2, shotHit2, shipDestroyed2, shipID2);
        p1->recordAttackByOpponent(p_2);
        
        if (!validShot2)
            cout << p2->name() << " wasted a shot at (" << p_2.r << "," << p_2.c << ")." << endl;
        else if (shotHit2 && shipDestroyed2)
            cout << p2->name() << " attacked (" << p_2.r << "," << p_2.c << ") and destroyed the " << shipName(shipID2) << ", resulting in: " << endl;
        else if (shotHit2)
            cout << p2->name() << " attacked (" << p_2.r << "," << p_2.c << ") and hit something, resulting in: " << endl;
        else
            cout << p2->name() << " attacked (" << p_2.r << "," << p_2.c << ") and missed, resulting in: " << endl;
        b1.display(p2->isHuman());
        
        if (b1.allShipsDestroyed())
        {
            cout << p2->name() << " wins!" << endl;
            return p2;
        }
        
        if (shouldPause)
            waitForEnter();
    }
    
    return nullptr;
                        // needs testing
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    
    Board b1(*this);
    Board b2(*this);
    
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

