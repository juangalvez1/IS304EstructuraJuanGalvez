#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool>> Matrix;

Matrix Identity(unsigned int size){
    Matrix I(size, vector<bool>(size, 0));

    for(int i = 0; i < size; i++){
        I[i][i] = 1;
    }

    return I;
}

Matrix OR(Matrix& A, Matrix& B){
    unsigned int size = A.size();
    Matrix R(size, vector<bool>(size));

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            R[i][j] = A[i][j] || B[i][j];
        }
    }

    return R;
}

Matrix AND(Matrix& A, Matrix& B){
    unsigned int size = A.size();
    Matrix R(size, vector<bool>(size));

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            R[i][j] = A[i][j] && B[i][j];
        }
    }

    return R;
}

Matrix multiplyMatrix(Matrix& A, Matrix& B){
    unsigned int size = A.size();
    Matrix R(size, vector<bool>(size));

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){
                R[i][j] = R[i][j] || (A[i][k] && B[k][j]);
            }
        }
    }

    return R;
}



void print_matrix(const Matrix &M, const string &name) {
    cout << "\nMatriz " << name << ":\n";
    for (const auto& row : M) {
        for (bool val : row)
        cout << val << " ";
    cout << endl;
}
}
Matrix calculateReachavility(Matrix& A){
    unsigned int size = A.size();
    Matrix C = Identity(size);
    Matrix aux = A;

    for(int i = 0; i < size; i++){
        C = OR(C, aux);
        print_matrix(C, "Ai");
        aux = multiplyMatrix(aux, A);
    }

    return C;
}

int main(){
    Matrix A = {
        {1, 0, 0},
        {0, 1, 1},
        {1, 1, 0}
    };

    Matrix C = calculateReachavility(A);

    print_matrix(C, "C");

    return 0;
}