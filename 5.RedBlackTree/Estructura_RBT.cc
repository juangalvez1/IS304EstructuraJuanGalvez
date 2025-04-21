#include <iostream>

using namespace std;

enum Color{RED, BLACK};

template<typename Type>
class RBT{
    private:
        class Node{
            private:
                Type data_;
                bool color_;
                Node* left_;
                Node* right_;
                Node* parent_;

            public:
                Node(Type elem = Type()) : data_(elem), left_(nullptr), right_(nullptr), parent_(nullptr), color_(RED) {}
                
                Type& data(){
                    return data_;
                }

                bool& color(){
                    return color_;
                }

                Node*& left(){
                    return left_;
                }

                Node*& right(){
                    return right_;
                }

                Node*& parent(){
                    return parent_;
                }
        };

        Node* root_;
        unsigned int size_;

        void rotateLeft(Node *x){
            Node *y = x->right();
            x->right() = y->left();
            
            if(y->left() != nullptr)
                y->left()->parent() = x;
            
            y->parent() = x->parent();

            if(x->parent() == nullptr){
                root_ = y;
            } else if(x == x->parent()->left()){ // Verificamos si x es un hijo izquierdo
                x->parent()->left() = y;
            } else{
                x->parent()->right() = y;
            }
        
            y->left() = x;
            x->parent() = y;
        }

        void rotateRight(Node *y){
            Node* x = y->left();
            y->left() = x->right();

            if(x->right() != nullptr)
                x->right()->parent() = y;

            x->parent() = y->parent();

            if(y->parent() == nullptr){
                root_ = x;
            } else if(y == y->parent()->left()){ // Verificamos si y es un hijo izquierdo
                y->parent()->left() = x;
            } else {
                y->parent()->right() = x;
            }

            x->right() = y;
            y->parent() = x;
        }

        void fixInsert(Node *node){
            while(node != root_ && node->parent()->color() == RED){
                Node* parent = node->parent();
                Node* grandParent = parent->parent();

                if(parent == grandParent->left()){
                    Node* uncle = grandParent->right();

                    if(uncle != nullptr && uncle->color() == RED){

                        parent->color() = BLACK;
                        uncle->color() = BLACK;
                        grandParent->color() = RED;
                        node = grandParent;

                    } else {
                        // RI case
                        if(node == parent->right()){
                            node = parent;
                            rotateLeft(node);
                        }
                        // II case
                        parent->color() = BLACK;
                        grandParent->color() = RED;
                        rotateRight(grandParent);

                    }
                } else {
                    Node* uncle = grandParent->left();

                    if(uncle != nullptr && uncle->color() == RED){

                        parent->color() = BLACK;
                        uncle->color() = BLACK;
                        grandParent->color() = RED;
                        node = grandParent;

                    } else {
                        // IR case
                        if(node == parent->left()){
                            node = parent;
                            rotateRight(node);
                        }
                        // RR case
                        parent->color() = BLACK;
                        grandParent->color() = RED;
                        rotateLeft(grandParent);

                    }
                }
            }
            root_->color() = BLACK;
        }

    public:
        RBT() : root_(nullptr), size_(0) {}

        void insert(const Type& elem){
            Node* newNode = new Node(elem);
            if (root_ == nullptr) {
                newNode->color() = BLACK;
                root_ = newNode;
                size_++;
                return;
            }

            Node* curr = root_;
            Node* parent = nullptr;

            while (curr != nullptr) {
                assert(elem != curr->get_data());
                parent = curr;
                if(elem < curr->data()){
                    curr = curr->left();
                } else {
                    curr = curr->right();
                }
            }

            newNode->parent() = parent;

            if(elem < parent->data()){
                parent->left() = newNode;
            } else {
                parent->right() = newNode;
            }

            size_++;

            if(parent->color() == RED){
                fixInsert(newNode);
            }
        }

        bool find(Type& elem) const {
            Node* curr = root_;

            while (curr != nullptr) {
                if (elem == curr->data()) {
                    return true;
                } else if (elem < curr->data()) {
                    curr = curr->left();
                } else {
                    curr = curr->right();
                }
            }
            
            return false;
        }

        unsigned int size() const {
            return size_;
        }
};

int main(){
    cout << "RBT" << endl;

    return 0;
}