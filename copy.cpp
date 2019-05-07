
class Vector {
    int size;
    vector<double> data;
public:
    Vector (int size) : size(size), data(vector<double> (size, 0.5)) {}
    int getSize() {
        return size;
    }
    Vector operator+(const Vector& vc) {
        Vector new_vc(size);
        for (int i = 0 ; i < size; i++) {
            new_vc = data[i] + vc.data[i];
        }
        return new_vc;
    }
    Vector operator-(const Vector& vc) {
        Vector new_vc(size);
        for (int i = 0 ; i < size; i++) {
            new_vc = data[i] - vc.data[i];
        }
        return new_vc;
    }
    Vector operator=(const Vector& vc) {
        for (int i = 0 ; i < size; i++) {
            data[i] = vc.data[i];
        }
        return *this;
    }
 
    Vector operator*(const Vector& vc);
    double operator[](int i) {
        return data[i];
    }
    friend std::istream& operator>>(istream &in, Vector& vc) {
        double num;
        for (int i = 0; i < vc.size; i++) {
            cin>>num;
            vc.data[i] = num;
        }
        return in;
    }
    friend std::ostream& operator<<(ostream &out, Vector vc) {
        int num;
        for (int i = 0; i < vc.size; i++) {
                cout<<vc.data[i]<<' ';
        }
        return out; 
    }

