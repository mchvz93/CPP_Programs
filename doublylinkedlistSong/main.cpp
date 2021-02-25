//
//  main.cpp
//  doublylinkedlistSong
//
//  Created by Marco A. Chavez Jr. on 3/20/18.
//  Copyright © 2018 Marco A. Chavez Jr. All rights reserved.
//

#include <iostream>


struct data {
    data() : data(" ", 0) {}
    data(const std::string& song, size_t plays) : song_(song), plays_(plays) {}

    friend std::istream& operator>> (std::istream& is, data& d) {
        return is >> d.song_ >> d.plays_ ;
    }
    friend std::ostream& operator <<(std::ostream& os, data& d) {
        return os << d.song_ << " , " << d.plays_;
    }

    std::string song_;
    size_t plays_;

};

struct dnode {
    dnode() : dnode(data()) {}
    dnode(const data& data, dnode* prev=nullptr, dnode* next=nullptr)
    : data_(data),  prev_(prev), next_(next) {}

    friend std::istream& operator>>(std::istream& is, dnode& node) {
        is >> node.data_;
        node.prev_ = node.next_ = nullptr;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, dnode& node) {
        return os << node.prev_ << "<-" << node.data_  << "(" << &node << ")->" << node.next_;
    }

    data data_;
    dnode* prev_;
    dnode* next_;

};


class dlinkedlist {
public:
    dlinkedlist() : head_(nullptr), tail_(nullptr), size_(0) {}
    dnode* head() { return head_; }
    dnode* tail() { return tail_; }
    bool empty() const {return size_ == 0; }
    size_t size() const { return size_; }
    friend std::ostream& operator<<(std::ostream& os, const dlinkedlist& dli) {
        if (dli.empty()) { return os << "the list is empty\n\n"; }
        dnode* m = dli.head_;
        while (m != NULL) {
            os << *m << "\n";
            m = m->next_;
        }
        return os;

    }

    //for dnodes that use constant
    void prepend(const data& data) { prepend(new dnode(data, head_, nullptr)); }
    void append(const data& data) { append(new dnode(data, tail_, nullptr)); }

    //for dnodes that change data
    void prepend(dnode* node) {
        if (node == nullptr) { throw new std::invalid_argument("null"); }
        node->next_ = head_;
        node->prev_ = nullptr;

        if (head_ != nullptr) { head_->prev_ = node; }
        head_ = node;

        if(size_ == 0) { tail_ = head_; }
        ++size_;
    }

    void append(dnode* node) {
        if (node == nullptr) { throw new std::invalid_argument("null pointer found"); }
        if (size_ == 0 ) { prepend(node); return; }
        node->prev_ = tail_;
        node->next_ = nullptr;
        tail_->next_ = node;
        tail_ = node;
        ++size_;
    }

    //removes the head of the list
    dnode* removehead() {
        if (empty()) { return nullptr; }
        dnode* remove_head = head_;
        head_ = head_->next_;
        if (size_ == 1 ) { tail_ = head_; }
        else { head_->prev_ = nullptr; }
        --size_;

        remove_head->next_ = remove_head->prev_ = nullptr;
        return remove_head;
    }
    //removes the last node from the list
    dnode* removetail() {
        if (empty()) { return nullptr; }
        dnode* remove_tail = tail_;
        tail_ = tail_->prev_;
        if (size_ == 1) { head_ = tail_; }
        else { tail_->next_ = nullptr; }
        --size_;

        remove_tail->next_ = remove_tail->prev_ = nullptr;
        return remove_tail;
    }
    template <typename T>
    void print(const std::string& msg, const T& dli) { std::cout << msg << dli << "\n"; }

private:
    dnode* head_;
    dnode* tail_;
    size_t size_;

};

//char menu() {
//    char choice;
//    std::cout << "Menu \n";
//    std::cout << "1. Add item. \n";
//    std::cout << "2. Remove the head. \n";
//    std::cout << "3. Remove the tail. \n";
//    std::cout << "4. Exit. \n";
//    std::cout << std::endl;
//    std::cin >> choice;
//    return choice;
//
//}


int main(int argc, const char * argv[]) {
////    data d;
////    dnode dno;
//    dlinkedlist dli;
////    char choice;
////    size_t userinput;
////    dnode *head = NULL;
////    dnode *last = NULL;
//    char choice;
//    int number;
//
//    do {
//
//        choice = menu();
//        switch(choice) {
//            case '1' :
//
////                std::cout << "Enter the name of the song\n";
////                std::cin >> dno.;
////                std::cout << "Enter number of plays\n";
////                std::cin >> d.plays_;
//
//
//
//                break;
//            case '2' :
//                break;
//            case '3' :
//                break;
//            default: std::cout << "Goodbye. \n";
//                break;
//            }
//
//        }while(choice != '4');
//
//        return 0;
    dlinkedlist dli;
    
    dli.print("li is ..\n", dli);
    dli.append(data("Hammer Smashed Face", 3));
    dli.append(data("Where is your God now?", 7));
    dli.append(data("I Thank God For The Suffering", 9));
    dli.print("dli is.. ", dli);

    std::cout  << "Done...\n";
    return 0;
    
}

