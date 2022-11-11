//
//  LevelList.cpp
//  homework1
//
//  Created by Izma Zuberi on 4/12/22.
//

#include "LevelList.h"

LevelList::LevelList():levellist()
{
}


bool LevelList::add(unsigned long level) //done
{
    if (level >= 30 && level <= 400 && levellist.size() < DEFAULT_MAX_ITEMS)
    {
        levellist.insert(levellist.size(), level);
        return true;
    }
    return false;
}

bool LevelList::remove(unsigned long level) //done
{
    int i = levellist.find(level);
    if (i == -1)
    {
        return false;
    }
    levellist.erase(i);
    return true;
}

int LevelList::size() const //done
{
    return levellist.size();
}

unsigned long LevelList::minimum() const //done
{
    if (levellist.size() == 0)
        return NO_LEVEL;
    
    unsigned long min;
    levellist.get(0, min);
    
    unsigned long test;
    for(int i = 0; i < levellist.size(); i++)
    {
        levellist.get(i, test);
        if (min > test)
            min = test;
    }
    return min;
}

unsigned long LevelList::maximum() const //done
{
    if (levellist.size() == 0)
        return NO_LEVEL;

    unsigned long max;
    levellist.get(0, max);
    
    unsigned long test;
    for(int i = 0; i < levellist.size(); i++)
    {
        levellist.get(i, test);
        if (max < test)
            max = test;
    }
    return max;
}
