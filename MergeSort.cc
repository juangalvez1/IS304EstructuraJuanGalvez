#include <iostream>
#include <random>
#include <vector>

using namespace std;

void PrintVector(vector<int> *vector){
    for(int l = 0; l < vector->size(); l++){
        cout << " " << vector->at(l);
    }
    cout << endl;
}

void Merge(vector<int> *list, int left, int rigth, int middle){
    int tamLeftVector = middle - left + 1;
    int tamRigthVector = rigth - middle;

    vector<int> leftVector(tamLeftVector);
    vector<int> rigthVector(tamRigthVector);

    for(int i = 0; i < tamLeftVector; i++){
        leftVector.at(i) = list->at(left + i);
    }

    for(int j = 0; j < tamRigthVector; j++){
        rigthVector.at(j) = list->at(middle + j + 1);
    }

    int l = 0, r = 0;
    int pos = left;

    while (l < tamLeftVector && r < tamRigthVector) {
        if (leftVector.at(l) <= rigthVector.at(r)) {
            list->at(pos) = leftVector.at(l);
            l++;
        } else {
            list->at(pos) = rigthVector.at(r);
            r++;
        }
        pos++;
    }

    while (l < tamLeftVector) {
        list->at(pos) = leftVector.at(l);
        l++;
        pos++;
    }

    while (r < tamRigthVector) {
        list->at(pos) = rigthVector.at(r);
        r++;
        pos++;
    }
}

void MergeSort(vector<int> *vector, int left, int rigth){
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

    int quantity = 0, pivot = 0;
    vector<int> variables;
   
    cout << "cantidad de numeros en el vector: "; cin >> quantity;
   
    for(int l = 0; l < quantity; l++){
        variables.push_back(dist(gen));
    }
    PrintVector(&variables);
    
    MergeSort(&variables, 0, variables.size() - 1);

    PrintVector(&variables);
    return 0;
}