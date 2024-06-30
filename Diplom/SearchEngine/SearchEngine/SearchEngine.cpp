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
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

#include <vector>
#include <ranges>
#include <map>
#include <sstream>

#include <pqxx/pqxx>
#include <pqxx/connection>
#include <pqxx/transaction>

#include "Resurs/include/sch_engine/processing_functions.h"

#include "ShellAPI.h"
#include <windows.h>
//#pragma comment(lib,"shell32")


/*/namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;*/           // from <boost/asio/ip/tcp.hpp>

//std::string all_text;// = "";

int main()
{
    SetConsoleCP(65001);//1251, 855, 65001
    //SetConsoleOutputCP(855);
    SetConsoleOutputCP(65001);
    //setlocale(LC_ALL, "Russian");
    //system("chcp 1251");
    setlocale(LC_ALL, "ru_RU.UTF8");

    //SetConsoleOutputCP(CP_UTF8);

    std::string p;
    std::map<std::string, int> m;

    std::string BD_host;
    std::string BD_port;
    std::string BD_name;
    std::string BD_user;
    std::string BD_parole;
    std::string html_start = "https://wikipedia.org/"; //"https://ru.wikipedia.org/wiki/";
    std::string html_start1 = "file:///E:/HTML/Simple.html";
    std::string s;
    size_t pars_recurs = 3;
    size_t http_port = 80;
    std::string er{"Error"};
    int id;
    std::string id_str;
    std::vector<std::string> links;
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
        /*"Ссылки VARCHAR(60) NOT NULL DEFAULT 'htpp', "
        "Lastname TEXT NOT NULL DEFAULT 'Voevoda', "
        "Email TEXT UNIQUE)");  //как здесь реалтзовать защиту от SQL инъекций?*/
        xact.exec("CREATE TABLE IF NOT EXISTS Words "
            "(id SERIAL PRIMARY KEY, "
            "Word TEXT UNIQUE)");
        xact.exec("CREATE TABLE IF NOT EXISTS Word_frequency "
            "(id SERIAL PRIMARY KEY, "
            "Pages_id INTEGER NOT NULL REFERENCES Pages, "
            "Words_id   INTEGER NOT NULL REFERENCES Words, "
            "Count INTEGER, "
            "UNIQUE(Pages_id, Words_id));");
        xact.commit();

        // define the user agent for the GET request
        cpr::Header headers = { {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"} };
        // make the HTTP request to retrieve the target page
       
        cpr::Response response = cpr::Get(cpr::Url{html_start}, headers);
        
        if (response.status_code >= 400) {
            //std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
            er = "Error [";
            er += response.status_code;
            er += "] making request";
            throw er;
        }
       
       
        // parse the HTML document returned by the server
        //htmlDocPtr doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, nullptr, HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
        htmlDocPtr doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, "utf-8", HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
        // define an array to store all retrieved data
        //std::vector<IndustryCard> industry_cards;
        
        // set the libxml2 context to the current document
        xmlXPathContextPtr context = xmlXPathNewContext(doc);
        // select all industry card HTML elements
        // with an XPath selector
        //xmlXPathObjectPtr industry_card_html_elements = xmlXPathEvalExpression((xmlChar*)"//div[contains(@class, 'section_cases_row_col_item')]", context);
        xmlXPathObjectPtr all_links = xmlXPathEvalExpression((xmlChar*)"//a/@href", context);

        // iterate over the list of industry card elements
        for (int i = 0; i < all_links->nodesetval->nodeNr; ++i)
        {
            // get the current element of the loop
            xmlNodePtr all_link = all_links->nodesetval->nodeTab[i];
            // set the libxml2 context to the current element
            // to limit the XPath selectors to its children
            xmlXPathSetContextNode(all_link, context);

            xmlNodePtr url_html_link = xmlXPathEvalExpression((xmlChar*)"//a", context)->nodesetval->nodeTab[0];
            std::string url = std::string(reinterpret_cast<char*>(xmlGetProp(url_html_link, (xmlChar*)"href")));

            /*xmlNodePtr image_html_element = xmlXPathEvalExpression((xmlChar*)".//figure/a/img", context)->nodesetval->nodeTab[0];
            std::string image = std::string(reinterpret_cast<char*>(xmlGetProp(image_html_element, (xmlChar*)"data-lazy-src")));

            xmlNodePtr url_html_element = xmlXPathEvalExpression((xmlChar*)".//figure/a", context)->nodesetval->nodeTab[0];
            std::string url = std::string(reinterpret_cast<char*>(xmlGetProp(url_html_element, (xmlChar*)"href")));

            xmlNodePtr name_html_element = xmlXPathEvalExpression((xmlChar*)".//div[contains(@class, 'elementor-image-box-title')]/a", context)->nodesetval->nodeTab[0];
            std::string name = std::string(reinterpret_cast<char*>(xmlNodeGetContent(name_html_element)));*/

            // instantiate an IndustryCard struct with the collected data
            //IndustryCard industry_card = { image, url, name };

            // add the object with the scraped data to the vector
            links.push_back(url);
        }
        
        parseHTML(context, all_text);

        xmlNodePtr cur;
        //xmlDoc* doc2 = NULL;
        //xmlNode* root_element = NULL;

        //doc1 = doc;// htmlParseFile(response.text.c_str(), "UTF - 8"); //xmlParseFile(response.text.c_str());
        if (doc == NULL) {
            er = "Document not parsed successfully.\n";
            throw er;
            //fprintf(stderr, "Document not parsed successfully.\n");
            //return 1;
        }

        cur = xmlDocGetRootElement(doc);

        if (cur == NULL) {
            er = "empty document\n";
            throw er;
            fprintf(stderr, "empty document\n");
            return 1;
        }

        
        cur = cur->xmlChildrenNode;
            while (cur != NULL) {
                //if ((!xmlStrcmp(cur->name, (const xmlChar*)"storyinfo"))) {
                //parseStory(doc, cur);
                //}
                //auto v = cur->content;
                //xmlChar* key1 = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                //fprintf(v, "cont");
                //printf("keyword: %s\n", key1);
                //if (v!=NULL) xmlFree(v);

                cur = cur->next;
            }


        // free up the resource allocated by libxml2
        xmlXPathFreeObject(all_links);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        
        pqxx::work xact1(c);

       auto r = xact1.exec("INSERT INTO Pages(Links) "
           "VALUES('" + xact1.esc(html_start) + "') on conflict (Links) do nothing RETURNING id;");
       if (r.empty()){r = xact1.exec("SELECT id FROM Pages WHERE Links = '" + xact1.esc(html_start) + "';"); }
       //pqxx::result::const_iterator ptr = r.begin();
       std::string pages_id_str = (r[0][0].as<std::string>());
       
        //std::cout << "ALL TEXT: " << all_text << std::endl;
        //std::cout << std::endl;
        std::cout << std::endl;

        //std::cout << "WANT TEXT: " << removeParser(toUTF16(all_text), min, max) << std::endl;
        //std::cout << "WANT TEXT: " << removeParser(ToLower(all_text), min, max) << std::endl;

        std::stringstream words(removeParser(ToLower(all_text), min, max));
        while (words >> p)
        {
            m[p]++;
        }

        for (auto e : m)
        {
            r = xact1.exec("INSERT INTO Words(Word) "
                "VALUES('" + xact1.esc(e.first) + "') on conflict (Word) do nothing RETURNING id;");
            if (r.empty()){ r = xact1.exec("SELECT id FROM Words WHERE Word = '" + xact1.esc(e.first) + "';"); }
            std::string words_id_str = (r[0][0].as<std::string>());
            std::string preobraz{std::to_string(e.second)};
            xact1.exec("INSERT INTO Word_frequency(Pages_id, Words_id, Count) "
                "VALUES(" + xact1.esc(pages_id_str) + ", " + xact1.esc(words_id_str) + ", " + xact1.esc(preobraz) + ") on conflict (Pages_id, Words_id) do nothing;");
            std::cout << e.first << " --> " << e.second << "\n";
        }

        xact1.commit();
        c.close();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;// EXIT_FAILURE;
    }
    catch (std::string error_message)
    {
        std::cout << error_message << std::endl;
    }
    
    

    std::getchar();
    return 0;// EXIT_SUCCESS;
}
