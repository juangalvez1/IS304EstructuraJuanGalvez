#include <iostream>
#include <cassert>

using namespace std;

template <typename Type>   // Se incluye para manejar a Type como el tipo de dato que va a usar el Vector en sus elementos
                        // Y poder hacer que los vectores manejen cualquier tipo de dato
class Vector {
    private: // ATRIBUTOS
        Type *storage_;
        // Puntero al arreglo que manejaremos como Vector
        unsigned int capacity_;
        // Capacidad total actual del Vector
        unsigned int size_;
        // Tamaño actual del Vector
    
    public: // CONSTRUCTORES
        Vector(){
            capacity_ = 5; //Capacidad incial del Vector
            storage_ = new Type[capacity_];
            // new: reserva una posicion de memoria y devuelve su direccion
            size_ = 0; // cantidad de datos iniciales del Vector
        }
        
		Vector(unsigned int tam, Type elem = Type()){
		    // Type elem = Type() - quiere decir que el elemento con el que vamos a llenar el Vector es del mismo tipo que el Vector
		    // Se llama el constructor de la clase del tipo de dato de type
            capacity_ = tam; //Capacidad incial del Vector
            storage_ = new Type[capacity_];
    		for(unsigned int i = 0; i < capacity_; i++){
				storage_[i] = elem;
			}
            size_ = capacity_; // cantidad de datos iniciales del Vector
        }

        Vector(initializer_list<Type> list){
            capacity_ = list.size();  // La capacidad es el número de elementos en la lista
            storage_ = new Type[capacity_];
            size_ = list.size();
            unsigned int i = 0;
            for (const Type& elem : list) {
                storage_[i] = elem;  // Copiamos cada elemento al array
                i++;
            }
        }
    
    private: // METODOS PRIVADOS
        void resize(){
            if(size_ == capacity_){
                // capacity_ += 1;     // Aumentamos la nueva capacidad del Vector: politica de Brahian
                // capacity_ += 2;     // Aumentamos la nueva capacidad del Vector: politica de 
                capacity_ *= 1.5;   // Aumentamos la nueva capacidad del Vector: politica de Carlos
                // capacity_ *= 1.7;   // Aumentamos la nueva capacidad del Vector: politica de 
                // capacity_ *= 2;     // Aumentamos la nueva capacidad del Vector: politica de Martin
            }
            Type *storage_2 = new Type[capacity_]; // Creamos un arreglo con la nueva capacidad

            for(unsigned int i = 0; i < size_; i++){
                storage_2[i] = storage_[i]; // Copiamos los datos del arreglo de menor al de mayor capacidad
            }

            delete [] storage_; // Liberamos la memoria que ocupaba el Vector anterior
            storage_ = storage_2; // Copiamos en el puntero originial la dir del nuevo arreglo mas grande            
        }

    public: // METODOS PUBLICOS
        const Type& operator[](unsigned int pos) const { // El const despues de los () sirve para decir que la operacion no cambiara ninguno de los atributos de la class
            assert(pos >= 0 && pos < size_); // de la libreria <cassert>, recibe una expresion booleana
            return storage_[pos];
        }
        
        Type& at(const unsigned int pos) const { // UNFINISHED
            assert(pos >= 0 && pos < size_); // de la libreria <cassert>, recibe una expresion booleana
            return storage_[pos];
        }
        
        unsigned int size() const {
            return size_;
        }

        unsigned int capacity() const {
            return capacity_;
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
            storage_[size_] = elem; // Ingresa un elemento al Vector, por la cola
            size_ ++; // Aumenta la cantidad de elementos en el Vector
        }
        
        void pop_back(){
            assert(size_);
            size_--; // Le quitamos uno a la variable que usamos como indice porque queremos dejar de usar el ultimo elemento como parte del Vector
        }
        
        void push_front(const Type& elem){
            if(size_ == capacity_){
                resize(); // Si necesiamos mas espacio para guardar todos los elementos del Vector aumentamos el tamaño del arreglo
            }
            for(int i = size_; i > 0; --i){
                storage_[i] = storage_[i - 1]; // Movemos todos los elementos del Vector uno a la der
            }
            storage_[0] = elem; // Insertamos el elemento deseado al principio
            size_++; // Aumentamos la cantidad de datos del Vector
        }
        
        void pop_front(){
            assert(size_);
            for(int i = 0; i < size_ - 1; ++i){
                storage_[i] = storage_[i + 1]; // Movemos todos los elementos del Vector uno hacia atras
            }
            size_--;
        }

        void insert(const Type& elem, const unsigned int pos){
            assert(pos < size_);
            if(size_ == capacity_){
                resize();
            }
            
            for(unsigned int i = size_; i > pos; i--){
                storage_[i] = storage_[i - 1];
            }
            
            storage_[pos] = elem;
            size_++;
        }
        
        void erase(const unsigned int pos){
            cout << pos << endl;
            assert(pos < size_);
            for (unsigned int i = pos; i < size_; i++) {
                storage_[i] = storage_[i + 1];
            }
            size_--;
        }
        
        int waste() const {
            return capacity_ - size_;
        }

        bool empty(){
            return !size_;
        }
};

template <typename Type>
class Stack{
    private:
        unsigned int top;
        Vector<Type> storage_; 

    public:
        Stack(const Type elem = Type()){
            top = 0;
            storage_.push_back(elem); 
        }

        void push(const Type elem){
            top++;
            storage_.push_back(elem);

        }

        Type pop(){
            assert(top > 0);
            Type elem = storage_[top];
            storage_.pop_back();
            top--;
            return elem; 
        }
        
         Type peek(){
          return storage_.at(top);
        }
        
        bool empty(){
          return storage_ == 0;
        }
};

template <typename Type>
void Merge(Vector<Type> *Vector, int left, int rigth, int middle) {
    int tamLeftVector = middle - left + 1;
    int tamRigthVector = rigth - middle;

    ::Vector<Type> leftVector(tamLeftVector);
    ::Vector<Type> rigthVector(tamRigthVector);

    for(int i = 0; i < tamLeftVector; i++) {
        leftVector.at(i) = Vector->at(left + i);
    }

    for(int j = 0; j < tamRigthVector; j++) {
        rigthVector.at(j) = Vector->at(middle + j + 1);
    }

    int l = 0, r = 0;
    int pos = left;

    while (l < tamLeftVector && r < tamRigthVector) {
        if (leftVector[l] <= rigthVector[r]) {
            Vector->at(pos) = leftVector[l];
            l++;
        } else {
            Vector->at(pos) = rigthVector[r];
            r++;
        }
        pos++;
    }

    while (l < tamLeftVector) {
        Vector->at(pos) = leftVector[l];
        l++;
        pos++;
    }

    while (r < tamRigthVector) {
        Vector->at(pos) = rigthVector[r];
        r++;
        pos++;
    }

    // ::Vector<Type>().swap(leftVector);
    // ::Vector<Type>().swap(rigthVector);
}

template <typename Type>
void MergeSort(Vector<Type> *Vector, int left, int rigth){
    if (left < rigth) {
        int middle = left + ((rigth - left) / 2);

        MergeSort(Vector, left, middle);

        MergeSort(Vector, middle + 1, rigth);

        Merge(Vector, left, rigth, middle);
    }
}

template <typename Type>
Vector<Type> removeDuplicates(Vector<Type>& vector){
    if(!vector.size()){
        return vector;
    }
    
    ::Vector<Type> newVector;
    
    for (unsigned int i = 0; i < vector.size(); i++) {
        bool flag = true;
        
        for(unsigned int j = 0; j < newVector.size(); j++){
            if(vector[i] == newVector[j]){
                flag = false;
                break;
            }
        }
        
        if(flag){
            newVector.push_back(vector[i]);
        }
    }
    return newVector;
}

template <typename Type>
Vector<Type> mergeSortedVectors(Vector<Type>& vector1, Vector<Type>& vector2){
    unsigned int size1 = vector1.size(), size2 = vector2.size();
    if(!size1){
        return vector2;
    } else if (!size2) {
        return vector1;
    } else if (!size1 && !size2) {
        return Vector<Type>();
    }

    Vector<Type> newVector;

    unsigned int i = 0, j = 0;

    for(; i < size1 || j < size2;){
        if(i < size1){
            newVector.push_back(vector1[i]);
            i++;
        } else if (j < size2){
            newVector.push_back(vector2[j]);
            j++;
        }
    }

    MergeSort(&newVector, 0, newVector.size() - 1);

    return newVector;
}

int main(){
    // cout << "Vector" << endl;
    // Vector<int> x;  
    // x.print();
    // // z.print();   // Si se descomenta saldra un error, ya que no se puede imprimir directamente una clase como Complex con cout.
    //                 // Para eso se usa la funcion de tipo friend en public de Complex.
    // // Complex a;
    // // cout << a << endl; // Sigue funcionando para variables de tipo Complex pero no solo para un Vector de ese tipo.
    // for(int i = 0; i < 10; i++){
    //     x.push_back(i * 10);
    // }

    /* prueba de class Vector en general
    Vector<int> myVector;

    // Test push_back
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);

    cout << myVector.size() << endl; // Expected: 3
    cout << myVector.capacity() << endl; // Expected: Initial capacity, e.g., 4 or 8

    // Test pop_back
    myVector.pop_back();
    cout << myVector.size() << endl; // Expected: 2

    // Test at with valid and invalid indices
    cout << myVector.at(0) << endl; // Expected: 10
    cout << myVector.at(1) << endl; // Expected: 20

    // Border case: Accessing an out-of-bounds index
    cout << myVector.at(2) << endl; // Should crash!

    // Border case: pop_back on empty Vector
    Vector<int> emptyVector;
    emptyVector.pop_back(); // should crash!
    */

    /* prueba de removeDuplicates
    Vector<int> numbers = {1, 2, 2, 3, 4, 4, 5};
    Vector<int> uniqueNumbers = removeDuplicates(numbers);

    uniqueNumbers.print(); // Expected: {1, 2, 3, 4, 5}

    Vector<int> numbers2 = {1,1,1,1,1,1};
    Vector<int> uniqueNumbers2 = removeDuplicates(numbers2);
    uniqueNumbers2.print(); // Expected: {1}

    Vector<int> numbers3 = {};
    Vector<int> uniqueNumbers3 = removeDuplicates(numbers3);
    uniqueNumbers3.print(); // Expected: {}

    Vector<int> numbers4 = {1};
    Vector<int> uniqueNumbers4 = removeDuplicates(numbers4);
    uniqueNumbers4.print(); // Expected: {1}
    */

    /* prueba de mergeSortVectors
    Vector<int> vector1 = {1, 3, 5};
    Vector<int> vector2 = {2, 4, 6};
    Vector<int> mergedVector = mergeSortedVectors(vector1, vector2);
    
    mergedVector.print(); // Expected: {1, 2, 3, 4, 5, 6}
    
    Vector<int> vector3 = {1, 2, 3};
    Vector<int> vector4 = {};
    Vector<int> mergedVector2 = mergeSortedVectors(vector3, vector4);
    mergedVector2.print(); // Expected: {1, 2, 3}
    
    Vector<int> vector5 = {};
    Vector<int> vector6 = {4,5,6};
    Vector<int> mergedVector3 = mergeSortedVectors(vector5, vector6);
    mergedVector3.print(); // Expected: {4, 5, 6}
    
    Vector<int> vector7 = {1,1,1,1};
    Vector<int> vector8 = {1,1,1,1};
    Vector<int> mergedVector4 = mergeSortedVectors(vector7, vector8);
    mergedVector4.print(); // Expected: {1,1,1,1,1,1,1,1}

    Vector<int> vector9 = {1, 1, 2, 4, 20, 9, 3, 5};
    Vector<int> vector10 = {2, 4, 6, 10, 2};
    Vector<int> mergedVector5 = mergeSortedVectors(vector9, vector10);
    mergedVector5.print(); // Expected: {1, 1, 2, 2, 2, 3, 4, 4, 5, 6, 9, 10, 20}
    */

    Stack<int> pila;

    cout << pila.peek() << endl;
    pila.push(20);
    cout << pila.peek() << endl;
    pila.pop();
    cout << pila.peek() << endl;
    pila.push(30);
    cout << pila.peek() << endl;
    cout << pila.peek() << endl;

    return 0;
}
