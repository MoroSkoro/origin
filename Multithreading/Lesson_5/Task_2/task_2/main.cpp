#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>


using namespace std::chrono_literals;

std::mutex m;

void SetCursorPos(int XPos, int YPos)
{
    printf("\033[%d;%dH", YPos + 1, XPos + 1);
}

void fProgressBar(int i, int barWidth) {
    auto start = std::chrono::steady_clock::now();

    int x = 10;
    const int y = (i+1)*3;
    int j = 0;
        

    //Порядковый номер потока
    m.lock();
      /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(0), static_cast<SHORT>(y) });*/
    SetCursorPos(x, y);

      std::cout << "Potok " << i + 1;
    m.unlock();

    //id потока
    m.lock();
      /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(0), static_cast<SHORT>(y+1) });*/
    SetCursorPos(x, y);

      std::cout << "id potoka: " << std::this_thread::get_id()<<".";
    m.unlock();
    
    //Начало пргрессбар
    m.lock();
      //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
      SetCursorPos(x, y);
      //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        //{ static_cast<SHORT>(x), static_cast<SHORT>(y) });

      std::cout << "[";
    m.unlock();
    
    while (j < barWidth) {
        ++x;
        std::this_thread::sleep_for(200ms);
        m.lock();
        /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
            { static_cast<SHORT>(x), static_cast<SHORT>(y) });*/
        SetCursorPos(x, y);

        std::cout << "=";
        m.unlock();
        j++;
    }

    //Конец прогрессбар
    m.lock();
    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(x+1), static_cast<SHORT>(y) });*/
    SetCursorPos(x, y);

    std::cout << "] End";
    m.unlock();
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    double t1 = elapsed_seconds.count();
    
    //Затраченное время
    m.lock();
    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | i + 4));
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(18), static_cast<SHORT>(y+1) });*/
    SetCursorPos(18, y+1);

    std::cout << "Elapsed time: " << t1;
    m.unlock();
}

int main()
{
    
    int n = 5;
    int calculation_length = 40;
    std::vector<std::thread> vec(n);
    
    std::system("clear");

    for (int i = 0; i < n; i++) {
        vec[i] = std::thread(fProgressBar, i, calculation_length);
    }
    for (auto& v : vec) {
        v.join();
    }
    /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((0 << 4) | 15));
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        { static_cast<SHORT>(0), static_cast<SHORT>(n*3+2) });*/
    SetCursorPos(0, (n*3+2));
    std::cout << "\n";

    std::cout << "\n Press any key...";
    std::cin.get();
    return 0;
}