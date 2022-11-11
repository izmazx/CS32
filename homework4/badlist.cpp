//
//  badlist.cpp
//  homework4
//
//  Created by Izma Zuberi on 5/23/22.
//


void removeBad(list<Restaurant*>& li)
{
    for (auto p = li.begin(); p != li.end(); p++)
    {
        if ((*p)->stars() <= 2)
        {
            delete *p;
            p = li.erase(p);
            p--;
        }
    }
}


