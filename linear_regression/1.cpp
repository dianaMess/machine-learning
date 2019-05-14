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
    void set(vector <vector <double > > vec) { 
        for (int i = 0; i < vec.size(); i++)
            for (int j = 0; j < vec[i].size(); j++)
                data[i][j] = vec[i][j];
    }
    
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
    ifstream file(argv[1]);  
    ifstream file1(argv[2]);  
    ifstream file2(argv[3]);  

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
    Matrix B = A * K.transpose();
    cout<<endl<<"answer: "<<endl;
    cout<<B;

    return 0;
}
    
