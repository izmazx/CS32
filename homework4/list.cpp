//
//  test.cpp
//  homework4
//
//  Created by Izma Zuberi on 5/23/22.
//


void listAll(const Domain* d, string path) // two-parameter overload
{
    if (d->subdomains().empty())
    {
        cout << path << endl;
        return;
    }

    if (path != "")
        path = '.' + path;
    for (auto p = d->subdomains().begin(); p != d->subdomains().end(); p++)
        listAll(*p, (*p)->label() + path);
}


