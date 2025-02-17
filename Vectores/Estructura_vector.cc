#include <iostream>

using namespace std;

class Vector{
    private: // ATRIBUTOS
        int *storage_;
        // Puntero al arreglo que manejaremos como vector
        long capacity_;
        // Capacidad total actual del vector
        long size_;
        // Tamaño actual del vector
    
    public: // CONSTRUCTORES
        Vector(){
            capacity_ = 5; //Capacidad incial del vector
            storage_ = new int[capacity_];
            // new: reserva una posicion de memoria y devuelve su direccion

            size_ = 0; // cantidad de datos iniciales del vector
        }
        Vector(int tam){
            capacity_ = tam; //Capacidad incial del vector
            storage_ = new int[capacity_];
            // new: reserva una posicion de memoria y devuelve su direccion
    
            size_ = 0; // cantidad de datos iniciales del vector
        }
    
    private: // METODOS PRIVADOS
        void resize(){
            capacity_ += 5; // Aumentamos la nueva capacidad del vector
            int *storage_2 = new int[capacity_]; // Creamos un arreglo con la nueva capacidad

            for(int i = 0; i < size_; i++){
                storage_2[i] = storage_[i]; // Copiamos los datos del arreglo de menor al de mayor capacidad
            }

            delete [] storage_; // Liberamos la memoria que ocupaba el vector anterior
            storage_ = storage_2; // Copiamos en el puntero originial la dir del nuevo arreglo mas grande            
        }

    public: // METODOS PUBLICOS
        void push_back(int num){
            if(size_ == capacity_){
                resize();
            }
            storage_[size_] = num; // Ingresa un elemento al vector, por la cola
            size_ ++; // Aumenta la cantidad de elementos en el vector
        }      long size(){
            return size_;
        }
};

int main(){
    cout << "Hello" << endl;

    return 0;
}