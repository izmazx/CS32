//
//  main.cpp
//  project2
//
//  Created by Izma Zuberi on 4/17/22.
//

#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    s.insert(1);
    s.insert(1, 2);
    s.insert(2, 3);
    Sequence r;
    r.insert(5);
    r.insert(6);
    r.insert(7);
    r.insert(8);
    
    assert(s.size() == 3);
    assert(r.size() == 4);
    
    ItemType value;
    ItemType value2;

    Sequence q(r);
    s = r;
   // assert(s.size() == r.size());
    assert(q.get(0, value) == r.get(0, value2));
   // assert(s.get(2, value) == r.get(2, value2));

    
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
    
    
}
