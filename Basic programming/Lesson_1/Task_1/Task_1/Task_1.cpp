// Task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

int main() {
    int N, M, shift;
    std::ifstream fin("in.txt");
    if (!fin.is_open()) {
        std::cout << "Не получилось открыть файл in.txt" << std::endl;
        return 1;
    }
    fin >> N;
    int* arr1 = new int [N];
    for (int i = 0; i < N; i++) {
        fin >> arr1[i];
    }
    fin >> M;
    int* arr2 = new int[M];
    for (int i = 0; i < M; i++) {
        fin >> arr2[i];
    }
    fin.close();
    
    shift = arr1[0];
    for (int i = 0; i < N-1; i++) {
        arr1[i] = arr1[i+1];
    }
    arr1[N-1] = shift;

    shift = arr2[M-1];
    for (int i = M-1; i > 0; i--) {
        arr2[i] = arr2[i-1];
    }
    arr2[0] = shift;

    std::ofstream fout("out.txt");
    if (!fout.is_open()) {
        std::cout << "Не получилось открыть файл out.txt" << std::endl;
        return 1;
    }
    fout << M << std::endl;
    for (int i = 0; i < M; i++) {
        fout << arr2[i] << " ";
    }
    fout << std::endl;
    fout << N << std::endl;
    for (int i = 0; i < N; i++) {
        fout << arr1[i] << " ";
    }
    fout << std::endl;
    fout.close();

    delete[]   arr1;
    arr1 = nullptr;
    delete[]   arr2;
    arr2 = nullptr;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
