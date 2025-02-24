#include <iostream>

using namespace std;

template <typename Type>

class List {
    private:
        class Node {  // Los elementos de la lista seran objetos "Node", ya que necesitamos el elemento que vamos a guardar y la dir del siguiente
            private:
                Type data_;
                Node *next_;
            public:
                Node(){
                    data_ = Type();     // Inicializar data_ con el constructor por defecto del tipo de dato que se use en la lista
                    next_ = nullptr;
                }

                Node(const Type& elem){
                    data_ = elem;
                    next_ = nullptr;
                }

                void setNext(Node *newNext){    // Metodo para modificar la variable que apunta al siguiente nodo en la lista
                    next_ = newNext;        
                }

                Node* getNext(){
                    return next_;
                }
        };
    private:
        Node *first_;       // Puntero al primer nodo de la lista
        Node *last_;        // Puntero al ultimo elemento de la lista
        unsigned int size_; // Cantidad de elementos en la lista
    public:
        List(){
            first_ = nullptr;
            last_= nullptr;
            size_ = 0;
        }

        void push_back(const Type& elem){
            Node *newNode = new Node(elem); // Creamos un nuevo nodo para almacenar el valor que quiera el usuario
            last_->setNext(newNode);        // Hacemos que el nodo al que apunta last_ en su parametro next apunte al nuevo nodo
            last_ = newNode;                // Ahora el puntero last_ apuntara al nuevo nodo
            if(!empty()){
                first_ = newNode;           // Si la lista esta vacia entonces que first_ tambien apunte al nodo recien ingresado
            }
            size_++;                        // Aumentamos el size_ de la lista
        }

        void pop_back(){
            Node* p = first_, temp = nullptr;   // Creamos dos punteros temporales, uno recorre la lista el otro se usa despues
            for(int i = 0; i < size_ - 1; i++){ // for para lelgar al penultimo elemento de la lista
                p = p->getNext();
            }
            temp = p;                           // Copiamos la dir del penultimo elemento que esta en p y la guardamos en temp
            delete [] p;                        // Liberamos la memoria del penultimo nodo
            temp->setNext(nullptr);             // Seteamos el next del penultimo nodo a nullptr ya que es el ultimo
            last_ = temp;                       // Ahora last_ apunta a este penultimo nodo de la lista
            size_--;                            // Disminuimos la cantidad de elementos de la lista
        }
        
        void push_front(const Type& elem){
            Node *newNode = new Node(elem); // Creamos un nuevo nodo para almacenar el valor que quiera el usuario
            newNode->setNext(first_);       // Hacemos que el nuevo nodo apunte al que apunta first ya que ese se volvera el segundo nodo
            first_ = newNode;               // Ahora first_ apuntara a el nuevo nodo;
            if(empty()){
                last_ = newNode;            // Si la lista exta vacia entonces que last_ apunte al nodo recien ingresado
            }
            size_++;                        // Aumentamos el size_ de la lista
        }
        
        void pop_front(){
            Node *temp = first_;            // Creamos un puntero temporal que almacena la direccion a la que apunta first_
            delete [] first_;               // Liberamos la memoria a la que apuntaba first_
            first_ = temp->next;            // Ahora el primer elemento de la lista sera el que tenia first en next, para eso es la temporal
            size_--;                        // Disminuimos la cantidad de elementos de la lista
        }

        unsigned int size() const{
            return size_;
        }

        bool empty(){
            return !size_;  // Si size = 0 entonces devovlera true. Si size != 0  entonces devolvera false
        }
};

int main(){

    cout << "Listas" << endl;

    return 0;
}