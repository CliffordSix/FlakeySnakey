#if !defined    LIST_HPP
#define         LIST_HPP

#include <string>

class Node;
struct point{

        int x;
        int y;

};

class List {

    public:

        ~List();

        void pushBack( const point& midpoint );
        void popBack();

        bool empty() const { return size_ == 0; }



    private:
        Node* head_ { nullptr };
        Node* tail_ { nullptr };

        unsigned int size_ { 0 };
};

class Node {

    public:
        Node() = default;

        Node( const point& midpoint, Node* prev = nullptr, Node* next = nullptr );

        point midpoint() const { return midpoint_; }

    private:

        friend class List;

        Node* prev_ { nullptr };
        Node* next_ { nullptr };
        point midpoint_;

};

#endif
