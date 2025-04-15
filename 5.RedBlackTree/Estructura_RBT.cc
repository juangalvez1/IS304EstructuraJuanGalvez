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

    public:
        RBT() : root_(nullptr) {}

        void insert(Type& elem, Node* start= nullptr){
            if (start == nullptr) {
                start = root_;
            }
            Node* newNode = new Node(elem);
        }
};

int main(){
    cout << "RBT" << endl;

    return 0;
}