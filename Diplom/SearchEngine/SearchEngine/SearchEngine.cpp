
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <vector>
#include <ranges>
#include <map>
#include <sstream>
#include <thread>

#include "cpr/cpr.h"
#include "libxml/htmlparser.h"
#include "libxml/xpath.h"

#include <pqxx/pqxx>
#include <pqxx/connection>
#include <pqxx/transaction>

#include "Resurs/include/sch_engine/processing_functions.h"

#include "ShellAPI.h"
#include <windows.h>

//#include <curl/curl.h>
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF8");

    std::string p;
    std::map<std::string, int> m;

    std::string BD_host;
    std::string BD_port;
    std::string BD_name;
    std::string BD_user;
    std::string BD_parole;
    std::string html_start = "https://wikipedia.org/"; //"https://ru.wikipedia.org/wiki/";
    std::string html_start1 = "https://www.google.com";//"file:///E:/HTML/Simple.html"; //"https://wikipedia.org"; //"https://www.google.com";//  https://meta.wikimedia.org/wiki/Special:MyLanguage/List_of_Wikipedias";
    std::string s;
    size_t pars_recurs = 1;
    size_t http_port = 80;
    std::string er{"Error"};
    int id;
    unsigned short rep = 2000;
    std::string id_str;
    std::vector<std::string> links_to_scrape;
    links_to_scrape.reserve(rep);
    std::vector<std::string> discovered_links;
    discovered_links.reserve(rep);
    std::vector<std::string> buffer_links;
    buffer_links.reserve(rep);
    std::vector<std::string> buffer_links_for_all;
    buffer_links_for_all.reserve(rep);
    std::vector<std::string> del_already_verified;
    del_already_verified.reserve(rep);
    size_t current_recurs = 0;
    std::string all_text;
    int min = 3;
    int max = 33;
    if (links_to_scrape.empty()) std::cout << "Вектора пустые!" << std::endl;
    else std::cout << "Вектора NONпустые!" << std::endl;
    try
    {

        std::ifstream ini("SearchEngine.ini");
        std::ofstream fout("output.txt");

        if (ini.is_open())
        {
            std::getline(ini, BD_host);
            std::getline(ini, BD_port);
            //BD_port= stoi(s);
            std::getline(ini, BD_name);
            std::getline(ini, BD_user);
            std::getline(ini, BD_parole);
            std::getline(ini, html_start);
            std::getline(ini, s);
            pars_recurs = stoi(s);
            std::getline(ini, s);
            http_port = stoi(s);
            std::cout << "Pars - " << pars_recurs << std::endl;
        }
        else {
            er = "Failed to read file SearchEngine.ini";
            throw er;
        }
        ini.close();

        std::string conect = "host=" + BD_host + " " + "port=" + BD_port + " " + "dbname=" + BD_name + " " + "user=" + BD_user + " " + "password=" + BD_parole;

        pqxx::connection c(conect);
        if (c.is_open()) {
            std::cout << "Opened database successfully: " << c.dbname() << std::endl;
        }
        else {
            er = "Can't open database\n";
            throw er;
        }
        pqxx::work xact(c);
        xact.exec("CREATE TABLE IF NOT EXISTS Pages "
            "(id SERIAL PRIMARY KEY, "
            "Links TEXT UNIQUE)");
        xact.exec("CREATE TABLE IF NOT EXISTS Words "
            "(id BIGSERIAL PRIMARY KEY, "
            "Word TEXT UNIQUE)");
        xact.exec("CREATE TABLE IF NOT EXISTS Word_frequency "
            "(id BIGSERIAL PRIMARY KEY, "
            "Pages_id BIGSERIAL NOT NULL REFERENCES Pages, "
            "Words_id   BIGSERIAL NOT NULL REFERENCES Words, "
            "Count BIGSERIAL, "
            "UNIQUE(Pages_id, Words_id));");
        xact.commit();

        bool do_not_execute = false;
        //links_to_scrape.push_back(html_start1);
        links_to_scrape.emplace_back(html_start);
        int f = 0;
        while (!links_to_scrape.empty() && (current_recurs < pars_recurs)) {
            // define the user agent for the GET request

            std::string link{};
            link = links_to_scrape.at(0);
            links_to_scrape.erase(links_to_scrape.begin());
            if (current_recurs == 0) { std::cout << "Pleas wait..." << std::endl; }
            //func
            std::cout << "111while = " << f << std::endl; f++;

            //link = "https://play.google.com/store/apps/details?id=org.wikipedia&referrer=utm_source%3Dportal%26utm_medium%3Dbutton%26anid%3Dadmob";
            //std::string hh = "https://itunes.apple.com/app/apple-store/id324715238?pt=208305&ct=portal&mt=8";
            //std::string hh = "http://apps.apple.com/us/app/wikipedia/id324715238";
            /*std::string hh = "http://apps.apple.com/us/app/wikipedia/id324715238";
            cpr::Response r = cpr::Get(cpr::Url{ hh });
            std::cout << "Text = " << r.text << std::endl;
            std::cout << "CPR cod = " << r.status_code << std::endl;
            if (r.status_code == 0) {
                auto error = r.error.code;
                std::cout << "Error cod: " << r.error.message << std::endl;
            }*/

            //if (link.empty()) { std::cout << "link EMPTY" << std::endl; }
            //std::cout << link << std::endl;
                if (func_pars(link, buffer_links, all_text)) {
                     
                     //if (all_text[0] != '0') {
                     if (!all_text.empty()) {
                         pqxx::work xact1(c);
                                     //std::cout << "Текущая ссылка: " << link << std::endl;
                         auto r = xact1.exec("INSERT INTO Pages(Links) "
                             "VALUES('" + xact1.esc(link) + "') on conflict (Links) do nothing RETURNING id;");
                         if (r.empty()) { r = xact1.exec("SELECT id FROM Pages WHERE Links = '" + xact1.esc(link) + "';"); }
                                     //pqxx::result::const_iterator ptr = r.begin();
                         std::string pages_id_str = (r[0][0].as<std::string>());
                         xact1.commit();
                         
                         std::wstring low = ToLower(all_text);
                         std::stringstream words(removeParser(low, min, max));
                         //std::stringstream words(removeParser(ToLower(all_text), min, max));
                         pqxx::work xact2(c);
                         while (words >> p) {
                             m[p]++;
                         }
                         for (auto e : m) {
                             r = xact2.exec("INSERT INTO Words(Word) "
                                 "VALUES('" + xact2.esc(e.first) + "') on conflict (Word) do nothing RETURNING id;");
                             if (r.empty()) { r = xact2.exec("SELECT id FROM Words WHERE Word = '" + xact2.esc(e.first) + "';"); }
                             std::string words_id_str = (r[0][0].as<std::string>());
                             std::string preobraz{ std::to_string(e.second) };
                             xact2.exec("INSERT INTO Word_frequency(Pages_id, Words_id, Count) "
                                 "VALUES(" + xact2.esc(pages_id_str) + ", " + xact2.esc(words_id_str) + ", " + xact2.esc(preobraz) + ") on conflict (Pages_id, Words_id) do nothing;");
                                         //std::cout << e.first << " --> " << e.second << "\n";
                         }
                         xact2.commit();
                     }
                         //discovered_links.push_back(link);
                }
                 discovered_links.emplace_back(link);
                 if (current_recurs < (pars_recurs - 1)) {
                     
                     for (auto stroc : buffer_links) {
                         if ((std::find(discovered_links.begin(), discovered_links.end(), stroc) == discovered_links.end())) {
                             if (stroc.starts_with("http")) {
                                 del_already_verified.emplace_back(stroc);
                                 //std::cout << url << std::endl;
                             }
                         }
                     }
                     buffer_links.clear();
                     buffer_links_for_all.insert(buffer_links_for_all.end(), del_already_verified.begin(), del_already_verified.end());
                 }
                 if (current_recurs <= pars_recurs) {
                     if (links_to_scrape.empty()) {
                         ++current_recurs;
                         if (!buffer_links_for_all.empty()) {
                         std::cout << "links_to_scrape = buffer_links_for_all;" << std::endl;
                         std::cout << "Size buffer_links_for_all - " << buffer_links_for_all.size() << std::endl;
                             links_to_scrape = buffer_links_for_all;
                             buffer_links_for_all.clear();
                         }
                         
                     }
                 }
                 std::cout << "while = true" << std::endl;
                 if (f > rep/20) break;
        }
             c.close();
    }
    
     catch (std::exception & e)
     {
         std::cerr << "Error: " << e.what() << std::endl;
         std::cout << "pars_ok = exseption" << std::endl;
         return 0;// EXIT_FAILURE;
     }
     catch (std::string error_message)
     {
         std::cout << error_message << std::endl;
     }

    // auto response = cpr::Get(cpr::Url{ " " });
     //std::cerr << "Ошибка запроса -> " << response.error.message << std::endl;
     //response.~Response();
     //if (&response != nullptr) std::cout << "response = nullptr" << std::endl; //*/

            std::cout << "Конец программы zzz!" << std::endl;
            std::getchar();
            return 0;// EXIT_SUCCESS;
        
}
