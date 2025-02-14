#include <iostream>
#include <vector>
#include <random>

using namespace std;

void PrintVector(vector<int> *vector){
    for(int l = 0; l < vector->size(); l++){
        cout << " " << vector->at(l);
    }
    cout << endl;
}

void QuickSort(vector<int> *vector, int start, int end, int chose){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(start, end);
    
    int l = 0, r = 0, middle = 0;
    int pivote = 0;

    middle = chose? (start + end) / 2 : dist(gen);
    pivote = vector->at(middle);
    l = start;
    r = end;

    do {
        while (vector->at(l) < pivote) l++;
        while (vector->at(r) > pivote) r--;
        if (l <= r) {
            // double tmp;
            // tmp = vector->at(l);
            // vector->at(l) = vector->at(r);
            // vector->at(r) = tmp;
            swap(vector->at(l), vector->at(r));
            l++;
            r--;
        }
    } while (l <= r);

    if (start < r){
        QuickSort(vector, start, r, chose);
    }
    if (l < end){
        QuickSort(vector, l, end, chose);
    }

    return;
}

int main(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);

    int quantity = 0, pivot = 0;
    vector<int> variables;
   
    cout << "cantidad de numeros en el vector: "; cin >> quantity;
   
    for(int l = 0; l < quantity; l++){
        variables.push_back(dist(gen));
    }
    PrintVector(&variables);

    cout << "Pivote en la mitad o aleatorio (1 en la mitad, 0 aleatorio)"; cin >> pivot;
    
    QuickSort(&variables, 0, variables.size() - 1, pivot);

    PrintVector(&variables);
    return 0;
}