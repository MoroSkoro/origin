/*#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>*/
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <locale>

#include "cpr/cpr.h"
#include "libxml/htmlparser.h"
#include "libxml/xpath.h"

#include <vector>
#include <ranges>
#include <map>
#include <sstream>

#include <pqxx/pqxx>
#include <pqxx/connection>
#include <pqxx/transaction>
#include <thread>

//#include "Resurs/include/sch_engine/processing_functions.h"

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
    std::string html_start1 = "file:///E:/HTML/Simple.html"; //"https://wikipedia.org"; //"https://www.google.com";//  https://meta.wikimedia.org/wiki/Special:MyLanguage/List_of_Wikipedias";
    std::string s;
    size_t pars_recurs = 1;
    size_t http_port = 80;
    std::string er{"Error"};
    int id;
    std::string id_str;
    std::vector<std::string> links_to_scrape{};
    std::vector<std::string> discovered_links{};
    std::vector<std::string> buffer_links{};
    size_t current_recurs = 0;
    std::string all_text;
    int min = 3;
    int max = 33;
    
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
            std::cout << pars_recurs << std::endl;
        }
        else {
            er = "Failed to read file SearchEngine.ini";
            throw er;
        }
        ini.close();

        if (fout.is_open())
        {
            fout << BD_host << std::endl;
            fout << BD_port << std::endl;
            fout << BD_name << std::endl;
            fout << BD_user << std::endl;
            fout << BD_parole << std::endl;
            fout << html_start << std::endl;
            fout << pars_recurs << std::endl;
            fout << http_port << std::endl;
        }
        else {
            er = "Failed to write file output.txt";
            throw er;
        }
        fout.close();

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
        links_to_scrape.push_back(html_start);
        int f = 0;
        while (!links_to_scrape.empty() && (current_recurs < pars_recurs)) {
            // define the user agent for the GET request

            std::string link{};
            link = links_to_scrape.at(0);
            links_to_scrape.erase(links_to_scrape.begin());
            if (current_recurs == 0) { std::cout << "Pleas wait..." << std::endl; }
            //func
            std::cout << "while = " << f << std::endl;


            const cpr::Header headers = { {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"} };
            //link = "https://play.google.com/store/apps/details?id=org.wikipedia&referrer=utm_source%3Dportal%26utm_medium%3Dbutton%26anid%3Dadmob";

            const cpr::Response r = cpr::Get(cpr::Url{ link }, headers);
            std::cout << "Status code: " << r.status_code << '\n';
            std::cout << "Header:\n";
            for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
                std::cout << '\t' << kv.first << ':' << kv.second << '\n';
            }
            std::cout << "Text: " << r.text << '\n';
            htmlDocPtr doc;
            xmlXPathContextPtr context;
           doc = htmlReadMemory(r.text.c_str(), r.text.length(), nullptr, "utf-8", HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
            if (doc == NULL) {
                er = "Document not parsed successfully.\n";
                std::cout << er << std::endl;
                throw er;
            }

            context = xmlXPathNewContext(doc);
            if (context) {
                xmlXPathObjectPtr all_links = xmlXPathEvalExpression((xmlChar*)"//a", context);
                std::string url{ 1 };
                // iterate over the list of industry card elements
                if (all_links && all_links->nodesetval) {
                    for (int i = 0; i < all_links->nodesetval->nodeNr; i++) {
                        xmlNodePtr url_html_link = all_links->nodesetval->nodeTab[i];
                        xmlXPathSetContextNode(url_html_link, context);
                        if (reinterpret_cast<char*>(xmlGetProp(url_html_link, (xmlChar*)"href"))) {
                            url = std::string(reinterpret_cast<char*>(xmlGetProp(url_html_link, (xmlChar*)"href")));
                        }
                        if ((std::find(discovered_links.begin(), discovered_links.end(), url) == discovered_links.end()) && (url != link)) {
                            if ((url.starts_with("http")) && (&url != nullptr)) {
                                buffer_links.push_back(url);
                                //std::cout << url << std::endl;
                            }
                        }
                    }
                }
                //parseHTML(context, all_text);
                xmlXPathFreeObject(all_links);
            }
            else {
                discovered_links.push_back(link);
                //pars_ok = false;
            }
            xmlXPathFreeContext(context);
            xmlFreeDoc(doc);

            /*тут1
                if (func_pars(link, discovered_links, buffer_links, all_text)) {
                     std::cout << "pars_ok = true" << std::endl;
                     std::cout << "while = " << f << std::endl;
                     if (all_text[0] != '0') {
                         pqxx::work xact1(c);
                                     //std::cout << "Текущая ссылка: " << link << std::endl;
                         auto r = xact1.exec("INSERT INTO Pages(Links) "
                             "VALUES('" + xact1.esc(link) + "') on conflict (Links) do nothing RETURNING id;");
                         if (r.empty()) { r = xact1.exec("SELECT id FROM Pages WHERE Links = '" + xact1.esc(link) + "';"); }
                                     //pqxx::result::const_iterator ptr = r.begin();
                         std::string pages_id_str = (r[0][0].as<std::string>());
                         xact1.commit();

                         std::stringstream words(removeParser(ToLower(all_text), min, max));
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
                 discovered_links.push_back(link);
                 if (current_recurs <= pars_recurs) {

                     if (links_to_scrape.empty()) {
                         //if (!buffer_links.empty()) {
                         std::cout << "pars_ok = false" << std::endl;
                             links_to_scrape = buffer_links;
                             buffer_links.clear();
                         //}
                         ++current_recurs;
                     }
                 }
                 std::cout << "while = true" << std::endl; f++;
            }
             std::cout << "while = false" << std::endl;
             c.close();*/ //тут1
        }
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

            std::cout << "Конец программы!" << std::endl;
            std::getchar();
            return 0;// EXIT_SUCCESS;
        
}
