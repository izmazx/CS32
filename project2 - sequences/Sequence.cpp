//
//  Sequence.cpp
//  project2
//
//  Created by Izma Zuberi on 4/17/22.
//

#include "Sequence.h"

Sequence::Sequence() //DONE
{
    length = 0;
    head = nullptr;
    tail = nullptr;
}

Sequence::Sequence(const Sequence& other) //WORKS BUT CAUSES ISSUES W DESTRUCTOR IDK WHY
{
    length = other.length; //set length to equal other sequence
    
    if (other.length == 0) //if length is 0; set head + tail to null
    {
        head = nullptr;
        tail = nullptr;
        return;
    }
    
    //initalize a new list, make first node head
    head = other.head;
    
    Node* list = head;
    
    //loop thru sequence, assigning values to list
    for (Node* p = other.head; p != nullptr; p = p->next)
    {
        Node* newNode = new Node; //initalize new node and copy p into it
        newNode->mvalue = p->mvalue;
        newNode->mpos = p->mpos;
        newNode->next = p->next; // !! these lines are wrong, should only point to value,
        newNode->prev = p->prev; // !! NOT the entire node; has not been fixed; will cause                             memory leak when ~Sequence() is run
        list = newNode; //make newNode connect to list
        if (list->mpos == 0)
            head = list;
        
    }
    
    //assign last node as tail
    tail = list;
}

Sequence& Sequence::operator=(const Sequence& other) //DONE
{
    //if sequences are diff, copy other into placeholder, swap and return the new sequence
    if (this != &other)
    {
        Sequence placeholder(other); 
        swap(placeholder);
    }
    return *this;
}

Sequence::~Sequence() //DONE
{
    //empty list has nothing to delete
    if (head == nullptr)
        return;

    //goes thru list, deleting each node
    Node* next;
    Node* x = head;

    while (x != nullptr)
    {
        next = x->next;
        delete x;
        x = next;
    }
}



bool Sequence::empty() const //DONE
{
    if(length == 0)
        return true;
    return false;
}

int Sequence::size() const //DONE
{
    return length;
}

int Sequence::insert(int pos, const ItemType& value) //DONE
{
    if (length == 0) //add first element of a list
    {
        //initalize a new node
        Node* p = new Node;
        p->mvalue = value;
        p->next = nullptr;
        p->prev = nullptr;
        p->mpos = 0;
        
        //assign to head and tail
        head = p;
        tail = p;
        length++;
        return 0;
    }
    
    if (pos >=0 && pos <= length)
    {
        Node* p = head;
        
        
        for (Node* a = head; a != nullptr; a = a->next)  //loop thru length until pos
        {
            p = a;
            
            if (pos == 0) //insert at beginning
            {
                Node* newNode = new Node; //initalize new node and fit into sequence
                head = newNode;
                newNode->mvalue = value;
                newNode->mpos = 0;
                newNode->next = p;
                newNode->prev = nullptr;
                p->prev = newNode;
                
                
                for(; p != nullptr; p = p->next) //adjust pos of all subsequent nodes
                    p->mpos = p->mpos + 1;
                break;
            }
            
            if (p->mpos == pos) //insert to middle
            {
                Node* newNode = new Node;   //initalize new node and fit into sequence
                newNode->mvalue = value;
                newNode->prev = p->prev;
                newNode->mpos = p->mpos;
                newNode->next = p;
                
                //readjust surrounding nodes to include newNode
                if(pos != 0)
                    p->prev->next = newNode;
            
                p->prev = newNode;

                for(; p != nullptr; p = p->next) //adjust pos of all subsequent nodes
                    p->mpos = p->mpos + 1;
            }
        }
        
        if (pos == length) //adding to end
        {
            p = tail;
            Node* newNode = new Node;   //initalize new node and give it p's values
            newNode->mvalue = value;
            newNode->prev = p;
            newNode->mpos = p->mpos + 1;
            newNode->next = nullptr;
            
            p->next = newNode;    //readjust surrounding nodes to include newNode
            tail = newNode;
        }
        length++;
        return pos;
    }
    
    return -1;
}

int Sequence::insert(const ItemType& value) //DONE
{
    int pos = length;
    //loop backwards thru sequence to find pos, then insert value
    for (Node* p = tail; p != nullptr; p = p->prev)
    {
        if (value <= p->mvalue)
            pos = p->mpos;
    }
    insert(pos, value);
    return pos;
}

bool Sequence::erase(int pos) //DONE
{
    if (length == 0) //cant erase from empty sequence
        return false;
    
    if (pos >= 0 && pos < length)
    {
        Node* p = head;
        for (; p != nullptr; p = p->next)
        {
            if (pos == 0) //delete from beginning of list
            {
                head = p->next;
                head->prev = nullptr;
                delete p;
                break;
            }
            else if (pos == length - 1) //deleting from end of list
            {
                p = tail;
                tail = p->prev;
                p->prev->next = nullptr;
                delete p;
                break;
            }
            else if (p->mpos == pos + 1) //middle of list, delete value before p
            {
                Node* holder = p->prev;
                p->prev = p->prev->prev;
                p->prev->next = p;
                delete holder;
                break;
            }
        }
        for(; p != nullptr; p = p->next) //adjust pos of p and all subsequent nodes
            p->mpos = p->mpos - 1;
        
        length--;
        return true;
    }
    
    return false;
}

int Sequence::remove(const ItemType& value) //DONE
{
    int removed = 0;
    //loop thru sequence to find value and erase
    for (Node* p = head; p != nullptr; p = p->next)
    {
        if (value == p->mvalue)
        {
            erase(p->mpos);
            removed++;
        }
    }
    return removed;
}

bool Sequence::get(int pos, ItemType& value) const //DONE
{
    if (pos >= 0 && pos < length)
    {
        //loop thru sequence, set value to node's value at given pos
        for (Node* p = head; p != nullptr; p = p->next)
        {
            if (p->mpos == pos)
            {
                value = p->mvalue;
                return true;
            }
        }
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value) //DONE
{
    if (pos >= 0 && pos < length)
    {
        //loop thru sequence, set node's value to given value at given pos
        for (Node* p = head; p != nullptr; p = p->next)
        {
            if (p->mpos == pos)
            {
                p->mvalue = value;
                return true;
            }
        }
    }
    return false;
}

int Sequence::find(const ItemType& value) const //DONE
{
    for (Node* p = head; p != nullptr; p = p->next) //loop thru sequence
    {
        if (p->mvalue == value)
            return p->mpos; //return the first instance; aka the smallest pos of value
    }
    return -1;
}

void Sequence::swap(Sequence& other) //DONE
{
    //swap sizes
    int holder = length;
    length = other.length;
    other.length = holder;
    
    //swap heads and tails
    Node* h_holder = head;
    head = other.head;
    other.head = h_holder;
    
    Node* t_holder = tail;
    tail = other.tail;
    other.tail = t_holder;
}



int subsequence(const Sequence& seq1, const Sequence& seq2) //DONE
{
    if (seq1.empty()) //return -1 for empty seq1
        return -1;
    if (seq2.size() > seq1.size()) //seq2 cannt be a subseq if its larger than seq1
        return -1;
    
    ItemType value1;
    ItemType value2;
    int count = -1;
    int i = 0;
    
    for (int j = 0; j < seq1.size(); j++) //loop thru seq1
    {
        i = 0;
        seq2.get(i, value2); //get first value of seq2 and current value of seq1
        seq1.get(j, value1);
        
        if (value1 == value2) //if equal, set count and loop thru seq2
        {
            count = j;
            for(; i < seq2.size(); i++) //check that subsequent values match up
            {
                seq2.get(i + 1, value2);
                seq1.get(j + 1, value1);
                if (value2 != value1) //if not, break
                {
                    count = -1;
                    break;
                }
                if (i + 2 == seq2.size()) //if yes, return count
                    return count;
                j++; //?
            }
        }
    }
    
    return -1;
   
    // is seq2 a subsequence of seq1? if yes, return first pos1 of seq2. else return -1
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) //DONE
{
    result = seq1;
    int resultpos = seq1.size(); //the next empty pos in result
    
    //loop thru seq2
    for (int pos = 0; pos < seq2.size(); pos++)
    {
        ItemType tobeinsert;
        seq2.get(pos, tobeinsert);
        if (pos >= seq1.size())
        {
            //if seq2 extends past seq1, insert value into next open pos of result
            result.insert(resultpos, tobeinsert);
            resultpos++;
        }
        else //insert seq2 value at alternating pos in result
        {
            result.insert(pos+pos+1, tobeinsert);
        }
            
    }
}


