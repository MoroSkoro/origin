#include <iostream>
#include <windows.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/Query.h>
#include <Wt/Dbo/collection.h>
#include <string>
#include <memory>
#include <exception>
#include <vector>


///Использовал эту функцию для преобразования кодировки
///т.к. невоспринимается ввод в консоль
/// как правильно или лучше это было бы реализовать?
/// В Wt есть классы и методы WString, toUTF8 () и др. но не смог разобраться, как они работают
std::string cp1251_to_utf8 (const char* str){
    std::string res;
    int result_u, result_c;

    result_u = MultiByteToWideChar(1251,0,str,-1,
        0,
        0);

    if (!result_u)
        return 0;

    wchar_t* ures = new wchar_t[result_u];

    if (!MultiByteToWideChar(1251,
        0,
        str,
        -1,
        ures,
        result_u))
    {
        delete[] ures;
        return 0;
    }

    result_c = WideCharToMultiByte(
        CP_UTF8,
        0,
        ures,
        -1,
        0,
        0,
        0, 0);

    if (!result_c)
    {
        delete[] ures;
        return 0;
    }

    char* cres = new char[result_c];

    if (!WideCharToMultiByte(
        CP_UTF8,
        0,
        ures,
        -1,
        cres,
        result_c,
        0, 0))
    {
        delete[] cres;
        return 0;
    }
    delete[] ures;
    res.append(cres);
    delete[] cres;
    return res;
}


class Stock;
class Publisher;
class Sale;

class Book {
public:
    std::string title;
    Wt::Dbo::ptr<Publisher> id_publisher;
    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> id_stock;
    template<class Action>
    void persist(Action& a){
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, id_publisher, "id_publisher");
        Wt::Dbo::hasMany(a, id_stock, Wt::Dbo::ManyToOne, "id_book");
    }
};

class Publisher {
public:
    std::string name;
    Wt::Dbo::collection<Wt::Dbo::ptr<Book>> id_book;
    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, id_book, Wt::Dbo::ManyToOne, "id_publisher");
    }
};

class Shop {
public:
    std::string name;
    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> id_stock;
    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, id_stock, Wt::Dbo::ManyToOne, "id_shop");
    }
};

class Stock {
public:
    int count;
    Wt::Dbo::ptr<Book> id_book;
    Wt::Dbo::ptr<Shop> id_shop;
    Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> id_sale;
    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::belongsTo(a, id_book, "id_book");
        Wt::Dbo::belongsTo(a, id_shop, "id_shop");
        Wt::Dbo::hasMany(a, id_sale, Wt::Dbo::ManyToOne, "id_stock");
    }
};

class Sale {
public:
    double price;
    std::string date_sale;
    int count;
    Wt::Dbo::ptr<Stock> id_stock;
    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, price, "price");
        Wt::Dbo::field(a, date_sale, "date_sale");
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::belongsTo(a, id_stock, "id_stock");
    }
};

void createdb(Wt::Dbo::Session& session) {
    try {
        

        /////////////Publisher1 and books//////////////////////////

        Wt::Dbo::Transaction transaction{ session };
        std::unique_ptr<Publisher> pub{ new Publisher() };
        pub->name = "Аврора";
        Wt::Dbo::ptr<Publisher> pubPtr = session.add(std::move(pub));

        std::unique_ptr<Book> bok{ new Book() };
        bok->title = "Капитанская дочка";
        bok->id_publisher = pubPtr;
        Wt::Dbo::ptr<Book> bokPtr = session.add(std::move(bok));

        std::unique_ptr<Book> bok1{ new Book() };
        bok1->title = "Метель";
        bok1->id_publisher = pubPtr;
        Wt::Dbo::ptr<Book> bok1Ptr = session.add(std::move(bok1));

        std::unique_ptr<Book> bok2{ new Book() };
        bok2->title = "Балда";
        bok2->id_publisher = pubPtr;
        Wt::Dbo::ptr<Book> bok2Ptr = session.add(std::move(bok2));

        /////////////Publisher2 and books//////////////////////////

        transaction.commit();

        Wt::Dbo::Transaction transaction1{ session };

        std::unique_ptr<Publisher> pub1{ new Publisher() };
        pub1->name = "Эврика";
        Wt::Dbo::ptr<Publisher> pub1Ptr = session.add(std::move(pub1));

        std::unique_ptr<Book> bok3{ new Book() };
        bok3->title = "Жизнь Арсеньева";
        bok3->id_publisher = pub1Ptr;
        Wt::Dbo::ptr<Book> bok3Ptr = session.add(std::move(bok3));

        std::unique_ptr<Book> bok4{ new Book() };
        bok4->title = "Цифры";
        bok4->id_publisher = pub1Ptr;
        Wt::Dbo::ptr<Book> bok4Ptr = session.add(std::move(bok4));

        std::unique_ptr<Book> bok5{ new Book() };
        bok5->title = "Лапти";
        bok5->id_publisher = pub1Ptr;
        Wt::Dbo::ptr<Book> bok5Ptr = session.add(std::move(bok5));

        transaction1.commit();

        /////////////Publisher3 and books//////////////////////////

        Wt::Dbo::Transaction transaction2{ session };

        std::unique_ptr<Publisher> pub2{ new Publisher() };
        pub2->name = "Питер";
        Wt::Dbo::ptr<Publisher> pub2Ptr = session.add(std::move(pub2));

        std::unique_ptr<Book> bok6{ new Book() };
        bok6->title = "О любви";
        bok6->id_publisher = pub2Ptr;
        Wt::Dbo::ptr<Book> bok6Ptr = session.add(std::move(bok6));

        std::unique_ptr<Book> bok7{ new Book() };
        bok7->title = "О животных";
        bok7->id_publisher = pub2Ptr;
        Wt::Dbo::ptr<Book> bok7Ptr = session.add(std::move(bok7));

        std::unique_ptr<Book> bok8{ new Book() };
        bok8->title = "О природе";
        bok8->id_publisher = pub2Ptr;
        Wt::Dbo::ptr<Book> bok8Ptr = session.add(std::move(bok8));
        transaction2.commit();

        ///////////////////////////////////////////////////////////////////////////////////////////

        Wt::Dbo::Transaction transaction3{ session };

        /////////////Shop//////////////////////////

        std::unique_ptr<Shop> shop1{ new Shop() };
        shop1->name = "На Таганке";
        Wt::Dbo::ptr<Shop> shop1Ptr = session.add(std::move(shop1));

        std::unique_ptr<Shop> shop2{ new Shop() };
        shop2->name = "На Пресне";
        Wt::Dbo::ptr<Shop> shop2Ptr = session.add(std::move(shop2));

        std::unique_ptr<Shop> shop3{ new Shop() };
        shop3->name = "На Арбате";
        Wt::Dbo::ptr<Shop> shop3Ptr = session.add(std::move(shop3));

        /////////////Stock//////////////////////////

        std::unique_ptr<Stock> stock1{ new Stock() };
        stock1->id_book = bokPtr;
        stock1->id_shop = shop1Ptr;
        stock1->count = 300;
        Wt::Dbo::ptr<Stock> stock1Ptr = session.add(std::move(stock1));

        std::unique_ptr<Stock> stock2{ new Stock() };
        stock2->id_book = bok1Ptr;
        stock2->id_shop = shop1Ptr;
        stock2->count = 200;
        Wt::Dbo::ptr<Stock> stock2Ptr = session.add(std::move(stock2));

        std::unique_ptr<Stock> stock3{ new Stock() };
        stock3->id_book = bok4Ptr;
        stock3->id_shop = shop2Ptr;
        stock3->count = 100;
        Wt::Dbo::ptr<Stock> stock3Ptr = session.add(std::move(stock3));

        std::unique_ptr<Stock> stock4{ new Stock() };
        stock4->id_book = bok5Ptr;
        stock4->id_shop = shop2Ptr;
        stock4->count = 500;
        Wt::Dbo::ptr<Stock> stock4Ptr = session.add(std::move(stock4));

        std::unique_ptr<Stock> stock5{ new Stock() };
        stock5->id_book = bok6Ptr;
        stock5->id_shop = shop3Ptr;
        stock5->count = 80;
        Wt::Dbo::ptr<Stock> stock5Ptr = session.add(std::move(stock5));

        std::unique_ptr<Stock> stock6{ new Stock() };
        stock6->id_book = bok7Ptr;
        stock6->id_shop = shop3Ptr;
        stock6->count = 3;
        Wt::Dbo::ptr<Stock> stock6Ptr = session.add(std::move(stock6));

        /////////////Sale//////////////////////////

        std::unique_ptr<Sale> sale1{ new Sale() };
        sale1->price = 500.40;
        sale1->date_sale = "15.31.00 21.03.2023";
        sale1->count = 30;
        sale1->id_stock = stock3Ptr;
        Wt::Dbo::ptr<Sale> sale1Ptr = session.add(std::move(sale1));

        std::unique_ptr<Sale> sale2{ new Sale() };
        sale2->price = 900;
        sale2->date_sale = "10.31.00 03.04.2023";
        sale2->count = 10;
        sale2->id_stock = stock5Ptr;
        Wt::Dbo::ptr<Sale> sale2Ptr = session.add(std::move(sale2));

        std::unique_ptr<Sale> sale3{ new Sale() };
        sale3->price = 732.56;
        sale3->date_sale = "16.22.00 04.04.2023";
        sale3->count = 1;
        sale3->id_stock = stock6Ptr;
        Wt::Dbo::ptr<Sale> sale3Ptr = session.add(std::move(sale3));

        transaction2.commit();
    }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
}
//////Подскажите, пожалуйста, как правильно вводить данные?
/////ведь 1000 наименований не прописывать же в программном коде
///// как это делается в реальных программах?
//// может из файлов CSV или json вводить?


int main() {
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //setlocale(LC_ALL, " Russian_Russia.1251");  
    setlocale(LC_ALL, "ru_RU.UTF-8");

    try {
    std::string connect = "host=localhost " // 127.0.0.1
        "port=5432 "
        "dbname=Lesson_6_DB "
        "user=postgres "
        "password=Iougurt13";

    auto connection = std::make_unique<Wt::Dbo::backend::Postgres>(connect);
    Wt::Dbo::Session session;
    session.setConnection(std::move(connection));

    session.mapClass<Publisher>("publisher");
    session.mapClass<Book>("book");
    session.mapClass<Stock>("stock");
    session.mapClass<Shop>("shop");
    session.mapClass<Sale>("sale");
    try { session.createTables(); }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    createdb(session); //После первого запуска программы лучше закоментировать,
    ///////////////////////иначе будут добавляться снова и снова с каждым запуском.
    //////////////////////отсюда и вопрос: как добавить if not exists и unique?

        /////////////Поиск магазинов//////////////////////////
   
        std::string publish;
        char str[20];
        
        std::cout << "Введите требуемого издателя (Аврора, Эврика, Питер): ";
        std::cin >> str;

        publish = cp1251_to_utf8(str);

        Wt::Dbo::Transaction transaction{ session };
        Wt::Dbo::ptr<Publisher> find_publish = session.find<Publisher>().where("name = ?").
            bind(publish);
       
        typedef Wt::Dbo::ptr<Book> BookPtr;
        typedef Wt::Dbo::collection<BookPtr> AccountsBook;
        Wt::Dbo::Query<BookPtr> query = session.find<Book>().where("book.id_publisher_id = ?").bind(find_publish);
        AccountsBook accounts_book = query.resultList();

        typedef Wt::Dbo::ptr<Stock> StockPtr;
        typedef Wt::Dbo::collection<StockPtr> AccountsStock;
        AccountsStock accounts_stock;
        std::vector<Wt::Dbo::ptr<Stock>> vec_stock;
        for (Wt::Dbo::ptr<Book> b : accounts_book) {
            Wt::Dbo::Query<StockPtr> query_stock = session.find<Stock>().where("stock.id_book_id = ?").bind(b);
            AccountsStock accounts_stock = query_stock.resultList();
            for(Wt::Dbo::ptr<Stock> st: accounts_stock){
                vec_stock.push_back(st);
            }
        };

        typedef Wt::Dbo::ptr<Shop> ShopPtr;
        typedef Wt::Dbo::collection<ShopPtr> AccountsShop;
        AccountsShop accounts_shop;
        std::vector<Wt::Dbo::ptr<Shop>> vec_shop;
        for (Wt::Dbo::ptr<Stock> st1 : vec_stock) {
                vec_shop.push_back(st1->id_shop);
        };
        vec_shop.erase(std::unique(vec_shop.begin(), vec_shop.end()), vec_shop.end());

        std::cout << "\nИздатель " << find_publish->name << " продает свои книги в магазинах:" <<std::endl;

        for (Wt::Dbo::ptr<Shop> sh : vec_shop) {
            std::cerr << "- " << sh->name << std::endl;
        }

        transaction.commit();
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
  
    getchar();
    return 0;
}