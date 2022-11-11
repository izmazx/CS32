//
//  main.cpp
//  homework4
//
//  Created by Izma Zuberi on 5/23/22.
//


void removeEven(list<int>& li)
{
    list<int>::iterator itr;
    itr = li.begin();
    
    while (itr != li.end())
    {
        if (*itr%2 == 0)
        {
            li.erase(itr);
        }
        itr++;
    }
}


