//
//  main.cpp
//  project1
//
//  Created by Izma Zuberi on 4/3/22.
//

#include "globals.h"
#include "Gark.h"
#include "Mesa.h"
#include "Player.h"
#include "Game.h"
#include "History.h"

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}
