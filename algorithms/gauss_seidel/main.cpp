/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 25, 2014, 10:22 PM
 */

#include <iostream>
using namespace std;

void GaussSeidel(int Iterations, float **EquationHolder, float *EquationResultHolder) {
    int InitialGuess = 0;
    float x1 = 0, x2 = 0, x3 = 0;
    while (InitialGuess < Iterations) {
        x1 = (1 / EquationHolder[0][0])*(EquationResultHolder[0]-((EquationHolder[0][1]) * x2)-((EquationHolder[0][2]) * x3));
        x2 = (1 / EquationHolder[1][1])*(EquationResultHolder[1]-((EquationHolder[1][0]) * x1)-((EquationHolder[1][2]) * x3));
        x3 = (1 / EquationHolder[2][2])*((EquationResultHolder[2]-((EquationHolder[2][0]) * x1)-((EquationHolder[2][1]) * x2)));
        InitialGuess += 1;
        cout << "---------------------Iteration #" << InitialGuess << "---------------------" << std::endl;
        cout << "X1: " << x1 << "\t" << x2 << "\t" << x3 << std::endl;
    }
}

int main() {
    int NumEquations = 3;
    // Equation Holder...
    float ** EquationHolder = new float *[3];
    for (int i = 0; i < NumEquations; i++) {
        EquationHolder[ i] = new float[3];
        cout << "Please Enter The Information Of Equation (" << i + 1 << ")...\n";
        for (int j = 0; j < NumEquations; j++) {
            cout << "X" << j + 1 << ": ";
            cin >> EquationHolder[i][j];
        }
    }

    // Equation Results Holder...
    float *EquationResultHolder = new float [NumEquations];
    for (int i = 0; i < NumEquations; i++) {
        cout << "Please Enter The Result Of Equation (" << i + 1 << ")... ";
        cin >> EquationResultHolder[i];
    }

    // Iterations Required...
    int RequiredIteration;
    cout << "Please Enter The Required Iterations: ";
    cin >> RequiredIteration;
    GaussSeidel(RequiredIteration, EquationHolder, EquationResultHolder);
    
   for (int i = 0; i < NumEquations; i++) {
        delete [] EquationHolder[ i];
    }
    delete [] EquationHolder;
    return 0;
}

