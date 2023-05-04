#include <chrono>
#include <iostream>
#include <string>
#include "api.cpp"
#include "graph.cpp"
int main(void)
{  
    std::string stockname = "AAPL";
    //std::cout << "Enter the name of stock: ";
    //std::cin >> stockname;
    time_t start, end;
    double elapsed, prev_elapsed = 0.0;
    time(&start);
    do
    {
        time(&end);
        elapsed = difftime(end, start);
        if (elapsed >= prev_elapsed+2)
            {
                uint64_t sec = std::chrono::system_clock::now().time_since_epoch().count() + 1;
                std::ostringstream oss;
                oss << sec;
                std::string url = "https://query1.finance.yahoo.com/v8/finance/chart/" + stockname + "?interval=1m" + "&period2=" + oss.str() +"&includePrePost=true";
                std:: map tempmap = getdata(url);
                std::map<std::string, float> latest;
                latest["open"] = tempmap["listopen"][tempmap["listopen"].size() - 1].asFloat();
                latest["close"] = tempmap["listclose"][tempmap["listclose"].size() - 1].asFloat();
                latest["low"] = tempmap["listlow"][tempmap["listlow"].size() - 1].asFloat();
                latest["high"] = tempmap["listhigh"][tempmap["listhigh"].size() - 1].asFloat();
                latest["time"] = tempmap["listtime"][tempmap["listtime"].size() - 1].asFloat();
                float length = (latest["open"] - latest["close"]);
                std::vector<float> open_array;
                for(int i = 0; i < tempmap["listopen"].size(); i++)
                {
                    open_array.push_back(tempmap["listopen"][i].asFloat());
                }
                system("clear");
                // std::cout << open_array[open_array.size() - 1] << std::endl;
                std::cout << "|  open: | close: |  low: |  high: |  time: |" << std::endl;
                std::cout << "| " << latest["open"] << " | " << latest["close"] << " | " << latest["low"] << " | " << latest["high"] << " | " << epoch_to_utc(latest["time"]) << std::endl;
                draw_axis(open_array);
                // std::cout << (latest["open"] - latest["close"]) << std::endl;
                // drawupperline(latest["high"], latest["open"], latest["close"], length);
                // drawbody(latest["open"], latest["close"], length);
                // drawlowerline(latest["low"], latest["open"], latest["close"], length);
                //std::cout << "enter something" << std::endl;
                prev_elapsed = elapsed;
            }
    } while(1 == 1);
}