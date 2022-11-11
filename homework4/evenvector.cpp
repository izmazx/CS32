//
//  evenvector.cpp
//  homework4
//
//  Created by Izma Zuberi on 5/23/22.
//


void removeEven(vector<int>& v)
{
    int i = 0;
    while (i < v.size())
    {
        if (v[i]%2 == 0)
        {
            vector<int>::iterator itr;
            itr = find(v.begin(), v.end(), v[i]);
            v.erase(itr);
            continue;
        }
        i++;
    }
}


