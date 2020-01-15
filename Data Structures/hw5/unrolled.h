//
// Created by ahmeds7 on 2/17/2019.
//

#ifndef HW5_UNROLLED_H
#define HW5_UNROLLED_H

#include <cassert>
#include <iostream>

//Global Variable
const int NUM_ELEMENTS_PER_NODE = 6;
// -----------------------------------------------------------------
// NODE CLASS

template <class T>
class Node {
public:
    Node() : next_(NULL), prev_(NULL) {}
    Node(const T& v) : value_(v), next_(NULL), prev_(NULL) {}
   // ~Node(){delete [] value_;}

    // REPRESENTATION
    T value_[NUM_ELEMENTS_PER_NODE];
    Node<T>* next_;
    Node<T>* prev_;
    int num_elements=0;
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    list_iterator() : ptr_(NULL) {}
    list_iterator(Node<T>* p) : ptr_(p),offset(0) {}
    list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_) {}
    list_iterator<T>& operator=(const list_iterator<T>& old) {
        ptr_ = old.ptr_; offset=old.offset; return *this; }
    ~list_iterator() {}

    // dereferencing operator gives access to the value at the pointer
    T& operator*()  { return ptr_->value_[offset];  }

    // increment & decrement operators
    list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
        if(offset<ptr_->num_elements-1){
        offset+=1;
        return *this;}
        else {
            offset=0;
            ptr_ = ptr_->next_;
            return *this;
        }
    }
    list_iterator<T> operator++(int) { // post-increment, e.g., iter++
        list_iterator<T> temp(*this);
        if(offset<ptr_->num_elements-1){
            offset+=1;
            return temp;}
        else {
            offset=0;
            ptr_ = ptr_->next_;
            return temp;
        }
    }
    list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
        if(offset>0){
            offset-=1;
            return *this;}
        else {
            if(ptr_->prev_!=NULL) {
                offset = ptr_->prev_->num_elements - 1;
            }
            ptr_ = ptr_->prev_;
            return *this;
        }
    }
    list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
        list_iterator<T> temp(*this);
        if(offset>0){
            offset-=1;
            return temp;}
        else {
            if(ptr_->prev_!=NULL) {
                offset = ptr_->prev_->num_elements - 1;
            }
            ptr_ = ptr_->prev_;
            return temp;
        }
    }
    // the UnrolledLL class needs access to the private ptr_ member variable
    friend class UnrolledLL<T>;

    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const {
        return ptr_ == r.ptr_; }
    bool operator!=(const list_iterator<T>& r) const {
        return ptr_ != r.ptr_; }

private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    int offset;

};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
    UnrolledLL(const UnrolledLL<T>& old) { this->copy_list(old); }
    UnrolledLL& operator= (const UnrolledLL<T>& old);
    ~UnrolledLL() { this->destroy_list(); }

    // simple accessors & modifiers
    unsigned int size() const { return size_; }
    bool empty() const { return head_ == NULL; }
    void clear() { this->destroy_list(); }

    // read/write access to contents
    const T& front() const { return head_->value_[0];  }
    T& front() { return head_->value_[0]; }
    const T& back() const { return tail_->value_[tail_->num_elements-1]; }
    T& back() { return tail_->value_[tail_->num_elements-1]; }
    void print(std::ostream &cout);

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();

    typedef list_iterator<T> iterator;
    iterator erase(iterator &itr);
    iterator insert(iterator &itr, const T& v);
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(NULL); }
    iterator rbegin(){iterator x; x.ptr_=tail_;x.offset=tail_->num_elements-1;return x;}
    iterator rend() { return iterator(NULL); }

private:
    // private helper functions
    void copy_list(const UnrolledLL<T>& old);
    void destroy_list();

    //REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
    // check for self-assignment
    if (&old != this) {
        this->destroy_list();
        this->copy_list(old);
    }
    return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {
    if (tail_==NULL and head_==NULL){
        Node<T>* x = new Node<T>;
        tail_=head_=x;
        tail_->value_[tail_->num_elements]=v;
        tail_->num_elements+=1;
        ++size_;
        return;}
    else if (head_->num_elements==NUM_ELEMENTS_PER_NODE){

        Node<T>* x = new Node<T>;
        x->value_[0]=v;
        x->num_elements+=1;
        x->next_=head_;
        head_->prev_=x;
        head_=x;
        ++size_;
        return;
    }
    else{
        for(int i=head_->num_elements;i>0;i--){
            head_->value_[i]=head_->value_[i-1];
        }
        head_->value_[0]=v;
        head_->num_elements+=1;
        ++size_;
        return;
    }
}

template <class T>
void UnrolledLL<T>::pop_front() {
    if(head_==NULL and tail_==NULL){
        return;
    }
    Node<T>* x= head_;
    for(int i=0;i<NUM_ELEMENTS_PER_NODE-1;i++){
        head_->value_[i]=head_->value_[i+1];
    }
    head_->num_elements-=1;
    --size_;
    if(head_->num_elements==0){
        if(tail_ ==head_){
            destroy_list();
            return;
        }
        head_->next_->prev_=NULL;
        head_=head_->next_;
        delete x;
    }


}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
    if (tail_==NULL and head_==NULL){
        Node<T>* x = new Node<T>;
        tail_=head_=x;
        tail_->value_[tail_->num_elements]=v;
        tail_->num_elements+=1;
        ++size_;
        return;
    }
    else if(tail_->num_elements==NUM_ELEMENTS_PER_NODE){
        Node<T>* x = new Node<T>;
        x->prev_=tail_;
        tail_->next_=x;
        tail_=x;
        tail_->value_[tail_->num_elements]=v;
        tail_->num_elements+=1;
        ++size_;
        return;
    }
    else{
        tail_->value_[tail_->num_elements]=v;
        tail_->num_elements=tail_->num_elements+1;
        ++size_;
        return;
    }

}

template <class T>
void UnrolledLL<T>::pop_back() {
    if(head_==NULL and tail_==NULL){
        return;
    }
    Node<T>* x= tail_;

    tail_->num_elements-=1;
    --size_;
    if(tail_->num_elements==0){
        if(tail_ ==head_){
            destroy_list();
            return;
        }
        tail_->prev_->next_=NULL;
        tail_=tail_->prev_;
        delete x;
    }
}

// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
    if (left.size() != right.size()) return false;
    typename UnrolledLL<T>::iterator left_itr = left.begin();
    typename UnrolledLL<T>::iterator right_itr = right.begin();
    // walk over both lists, looking for a mismatched value
    while (left_itr != left.end()) {
        if (*left_itr != *right_itr) return false;
        left_itr++; right_itr++;
    }
    return true;
}
template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator &itr) {
    assert (size_ > 0);
    --size_;
    iterator result;
    itr.ptr_->num_elements-=1;
    if(itr.ptr_->num_elements==0){
        if(itr.ptr_== head_ and itr.ptr_==tail_){
            head_ = tail_ = NULL;
            delete itr.ptr_;
            return result;
        }
        else if(itr.ptr_==head_){
            head_ = head_->next_;
            head_->prev_ = 0;
            result = itr.ptr_->next_;
            delete itr.ptr_;
            result.offset=0;
            return result;
        }
        else if(itr.ptr_==tail_){
            tail_ = tail_->prev_;
            tail_->next_ = 0;
            result= itr.ptr_->prev_;
            delete itr.ptr_;
            result.offset=0;
            return result;
        }
        else{
            result=itr.ptr_->next_;
            itr.ptr_->prev_->next_ = itr.ptr_->next_;
            itr.ptr_->next_->prev_ = itr.ptr_->prev_;
            delete itr.ptr_;
            result.offset=0;
            return result;
        }
    }

    else{
        for (int q = itr.offset; q < itr.ptr_->num_elements+1; q++) {
            itr.ptr_->value_[q] = itr.ptr_->value_[q + 1];
        }
        result = itr.ptr_;
        result.offset=0;
        return  result;
    }
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator &itr, const T& v) {
    size_+=1;
    if(itr.ptr_->num_elements<NUM_ELEMENTS_PER_NODE){
        for(int i=itr.ptr_->num_elements;i>itr.offset;i--){
            itr.ptr_->value_[i]=itr.ptr_->value_[i-1];
        }
        itr.ptr_->value_[itr.offset]=v;
        itr.ptr_->num_elements+=1;
    }
    else {
        Node<T> *x = new Node<T>;
        int new_index = 0;
        for (int i = itr.offset; i < itr.ptr_->num_elements; i++) {
            x->value_[new_index] = itr.ptr_->value_[i];
            x->num_elements += 1;
            new_index++;
        }
        itr.ptr_->num_elements -= x->num_elements;
        itr.ptr_->value_[itr.offset] = v;
        itr.ptr_->num_elements += 1;
        x->prev_=itr.ptr_;
        x->next_=itr.ptr_->next_;
        itr.ptr_->next_->prev_=x;
        itr.ptr_->next_=x;
    }
    //itr.offset=itr.offset;
    //itr.ptr_=itr.ptr_;
    iterator result;
    result.ptr_=itr.ptr_;
    result.offset=itr.offset;

    return result;
}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {

    UnrolledLL::iterator x=old.head_;
    while (x!=NULL){
        this->push_back(*x);
        x++;
    }
}

template <class T>
void UnrolledLL<T>::destroy_list() {
    Node<T>* i =head_;
    while(i!=NULL){
        Node<T>* temp = i->next_;
        --size_;
        delete i;
        i=temp;
    }
    head_=NULL;
    tail_=NULL;
    size_=0;
}
template <class T>
void UnrolledLL<T>::print(std::ostream &cout){
    Node<T>* i= head_;
    cout<<"UnrolledLL, size: "<<size_<<std::endl;
    while(i!=NULL){
        cout<<" node:["<<i->num_elements<<"]";

        int x= i->num_elements;
        for(int j=0;j<x;j++){
            cout<< " "<<i->value_[j];
        }
        cout<<std::endl;
        i=i->next_;
    }
}

#endif //HW5_UNROLLED_H
