#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cstring>
#include <future>
#include <vector>
#include <json/json.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<float> getdatalow(std::string url){
    CURL *curl;
    CURL *multi_curl;
    CURLMcode res;
    std::string readBuffer;
    int still_running = 1;
    multi_curl = curl_multi_init();
    curl = curl_easy_init();
    std::vector<float> _templist;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_multi_add_handle(multi_curl, curl);
        while(still_running != 0){
            res = curl_multi_perform(multi_curl, &still_running);
        }
        curl_multi_remove_handle(multi_curl, curl);
        curl_easy_cleanup(curl);
        Json::Value jsondata;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(readBuffer, jsondata);
        if ( !parsingSuccessful )
        {
            std::cout << "Error parsing the string" << std::endl;
        }
        Json::Value listlow = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["low"];
        int i = 0;
        while(listlow[i])
        {
            _templist.push_back(listlow[i].asFloat());
            i++;
        }
        return(_templist);
    }
    return(_templist);
}

std::vector<float> getdatahigh(std::string url){
    CURL *curl;
    CURL *multi_curl;
    CURLMcode res;
    std::string readBuffer;
    int still_running = 1;
    multi_curl = curl_multi_init();
    curl = curl_easy_init();
    std::vector<float> _templist;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_multi_add_handle(multi_curl, curl);
        while(still_running != 0){
            res = curl_multi_perform(multi_curl, &still_running);
        }
        curl_multi_remove_handle(multi_curl, curl);
        curl_easy_cleanup(curl);
        Json::Value jsondata;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(readBuffer, jsondata);
        if ( !parsingSuccessful )
        {
            std::cout << "Error parsing the string" << std::endl;
        }
        Json::Value listlow = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["high"];
        int i = 0;
        while(listlow[i])
        {
            _templist.push_back(listlow[i].asFloat());
            i++;
        }
        return(_templist);
    }
    return(_templist);
}

std::vector<float> getdataclose(std::string url){
    CURL *curl;
    CURL *multi_curl;
    CURLMcode res;
    std::string readBuffer;
    int still_running = 1;
    multi_curl = curl_multi_init();
    curl = curl_easy_init();
    std::vector<float> _templist;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_multi_add_handle(multi_curl, curl);
        while(still_running != 0){
            res = curl_multi_perform(multi_curl, &still_running);
        }
        curl_multi_remove_handle(multi_curl, curl);
        curl_easy_cleanup(curl);
        Json::Value jsondata;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(readBuffer, jsondata);
        if ( !parsingSuccessful )
        {
            std::cout << "Error parsing the string" << std::endl;
        }
        Json::Value listlow = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["close"];
        int i = 0;
        while(listlow[i])
        {
            _templist.push_back(listlow[i].asFloat());
            i++;
        }
        return(_templist);
    }
    return(_templist);
}

std::vector<float> getdataopen(std::string url){
    CURL *curl;
    CURL *multi_curl;
    CURLMcode res;
    std::string readBuffer;
    int still_running = 1;
    multi_curl = curl_multi_init();
    curl = curl_easy_init();
    std::vector<float> _templist;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_multi_add_handle(multi_curl, curl);
        while(still_running != 0){
            res = curl_multi_perform(multi_curl, &still_running);
        }
        curl_multi_remove_handle(multi_curl, curl);
        curl_easy_cleanup(curl);
        Json::Value jsondata;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(readBuffer, jsondata);
        if ( !parsingSuccessful )
        {
            std::cout << "Error parsing the string" << std::endl;
        }
        Json::Value listlow = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["open"];
        int i = 0;
        while(listlow[i])
        {
            _templist.push_back(listlow[i].asFloat());
            i++;
        }
        return(_templist);
    }
    return(_templist);
}

int main(void)
{  
    std::string stockname;
    std::cout << "Enter the name of stock: ";
    std::cin >> stockname;
    std::string url = "https://query1.finance.yahoo.com/v8/finance/chart/" + stockname + "?interval=1m";
    time_t start, end;
    double elapsed, prev_elapsed = 0.0;
    time(&start);
    do
    {
        time(&end);
        elapsed = difftime(end, start);
        if (elapsed >= prev_elapsed+2.0)
            {
                std::vector <float> listhigh = getdatahigh(url);
                std::vector <float> listclose = getdataclose(url);
                std::vector <float> listopen = getdataopen(url);
                std::vector <float> listlow = getdatalow(url);
                system("clear");
                std::cout << "|  open: | close: |  low: |  high: |" << std::endl;
                std::cout << "| " << listopen.back() << " | " << listclose.back() << " | " << listlow.back() << " | " << listhigh.back()<< " |" << std::endl;
                std::cout << std::endl;
                std::cout << "enter something" << std::endl;
                prev_elapsed = elapsed;
            }
    } while(1 == 1);
}