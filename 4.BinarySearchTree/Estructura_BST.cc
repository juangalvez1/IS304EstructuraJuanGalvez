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

                bool leaf(){
                    return (right == nullptr) && (left == nullptr);
                }
                
                void print(){
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
        // Atributos
        unsigned int size_;
        Node *root_;

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
            Node *tempNode = root_, *parent = nullptr;

            while (tempNode != nullptr) {
                assert(elem != tempNode->get_data());
                parent = tempNode;
                if (elem < tempNode->get_data()) {
                    tempNode = tempNode->get_left();
                } else {
                    tempNode = tempNode->get_right();
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
                return root_;
            }

            Node *tempNode = root_, *parent = nullptr;

            while (tempNode != nullptr) {
                parent = tempNode;
                if(elem == tempNode->get_data()){
                    tempNode->print();
                    return 1;
                } else if (elem < tempNode->get_data()) {
                    tempNode = tempNode->get_left();
                } else {
                    tempNode = tempNode->get_right();
                }
            }
            return 0;

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
    arbol.push(6);
    arbol.push(4);

    cout << arbol.size() << endl;
    // cout << arbol.find(4) << endl;
    // cout << arbol.find(5) << endl;
    // cout << arbol.find(6) << endl;
    arbol.print();
    cout << arbol.level() << endl;
    
}
