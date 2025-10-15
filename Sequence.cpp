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
        for (int i = 0; i < sz; i++) {
            newNode->next = new SequenceNode();
            newNode->next->prev = newNode;
            newNode = newNode->next;

            newNode->next = nullptr;
            last = newNode;
        }
        count = sz;
    }

}
// Creates a (deep) copy of sequence s
Sequence::Sequence(const Sequence& s) {
    *this = s;
}
// Destroys all items in the sequence and release the memory
// associated with the sequence
Sequence::~Sequence() {
    SequenceNode* curNode = first;
    while (curNode->next != nullptr) {
        SequenceNode* newNode = curNode->next;
        delete curNode;
        curNode = newNode;
    }
}
// The current sequence is released and replaced by a (deep) copy of sequence
// s. A reference to the copied sequence is returned (return *this;).
Sequence& Sequence::operator=(const Sequence& s) {
    //delete old list//////////////////////////////////////////////////////////////////////

    SequenceNode* oldListNode = new SequenceNode();
    SequenceNode* newListNode = new SequenceNode();

    first->item = s.first->item;
    first->next = newListNode;
    oldListNode = s.first->next;
    newListNode->item = oldListNode->item;
    newListNode->prev = first;

    for (int i = 0; i < s.count-1; i++) {
        //Move through old list one step
        oldListNode = oldListNode->next;

        //Create new node and set prev to previous node
        newListNode->next = new SequenceNode();
        newListNode->next->prev = newListNode;
        newListNode = newListNode->next;

        //Copy value of old list to new
        newListNode->item = oldListNode->item;
    }
    last = newListNode;
    last->item = newListNode->item;
    last->prev = newListNode->prev;
    last->next = nullptr;

    return *this;
}
// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence
std::string& Sequence::operator[](size_t position) {
    if (position < count and position >= 0) {
        int i = 0;
        SequenceNode* curNode = first;
        while (i < position) {
            curNode = curNode->next;
            i++;
        }
        return curNode->item;
    }
    throw std::out_of_range("Sequence::operator[]");
}

// The value of item is append to the sequence.
void Sequence::push_back(std::string item) {
    SequenceNode* newNode = new SequenceNode();
    newNode->next = nullptr;
    newNode->prev = last;
    newNode->item = item;
    last->next = newNode;
    last = newNode;
    this->count = this->count + 1;
}
// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back() {
    last->prev->next = nullptr;
    last = last->prev;
}
// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exceptionif the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item) {
    if ((position > -1) and (position < this->count)) {
        SequenceNode* newNode = new SequenceNode();
        newNode = first;
        for (int i = 0; i < position; i++) {
            newNode = newNode->next;
        }
        newNode->item = item;
    }
}
// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    return first->item;
}
// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    return last->item;
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
    delete this;
}
// The item at position is removed from the sequence, and the memory
// is released. If called with an invalid position throws an exception.
void Sequence::erase(size_t position) {
    if ((position < count) and (position > -1)) {
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
}
// The items in the sequence at ( position ... (position + count - 1) ) are
// deleted and their memory released. If called with invalid position and/or
// count throws an exception.
void Sequence::erase(size_t position, size_t count) {
    if (((position + count) < this->count) and (position > -1)) {
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
        while (i < count) {
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
}
// Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
// stream. This is *not* a method of the Sequence class, but instead it is a
// friend function
std::ostream& operator<<(std::ostream& os, const Sequence& s){
    std::string list;
    const SequenceNode *curNode = s.first;
    list = "<";
    while (curNode->next != nullptr) {
        list = list + curNode->item;
        curNode = curNode->next;
        if (curNode->next != nullptr) {
            list = list + ", ";
        }
    }
    list = list + ">";

    os << list;
    return os;
}