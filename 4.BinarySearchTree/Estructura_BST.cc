#include <iostream>
#include <cassert>
#include <iomanip>

using namespace std;

template<typename Type>
class BST{
    private:
        class Node{
            private:
                Node* left;
                Node* right;
                Type data;
            public:
                Node(const Type elem = Type()){
                    left = nullptr;
                    right = nullptr;
                    data = elem;
                }

                Node* get_left(){
                    return left;
                }

                Node* get_right(){
                    return right;
                }

                Type& get_data(){
                    return data;
                }

                void change_left(Node* newPtr){
                    left = newPtr;
                }

                void change_right(Node* newPtr){
                    right = newPtr;
                }

                void change_data(Type& elem){
                    data = elem;
                }

                bool leaf(){
                    return (right == nullptr) && (left == nullptr);
                }
                
                void printNode(){
                    cout << "\t" << get_data() << endl;
                    if(leaf()){
                        cout << "null" << "\t\t" << "null" << endl;
                    } else if(left == nullptr){
                        cout << "null" << "\t\t" << right->get_data() << endl;
                    } else if(right == nullptr){
                        cout << left->get_data() << "\t\t" << "null" << endl;
                    } else {
                        cout << left->get_data() << "\t\t" << right->get_data() << endl;
                    }
                }
        };
        
        int levelAux(Node* nodo){
            if(nodo == nullptr) return -1;

            return 1 + max(levelAux(nodo->get_left()), levelAux(nodo->get_right()));
        }

        void imprimirArbol(Node* raiz, int space = 0, int increment = 7) {
            // Caso base
            if (raiz == nullptr) {
                return;
            }
        
            // Aumentar el space entre niveles
            space += increment;
        
            // Imprimir el subárbol derecho primero (más cerca de la parte superior)
            imprimirArbol(raiz->get_right(), space);
        
            // Imprimir el valor del nodo actual con la cantidad de spaces necesarios
            cout << endl;
            cout << setw(space) << raiz->get_data() << endl;
        
            // Imprimir el subárbol izquierdo
            imprimirArbol(raiz->get_left(), space);
        }
        
        // Atributos
        unsigned int size_;
        Node *root_;
    
        public:
        BST(){
            size_ = 0;
            root_ = nullptr;
        }

        void push(const Type& elem){
            Node *newNode = new Node(elem);
            if(root_ == nullptr){
                root_ = newNode;
                size_++;
                return;
            }
            Node *curr = root_, *parent = nullptr;

            while (curr != nullptr) {
                assert(elem != curr->get_data());
                parent = curr;
                if (elem < curr->get_data()) {
                    curr = curr->get_left();
                } else {
                    curr = curr->get_right();
                }
            }
        
            if (elem < parent->get_data()) {
                parent->change_left(newNode);
            } else {
                parent->change_right(newNode);
            }
            size_++;
        }

        bool find(const Type& elem) const {
            if(empty()){
                return 0;
            } else if(size() == 1 && elem == root_->get_data()){
                root_->printNode();
                return 1;
            }

            Node *curr = root_, *parent = nullptr;

            while (curr != nullptr) {
                parent = curr;
                if(elem == curr->get_data()){
                    curr->printNode();
                    return 1;
                } else if (elem < curr->get_data()) {
                    curr = curr->get_left();
                } else {
                    curr = curr->get_right();
                }
            }
            return 0;

        }

        void remove(Type const elem, Node* curr = nullptr, Node* parent = nullptr){
            assert(!empty());

            if(curr == nullptr){
                curr = root_;
            }

            if(elem < curr->get_data()){
                remove(elem, curr->get_left(), curr);
            } else if(elem > curr->get_data()){
                remove(elem, curr->get_right(), curr);
            } else {
                if(curr->leaf()){
                    if (parent == nullptr) {
                        delete root_;
                        root_ = nullptr;
                        size_--;
                    } else if (parent->get_left() == curr) {
                        parent->change_left(nullptr);
                        delete curr;
                        size_--;
                    } else {
                        parent->change_right(nullptr);
                        delete curr;
                        size_--;
                    }

                } else if (curr->get_left() == nullptr || curr->get_right() == nullptr) {
                    Node* child = (curr->get_left() != nullptr) ? curr->get_left() : curr->get_right();
        
                    if (parent == nullptr) {
                        delete root_;
                        root_ = child;
                        size_--;
                    } else if (parent->get_left() == curr) {
                        parent->change_left(child);
                        delete curr;
                        size_--;
                    } else {
                        parent->change_right(child);
                        delete curr;
                        size_--;
                    }

                } else {
                    Node* newNode = curr->get_right();
                    Node* newNodeParent = curr;

                    while(newNode->get_left() != nullptr){
                        newNodeParent = newNode;
                        newNode = newNode->get_left();
                    }

                    curr->change_data(newNode->get_data());

                    remove(newNode->get_data(), curr->get_right(), curr);
                }
            }
        }

        bool empty() const {
            return !size_;
        }

        unsigned int size() const {
            return size_;
        }

        int level(){
            return 1 + levelAux(root_);
        }

        void print(){
            imprimirArbol(root_);
        }
};

int main(){
    cout <<"Binary Search Tree" << endl;

    BST<int> arbol;

    arbol.push(5);
    arbol.push(4);
    arbol.push(6);

    arbol.print();
    cout << arbol.size() << endl;
    cout << arbol.level() << endl;
    arbol.remove(5);
    arbol.print();
    cout << arbol.size() << endl;
    cout << arbol.level() << endl;

    cout << arbol.find(4) << endl;
    cout << arbol.find(5) << endl;
    cout << arbol.find(6) << endl;
}