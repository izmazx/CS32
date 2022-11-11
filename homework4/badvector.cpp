//
//  badvector.cpp
//  homework4
//
//  Created by Izma Zuberi on 5/23/22.
//

void removeBad(vector<Restaurant*>& v)
{
    for (auto p = v.begin(); p != v.end(); p++)
    {
        if ((*p)->stars() <= 2)
        {
            delete *p;
            p = v.erase(p);
            p--;
        }
    }
}

