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

int main()
{
    std::string url = "\"https://query1.finance.yahoo.com/v8/finance/chart/TSLA?interval=1m\"";
    std::string url1 = "https://query1.finance.yahoo.com/v8/finance/chart/TSLA?interval=1m";
    std::cout << url << std::endl;
    std::cout << url1 << std::endl;
    CURL *curl;
    CURL *multi_curl;
    CURLMcode res;
    std::string readBuffer;
    int still_running = 1;
    multi_curl = curl_multi_init();
    curl = curl_easy_init();
    std::vector<float> _templist;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url1.c_str());
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
        std::cout << _templist.back() << std::endl;
    }
}