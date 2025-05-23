#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool>> Matrix;

Matrix transpose(Matrix& A){
    int size = A.size();

    Matrix aux(size, vector<bool> (size, 0));

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            aux[j][i] = A[i][j];
        }
    }

    return aux;
}

vector<bool> multiplyMatrixVector(Matrix& A, vector<bool>& v){
    int size = A[0].size();
    vector<bool> aux(v.size());

    for(int i = 0; i < v.size(); i++){
        bool sum = 0;
        for(int j = 0; j < size; j++){
            sum = sum || (A[i][j] && v[j]);
        }
        aux[i] = sum;
    }

    return aux;
}

void printVector(const vector<bool>& v) {
    for (bool val : v) {
        cout << val << " ";
    }
    cout << endl;
}

void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (bool val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    Matrix A = {
        {1, 0, 0},
        {0, 1, 1},
        {1, 1, 0}
    };

    // Transponer matriz
    Matrix T = transpose(A);

    // Vector de entrada (por ejemplo: activamos nodo 0)
    vector<bool> node0 = {1, 0, 1};

    // Multiplicamos matriz transpuesta por el vector
    vector<bool> connectionsNode0 = multiplyMatrixVector(T, node0);

    cout << "Matriz original:\n";
    printMatrix(A);

    cout << "\nMatriz transpuesta:\n";
    printMatrix(T);

    cout << "\nConexiones que apuntan a nodo 0:\n";
    printVector(connectionsNode0);

    return 0;
}