
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
#include "Resurs/include/BS_thread_pool.hpp"
#include <future>

#include "ShellAPI.h"
#include <windows.h>

BS::thread_pool pool;


int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF8");

    //std::string p;
    //std::map<std::string, int> m;

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
    std::vector<std::string> buffer_links_for_all;
    buffer_links_for_all.reserve(rep);
    size_t current_recurs = 0;
    size_t number_sites_verified = 50;
    int min = 3;
    int max = 33;
    //mutable
    std::mutex t_mutex = {};
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
        unsigned short N{1};
        while (!links_to_scrape.empty() && (current_recurs < pars_recurs)) {
            //while (!links_to_scrape.empty()) {
            while (N>0) {
                if (current_recurs == 0) { std::cout << "Pleas wait..." << std::endl; }
                std::cout << "while = " << f << std::endl; f++;
                const std::future<void> my_future = pool.submit_task(
                    [&]{
                        std::string link;
                        {
                            const std::scoped_lock tasks_lock(t_mutex);
                            link = links_to_scrape.at(0);
                            links_to_scrape.erase(links_to_scrape.begin());
                        }
                        std::string all_text;
                        std::vector<std::string> buffer_links{};
                        std::vector<std::string> del_already_verified{};
                        std::string p;
                        std::map<std::string, int> m;
                        if (func_pars(link, buffer_links, all_text)) {

                            //if (all_text[0] != '0') {
                            if (!all_text.empty()) {
                                pqxx::work xact1(c);
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
                        }
                        {
                            const std::scoped_lock tasks_lock(t_mutex);
                            discovered_links.emplace_back(link);
                        }
                        if (current_recurs < (pars_recurs - 1)) {
                            {
                                const std::scoped_lock tasks_lock(t_mutex);
                                for (auto stroc : buffer_links) {
                                    if ((std::find(discovered_links.begin(), discovered_links.end(), stroc) == discovered_links.end())) {
                                        if (stroc.starts_with("http")) {
                                            del_already_verified.emplace_back(stroc);
                                        }
                                    }
                                }
                                //buffer_links.clear();
                                buffer_links_for_all.insert(buffer_links_for_all.end(), del_already_verified.begin(), del_already_verified.end());
                            }
                        }
                    });
                if (N > 0) --N;
                //if (pool.get_tasks_running() > 100) {
                if (f > number_sites_verified) {
                    current_recurs = pars_recurs;
                    break;
                }  
            }
            pool.wait();
            ++current_recurs;
            if (current_recurs < pars_recurs) {
                    if (!buffer_links_for_all.empty()) {
                        std::cout << "links_to_scrape = buffer_links_for_all;" << std::endl;
                        std::cout << "Size buffer_links_for_all - " << (N = buffer_links_for_all.size()) << std::endl;
                        for (auto stroc : buffer_links_for_all) {
                            if ((std::find(discovered_links.begin(), discovered_links.end(), stroc) == discovered_links.end())) {
                                if (stroc.starts_with("http")) {
                                    links_to_scrape.emplace_back(stroc);
                                }
                            }
                        }
                        //links_to_scrape = buffer_links_for_all;
                        buffer_links_for_all.clear();
                    }
            }
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

     std::cout << "Конец программы zzz!" << std::endl;
     std::getchar();
     return 0;// EXIT_SUCCESS;
        
}
