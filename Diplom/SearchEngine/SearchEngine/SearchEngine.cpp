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

//#pragma setlocale( "Russian" )

// define a struct where to store the scraped data
/*struct IndustryCard
{
    std::string image;
    std::string url;
    std::string name;
};*/


// UTF8 -> UTF16 conversion
std::wstring toUTF16(const std::string& input)
{
    // get length
    int length = MultiByteToWideChar(CP_UTF8, NULL,
        input.c_str(), input.size(),
        NULL, 0);
    if (!(length > 0))
        return std::wstring();
    else
    {
        std::wstring result;
        result.resize(length);

        if (MultiByteToWideChar(CP_UTF8, NULL,
            input.c_str(), input.size(),
            &result[0], result.size()) > 0)
            return result;
        else
            throw std::runtime_error("Failure to execute toUTF16: conversion failed.");
    }
}


std::wstring ToLower(std::string string) {
    std::wstring ws = std::filesystem::path(string).native();
    std::wstring outWs;
    std::string outS;

    for (wchar_t wc : ws) {

        unsigned int c = (unsigned int)wc;
        switch (c) {
        case L'A': outWs += 'a'; break;
        case L'B': outWs += 'b'; break;
        case L'C': outWs += 'c'; break;
        case L'D': outWs += 'd'; break;
        case L'E': outWs += 'e'; break;
        case L'F': outWs += 'f'; break;
        case L'G': outWs += 'g'; break;
        case L'H': outWs += 'h'; break;
        case L'I': outWs += 'i'; break;
        case L'J': outWs += 'j'; break;
        case L'K': outWs += 'k'; break;
        case L'L': outWs += 'l'; break;
        case L'M': outWs += 'm'; break;
        case L'N': outWs += 'n'; break;
        case L'O': outWs += 'o'; break;
        case L'P': outWs += 'p'; break;
        case L'Q': outWs += 'q'; break;
        case L'R': outWs += 'r'; break;
        case L'S': outWs += 's'; break;
        case L'T': outWs += 't'; break;
        case L'U': outWs += 'u'; break;
        case L'V': outWs += 'v'; break;
        case L'W': outWs += 'w'; break;
        case L'X': outWs += 'x'; break;
        case L'Y': outWs += 'y'; break;
        case L'Z': outWs += 'z'; break;

        case L'А': outWs += L'а'; break;
        case L'Б': outWs += L'б'; break;
        case L'В': outWs += L'в'; break;
        case L'Г': outWs += L'г'; break;
        case L'Д': outWs += L'д'; break;
        case L'Е': outWs += L'е'; break;
        case L'Ж': outWs += L'ж'; break;
        case L'З': outWs += L'з'; break;
        case L'И': outWs += L'и'; break;
        case L'Й': outWs += L'й'; break;
        case L'К': outWs += L'к'; break;
        case L'Л': outWs += L'л'; break;
        case L'Н': outWs += L'н'; break;
        case L'М': outWs += L'м'; break;
        case L'О': outWs += L'о'; break;
        case L'П': outWs += L'п'; break;
        case L'Р': outWs += L'р'; break;
        case L'С': outWs += L'с'; break;
        case L'Т': outWs += L'т'; break;
        case L'У': outWs += L'у'; break;
        case L'Ф': outWs += L'ф'; break;
        case L'Х': outWs += L'х'; break;
        case L'Ц': outWs += L'ц'; break;
        case L'Ч': outWs += L'ч'; break;
        case L'Ш': outWs += L'ш'; break;
        case L'Щ': outWs += L'щ'; break;
        case L'Ь': outWs += L'ь'; break;
        case L'Ъ': outWs += L'ъ'; break;
        case L'Ы': outWs += L'ы'; break;
        case L'Э': outWs += L'э'; break;
        case L'Ю': outWs += L'ю'; break;
        case L'Я': outWs += L'я'; break;
        default: {
            outWs += wc; break;
        }
        }
    }

    //string = std::filesystem::path(outWs).string();
    return outWs;
}


void parseStory(xmlDocPtr doc, xmlNodePtr cur);
void parseHTML(const xmlXPathContextPtr& context, std::string& returnString);
std::string removeParser(std::wstring a, int& const min, int& const max);
std::string wordsPars(std::wstring a, int& const min, int& const max);

#include "ShellAPI.h"
#include <windows.h>
//#pragma comment(lib,"shell32")


/*/namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;*/           // from <boost/asio/ip/tcp.hpp>

std::string all_text;// = "";

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


        // define the user agent for the GET request
        cpr::Header headers = { {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"} };
        // make the HTTP request to retrieve the target page
       
        cpr::Response response = cpr::Get(cpr::Url{html_start}, headers);
        //cpr::Response response = cpr::Get(cpr::Url{ "https://www.mashine.com/" }, headers);
        /*if (response.status_code == 0) {
            //std::cerr << response.error.message << std::endl;
            throw "Error: " + response.error.message;
        }
        else*/
        if (response.status_code >= 400) {
            //std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
            er = "Error [";
            er += response.status_code;
            er += "] making request";
            throw er;
        }
       
        setlocale(LC_ALL, "ru_RU.UTF8");
        // parse the HTML document returned by the server
        //htmlDocPtr doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, nullptr, HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
        htmlDocPtr doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, "utf-8", HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
        // define an array to store all retrieved data
        //std::vector<IndustryCard> industry_cards;
        std::vector<std::string> links;
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

        // initialize the CSV output file
        std::ofstream csv_file("output.csv");
        // write the CSV header
        csv_file << "Total links found:  "<< links.size() << std::endl;

        // poupulate the CSV output file
        for (std::string ref : links)
        {
            csv_file << ref << std::endl;
        }

        // free up the file resources
        csv_file.close();

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

    
        xact.exec("INSERT INTO Pages(Links) "
            "VALUES('" + html_start + "');");
        xact.commit();

        //ShellExecute(0, 0, L"http://www.google.com", 0, 0, SW_SHOWNORMAL);//SW_SHOW);
        std::cout << "ALL TEXT: " << all_text << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        int min = 1;
        int max = 33;

        //std::string res;
        //std::string  res(const wchar_t* s);
        //std::cout << "WANT TEXT: " << removeParser(toUTF16(all_text), min, max) << std::endl;

        //std::cout << "WANT TEXT: " << removeParser(ToLower(all_text), min, max) << std::endl;


        std::stringstream words(removeParser(ToLower(all_text), min, max));
        while (words >> p)
        {
            m[p]++;
        }

        for (auto e : m)
        {
            std::cout << e.first << " --> " << e.second << "\n";
        }

        

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



void parseStory(htmlDocPtr doc, xmlNodePtr cur) {
    xmlChar* key;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        //if ((!xmlStrcmp(cur->name, (const xmlChar*)"keyword"))) {
            key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

            //auto v = cur->content;
            //xmlChar* key1 = xmlNodeListGetString(doc1, cur->xmlChildrenNode, 1);
            //fprintf(v, "cont");
            //printf("keyword: %s\n", v);
            
            //if(v) xmlFree(v);

            printf("keyword: %s\n", key);
            
           if(key){
               std::string strok(reinterpret_cast<char*>(key));
               //key = _strdup(strok);
               all_text += " " + strok;
               xmlFree(key);
           }
        cur = cur->next;
    }
   // return;
}


void parseHTML(const xmlXPathContextPtr& context, std::string& returnString) {
    // �������������� ������ HTML
    /*htmlDocPtr doc = htmlReadMemory(html.c_str(), html.size(), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == NULL) {
        std::cerr << "Failed to parse HTML" << std::endl;
        return;
    }*/

    // ��������� ������ XPath ��� ���������� ������
    //xmlChar* xpath = (xmlChar*)"lower-case(//text(), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ','abcdefghijklmnopqrstuvwxyz')";
    //xmlChar* xpath = (xmlChar*)"translate(//text(), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ','abcdefghijklmnopqrstuvwxyz')";
    xmlChar* xpath = (xmlChar*)"//text()";
    //xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);

    if (result != NULL) {
        xmlNodeSetPtr nodes = result->nodesetval;
        for (int i = 0; i < nodes->nodeNr; ++i) {
            xmlNodePtr node = nodes->nodeTab[i];
            if (node->type == XML_TEXT_NODE) {
                xmlChar* content = xmlNodeGetContent(node);
                returnString += (const char*)content;

                xmlFree(content);
            }
        }
        xmlXPathFreeObject(result);
    }
    else std::cout << "NOT FINDE NODE" << std::endl;// << all_text << std::endl;
    // ����������� �������
    //xmlXPathFreeContext(context);
    //xmlFreeDoc(doc);
}

std::string removeParser(std::wstring a, int& const min, int& const max) {
    std::wstring resalt;
    int size_string = a.length();
    bool space = true;
    int n = 0;
    wchar_t c;
    std::locale loc1("ru_RU.UTF8");
    std::locale loc2("en_US.UTF8");
    for (int i = 0; i < size_string; i++) {
        
       // c = (wchar_t)a[i];
        if (isalpha(a[i], loc1)) {
            resalt += a[i];// towlower(a[i]);
            space = true;
            //n++;
        }
        else {
            if (space) {
                /*if ((n = min) || (n >= max)) {
                    resalt.erase(resalt.begin() + (i-n), resalt.begin() + (i));
                   
                }
                n = 0;*/
                resalt += L" ";
                space = false;
            }
        }
    }



    return std::filesystem::path(resalt).string();
}

std::string wordsPars(std::string& const a, int& const min, int& const max) {
    //setlocale(LC_ALL, "ru_RU.UTF-8");
    const std::string separators{ " ,;:.\"!?'*\n" };
    //const std::string separators{ " ,/\n" };
    std::vector<std::string> words; // ������ ��� �������� ����
    //const std::string s2(a.begin(), a.end());
    size_t start{ a.find_first_not_of(separators) }; // ��������� ������ ������� �����
    while (start != std::string::npos) // ��������, ���� � ������ �� �������� ������ ��������, ����� separators
    {
        size_t end = a.find_first_of(separators, start + 1); // �������, ��� ��������� �����
        if (end == std::string::npos) // ���� �� ������ �� ���� �� ��������-������������
            end = a.length();        // ������������� ���������� end �� ����� ������
        words.push_back(a.substr(start, end - start)); // ��������� � ������ �����
        start = a.find_first_not_of(separators, end + 1); // ������� ��������� ������ ���������� ����� � ����������������� start
    }
    std::string all_words;
    for (const auto& word : words)
    {
        all_words += word;
        all_words += ' ';
     
    }
    //all_words += '!';
    return all_words;
}