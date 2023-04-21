#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cstring>
#include <vector>
#include <json/json.h>
#include <map>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::map<std::string, Json::Value> getdata(std::string url){
    CURL *curl;
    std::map<std::string, Json::Value> map;
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
        Json::Value listtime = jsondata["chart"]["result"][0]["timestamp"];
        Json::Value listopen = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["open"];
        Json::Value listhigh = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["high"];
        Json::Value listlow = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["low"];
        Json::Value listclose = jsondata["chart"]["result"][0]["indicators"]["quote"][0]["close"];
        map["listtime"] = listtime;
        map["listlow"] = listlow;
        map["listhigh"] = listhigh;
        map["listclose"] = listclose;
        map["listopen"] = listopen;
        return(map);
    }
    return(map);
}

std::string epoch_to_utc(float epoch) {
  const time_t old = (time_t)epoch;
  struct tm *oldt = localtime(&old);
  return asctime(oldt);
}