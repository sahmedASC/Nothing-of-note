#include <iostream>

class Node{
public:
    int value=0;
    Node* left;
    Node* right;
};

bool shape(Node* &a, Node* &b){
    if(!a and !b){
        return true;
    }
    if(a and !b){
        return  false;
    }
    if(!a and b){
        return false;
    }
    bool x=shape(a->left,b->left);
    if(!x)return false;
    x= shape(a->right,b->right);
    if(!x) return false;
    return true;

}
void print(Node* &p){
    if(p) {
        print(p->left);
        print(p->right);
        std::cout << p->value<<" ";
        return;
    }
}
Node* find_tree(Node*&c, Node*&a){
    if(shape(c,a)){
        return c;
    }
    if(!c){
        return NULL;
    }
    else{
        Node*x= find_tree(c->left,a);
        if (x) return x;
        x=find_tree(c->right,a);
        if(x) return x;
    }
}
int main() {

    Node *c =new Node;
    c->value=15;
    c->left=new Node;
    c->left->value=20;
    c->left->left=new Node;
    c->left->left->value=4;
    c->left->right=new Node;
    c->left->right->value=12;
    c->right= new Node;
    c->right->value=14;
    c->right->left=new Node;
    c->right->left->value=16;
    c->right->left->left=new Node;
    c->right->left->left->value=3;
    c->right->left->right=new Node;
    c->right->left->right->value=18;
    c->right->right=new Node;
    c->right->right->value=2;
    c->right->right->right=new Node;
    c->right->right->right->value=19;

    Node * a = new Node;
    a->left = new Node;
    a->right = new Node;
    a->left->left = new Node;
    a->left->right = new Node;
    a->right->right = new Node;
    a->value = 5;
    a->left->value = 7;
    a->right->value = 13;
    a->left->left->value = 6;
    a->left->right->value = 11;
    a->right->right->value = 21;

    Node * a_ = new Node;
    a_->left = new Node;
    a_->right = new Node;
    a_->left->left = new Node;
    a_->left->right = new Node;
    a_->right->right = new Node;
    a_->value = 5;
    a_->left->value = 7;
    a_->right->value = 13;
    a_->left->left->value = 6;
    a_->left->right->value = 11;
    a_->right->right->value = 21;

    print(c);
    std::cout<<std::endl;
    print(a);
    std::cout<<std::endl;

    if(shape(a_,a)){
        std::cout<<"equal"<<std::endl;
    } else std::cout<<"not good"<<std::endl;

    Node* o = find_tree(c,a);
    print(o);
    std::cout<<std::endl;
    print(a);


    return 0;
}