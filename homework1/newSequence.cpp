//
//  newSequence.cpp
//  homework1
//
//  Created by Izma Zuberi on 4/12/22.
//

#include "newSequence.h"

Sequence::Sequence(int i) //done
{
    if (i < 0)
        exit(1);

    m_sequence = new ItemType[i];
    m = i;
}

Sequence::Sequence(const Sequence& other)
{
    m = other.m;
    m_size = other.m_size;
    m_sequence = new ItemType[other.m_size];
    for (int i = 0; i < m_size; i++)
    {
        *(m_sequence + i) = *(other.m_sequence + i);
    }
}

Sequence& Sequence::operator=(const Sequence& other)
{
    Sequence placeholder(other);
    swap(placeholder);
    return *this;
}

Sequence::~Sequence()
{
    delete [] m_sequence;
}

bool Sequence::empty() const //done
{
    if (m_size == 0)
        return true;
    return false;
}
    
int Sequence::size() const //done
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value) //done
{
    if (pos >= m || pos < 0)
        return false;
    else if (m_size == m)
            return false;

    if (pos >= 0 && pos <= m)
    {
        for (int i = m_size - 1; i >= pos; i--)
        {
            m_sequence[i + 1] = m_sequence[i];
        }
        m_size++;
        m_sequence[pos] = value;
        return pos;
    }
    return -1;
}

int Sequence::insert(const ItemType& value) //done
{
    if (m_size >= m)
            return -1;
    else if (m_size == 0)
    {
        m_sequence[0] = value;
        m_size++;
        return 0;
    }
    
    int i = 0;

    while (m_sequence[i] <= value)
    {
        if (i == m_size - 1)
        {
            m_sequence[m_size] = value;
            m_size++;
            return m_size - 1;
        }
        i++;
    }

    for (int j = m_size; j >= i; j--)
    {
        m_sequence[j + 1] = m_sequence[j];
    }

    m_sequence[i] = value;
    m_size++;
    return i;

}
 
bool Sequence::erase(int pos) //done
{
    if (pos >= 0 && pos < m)
    {
        for(int i = pos; i < m_size - 1 ; i++)
        {
            m_sequence[i] = m_sequence[i + 1];
        }
        m_size--;
        return true;
    }
    return false;
}
 
int Sequence::remove(const ItemType& value) //done
{
    int count = 0;
    
    for (int i = 0; i < m_size; i++)
    {
        if (m_sequence[i] == value)
        {
            for (int j = i; j < m_size; j++)
            {
                m_sequence[j] = m_sequence[j + 1];
            }
            count++;
            m_size--;
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const //done
{
    if (pos >= 0 && pos < m_size)
    {
        value = m_sequence[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value) //done
{
    if (pos >= 0 && pos < m)
    {
        m_sequence[pos] = value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const //done
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_sequence[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other) //done
{
    ItemType* ptr = m_sequence;
    m_sequence = other.m_sequence;
    other.m_sequence = ptr;

    int size = m_size;
    m_size = other.m_size;
    other.m_size = size;

    int m_m = m;
    m = other.m;
    other.m = m_m;
}
