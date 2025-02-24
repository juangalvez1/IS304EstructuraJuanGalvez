#include <iostream>
#include <cassert>

using namespace std;

template <typename Type>   // Se incluye para manejar a Type como el tipo de dato que va a usar el vector en sus elementos
                        // Y poder hacer que los vectores manejen cualquier tipo de dato
class Vector{
    private: // ATRIBUTOS
        Type *storage_;
        // Puntero al arreglo que manejaremos como vector
        unsigned int capacity_;
        // Capacidad total actual del vector
        unsigned int size_;
        // Tamaño actual del vector
    
    public: // CONSTRUCTORES
        Vector(){
            capacity_ = 5; //Capacidad incial del vector
            storage_ = new Type[capacity_];
            // new: reserva una posicion de memoria y devuelve su direccion
            size_ = 0; // cantidad de datos iniciales del vector
        }
        
		Vector(unsigned int tam, Type elem = Type()){
		    // Type elem = Type() - quiere decir que el elemento con el que vamos a llenar el vector es del mismo tipo que el vector
		    // Se llama el constructor de la clase del tipo de dato de type
            capacity_ = tam; //Capacidad incial del vector
            storage_ = new Type[capacity_];
    		for(unsigned int i = 0; i < capacity_; i++){
				storage_[i] = elem;
			}
            size_ = capacity_; // cantidad de datos iniciales del vector
        }
    
    private: // METODOS PRIVADOS
        void resize(){
            if(size_ == capacity_){
                // capacity_ += 1;     // Aumentamos la nueva capacidad del vector: politica de Brahian
                // capacity_ += 2;     // Aumentamos la nueva capacidad del vector: politica de 
                capacity_ *= 1.5;   // Aumentamos la nueva capacidad del vector: politica de Carlos
                // capacity_ *= 1.7;   // Aumentamos la nueva capacidad del vector: politica de 
                // capacity_ *= 2;     // Aumentamos la nueva capacidad del vector: politica de Martin
            }
            Type *storage_2 = new Type[capacity_]; // Creamos un arreglo con la nueva capacidad

            for(unsigned int i = 0; i < size_; i++){
                storage_2[i] = storage_[i]; // Copiamos los datos del arreglo de menor al de mayor capacidad
            }

            delete [] storage_; // Liberamos la memoria que ocupaba el vector anterior
            storage_ = storage_2; // Copiamos en el puntero originial la dir del nuevo arreglo mas grande            
        }

    public: // METODOS PUBLICOS
        const Type& operator[](unsigned int pos) const { // El const despues de los () sirve para decir que la operacion no cambiara ninguno de los atributos de la class
            return storage_[pos];
        }
        
        Type& at(const unsigned int pos) const { // UNFINISHED
            assert(pos >= 0 && pos < size_); // de la libreria <cassert>, recibe una expresion booleana
            return storage_[pos];
        }
        
        unsigned int size() const {
            return size_;
        }
        
        void print(){
            for(unsigned int i = 0; i < size(); i++) // Usamos el metodo size() dentro de la misma class
                cout << storage_[i] << " ";
            cout << endl;
        }
        
        void push_back(const Type &elem){
            if(size_ == capacity_){
                resize();
            }
            storage_[size_] = elem; // Ingresa un elemento al vector, por la cola
            size_ ++; // Aumenta la cantidad de elementos en el vector
        }
        
        void pop_back(){
            size_--; // Le quitamos uno a la variable que usamos como indice porque queremos dejar de usar el ultimo elemento como parte del vector
        }

        void push_front(const Type& elem){
            if(size_ == capacity_){
                resize(); // Si necesiamos mas espacio para guardar todos los elementos del vector aumentamos el tamaño del arreglo
            }
            for(int i = size_; i > 0; --i){
                storage_[i] = storage_[i - 1]; // Movemos todos los elementos del vector uno a la der
            }
            storage_[0] = elem; // Insertamos el elemento deseado al principio
            size_++; // Aumentamos la cantidad de datos del vector
        }
        
        void pop_front(){
            for(int i = 0; i < size_ - 1; ++i){
                storage_[i] = storage_[i + 1]; // Movemos todos los elementos del vector uno hacia atras
            }
            size_--;
        }
        
        int waste() const {
            return capacity_ - size_;
        }
};

class Complex{
    private:
        double real;
        double img;
    public:
        Complex(){
            // cout << "complex default constructor 1234567890" << endl;
            real = 5.;
            img = 10.;
        }
        
        friend ostream& operator<<(ostream& os, const Complex& c) { // Funcion amiga que ayduda a imprimir un tipo de dato complejo directamente en un cout
            os << "(" << c.real << ", " << c.img << "i)";
            return os;
        }
};

int main(){
    cout << "Vector" << endl;
    Vector<int> x(10, 55);
    Vector<Complex> z(5);
    
    x.print();
    // z.print();   // Si se descomenta saldra un error, ya que no se puede imprimir directamente una clase como Complex con cout.
                    // Para eso se usa la funcion de tipo friend en public de Complex.
    // Complex a;
    // cout << a << endl; // Sigue funcionando para variables de tipo Complex pero no solo para un vector de ese tipo.
    
    x.push_front(50);
    x.print();
    x.pop_front();
    x.print();
    cout << x.waste() << endl;

    return 0;
}
