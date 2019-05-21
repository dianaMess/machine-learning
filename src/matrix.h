#ifndef __MATRIX_H__
#define __MATRIX_H__
#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
using namespace std;

class Matrix {
    int row, col;
    vector <vector <double> > data;
public:
    Matrix (int row = 1, int col = 1): row(row), col(col),
           data(vector <vector <double > > (row, vector<double> (col, 0.5))) {}
    void set(vector <vector <double > > vec);
    int getRow();
    int getCol();
    Matrix operator+(const Matrix & mx);
    Matrix operator-(const Matrix & mx); 
    Matrix operator-(vector<double> vc);
    Matrix operator=(const Matrix & mx);
    Matrix operator=(std::vector<double> vc);
   std::vector< double > operator[] (int i);
    Matrix operator*(const Matrix & mx);
    Matrix operator*(vector<double> vc);
    Matrix operator*(double num);
    Matrix operator/(double num);
    Matrix transpose();
    friend std::istream& operator>>(istream &in, Matrix& mx) {
        double num;
        for (int i = 0; i < mx.row; i++) {
            for (int j = 0; j < mx.col; j++) {
                cin>>num;
                mx.data[i][j] = num;
            }
        }
        return in;
    }
    friend std::ostream& operator<<(ostream &out, Matrix mx) {
        for (int i = 0; i < mx.row; i++) {
            for (int j = 0; j < mx.col; j++) {
                cout<<mx.data[i][j]<<' ';
            }
            cout<<endl;
        }
        return out; 
    }

};
class Neuron {
    int n_size, m_size, h;
    Matrix xtrain;
    Matrix ytrain;
public:
    Neuron (int n_size, int m_size, int h) {
        Neuron::n_size = n_size;
        Neuron::m_size = m_size;
        Neuron::h = h;
    }
    Neuron (Matrix X, Matrix Y) { Neuron::xtrain = X; Neuron::ytrain = Y;}
    double norm(Matrix mx);
    Matrix train(Matrix xtrain, Matrix ytrain);
};
#endif
   
