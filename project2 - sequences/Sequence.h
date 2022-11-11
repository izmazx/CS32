//
//  Sequence.h
//  project2
//
//  Created by Izma Zuberi on 4/17/22.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>

using ItemType = int;

class Sequence
{
  public:
    Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);
    ~Sequence();
    
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
  private:
    struct Node
    {
        ItemType mvalue;
        Node* next;
        Node* prev;
        int mpos;
    };
    
    Node* head;
    Node* tail;
    int length;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif /* Sequence_h */
