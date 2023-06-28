#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <exception>
#include <windows.h>
#include <memory>
#include <vector>


class Working_with_database {
	
	std::unique_ptr<pqxx::connection> c;
	pqxx::work tx;
public:
	Working_with_database(std::unique_ptr<pqxx::connection>& l) : c{ std::move(l) }, tx{*c} {
		
	}
	~Working_with_database() { tx.commit(); };

	void create_table(std::string& z, std::string& z1) {

		tx.exec("CREATE TABLE IF NOT EXISTS " + tx.esc(z) + " ("+ z1 +");"); //как здесь реалтзовать защиту от SQL инъекций?
	}

	void add_client() {
		std::string z;
		std::vector<std::string> v;
		std::cout << "Введите имя клиента: ";
		std::cin >> z;
		v.push_back(z);
		std::cout << "Введите фамилию клиента: ";
		std::cin >> z;
		v.push_back(z);
		std::cout << "Введите email клиента: ";
		std::cin >> z;
		v.push_back(z);
		bool t = true;
		while (t) {
			std::cout << "Введите телефон клиента или нажмите q: ";
			std::cin >> z;

			if (z == "q") { t = false; }
			else v.push_back(z);
		}
		
		tx.exec("INSERT INTO Clients (name, lastname, email) VALUES ('" + tx.esc(v[0]) + "', '"
			+ tx.esc(v[1]) + "', '" + tx.esc(v[2]) + "');");
		if (v.size() >= 3) {
			for (int i = 3; i <= v.size() - 1; i++) {
				tx.exec("INSERT INTO Phones (number, client_id) VALUES ('" + tx.esc(v[i]) + "', "
					+ " (SELECT id FROM Clients WHERE email LIKE '" + tx.esc(v[2]) + "'));");
			};
		}

	}

	void add_phone() {
		std::string z;
		std::vector<std::string> v;
		std::cout << "Введите email клиента для которого нужно добавить телефон: ";
		std::cin >> z;
		v.push_back(z);
		
		bool t = true;
		while (t) {
			std::cout << "Введите телефон клиента или нажмите q: ";
			std::cin >> z;

			if (z == "q") { t = false; }
			else v.push_back(z);
		}

		for (int i = 1; i <= v.size() - 1; i++) {
				tx.exec("INSERT INTO Phones (number, client_id) VALUES ('" + tx.esc(v[i]) + "', "
					+ " (SELECT id FROM Clients WHERE email LIKE '" + tx.esc(v[0]) + "'));");
		}

	}

	void update_client() {
		std::string z, z1;
		std::vector<std::string> v;
		std::cout << "Введите email клиента для которого нужно изменить данные или номер телефона если нужно изменить телефон: ";
		std::cin >> z;
		v.push_back(z);
		if (z.find('@') != std::string::npos) z1 = "email";
		else z1 = "number";

		std::cout << "Введите название таблицы: ";
		std::cin >> z;
		v.push_back(z);

		std::cout << "Введите название столбца: ";
		std::cin >> z;
		v.push_back(z);

		std::cout << "Введите нужные данные: ";
		std::cin >> z;
		v.push_back(z);

		tx.exec("UPDATE " + tx.esc(v[1]) + " SET " + tx.esc(v[2]) + " = '"
				+ tx.esc(v[3]) + "' WHERE "+z1+" LIKE '" + tx.esc(v[0]) + "'; ");
	}

	void delete_phone() {
		std::string z;
		std::cout << "Введите номер телефона который нужно удалить: ";
		std::cin >> z;
		tx.exec("DELETE FROM Phones WHERE number = '" + tx.esc(z) + "'; ");
	}

	void delete_client() {
		std::string z;
		std::cout << "Введите email клиента которого нужно удалить: ";
		std::cin >> z;
		tx.exec("DELETE FROM Clients WHERE email = '" + tx.esc(z) + "'; ");
	}

	void select_client() {
		std::string z;
		std::cout << "Введите данные клиента (имя, фамилию, email или телефон): ";
		std::cin >> z;
		
		for (auto [name, lastname, email, number] : tx.query<std::string,
			std::string, std::string, std::string>
			("SELECT name, lastname, email, number FROM clients JOIN phones "
				"ON clients.id = phones.client_id WHERE email = '" + tx.esc(z)+"' OR name = '"
				+ tx.esc(z)+"' OR lastname = '" + tx.esc(z) + "' OR number = '" + tx.esc(z) + "'"))
		{
			std::cout << "Client is: " << name << " " << lastname << " " << email << " " << number << ".\n";
		}
		
	}
};

int main() {
	
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru_RU.UTF-8");  //"Russian");

	try{
		auto up1 = std::make_unique<pqxx::connection> (
			"host=localhost " // 127.0.0.1
			"port=5432 "
			"dbname=lesson_clients "
			"user=postgres "
			"password=Iougurt13");

		Working_with_database d(up1);

		/*Создаем таблицу Clients*/
		std::string z = "Clients";
		std::string z1 = "id SERIAL PRIMARY KEY, "
			"Name VARCHAR(60) NOT NULL DEFAULT 'РќР•РР—Р’Р•РЎРўРќРћ', "
			"Lastname TEXT NOT NULL DEFAULT 'РќР•РР—Р’Р•РЎРўРќРћ', "
			"Email TEXT UNIQUE";
		d.create_table(z, z1);

		/*Создаем таблицу Phones*/
		z = "Phones";
		z1 = "id SERIAL PRIMARY KEY, "
			"number VARCHAR(60) UNIQUE, "
			"client_id INT REFERENCES Clients(id) ON UPDATE CASCADE ON DELETE CASCADE";
		d.create_table(z, z1);

		/*Добавляем клиента*/
		d.add_client();
		
		/*Добавляем телефон*/
		d.add_phone();

		/*Изменить данные о клиенте*/
		d.update_client();
		
		/*Удалить телефон*/
		d.delete_phone();

		/*Удалить клиента*/
		d.delete_client();

		/*Выбор клиента*/
		d.select_client();

		std::cout << "All rite" << std::endl;

	}
	catch (pqxx::sql_error e){
		std::cout << e.what() << std::endl;
	}
	
	getchar();
	return 0;
}