#include "Functions.h"


bool check(double& d, std::vector < std::string >& v_check, int& number_of_participants, int& reg) {
    bool good_reg = false;
    std::string target = "null";
    if (number_of_participants <= 7) {
        switch (reg) {
        case 1:
            target = "�������-���������";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\n�������-��������� ��� ����������������! ������� ������ ������������ ��������\n";
            }
            else {
                v_check.push_back("�������-���������");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 2:
            target = "�����";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\n����� ��� ����������������! ������� ������ ������������ ��������\n";
            }
            else {
                v_check.push_back("�����");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 3:
            target = "�������";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\n������� ��� ���������������! ������� ������ ������������ ��������\n";
            }
            else {
                v_check.push_back("�������");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 4:
            target = "�������";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\n������� ��� ���������������! ������� ������ ������������ ��������\n";
            }
            else {
                v_check.push_back("�������");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 5:
            target = "����";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\n���� ��� ���������������! ������� ������ ������������ ��������\n";
            }
            else {
                v_check.push_back("����");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 6:
            target = "�������-���������";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\n�������-��������� ��� ���������������! ������� ������ ������������ ��������\n";
            }
            else {
                v_check.push_back("�������-���������");
                number_of_participants++;
                good_reg = true;
            }
            break;
        case 7:
            target = "����� �������";
            if (std::find(v_check.begin(), v_check.end(), target) != v_check.end()) {
                std::cout << "\n����� ������� ��� ���������������! ������� ������ ������������ ��������\n";
            }
            else {
                v_check.push_back("����� �������");
                number_of_participants++;
                good_reg = true;
            }
            break;
        }
    }
    else { std::cout << "\n" << "����������� ��������� ����� ���������� ����������������! ������� �����!\n"; }
    return good_reg;
}
//��������

void print_check(double& d, std::vector < std::string >& v_check, int& number_of_participants, int& reg) {
    if (check(d, v_check, number_of_participants, reg)) {
        for (std::vector<std::string>::iterator iter = v_check.begin(); iter != v_check.end(); iter++)
        {
            if (iter != (v_check.end() - 1)) {
                std::cout << (*iter) << ", ";
            }
            else { std::cout << (*iter) << " - "; }
        }
        std::cout << "������� �����������������!" << std::endl;
        std::cout << std::endl;
    }
}
//����������

void registration(double& d, std::string& tRace, int typeRace, std::vector < std::string >& v_check, int& number_of_participants) {
    int exit = 1;
    int reg;
    while (exit != 0) {
        std::cout << "\n" << tRace << " ����������: " << d << std::endl;
        std::cout << "1. �������-���������\n";
        std::cout << "2. �����\n";
        std::cout << "3. �������\n";
        std::cout << "4. �������\n";
        std::cout << "5. ����\n";
        std::cout << "6. �������-���������\n";
        std::cout << "7. ����� �������\n";
        std::cout << "0. ��������� �����������\n";
        std::cout << "\n�������� ��������� ��� 0 ��� ��������� �������� �����������: ";
        std::cin >> reg;
        switch (reg) {
        case 1:
            if (typeRace == 2) {
                std::cout << "\n������� ���������������� ������������ ��� ������������� ��������!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 2:
            if (typeRace == 1) {
                std::cout << "\n������� ���������������� ������������ ��� ������������� ��������!\n";
            }
            else {

                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 3:
            if (typeRace == 2) {
                std::cout << "������� ���������������� ������������ ��� ������������� ��������!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 4:
            if (typeRace == 2) {
                std::cout << "������� ���������������� ������������ ��� ������������� ��������!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 5:
            if (typeRace == 1) {
                std::cout << "������� ���������������� ������������ ��� ������������� ��������!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 6:
            if (typeRace == 2) {
                std::cout << "������� ���������������� ������������ ��� ������������� ��������!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 7:
            if (typeRace == 1) {
                std::cout << "������� ���������������� ������������ ��� ������������� ��������!\n";
            }
            else {
                print_check(d, v_check, number_of_participants, reg);
            }
            break;
        case 0:
            if (number_of_participants < 2) {
                std::cout << "\n������ ���� ���������������� ������ 2 ������������ ��������." << std::endl;
                std::cout << "��������������� �� ����� 2 ������������ ��������." << std::endl;
            }
            else { exit = 0; }
        }
    }
}


bool sortBy_t(Transport l_t, Transport r_t) {
    return (l_t.get_t() < r_t.get_t());
}


void gonka ( std::vector<std::string> &v_check, double& d){

    std::vector<Transport> v1;
    std::string target = "null";
    for (std::vector<std::string>::iterator iter = v_check.begin(); iter != v_check.end(); iter++)
    {
        target = *iter;
        if (target == "�������-���������") {
            Boots_AllTerrain boots(d);
            v1.push_back(boots);
            
        }
        if (target == "�����") {
            Broom broom(d);
            v1.push_back(broom);
        }
        if (target == "�������") {
            Camel camel(d);
            v1.push_back(camel);
        }
        if (target == "�������") {
            Krahotabl krahotabl(d);
            v1.push_back(krahotabl);
        }
        if (target == "����") {
            Eagle eagle(d);
            v1.push_back(eagle);
        }
        if (target == "�������-���������") {
            CamelFast camelFast(d);
            v1.push_back(camelFast);
        }
        if (target == "����� �������") {
            Magic_carpet magic_carpet(d);
            v1.push_back(magic_carpet);
        }
        
    }

    std::sort(v1.begin(), v1.end(), sortBy_t);
    int i = 1;
    for (std::vector<Transport>::iterator iter1 = v1.begin(); iter1 != v1.end(); iter1++)
    {
        std::cout << i << ". " << iter1->get_name() << ". �����: " << iter1->get_t() << "\n";
        std::cout << std::endl;
        i++;
    }
}