#include <string>

class SequenceNode {
public: // to make it easier, we can make the data members public so we don't need
    // getters and setters
    SequenceNode* next; // pointer to next Node. If node is the tail, next is
    // nullptr
    SequenceNode* prev; // pointer to previous Node. If node is the head, prev is
    // nullptr
    std::string item; // the element being stored in the node
    //default constructor, ensure next and prev are nullptr
    SequenceNode() : next(nullptr), prev(nullptr)
    {}
    /// parameterized constructor, next and prev are set to nullptr and the
    /// node's element is set to the given value
    SequenceNode(std::string item) : next(nullptr), prev(nullptr), item(item)
    {}
};

class Sequence {
    private:
        SequenceNode* first;
        SequenceNode* last;
        size_t count;


    public:
        Sequence(size_t sz = 0);
        Sequence(const Sequence& s);
        ~Sequence();
        Sequence& operator=(const Sequence& s);
        std::string& operator[](size_t position);
        void push_back(std::string item);
        void pop_back();
        void insert(size_t position, std::string item);
        std::string front() const;
        std::string back() const;
        bool empty() const;
        size_t size() const;
        void clear();
        void erase(size_t position);
        void erase(size_t position, size_t count);
        friend std::ostream& operator<<(std::ostream& os, const Sequence& s);
    /*
     *  <<: returns all the elements in the list in string format to stream
     *
     * returns: ostream
     */
    friend std::ostream& operator<<(std::ostream& os, const Sequence& s){
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
};
