#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
using namespace std;

class Matrix {
    int row, col;
    vector <vector <double> > data;
//    string filename;
public:
    Matrix (int row = 1, int col = 1): row(row), col(col),
           data(vector <vector <double > > (row, vector<double> (col, 0.5))) {}
    int getRow() {
        return row;
    }
    int getCol() {
        return col;
    }
    Matrix operator+(const Matrix & mx) {
        Matrix new_mx(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                new_mx.data[i][j] = data[i][j] + mx.data[i][j];
        return new_mx;
    }

    Matrix operator-(const Matrix & mx) { 
        Matrix new_mx(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                new_mx.data[i][j] = data[i][j] - mx.data[i][j];
        return new_mx;
    }

    Matrix operator-(vector<double> vc) { 
        Matrix new_mx(vc.size(), col);
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                new_mx.data[i][j] = data[i][j] - vc[j];
        return new_mx;
    }
 
    Matrix operator=(const Matrix & mx) {
        for (int i = 0; i < row; i++)
            for (int j = 0 ; j < col; j++)
                data[i][j] = mx.data[i][j];
        return *this;
    }
    Matrix operator=(std::vector<double> vc) {
        for (int i = 0; i < vc.size(); i++) {
            data[i][0] = vc[i];
        }
        return *this;
    }
    std::vector< double > operator[] (int i) {
        return data[i];
    }
    Matrix operator*(const Matrix & mx) {
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

    Matrix operator*(vector<double> vc) {
        Matrix mx_new(vc.size(), row);
        for (int i = 0; i < vc.size(); i++) {
            for (int j = 0; j < row; j++) {
                mx_new[i][j] = data[i][j] * vc[j];
            }
        }
        return mx_new;
    }
 
    Matrix operator*(double num) {
        Matrix mx(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0 ; j < col; j++) {
                mx.data[i][j] = data[i][j] * num;
            }
        }
        return mx;
    }

    Matrix operator/(double num) {
        Matrix mx(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0 ; j < col; j++) {
                mx.data[i][j] = data[i][j] / num;
            }
        }
        return mx;
    }
 
    Matrix transpose() {
        Matrix mx(col, row);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mx.data[j][i] = data[i][j];
            }
        }
        return mx;
    }
    friend std::istream& operator>>(istream &in, Matrix& mx) {
        double num;
//        string f = filename;
//        std::ifstream file("test2.txt");  
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
    double norm(Matrix mx) {
        double sum = 0.0;
        for (int i = 0; i < mx.getRow(); i++) {
            for (int j = 0 ; j < mx.getCol(); j++) {
               sum += mx[i][j] * mx[i][j];
            }
        }
        sum = sqrt(sum); 
        return sum;
    }

    Matrix train(Matrix xtrain, Matrix ytrain) {
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
        return A_new;
    }
};

int main(int argc, char * argv[]) {
    Matrix X(8, 7), Y(8, 1), K(5, 7);
//    std::ifstream file("test2.txt");  
    cin>>X;
//    cout<<X;
    cin>>Y;
    Neuron model(X, Y);
    cin>>K;
    Matrix A = model.train(X, Y);
    Matrix B = A * K.transpose();
    cout<<endl<<"answer: "<<endl;
    cout<<B;
    return 0;
}
    
