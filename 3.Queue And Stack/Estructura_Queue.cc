#include <iostream>
#include "../1.Vectores/Estructura_Vector.cc"
#include "../2.Listas/Estructura_lista_sencilla.cc"

using namespace std;

template <typename Type>
class Stack {
    private:
        List<Type> storage_;

    public:
        Stack(){}

        void push(const Type& elem) {
            storage_.push_back(elem);
        }

        Type pop() {
            assert(!empty());
            Type elem = storage_.at(storage_.size() - 1);
            storage_.pop_back();
            return elem;
        }

        Type peek(){
            assert(!empty());
            return storage_.at(storage_.size() - 1);
        }

        bool empty(){
            return storage_.empty();
        }
};

template <typename Type>
class Queue {
    private:
        List<Type> storage_;

    public:
        Queue() {}

        void push(const Type& elem) {
            storage_.push_back(elem);
        }

        Type pop() {
            assert(!empty());
            Type elem = storage_.at(0);
            storage_.pop_front();
            return elem;
        }

        Type peek() const {
            assert(!empty());
            return storage_.at(0);
        }

        bool empty() const {
            return storage_.empty();
        }
};


int main(){
    cout << "hola" << endl;

    Stack<int> pila;

    cout << pila.peek() << endl;
}