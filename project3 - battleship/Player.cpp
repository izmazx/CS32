#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
  public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
 : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
      // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
      // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

class HumanPlayer: public Player
{
  public:
    HumanPlayer(string nm, const Game& g);
    virtual bool isHuman() const { return true; }

    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
};

HumanPlayer::HumanPlayer(string nm, const Game& g): Player(nm, g)
{}

bool HumanPlayer::placeShips(Board &b)
{
    int r;
    int c;
    char dir;
    Direction dirc = HORIZONTAL;
    int i = 0;
    
    cout << name() << " must place " << game().nShips() << " ships." << endl;
    b.display(false);
    
    while(i < game().nShips())
    {
        bool validPlace = false;
        bool validDir = false;
        
        while(!validDir)
        {
            cout << "Enter 'h' or 'v' for direction of " << game().shipName(i) << " (length " << game().shipLength(i) << "): ";
            cin >> dir;
            if (dir == 'h')
            {
                dirc = HORIZONTAL;
                validDir = true;
            }
            else if (dir == 'v')
            {
                dirc = VERTICAL;
                validDir = true;
            }
            else
            {
                cout << "Direction must be h or v" << endl;
                continue;
            }
        }
        while (!validPlace)
        {
            if (dirc == HORIZONTAL)
                cout << "Enter row and column of leftmost cell (e.g., 3 5): ";
            else
                cout << "Enter row and column of topmost cell (e.g., 3 5): ";

            if (!getLineWithTwoIntegers(r, c))
            {
                cout << "You must enter two integers." << endl;
                continue;
            }
            if (r < 0 || r >= game().rows() || c < 0 || c >= game().cols())
            {
                cout << "The ship can not be placed there." << endl;
                continue;
            }

            if (b.placeShip(Point(r,c), i, dirc))
            {
                validPlace = true;
                b.display(false);
                i++;
            }
            else
            {
                cout << "The ship can not be placed there." << endl;
                continue;

            }
        }
    }
    return true;
}

Point HumanPlayer::recommendAttack()
{
    int r = 0;
    int c = 0;
    bool isValid = false;
    
    while (!isValid)
    {
        cout << "Enter the row and column to attack (e.g., 3 5): ";
        if (!getLineWithTwoIntegers(r, c))
        {
            cout << "You must enter two integers." << endl;
            continue;
        }
        else
            isValid = true;
    }
    return Point(r,c);
}

void HumanPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // human does not need to use this fcn
}

void HumanPlayer::recordAttackByOpponent(Point /* p */)
{
      // human does not need to use this fcn
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

class MediocrePlayer: public Player
{
  public:
    MediocrePlayer(string nm, const Game& g);
    bool placeallships(Board& b, int ships);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    bool activate;
    bool valid;
    bool hit;
    bool destroyed;
    int ship;
    vector<Point> validPoints;
    bool gridattacked[MAXROWS][MAXCOLS];
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g): Player(nm, g), activate(false), valid(false), hit(false), destroyed(false), ship(0)
{
    for (int r = 0; r < game().rows(); r++)
    {
        for (int c = 0; c < game().cols(); c++)
        {
            gridattacked[r][c] = false;
        }
    }
}

bool MediocrePlayer::placeallships(Board& b, int ships)
{    
    if (ships < 0)
        return true;
    
    for (int r = 0; r < game().rows(); r++)
    {
        for (int c = 0; c < game().cols(); c++)
        {
            if(b.placeShip(Point(r, c), ships, HORIZONTAL))
                return placeallships(b, ships - 1);
            
            if(b.placeShip(Point(r,c), ships, VERTICAL))
                return placeallships(b, ships - 1);
        }
    }

    return false;
}

bool MediocrePlayer::placeShips(Board& b)
{
    for (int i = 0; i < 50; i++)
    {
        b.clear();
        b.block();
        if (placeallships(b, game().nShips() - 1))
        {
            b.unblock();
            return true;
        }
        
        b.unblock();
    }
    return false;
}

Point MediocrePlayer::recommendAttack()
{
    if (!activate)
    {
        int r = randInt(game().rows());
        int c = randInt(game().cols());
        for (int i = 0; i < game().rows()*game().cols(); i++) //try rows*cols times to generate random unused pt
        {                                                     // if cant, return first open pt
            r = randInt(game().rows());
            c = randInt(game().cols());
            if (!gridattacked[r][c])
                return Point(r,c);
        }
        for (int r = 0; r < game().rows(); r++)
        {
            for (int c = 0; c < game().cols(); c++)
            {
                if (!gridattacked[r][c])
                    return Point(r,c);
            }
        }
        
    }
    else
    {
        Point attack = validPoints.back();
        validPoints.pop_back();
        if (validPoints.empty())
            activate = false;
        return attack;
    }
    return Point(0,0);
}
void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId)
{
    valid = validShot;
    hit = shotHit;
    destroyed = shipDestroyed;
    ship = shipId;
    if (validShot)
        gridattacked[p.r][p.c] = true;
    
    if(!activate && hit && !destroyed)
    {
        activate = true;
        cerr << "active" << endl;
        while(!validPoints.empty())
        {
            validPoints.pop_back();
        }
        for (int i = 1; i < 5; i++)
        {
            if (p.r + i < game().rows() && !gridattacked[p.r+i][p.c])
                validPoints.push_back(Point(p.r + i, p.c));
            
            if (p.r - i >= 0 && !gridattacked[p.r-i][p.c])
                validPoints.push_back(Point(p.r - i, p.c));
            
            if (p.c + i < game().cols() && !gridattacked[p.r][p.c+i])
                validPoints.push_back(Point(p.r, p.c + i));
            
            if (p.c - i >= 0 && !gridattacked[p.r][p.c-i])
                validPoints.push_back(Point(p.r, p.c - i));
        }
    }
    if (activate && destroyed)
        activate = false;
}

void MediocrePlayer::recordAttackByOpponent(Point p)
{
    //fcn does nothing
}

//*********************************************************************
//  GoodPlayer
//*********************************************************************


class GoodPlayer: public Player
{
  public:
    GoodPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    bool placeallships(Board& b, int ships);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    bool activate;
    bool valid;
    bool hit;
    bool destroyed;
    int ship;
    list<Point> validPoints;
    bool gridattacked[MAXROWS][MAXCOLS];

};

GoodPlayer::GoodPlayer(string nm, const Game& g): Player(nm, g), activate(false), valid(false), hit(false), destroyed(false), ship(0)
{
    for (int r = 0; r < game().rows(); r++)
    {
        for (int c = 0; c < game().cols(); c++)
        {
            gridattacked[r][c] = false;
        }
    }
}

bool GoodPlayer::placeallships(Board& b, int ships)
{
    if (ships < 0)
        return true;
    
    for (int r = 0; r < game().rows(); r++)
    {
        for (int c = 0; c < game().cols(); c++)
        {
            if(b.placeShip(Point(r, c), ships, HORIZONTAL))
                return placeallships(b, ships - 1);

            if(b.placeShip(Point(r,c), ships, VERTICAL))
                return placeallships(b, ships - 1);
        }
    }
    return false;
}

bool GoodPlayer::placeShips(Board& b)
{
    for (int i = 0; i < 50; i++)
    {
        b.clear();
        b.block();
        if (placeallships(b, game().nShips() - 1))
        {
            b.unblock();
            return true;
        }
        
        b.unblock();
    }
    return false;
}

Point GoodPlayer::recommendAttack()
{
    if (!activate)
    {
        int r = randInt(game().rows());
        int c = randInt(game().cols());
        for (int i = 0; i < game().rows()*game().cols(); i++) 
        {
            r = randInt(game().rows());
            c = randInt(game().cols());
            if (!gridattacked[r][c])
                return Point(r,c);
        }
        for (int r = 0; r < game().rows(); r++)
        {
            for (int c = 0; c < game().cols(); c++)
            {
                if (!gridattacked[r][c])
                    return Point(r,c);
            }
        }
    }
    else
    {
        Point attack = validPoints.front();
        validPoints.pop_front();
        if (validPoints.empty())
            activate = false;
        return attack;
    }
    return Point(0,0);
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit,
                                    bool shipDestroyed, int shipId)
{
    valid = validShot;
    hit = shotHit;
    destroyed = shipDestroyed;
    ship = shipId;
    if (validShot)
        gridattacked[p.r][p.c] = true;
    
    if(!activate && hit && !destroyed)
    {
        activate = true;
        cerr << "active" << endl;
        while(!validPoints.empty())
        {
            validPoints.pop_front();
        }
        for (int i = 1; i < 5; i++)
        {
            if (p.r + i < game().rows() && !gridattacked[p.r+i][p.c])
                validPoints.push_back(Point(p.r + i, p.c));
            
            if (p.r - i >= 0 && !gridattacked[p.r-i][p.c])
                validPoints.push_back(Point(p.r - i, p.c));
            
            if (p.c + i < game().cols() && !gridattacked[p.r][p.c+i])
                validPoints.push_back(Point(p.r, p.c + i));
            
            if (p.c - i >= 0 && !gridattacked[p.r][p.c-i])
                validPoints.push_back(Point(p.r, p.c - i));
        }
    }
    if (activate && destroyed)
        activate = false;
}

void GoodPlayer::recordAttackByOpponent(Point p)
{
    //goodplayer doesnt utilize this fcn in my implmentation
}


//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
                                                     type != types[pos]; pos++)
        ;
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}
