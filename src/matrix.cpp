#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include"matrix.h"
using namespace std;
    void Matrix::set(vector <vector <double > > vec) { 
        for (int i = 0; i < vec.size(); i++)
            for (int j = 0; j < vec[i].size(); j++)
                data[i][j] = vec[i][j];
    }
    
    int Matrix::getRow() {
        return row;
    }
    int Matrix::getCol() {
        return col;
    }
    Matrix Matrix::operator+(const Matrix & mx) {
        Matrix new_mx(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                new_mx.data[i][j] = data[i][j] + mx.data[i][j];
        return new_mx;
    }

    Matrix Matrix::operator-(const Matrix & mx) { 
        Matrix new_mx(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                new_mx.data[i][j] = data[i][j] - mx.data[i][j];
        return new_mx;
    }

    Matrix Matrix::operator-(vector<double> vc) { 
        Matrix new_mx(vc.size(), col);
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                new_mx.data[i][j] = data[i][j] - vc[j];
        return new_mx;
    }
 
    Matrix Matrix::operator=(const Matrix & mx) {
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                data[i][j] = mx.data[i][j];
        return *this;
    }
    Matrix Matrix::operator=(std::vector<double> vc) {
        for (int i = 0; i < vc.size(); i++) {
            data[i][0] = vc[i];
        }
        return *this;
    }
    vector< double > Matrix::operator[] (int i) {
        return data[i];
    }
    Matrix Matrix::operator*(const Matrix & mx) {
        Matrix mx_new(row, mx.col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < mx.col; j++) {
                for (int k = 0; k < col; k++) {
                    mx_new.data[i][j] += data[i][k] * mx.data[k][j];
                }
            }
        }
        return mx_new;
    }

    Matrix Matrix::operator*(vector<double> vc) {
        Matrix mx_new(vc.size(), row);
        for (int i = 0; i < vc.size(); i++) {
            for (int j = 0; j < row; j++) {
                mx_new[i][j] = data[i][j] * vc[j];
            }
        }
        return mx_new;
    }
 
    Matrix Matrix::operator*(double num) {
        Matrix mx(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0 ; j < col; j++) {
                mx.data[i][j] = data[i][j] * num;
            }
        }
        return mx;
    }

    Matrix Matrix::operator/(double num) {
        Matrix mx(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0 ; j < col; j++) {
                mx.data[i][j] = data[i][j] / num;
            }
        }
        return mx;
    }
 
    Matrix Matrix::transpose() {
        Matrix mx(col, row);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mx.data[j][i] = data[i][j];
            }
        }
        return mx;
    }


    double Neuron::norm(Matrix mx) {
        double sum = 0.0;
        for (int i = 0; i < mx.getRow(); i++) {
            for (int j = 0 ; j < mx.getCol(); j++) {
               sum += mx[i][j] * mx[i][j];
            }
        }
        sum = sqrt(sum); 
        return sum;
    }

    Matrix Neuron::train(Matrix xtrain, Matrix ytrain) {
        double eps = 0.000020;
//        double h = 0.000095;
        double h = 0.00000223;
        Matrix A_old(ytrain.getCol(), xtrain.getCol()),
        A_new(ytrain.getCol(), xtrain.getCol());
        A_new = A_old;
        int count = 0;
        do {
            A_old = A_new;
            Matrix A_sum(ytrain.getCol(), xtrain.getCol());
            for (int i = 0; i < xtrain.getRow(); i++) {
                Matrix x(xtrain.getCol(), 1);
                x = xtrain[i];
                Matrix y(ytrain.getCol(), 1);
                y = ytrain[i];
                A_sum = A_sum + ((A_old * x - y) * x.transpose());
            }
            A_sum = A_sum * h;
            A_new = A_old - A_sum; 
            count++;
        } while (abs(norm(A_new - A_old)) > eps);
        cout<<count<<endl;
        return A_new;
    }

   
