
#include <iostream>
#include <string>
#include <windows.h>

struct account {
    long long int account_number;
    std::string name;
    long double balance;
};

void operation(account& client, long double& new_balance) {
    client.balance = new_balance;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian"); 
    
    account client;
    long double new_balance;
           
    std::cout << "Введите номер счета: ";
    std::cin >> client.account_number;
    std::cout << "Введите имя владельца: ";
    std::cin.ignore();
    getline(std::cin, client.name);
    std::cout << "Введите баланс: ";
    std::cin >> client.balance;
    std::cout << "Введите новый баланс: ";
    std::cin >> new_balance;
    operation(client, new_balance);
    std::cout << "Ваш счет: " << client.name << ", " << client.account_number << ", " << client.balance;
    
}
