//
//  testLevelList.cpp
//  homework1
//
//  Created by Izma Zuberi on 4/12/22.
//

#include "LevelList.h"

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    LevelList s;
    assert(s.maximum() == NO_LEVEL);
    assert(s.minimum() == NO_LEVEL);
    assert(!s.add(500));
    assert(s.add(50));
    s.add(200);
    s.add(99);
    s.add(60);
    s.add(60);
    assert(s.maximum() == 99);
    assert(s.minimum() == 50);
    assert(s.size() == 5);
    assert(s.remove(60) == 1);
    assert(s.remove(99) == 1);
    assert(s.size() == 3);
    assert(s.maximum() == 60);
    assert(s.remove(500) == 0);
    assert(s.remove(69) == 0);

    cerr << "slay" << endl;
    return 0;
}

