//
//  newSequence.h
//  homework1
//
//  Created by Izma Zuberi on 4/12/22.
//

#ifndef newSequence_h
#define newSequence_h

#include <iostream>

using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 180;

class Sequence
{
  public:
    Sequence(int i = DEFAULT_MAX_ITEMS);
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);
    ~Sequence();
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
  private:
    int m_size;
    int m;
    ItemType *m_sequence;
        
};


#endif /* newSequence_h */
