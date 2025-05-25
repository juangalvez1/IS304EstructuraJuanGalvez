#include <iostream>
#include <vector>
#include <stdexcept> // For invalid_argument
#include <limits>


using namespace std;
typedef vector<vector<double>> Matrix;
const double m = numeric_limits<double>::max();


// Function to perform matrix multiplication
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    
    // Get dimensions of matrices
    if (A.empty() || B.empty() || A[0].empty() || B[0].empty()) {
        throw invalid_argument("Input matrices cannot be empty.");
    }

    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    // Check if multiplication is possible
    // Number of columns in A must be equal to the number of rows in B
    if (colsA != rowsB) {
        throw invalid_argument(
            "Number of columns in the first matrix must be equal to the "
            "number of rows in the second matrix for multiplication.");
    }

    // Initialize the result matrix C with zeros
    // The dimensions of C will be rowsA x colsB
    Matrix C(rowsA, vector<double>(colsB, m));

    // Perform multiplication
    for (int i = 0; i < rowsA; ++i) {        // Iterate over rows of A
        for (int j = 0; j < colsB; ++j) {    // Iterate over columns of B
            double minim = A[i][j];
            for (int k = 0; k < colsA; ++k) { // Iterate over columns of A / rows of B
                // cout << "(" << i << "," << j << ")" << " k: " << k << " a(i,k) " << A[i][k] << " a(k,j) " << B[k][j] << endl;
                minim = min(minim,  (A[i][k] + B[k][j]));
            }
            C[i][j] = i == j ? 0 : minim;
        }
    }
    
    return C;
}

// Function to print a matrix
void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            if(val == m){
                cout << "∞" << "\t";
            } else {
                cout << val << "\t";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}


int main() {
   
    // Example Matrices
    Matrix A = {
        {m, 2, 1, m, 3},
        {m, m, m, 4, m},
        {m, 1, m, m, 1},
        {1, m, 3, m, 5},
        {m, m, m, m, m}
    }; // 2x3 matrix


    cout << "Graph:" << endl;
    printMatrix(A);
    
    Matrix Ai = A;
    for (int i = 1; i < 4; i++) {
        Ai = multiplyMatrices(Ai, A);
        // cout << "\nResult of A :-) " << i << ": " << endl;
        // printMatrix(Ai);
    }

    cout << "A:-):" << endl;
    printMatrix(Ai);

    return 0;
}