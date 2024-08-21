#include "../../include/sch_engine/processing_functions.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>

std::wstring toUTF16(const std::string& input)
{
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
    xmlChar* xpath = (xmlChar*)"//text()";
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
}


std::string removeParser(std::wstring a, int& const min, int& const max) {
    std::wstring resalt, outs, res;
    int size_string = a.length();
    bool space = true;
    wchar_t c;
    std::locale loc1("ru_RU.UTF8");
    std::locale loc2("en_US.UTF8");
    for (int i = 0; i < size_string; i++) {

        // c = (wchar_t)a[i];
        if (isalpha(a[i], loc1)) {
            resalt += a[i];// towlower(a[i]);
            space = true;
        }
        else {
            if (space) {
                resalt += L" ";
                space = false;
            }
        }
    }
    std::wstringstream words(resalt);
    while (words >> outs)
    {
        if (min < outs.length() and outs.length() < max) {
            res += outs + L" ";
        }
    }
    return std::filesystem::path(res).string();
}


bool func_pars(std::string& link, std::vector<std::string>& buffer_links, std::string& all_text) {
    std::string err{1};
        bool pars_ok{ true };
            try {
                cpr::Header headers = { {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"} };
                htmlDocPtr doc;
                xmlXPathContextPtr context;
                std::string const u = link;
                cpr::Response response = cpr::Get(cpr::Url{ u }, headers);
                int cod_int = response.status_code;
                //std::cout << "CPR cod = " << cod_int << std::endl;
                std::string cod_str = std::to_string(cod_int);
                if (cod_int >= 400) {
                    err = "Error [";
                    err += cod_str;
                    err += "] response status code";
                    std::cerr << "Ошибка запроса -> " << response.error.message << std::endl;
                    throw err;
                }
                doc = htmlReadMemory(response.text.c_str(), response.text.length(), nullptr, "utf-8", HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);
                if (doc == NULL) {
                    err = "Document not parsed successfully.\n";
                    std::cout << err << std::endl;
                    throw err;
                }
                
                context = xmlXPathNewContext(doc);
                if (context){
                    xmlXPathObjectPtr all_links = xmlXPathEvalExpression((xmlChar*)"//a", context);
                    std::string url{ 1 };
                    if (all_links && all_links->nodesetval){
                        for (int i = 0; i < all_links->nodesetval->nodeNr; i++){
                            xmlNodePtr url_html_link = all_links->nodesetval->nodeTab[i];
                            xmlXPathSetContextNode(url_html_link, context);
                            if (reinterpret_cast<char*>(xmlGetProp(url_html_link, (xmlChar*)"href"))){
                                url = std::string(reinterpret_cast<char*>(xmlGetProp(url_html_link, (xmlChar*)"href")));
                            }
                            buffer_links.emplace_back(url);
                        }
                    }
                    parseHTML(context, all_text);
                    xmlXPathFreeObject(all_links);
                    xmlXPathFreeContext(context);
                    xmlFreeDoc(doc);
                }
                else {
                //discov.push_back(link);
                    xmlFreeDoc(doc);
                    pars_ok = false;
                }
                
            }
            catch (std::exception const& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
                return false;
            }
            catch (std::string error_message)
            {
                std::cout << error_message << std::endl;
                std::cout << "По ссылке: " << link << std::endl;
                pars_ok = false;
            }
        
        return pars_ok;
}