#include <iostream>

using namespace std;

void PrintVector(double *vector){
    for(int i = 0; i < 9; i++){
        cout << " " << vector[i];
    }
    cout << endl;
}

void quicksort(double a[], int primero, int ultimo){
    int i, j, central;
    double pivote;
    central = (primero + ultimo)/2;
    pivote = a[central];
    i = primero;
    j = ultimo;
    do {
    while (a[i] < pivote) i++;
    while (a[j] > pivote) j--;
    if (i<=j) {
        double tmp;
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp; /* intercambia a[i] con a[j] */
        i++;
        j--;
    }
    }while (i <= j);
    if (primero < j)
        quicksort(a, primero, j);/* mismo proceso con sublista izqda */
    if (i < ultimo)
        quicksort(a, i, ultimo); /* mismo proceso con sublista drcha */
}

int main(){

    double vector[9] = {1.6, 2.6, 9.8, 5.6, 4.5, 9.4, 8.2, 3.2, 2.3};

    PrintVector(vector);
    quicksort(vector, 0, 8);
    PrintVector(vector);

    return 0;
}