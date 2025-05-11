#include <iostream>
#include <vector>

using namespace std;

int DotProduct(){

    vector<int> a;
    vector<int> b;

    unsigned int n = 0;

    cout << "Ingrese el tamaño de los vectores: ";
    cin >> n;

    a.resize(n); b.resize(n);

    cout << endl;
    int input = 0;
    for(int i = 0; i < n; i++){
        cout << "valor del vector a en la pos " << i << ": ";
        cin >> a[i];
    }
   cout << endl;
    for(int i = 0; i < n; i++){
        cout << "valor del vector b en la pos " << i << ": ";
        cin >> b[i];
    }
   
    cout << endl;
    int result = 0;
    for(int i = 0; i < n; i++){
        result += a[i] * b[i];
    }
   
    return result;

}

int main(){

    int dotProduct = DotProduct();

    cout << "El resultado del producto punto es :" << dotProduct << endl;

    return 0;
}