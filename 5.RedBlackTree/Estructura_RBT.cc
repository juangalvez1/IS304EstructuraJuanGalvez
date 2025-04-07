#include <iostream>

using namespace std;

enum Color{RED, BLACK};

template<typename Type>
class RBT{
    private:
        class Node{
            public:
                Type data;
                bool color;
                Node* left;
                Node* right;
                Node* parent;

                Node(Type elem = Type()) : data(elem), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}

                // Type get_data(){
                //     return data;
                // }

                // bool get_color(){
                //     return color;
                // }
        };

        Node* root_;

        void rotateLeft(Node *x){
            Node *y = x->right;
            x->right = y->left;
            
            if(y->left != nullptr)
                y->left->parent = x;
            
            y->parent = x->parent;

            if(x->parent == nullptr){
                root_ = y;
            } else if(x == x->parent->left){ // Verificamos si x es un hijo izquierdo
                x->parent->left = y;
            } else{
                x->parent->right = y;
            }
        
            y->left = x;
            x->parent = y;
        }

        void rotateRight(Node* y){
            Node* x = y->left;
            y->left = x->right;

            if(x->right != nullptr)
                x->right->parent = y;

            x->parent = y->parent;

            if(y->parent == nullptr){
                root_ = x;
            } else if(y == y->parent->left){ // Verificamos si y es un hijo izquierdo
                y->parent->left = x;
            } else {
                y->parent->right = x;
            }

            x->right = y;
            y->parent = x;
        }

    public:
        RBT() : root_(nullptr) {}

        void insert(Type elem){

        }
};

int main(){
    cout << "RBT" << endl;

    return 0;
}