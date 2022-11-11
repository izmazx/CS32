// NameTable.cpp

// This is a correct but inefficient implementation of
// the NameTable functionality.

#include "NameTable.h"
#include <string>
#include <list>
#include <algorithm>
#include <functional>
using namespace std;

  // This class does the real work of the implementation.
//fastest is 57 for 400k
const int BUCKETS = 409;


class NameTableImpl
{
  public:
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
    unsigned int hashString(const string &id) const;

  private:
    struct Bucket
    {
        string m_id;
        int m_line;
        int m_scope;
    };
    
    list<Bucket> table[BUCKETS];
    int currentScope = 0;
};



unsigned int NameTableImpl::hashString(const string &id) const
{
    std::hash<string> strhash;
    unsigned int hashVal = strhash(id);
    return (hashVal%BUCKETS);
}

void NameTableImpl::enterScope()
{
    currentScope++;
}

bool NameTableImpl::exitScope()
{
    if (currentScope == 0)
        return false;
    
    for (int i = 0; i < BUCKETS; i++)
    {
        if (table[i].empty())
            continue;
        
        while (table[i].back().m_scope >= currentScope && table[i].size() > 0)
        {
            table[i].pop_back();
        }
    }

    currentScope--;
    return true;

}

bool NameTableImpl::declare(const string& id, int lineNum)
{
    if (id.empty())
        return false;

    int hashVal = hashString(id);
    //if same value is found and has same m_scope as currentScope, return false
    
    if(!table[hashVal].empty())
    {
        for (auto itr = table[hashVal].begin(); itr != table[hashVal].end(); itr++)
        {
            if (itr->m_id == id && itr->m_scope == currentScope)
                return false;
        }
    }
    
    table[hashVal].push_back(Bucket{id, lineNum, currentScope});
    return true;

}

int NameTableImpl::find(const string& id) const
{
    if (id.empty())
        return -1;

    
    int hashVal = hashString(id);
    int line = -1;

    if (!table[hashVal].empty())
    {
        for (auto i = table[hashVal].begin(); i != table[hashVal].end(); i++)
        {
            if (i->m_id == id)
            {
                line = i->m_line;
            }
        }
        return line;
    }
    return -1;

}

//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl;
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}


