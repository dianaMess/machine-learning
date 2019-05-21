#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include"src/matrix.h"
using namespace std;
int main(int argc, char * argv[]) {
    Matrix X(8, 7), Y(8, 1), K(5, 7), Z(5, 1);
    ifstream file(argv[1]);  
    ifstream file1(argv[2]);  
    ifstream file2(argv[3]);  
    ifstream file3(argv[4]);
    double num;
    vector<vector<double>> X1(8, vector<double>(7));
    if (file.is_open()) {
        for (int i = 0; i < 8; i++)
            for(int j = 0; j < 7; j++) {
                if (file.eof())
                    break;
                file>>num;
                X1[i][j] = num;
            }
    }
    X.set(X1);
cout<<X;
    vector<vector<double>> Y1(8, vector<double>(1));
    if (file1.is_open()) {
        for (int i = 0; i < 8; i++)
            for(int j = 0; j < 1; j++) {
                if (file1.eof())
                    break;
                file1>>num;
                Y1[i][j] = num;
            }
    }

    Y.set(Y1);
cout<<Y;
    vector<vector<double>> K1(5, vector<double>(7));
    if (file2.is_open()) {
        for (int i = 0; i < 5; i++)
            for(int j = 0; j < 7; j++) {
                 if (file2.eof())
                    break;
                file2>>num;
                K1[i][j] = num;
            }
    }         
    K.set(K1);
cout<<K;
    Neuron model(X, Y);
    Matrix A = model.train(X, Y);
    cout<<A;
    Matrix B = A * K.transpose();
    cout<<endl<<"answer: "<<endl;
    cout<<B;
    cout<<endl<<"right answer: "<<endl;
    vector<vector<double>> Z1(5, vector<double>(1));
    if (file3.is_open()) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 1; j++) {
                if (file3.eof())
                   break;
                file3>>num;
                Z1[i][j] = num;
            }
        }
    }       
    Z.set(Z1); 
    cout<<Z; 
    return 0;
}
    
