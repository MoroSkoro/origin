#include "../../include/sch_engine/processing_functions.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>

/*#include "cpr/cpr.h"
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

//UTF8 -> UTF16 conversion
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


void parseHTML(const xmlXPathContextPtr& context, std::string& returnString) {
    // �������������� ������ HTML*/
    /*htmlDocPtr doc = htmlReadMemory(html.c_str(), html.size(), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (doc == NULL) {
        std::cerr << "Failed to parse HTML" << std::endl;
        return;
    }*/

    // ��������� ������ XPath ��� ���������� ������
    //xmlChar* xpath = (xmlChar*)"lower-case(//text(), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ','abcdefghijklmnopqrstuvwxyz')";
    //xmlChar* xpath = (xmlChar*)"translate(//text(), 'ABCDEFGHIJKLMNOPQRSTUVWXYZ','abcdefghijklmnopqrstuvwxyz')";
   /* xmlChar* xpath = (xmlChar*)"//text()";
    //xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);

    if (result != NULL) {
        xmlNodeSetPtr nodes = result->nodesetval;
        if (nodes) {
            for (int i = 0; i < nodes->nodeNr; ++i) {
                xmlNodePtr node = nodes->nodeTab[i];
                if (node->type == XML_TEXT_NODE) {
                    xmlChar* content = xmlNodeGetContent(node);
                    returnString += (const char*)content;

                    xmlFree(content);
                }
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
    std::wstring resalt, outs, res;
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
//                resalt += L" ";
//                space = false;
//            }
//        }
//    }
//    std::wstringstream words(resalt);
//    while (words >> outs)
//    {
//        if (min < outs.length() and outs.length() < max) {
//            res += outs + L" ";
//        }
//    }
//    return std::filesystem::path(res).string();
//}
//
//
////xz
//
//void parseStory(htmlDocPtr doc, xmlNodePtr cur, std::string& all_text) {
//    xmlChar* key;
//    cur = cur->xmlChildrenNode;
//    while (cur != NULL) {
//        //if ((!xmlStrcmp(cur->name, (const xmlChar*)"keyword"))) {
//        key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
//
//        //auto v = cur->content;
//        //xmlChar* key1 = xmlNodeListGetString(doc1, cur->xmlChildrenNode, 1);
//        //fprintf(v, "cont");
//        //printf("keyword: %s\n", v);
//
//        //if(v) xmlFree(v);
//
//        printf("keyword: %s\n", key);
//
//        if (key) {
//            std::string strok(reinterpret_cast<char*>(key));
//            //key = _strdup(strok);
//            all_text += " " + strok;
//            xmlFree(key);
//        }
//        cur = cur->next;
//    }
//    // return;
//}



//std::string wordsPars(std::string& const a, int& const min, int& const max) {
//    //setlocale(LC_ALL, "ru_RU.UTF-8");
//    const std::string separators{ " ,;:.\"!?'*\n" };
//    //const std::string separators{ " ,/\n" };
//    std::vector<std::string> words; // ������ ��� �������� ����
//    //const std::string s2(a.begin(), a.end());
//    size_t start{ a.find_first_not_of(separators) }; // ��������� ������ ������� �����
//    while (start != std::string::npos) // ��������, ���� � ������ �� �������� ������ ��������, ����� separators
//    {
//        size_t end = a.find_first_of(separators, start + 1); // �������, ��� ��������� �����
//        if (end == std::string::npos) // ���� �� ������ �� ���� �� ��������-������������
//            end = a.length();        // ������������� ���������� end �� ����� ������
//        words.push_back(a.substr(start, end - start)); // ��������� � ������ �����
//        start = a.find_first_not_of(separators, end + 1); // ������� ��������� ������ ���������� ����� � ����������������� start
//    }
//    std::string all_words;
//    for (const auto& word : words)
//    {
//        all_words += word;
//        all_words += ' ';
//
//    }
//    //all_words += '!';
//    return all_words;
//}

//bool func_pars(std::string& link, std::vector<std::string>& discov, std::vector<std::string>& buffer_links, std::string& all_text) {
//    std::string err{1};
//        bool pars_ok{ true };
//        if (std::find(discov.begin(), discov.end(), link) == discov.end()) {
//            
//            try {
//                cpr::Header headers = { {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"} };
//                htmlDocPtr doc;
//                xmlXPathContextPtr context;
//                std::string const u = link;
//                cpr::Response response = cpr::Get(cpr::Url{ u }, headers);
//                int cod_int = response.status_code;
//                std::string cod_str = std::to_string(cod_int);
//                if ((cod_int >= 400) || (cod_int == 500)) {
//                    err = "Error [";
//                    err += cod_str;
//                    err += "] response status code";
//                    std::cerr << "Ошибка запроса -> " << response.error.message << std::endl;
//                    throw err;
//                }
//                doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, "utf-8", HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
//                if (doc == NULL) {
//                    err = "Document not parsed successfully.\n";
//                    std::cout << err << std::endl;
//                    throw err;
//                }
//            
//                context = xmlXPathNewContext(doc);
//                if (context) {
//                xmlXPathObjectPtr all_links = xmlXPathEvalExpression((xmlChar*)"//a", context);
//                std::string url{ 1 };
//                // iterate over the list of industry card elements
//                if (all_links && all_links->nodesetval) {
//                    for (int i = 0; i < all_links->nodesetval->nodeNr; i++) {
//                        xmlNodePtr url_html_link = all_links->nodesetval->nodeTab[i];
//                        xmlXPathSetContextNode(url_html_link, context);
//                        if (reinterpret_cast<char*>(xmlGetProp(url_html_link, (xmlChar*)"href"))) {
//                            url = std::string(reinterpret_cast<char*>(xmlGetProp(url_html_link, (xmlChar*)"href")));
//                        }
//                        if ((std::find(discov.begin(), discov.end(), url) == discov.end()) && (url != link)) {
//                            if ((url.starts_with("http")) && (&url != nullptr)) {
//                                buffer_links.push_back(url);
//                                //std::cout << url << std::endl;
//                            }
//                        }
//                    }
//                }
//                parseHTML(context, all_text);
//                xmlXPathFreeObject(all_links);
//                }
//                else {
//                discov.push_back(link);
//                pars_ok = false;
//                }
//                xmlXPathFreeContext(context);
//                xmlFreeDoc(doc);
//            }
//            catch (std::exception const& e)
//            {
//                std::cerr << "Error: " << e.what() << std::endl;
//                return false;
//                //pars_ok = false;
//                //exit;
//            }
//            catch (std::string error_message)
//            {
//                //discov.push_back(link);
//                std::cout << link << std::endl;
//                std::cout << " 222 " << error_message << std::endl;
//                pars_ok = false;
//                return false;
//                
//                //exit;
//            }
//        }
//        else pars_ok = false;
//        return pars_ok;
//}