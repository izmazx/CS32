//
//  Sequence.cpp
//  homework1
//
//  Created by Izma Zuberi on 4/12/22.
//

#include "Sequence.h"

Sequence::Sequence() //done
{
    m_size = 0;
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
    if (pos >= 0 && pos <= m_size)
    {
        for (int i = m_size - 1; i > pos; i--)
        {
            m_sequence[i] = m_sequence[i - 1];
        }
        m_size++;
        m_sequence[pos] = value;
        return pos;
    }
    return -1;
}

int Sequence::insert(const ItemType& value) //done
{
    if (m_size >= DEFAULT_MAX_ITEMS)
        return -1;
    
    int p = 0;
    for(int i = 0; i < m_size; i++)
    {
        if(value <= m_sequence[i])
        {
            break;
        }
        p++;
    }
    
    for (int i = m_size; i > p; i--)
    {
        m_sequence[i] = m_sequence[i - 1];
    }
    
    m_sequence[p] = value;
    m_size++;
    return p;

}
 
bool Sequence::erase(int pos) //done
{
    if (pos >= 0 && pos < m_size)
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
    if (pos >= 0 && pos < m_size)
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
    Sequence placeholder;
    
    placeholder.m_size = other.m_size;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        placeholder.m_sequence[i] = other.m_sequence[i];
        placeholder.m_size = other.m_size;
    }
    
    other.m_size = m_size;
    for (int j = 0; j < DEFAULT_MAX_ITEMS; j++)
    {
        other.m_sequence[j] = m_sequence[j];
    }
    
    m_size = placeholder.m_size;
    for (int k = 0; k < DEFAULT_MAX_ITEMS; k++)
    {
        m_sequence[k] = placeholder.m_sequence[k];
    }
}

