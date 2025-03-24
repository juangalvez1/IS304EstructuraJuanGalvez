#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <chrono>
#include <fstream>

using namespace std;

template <typename Type>
void Merge(vector<Type> *Vector, int left, int rigth, int middle) {
    int tamLeftVector = middle - left + 1;
    int tamRigthVector = rigth - middle;

    vector<Type> leftVector(tamLeftVector);
    vector<Type> rigthVector(tamRigthVector);

    for(int i = 0; i < tamLeftVector; i++) {
        leftVector[i] = Vector->at(left + i);
    }

    for(int j = 0; j < tamRigthVector; j++) {
        rigthVector[j] = Vector->at(middle + j + 1);
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

    vector<Type>().swap(leftVector);
    vector<Type>().swap(rigthVector);
}

template <typename Type>
void MergeSort(vector<Type> *vector, int left, int rigth){
    if (left < rigth) {
        int middle = left + ((rigth - left) / 2);

        MergeSort(vector, left, middle);

        MergeSort(vector, middle + 1, rigth);

        Merge(vector, left, rigth, middle);
    }
}

int main(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);
   
    int quantity = 0;
    vector<unsigned int> variables;    

    ofstream tiempos("tiemposMerge.dat", ios::app);
    if (!tiempos){
      cout << "Error al abrir tiemposMerge.dat\n";
      exit(EXIT_FAILURE);
    }
    
    auto start = chrono::high_resolution_clock::now();

    for(int pot = 1; pot <= 9; pot++){
        quantity = pow(10, pot);
        variables.reserve(quantity);
        tiempos << endl << endl << "Potencia " << pot << endl;
        for (int times = 1; times <= 10; times++){
            variables.clear();
            auto start = chrono::high_resolution_clock::now();
            for(int l = 0; l < quantity; l++){
                variables.push_back(dist(gen));
            }
            auto end = chrono::high_resolution_clock::now();
            auto duracion1 = chrono::duration_cast<chrono::nanoseconds>(end - start);
            cout << times << ".\t" << "Potencia " << pot << "\t" << duracion1.count() << endl;

            auto inicio = chrono::high_resolution_clock::now();

            MergeSort(&variables, 0, variables.size() - 1);

            auto fin = chrono::high_resolution_clock::now();
        
            auto duracion = chrono::duration_cast<chrono::nanoseconds>(fin - inicio);
        
            tiempos << times << ".\t" << duracion.count() << endl;
        }
        cout << endl;
    }

    auto end = chrono::high_resolution_clock::now();

    auto totalDutacion = chrono::duration_cast<chrono::milliseconds>(end - start);

    tiempos << endl << "Duracion total en milisegundos: " << totalDutacion.count() << endl;



    return 0;
}