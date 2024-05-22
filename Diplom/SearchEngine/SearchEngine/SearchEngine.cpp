/*#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>*/
#include <cstdlib>
#include <iostream>
#include <string>

#include "cpr/cpr.h"
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

#include <vector>

// define a struct where to store the scraped data
struct IndustryCard
{
    std::string image;
    std::string url;
    std::string name;
};

void parseStory(xmlDocPtr doc, xmlNodePtr cur);
void parseHTML(const xmlXPathContextPtr& context, std::string& returnString);

#include "ShellAPI.h"
#include <windows.h>
//#pragma comment(lib,"shell32")


/*/namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;*/           // from <boost/asio/ip/tcp.hpp>

std::string all_text = "";

int main()
{
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.UTF-8");


    
    try
    {
       
        // define the user agent for the GET request
        cpr::Header headers = { {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"} };
        // make the HTTP request to retrieve the target page
        //cpr::Response response = cpr::Get(cpr::Url{ "https://wikipedia.org/" }, headers);
        //cpr::Response response = cpr::Get(cpr::Url{ "https://www.mashine.com/" }, headers);
        cpr::Response response = cpr::Get(cpr::Url{ "file:///E:/HTML/Simple.html" }, headers);
        /*if (response.status_code == 0) {
            //std::cerr << response.error.message << std::endl;
            throw "Error: " + response.error.message;
        }
        else*/
        if (response.status_code >= 400) {
            //std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
            std::string er = "Error [";
            er += response.status_code;
            er += "] making request";
            throw er;
        }
       

        // parse the HTML document returned by the server
        htmlDocPtr doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, nullptr, HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);

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


        
        void parseHTML(const xmlXPathContextPtr & context, std::string & all_text);

        xmlNodePtr cur;
        //xmlDoc* doc2 = NULL;
        //xmlNode* root_element = NULL;

        //doc1 = doc;// htmlParseFile(response.text.c_str(), "UTF - 8"); //xmlParseFile(response.text.c_str());
        if (doc == NULL) {
            fprintf(stderr, "Document not parsed successfully.\n");
            return 1;
        }

        cur = xmlDocGetRootElement(doc);

        if (cur == NULL) {
            fprintf(stderr, "empty document\n");
            //xmlFreeDoc(doc1);
            return 1;
        }

        /*if (xmlStrcmp(cur->name, (const xmlChar*)"story")) {
            fprintf(stderr, "document of the wrong type, root node != story");
            xmlFreeDoc(doc1);
            return;
        }*/
        //xmlChar* v;
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


        // Gracefully close the socket
        //beast::error_code ec;
        
        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        //if (0);// (ec && ec != beast::errc::not_connected)
            //throw beast::system_error{ ec };

        // If we get here then the connection is closed gracefully
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
    
    //ShellExecute(0, 0, L"http://www.google.com", 0, 0, SW_SHOWNORMAL);//SW_SHOW);
    std::cout << "ALL TEXT: " << all_text << std::endl;
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
    // Инициализируем парсер HTML
    /*htmlDocPtr doc = htmlReadMemory(html.c_str(), html.size(), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == NULL) {
        std::cerr << "Failed to parse HTML" << std::endl;
        return;
    }*/

    // Выполняем запрос XPath для извлечения текста
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

    // Освобождаем ресурсы
    //xmlXPathFreeContext(context);
    //xmlFreeDoc(doc);
}