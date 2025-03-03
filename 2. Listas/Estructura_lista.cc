#include <iostream>
#include <cassert>

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

                void set_next(Node *newNext){    // Metodo para modificar la variable que apunta al siguiente nodo en la lista
                    next_ = newNext;        
                }

                Type& get_data(){
                    return data_;
                }

                Node* get_next(){
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
            if(last_){
                last_->set_next(newNode);    // Hacemos que el nodo al que apunta last_ en su parametro next apunte al nuevo nodo  
            } else {
                first_ = newNode;           // Si la lista esta vacia entonces que first_ tambien apunte al nodo recien ingresado
            }
            last_ = newNode;                // Ahora el puntero last_ apuntara al nuevo nodo
            size_++;                        // Aumentamos el size_ de la lista
        }

        void pop_back(){
            if(empty()){
                return;
            } else if(size_ == 1){
                delete first_;
                first_ = last_ = nullptr;           // Se le asigna a ambos punteros 'nullptr'
            } else {
                Node* p = first_;                   // Creamos dos punteros temporales, uno recorre la lista el otro se usa despues
                for(int i = 0; p->get_next() != last_; i++){ // for para llegar al penultimo elemento de la lista
                    p = p->get_next();
                }
                delete last_;                       // Liberamos la memoria del ultimo nodo
                last_ = p;                          // Ahora last_ apunta a este penultimo nodo de la lista
                last_->set_next(nullptr);           // Seteamos el next del penultimo nodo a nullptr ya que es el ultimo
            }
            size_--;                                // Disminuimos la cantidad de elementos de la lista
        }
        
        void push_front(const Type& elem){
            Node *newNode = new Node(elem); // Creamos un nuevo nodo para almacenar el valor que quiera el usuario
            if(empty()){
                last_ = newNode;            // Si la lista exta vacia entonces que last_ apunte al nodo recien ingresado
            }
            newNode->set_next(first_);      // Hacemos que el nuevo nodo apunte al que apunta first ya que ese se volvera el segundo nodo
            first_ = newNode;               // Ahora first_ apuntara a el nuevo nodo;
            size_++;                        // Aumentamos el size_ de la lista
        }
        
        void pop_front(){
            if(empty()){
                return;
            }
            Node *temp = first_;            // Creamos un puntero temporal que almacena la direccion a la que apunta first_
            first_ = first_->get_next();    // Ahora el primer elemento de la lista sera el que tenia first en next, para eso es la temporal
            delete temp;                    // Liberamos la memoria a la que apuntaba first_
            size_--;                        // Disminuimos la cantidad de elementos de la lista
            
            if(empty()){
                last_ = nullptr;
            }
        }

        int find(Type& elem){
            assert(size_ != 0);
            Node *p = first_;
            unsigned int position = 0;
            while (p->get_next() != nullptr){
                if(p->get_data() == elem){
                    return position;        // En caso de que no se encuentre el elemento
                }
                p = p->get_next();
                position++;
            }

            return -1;
        }

        Type& at(unsigned int position){
            assert(position < size_);
            Node *p = first_;
            for(int i = 0; i < position; i++){
                p = p->get_next();
            }
            return p->get_data();
        }

        unsigned int size() const{
            return size_;
        }

        bool empty(){
            return !size_;  // Si size = 0 entonces devovlera true. Si size != 0  entonces devolvera false
        }

        void print(){
            if(empty()){
                cout << "Vacia" << endl;
                return;
            }

            Node* p = first_;  
            while (p){
                cout << p->get_data() << " ";
                p = p->get_next();
            }
            cout << endl;
        }
};

int main() {
    cout << "Listas" << endl;
    List<int> lista;
    int variable = 1;
    lista.push_back(20);
    lista.push_front(10);
    lista.push_back(30);

    cout << lista.at(0) << endl;
    cout << lista.at(1) << endl;
    cout << lista.at(2) << endl;
    
    cout << lista.find(variable) << endl;

    lista.print();
    
    lista.pop_back();
    
    lista.print();

    lista.pop_front();

    lista.print();

    cout << lista.empty() << endl;

    return 0;
}