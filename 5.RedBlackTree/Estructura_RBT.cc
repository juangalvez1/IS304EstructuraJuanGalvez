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

        void fixDelete(Node* x) {
            while (x != root_ && (x == nullptr || x->color() == BLACK)) {
                if (x == x->parent()->left()) {
                    Node* w = x->parent()->right();
        
                    // Caso 1: El hermano es rojo
                    if (w != nullptr && w->color() == RED) {
                        w->color() = BLACK;
                        x->parent()->color() = RED;
                        rotateLeft(x->parent());
                        w = x->parent()->right();
                    }
        
                    // Caso 2: Hermano y ambos hijos negros
                    if ((w->left() == nullptr || w->left()->color() == BLACK) &&
                        (w->right() == nullptr || w->right()->color() == BLACK)) {
                        w->color() = RED;
                        x = x->parent();
                    } else {
                        // Caso 3: Hermano negro con hijo izquierdo rojo y derecho negro
                        if (w->right() == nullptr || w->right()->color() == BLACK) {
                            if (w->left() != nullptr)
                                w->left()->color() = BLACK;
                            w->color() = RED;
                            rotateRight(w);
                            w = x->parent()->right();
                        }
        
                        // Caso 4: Hermano negro con hijo derecho rojo
                        w->color() = x->parent()->color();
                        x->parent()->color() = BLACK;
                        if (w->right() != nullptr)
                            w->right()->color() = BLACK;
                        rotateLeft(x->parent());
                        x = root_;
                    }
                } else {
                    // Versión espejo
                    Node* w = x->parent()->left();
        
                    if (w != nullptr && w->color() == RED) {
                        w->color() = BLACK;
                        x->parent()->color() = RED;
                        rotateRight(x->parent());
                        w = x->parent()->left();
                    }
        
                    if ((w->left() == nullptr || w->left()->color() == BLACK) &&
                        (w->right() == nullptr || w->right()->color() == BLACK)) {
                        w->color() = RED;
                        x = x->parent();
                    } else {
                        if (w->left() == nullptr || w->left()->color() == BLACK) {
                            if (w->right() != nullptr)
                                w->right()->color() = BLACK;
                            w->color() = RED;
                            rotateLeft(w);
                            w = x->parent()->left();
                        }
        
                        w->color() = x->parent()->color();
                        x->parent()->color() = BLACK;
                        if (w->left() != nullptr)
                            w->left()->color() = BLACK;
                        rotateRight(x->parent());
                        x = root_;
                    }
                }
            }
        
            if (x != nullptr)
                x->color() = BLACK;
        }
        

        void transplant(Node *u, Node *v){
            if(u->parent() == nullptr){
                root_ = v;
            } else if(u == u->parent()->left()){
                u->parent()->left() = v;
            } else {
                u->parent()->right() = v;
            }
        
            if(v != nullptr){
                v->parent() = u->parent();
            }
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
                assert(elem != curr->data());
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

        void remove(const Type& elem) {
            if (empty()) return;
        
            Node* z = root_;
        
            // Buscar el nodo z con el valor a eliminar
            while (z != nullptr && z->data() != elem) {
                if (elem < z->data()) {
                    z = z->left();
                } else {
                    z = z->right();
                }
            }

            if (z == nullptr){
                return;
            }

            Node* y = z; 
            bool originalColor = y->color();
            Node* x = nullptr;
        
            if (z->left() == nullptr) {
                x = z->right();
                transplant(z, x);
            } else if (z->right() == nullptr) {
                x = z->left();
                transplant(z, x);
            } else {
                y = z->right();
                while (y->left() != nullptr) {
                    y = y->left();
                }
        
                originalColor = y->color();
                x = y->right();
        
                if (y->parent() == z) {
                    if (x != nullptr)
                        x->parent() = y;
                } else {
                    transplant(y, x);
                    y->right() = z->right();
                    y->right()->parent() = y;
                }
        
                transplant(z, y);
                y->left() = z->left();
                y->left()->parent() = y;
                y->color() = z->color();
            }
        
            size_--;
        
            if(originalColor == BLACK){
                fixDelete(x);
            }
        
            delete z; // Liberamos la memoria del nodo original
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

        bool empty() const {
            return !size();
        }
};

int main(){
    cout << "RBT" << endl;

    return 0;
}