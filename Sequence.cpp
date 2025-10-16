/*
*  Name: Wyatt Ritchie
 *  Project: Sequence CS3100 Project 3
 *
 *  Desc: Implementation of doubly linked list
 */

#include "Sequence.h"

#include <stdexcept>
#include <string>

/* Sequence Constructor: Create a sequence with size sz
 *
 * param sz: Size of the sequence
 */
Sequence::Sequence(size_t sz) {
    if (sz > 0) {
        SequenceNode* newNode = new SequenceNode();
        first = newNode;
        last = newNode;
        for (int i = 0; i < sz-1; i++) {
            newNode->next = new SequenceNode();
            newNode->next->prev = newNode;
            newNode = newNode->next;

            newNode->next = nullptr;
            last = newNode;
        }
        count = sz;
    }
    else {
        count = 0;
        first = nullptr;
        last = nullptr;
    }

}

/*
 * Sequence: Creates a new sequence as a deep copy of another
 *
 * param s: The sequence that you are copying from
 */
Sequence::Sequence(const Sequence& s) {
    *this = s;
}

/* Destructor: Deletes all the nodes within the list and then releases list
*
*/
Sequence::~Sequence() {
    this->clear();
}


/*
 * Sequence =: Clear current sequence and make a deep copy of the one passed
 *
 * param s: Sequence to make deep copy of
 */
Sequence& Sequence::operator=(const Sequence& s) {
    this->clear();

    SequenceNode* oldListNode = s.first;
    SequenceNode* newListNode = new SequenceNode();

    newListNode->item = oldListNode->item;
    first = newListNode;

    while (oldListNode->next != nullptr) {
        //Move through old list one step
        oldListNode = oldListNode->next;

        //Create new node and set prev to previous node
        newListNode->next = new SequenceNode();
        newListNode->next->prev = newListNode;
        newListNode = newListNode->next;

        //Copy value of old list to new
        newListNode->item = oldListNode->item;
    }

    //setup last as the last copied over value
    last = newListNode;
    last->item = newListNode->item;
    last->prev = newListNode->prev;
    last->next = nullptr;
    count = s.count;

    return *this;
}

/* Operator[]: Go to specific position of list and return element
 *
 *  param position: point in list to return element from
 */
std::string& Sequence::operator[](size_t position) {
    //Make sure position is in range of number of elements
    if (position < count and position >= 0) {
        int i = 0;
        SequenceNode* curNode = first;
        while (i < position) {
            curNode = curNode->next;
            i++;
        }
        return curNode->item;
    }
    throw std::invalid_argument("Invalid position");
}

/*
 * push_back: Append item to end of list
 *
 * param item: The string to put in node at back of list
 */
void Sequence::push_back(std::string item) {
    //Create new node to be last item
    SequenceNode* newNode = new SequenceNode();
    if (first == nullptr) {
        first = newNode;
    }
    else {
        last->next = newNode;
        newNode->next = nullptr;
        newNode->prev = last;
    }

    newNode->item = item;

    //Set last to be the new node and add to count
    last = newNode;
    count = count + 1;
}

/*
 * pop_back: delete last item of sequence
 */
void Sequence::pop_back() {
    if (first != nullptr) {
        SequenceNode* curLast = last;
        if (first != last) {
            last = last->prev;
            last->next = nullptr;
        }
        else {
            delete curLast;
            curLast = first;
            first = nullptr;
            last = nullptr;
        }

        delete curLast;
        count--;
    }
    else {
        throw std::invalid_argument("Nothing in list");
    }

}
/*
 * insert: Insert item at specific point of list
 *
 * param position: Position to insert at
 *        item: String to insert at position
 */
void Sequence::insert(size_t position, std::string item) {
    //Make sure position is in element list
    if ((position >= 0) and (position < this->count)) {
        //Create new node
        SequenceNode* newNode = new SequenceNode();
        SequenceNode* curNode = first;

        //Get to position in list where insert will happen
        for (int i = 0; i < position; i++) {
            curNode = curNode->next;
        }
        //set the next nodes previous node to the new one
        newNode->next = curNode;
        newNode->prev = curNode->prev;

        //Set next node to new node
        if (curNode != first) {
            curNode->prev->next = newNode;
        }
        else {
            first = newNode;
        }
        curNode->prev = newNode;


        newNode->item = item;

        count++;
    }
    else {
        throw std::invalid_argument("Invalid position");
    }
}

/*
 * front: returns the first element of the list
 */
std::string Sequence::front() const {
    if (first != nullptr) {
        return first->item;
    }
    throw std::runtime_error("Empty sequence");
}
/*
 * back: returns the last element of the list
 */
std::string Sequence::back() const {
    if (first != nullptr) {
        return last->item;
    }
    throw std::runtime_error("Empty sequence");
}

/*
 *  empty: returns true if sequence is empty
 *
 *  return boolean of if sequence is empty or not
 */
bool Sequence::empty() const {
    if (first->next == nullptr && last->prev == nullptr) {
        return true;
    }
    else {
        return false;
    }
}
/*
 * Size returns the number of elements in list
 *
 * return size_t count of list
 */
size_t Sequence::size() const {
    return this->count;
}

/*
 * clear: items in list deleted with memory cleared
 */
void Sequence::clear() {
    if (first != nullptr) {
        SequenceNode* curNode = first;
        while (curNode->next != nullptr) {
            SequenceNode* newNode = curNode->next;
            delete curNode;
            curNode = newNode;
        }
    }
    first = nullptr;
    last = nullptr;
    count = 0;
}

/*
 * erase: Get rid of node at specific position
 *
 * param
 *  position: position to delete element from
 */
void Sequence::erase(size_t position) {
    if ((position < count) and (position >= 0)) {
        int i = 0;
        SequenceNode* curNode = first;
        while (i < position) {
            curNode = curNode->next;
            i++;
        }
        curNode->prev->next = curNode->next;
        curNode->next->prev = curNode->prev;
        delete curNode;
    }
    else {
        throw std::invalid_argument("Invalid position");
    }
}
/*
 * erase: delete nodes from starting position till end of count supplied
 *
 * params
 *  position: position to start deletion at
 *  count: number of nodes to delete starting from position
 */
void Sequence::erase(size_t position, size_t count) {
    if (((position + count) < this->count) and (position >= 0)) {
        //Find first node that needs deleted
        int i = 0;
        SequenceNode* firstDeleteNode = first;
        while (i < position) {
            firstDeleteNode = firstDeleteNode->next;
            i++;
        }

        //Find last node that needs deleted
        i = 0;
        SequenceNode* lastDeleteNode = firstDeleteNode;
        while (i < count-1) {
            lastDeleteNode = lastDeleteNode->next;
            i++;
        }

        //Setup nodes outside of delete range to be connected
        firstDeleteNode->prev->next = lastDeleteNode->next;
        lastDeleteNode->next->prev = firstDeleteNode->prev;

        //Delete range of nodes that need deleted
        while (firstDeleteNode != lastDeleteNode) {
            firstDeleteNode = firstDeleteNode->next;
            delete firstDeleteNode->prev;
        }
        delete lastDeleteNode;
    }
    else {
        throw std::invalid_argument("Invalid position or count");
    }
}

