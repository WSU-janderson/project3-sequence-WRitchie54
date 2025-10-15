#include "Sequence.h"

#include <stdexcept>
#include <string>
// Creates an empty sequence (numElts == 0) or a sequence of numElts items
// indexed from 0 ... (numElts - 1).
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
// Creates a (deep) copy of sequence s
Sequence::Sequence(const Sequence& s) {
    *this = s;
}
// Destroys all items in the sequence and release the memory
// associated with the sequence
Sequence::~Sequence() {
    this->clear();
}
// The current sequence is released and replaced by a (deep) copy of sequence
// s. A reference to the copied sequence is returned (return *this;).
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
// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence
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

// The value of item is append to the sequence.
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
// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
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
// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exceptionif the position is outside the bounds of the
// sequence
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
// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    if (first != nullptr) {
        return first->item;
    }
    throw std::runtime_error("Empty sequence");
}
// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    if (first != nullptr) {
        return last->item;
    }
    throw std::runtime_error("Empty sequence");
}
// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const {
    if (first->next == nullptr && last->prev == nullptr) {
        return true;
    }
    else {
        return false;
    }
}
// Return the number of elements in the sequence.
size_t Sequence::size() const {
    return this->count;
}
// All items in the sequence are deleted and the memory associated with the
// sequence is released, resetting the sequence to an empty state that can have
// items re-inserted.
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
// The item at position is removed from the sequence, and the memory
// is released. If called with an invalid position throws an exception.
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
// The items in the sequence at ( position ... (position + count - 1) ) are
// deleted and their memory released. If called with invalid position and/or
// count throws an exception.
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
// Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
// stream. This is *not* a method of the Sequence class, but instead it is a
// friend function
std::ostream& operator<<(std::ostream& os, const Sequence& s){
    //Setup string to hold node info
    std::string list;
    //start at first node
    const SequenceNode *curNode = s.first;
    list = "<";
    //Until end of list add each item to string output
    while (curNode->next != nullptr) {
        list = list + curNode->item;
        curNode = curNode->next;
        if (curNode != nullptr) {
            list = list + ", ";
        }
    }
    list = list + curNode->item;
    list = list + ">";

    //Return string to stream
    os << list;
    return os;
}