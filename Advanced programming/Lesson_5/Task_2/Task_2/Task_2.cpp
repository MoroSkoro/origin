#include <iostream>

template <class T>
class table {
private:
    class sub_mas{
    public:
        T* arr_columns;
        sub_mas(){}
        sub_mas(size_t size) {
            arr_columns = new T[size]{};
        }
        T& operator [] (size_t i){
            return arr_columns[i];
        }
        const T& operator[](size_t i) const { return arr_columns[i]; };
    };

    size_t num_columns = 1;
    size_t num_rows = 1;
    sub_mas* rows;
public:
    table(size_t row, size_t col) {
        row < 1 ? num_rows = 1 : num_rows = row;
        col < 1 ? num_columns = 1 : num_columns = col;
 
        rows = new sub_mas[num_rows];
        for (size_t i = 0; i < num_rows; i++){
            rows[i] = sub_mas(num_columns);
        }
    }
    ~table(){
        for (size_t i = 0; i < num_rows; i++) {
            if (rows[i].arr_columns != nullptr)
            delete[] rows[i].arr_columns;
        }
        
        if (rows != nullptr) delete[] rows;
    }

    sub_mas& operator[](size_t i){ return rows[i];};
    const sub_mas& operator[](size_t i) const { return rows[i]; };

    const size_t Size() { return num_columns * num_rows; };
};

int main()
{
    size_t row = 4;
    size_t col = 5;

    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0];
    std::cout << "\n\n";

    auto v = table<int>(row, col);
    std::cout <<"Size v = " << v.Size() << "\n";
    int d = 3;

    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            v[i][j] = d+i+j;
        }
    }

    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            std::cout << v[i][j] << " ";
        }
        std::cout << "\n";
    }
}