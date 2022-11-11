//
//  Game.h
//  project1
//
//  Created by Izma Zuberi on 4/3/22.
//

#ifndef Game_h
#define Game_h

class History;
class Mesa;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

#endif /* Game_h */
