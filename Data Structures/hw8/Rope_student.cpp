/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
    //taken from lecture. In order traversal
    if (ptr_->right != NULL) {
        ptr_ = ptr_->right;
        while (ptr_->left != NULL) {
            ptr_ = ptr_->left;
        }
    }
    else {
        while (ptr_->parent != NULL && ptr_->parent->right == ptr_) {
            ptr_ = ptr_->parent;
        }
        ptr_ = ptr_->parent;
    }
    return *this;
}


//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
    //make sure the root is valid and find the left most node
	if(root==NULL){
	    rope_iterator garbage = NULL;
	    return garbage;
	}
    Node * temp =root;
	while (temp->left !=NULL){
	    temp = temp->left;
	}
	rope_iterator test= temp;
	return test;
}

Rope::Rope(){
    size_=0;
    root=NULL;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	size_=0;
	root=p;
	Node* t= p;
	while (t!= NULL){
	    //increase the size by adding the right weights
	    size_+=t->weight;
	    t=t->right;
	}
}
void Rope::destroy_rope(Node* p) {
    //Based off of lecture code
    if(p!=NULL){
        destroy_rope(p->left);
        destroy_rope(p->right);
        delete p;
        size_--;
    }
}

Rope::~Rope(){
	this->destroy_rope(root);
	root=NULL;
	size_=0;
}

Rope::Rope(const Rope& r){
    size_=r.size_;
    root= this->copy_rope(r.root,NULL);
}

Node* Rope::copy_rope(Node *old, Node *parent) {
    //Based off lecture. Assert the node is good and recursively add nodes
    //Similar to ds_set copy made in lab
    if (old == NULL) {
        return NULL;
    }
    Node *answer = new Node();
    answer->weight = old->weight;
    answer->value=old->value;
    answer->left = copy_rope(old->left,answer);
    answer->right = copy_rope(old->right,answer);
    answer->parent = parent;
    return answer;
}

Rope& Rope::operator= (const Rope& r){
    if (&r != this) {
        this->destroy_rope(root);
        root = this->copy_rope(r.root,NULL);
        size_ = r.size_;
    }
    return *this;

}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
    //following the steps in homework
    //check the index
    Node * temp = root;
    if(i<0 or i>=size_){
        //std::cerr<<"Bad index"<<std::endl;
        return false;
    }
    //it will always try to traverse to the left so when it can't
    //that means it's at a leaf
    while (temp->left!=NULL){
        if(i>=temp->weight){
            i-=temp->weight;
            temp=temp->right;
            continue;
        }
        else if (i<temp->weight){
            temp=temp->left;
            continue;
        }
        else{
            temp=temp->left;
            continue;
        }
    }
    //extra assertion
    if(is_leaf(temp)) {
        c = temp->value[i];
        return true;
    }
    return false;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
    //following the steps in hw handout
    //make sure the size is good
    if(r.size()==0){
        return;
    }
    Node* temp_r;
    //run the copy function
    temp_r=copy_rope(r.root,NULL);

    //create the nodes and assign values
    Node* new_= new Node;
    new_->left=root;
    new_->weight=size_;
    new_->right=temp_r;

    temp_r->parent=new_;
    root->parent=new_;
    //adjust the sizes
    root=new_;
    size_+=r.size_;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
    //essentially run the index function from i to j
    //and concatenate the string together
    if(i<0 or j>= root->weight or j<i){
        //std::cerr<<"Bad index (report)"<<std::endl;
        return false;
    }

    s="";

    for (int k =i; k<j+1;k++){
        char c;
	    if(index(k,c)){
	        s+= c;
	    } else{ return false;}
	}
    return true;
}

void Rope::get_size(Node *n, int &s) {
    //use recursion to go through every node
    //and if it's a leaf you increase the value
    if (n!=NULL){
        get_size(n->left,s);
        get_size(n->right,s);
        if(is_leaf(n)){
            s+=n->value.size();
            return ;
        }
    }
}

void Rope::update() {
    //use iterators to go through whole rope
    //use the get size function to assign weights
    int x= 0;
    for (rope_iterator i= this->begin(); i!= this->end();i++){
        //case checking
        if(i.ptr_->right) {
            get_size(i.ptr_->left, x);
            i.ptr_->weight=x;
        }
        else{
            get_size(i.ptr_, x);
            i.ptr_->weight=x;
        }
        x=0;
    }
}
//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
    //Follows along with the homework handout
    //valid index
    if(i<0 or i>=size_){
        return *this;
    }
    //find the node where the index i is located
    Node * temp =root;
    while (temp->left!=NULL){
        if(temp->weight<=i){
            i-=temp->weight;
            temp=temp->right;
            continue;
        }
        else{
            temp=temp->left;
            continue;
        }
    }
    //see if we need to split at the middle
    if(i!=0){
        Node* child1= new Node; Node* child2 = new Node;

        child1->value= temp->value.substr(0,i);
        child2->value= temp->value.substr(i);
        child1->weight=child1->value.size();
        child2->weight=child2->value.size();
        temp->left=child1;
        temp->right=child2;
        temp->value="";
        child1->parent=temp; child2->parent=temp;
        temp->weight=child1->weight;
        temp=child2;
    }
    //find the location where we need to cut
    //check until the left side is the OTHER side of the rope
    while (true){
        if(temp->parent->left==temp){
            temp = temp->parent;
        }
        else{
            break;
        }
    }

    rhs.root=temp;
    temp= temp->parent;
    temp->right=NULL;

    //go up the rope until you reach the root
    //concatenate as you go along
    while (root != temp){
        if(temp->parent->left != temp or temp->parent->right==NULL){
            temp =temp->parent;
            continue;
        }
        else{
            if(temp->parent->right->parent!=NULL){
                temp->parent->right->parent=NULL;
            }
            Rope test(temp->parent->right);
            temp->parent->right=NULL;
            temp = temp->parent;
            rhs.concat(test);

        }
    }
    //adjust the sizes
    int x=0;
    get_size(rhs.root,x);
    rhs.size_=x;

    x=0;
    get_size(root,x);
    size_=x;
    //update the weights
    this->update();
    rhs.update();
    return *this;

}
