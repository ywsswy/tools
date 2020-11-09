#include <string>
#include <chrono>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <unordered_set>


std::string RandString(size_t len)
{
    std::string res;
    for (size_t i = 0; i < len; ++i)
    {
        char c = rand()%255;
        res += c;
    }
    return res;
}

std::vector<std::string> RandVector(int num)
{
    std::vector<std::string> ve;
    for (int i = 0; i < num; ++i)
    {
        ve.push_back(RandString(20));
    }
    return ve;
}

std::unordered_set<std::string> RandSet(int num)
{
    std::unordered_set<std::string> se;
    for (int i = 0; i < num; ++i)
    {
        se.insert(RandString(20));
    }
    return se;
}

int main()
{
    std::string str_from;
    std::string str_to1;
    std::string str_to2;
    size_t len = 50;
    srand(time(NULL));
    std::vector<std::string> ve = RandVector(50);
    std::unordered_set<std::string> se = RandSet(50);
    for (std::unordered_set<std::string>::iterator it = se.begin(); it != se.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    int not_find = 0;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    for (size_t i = 0; i < ve.size(); ++i)
    {
        if (se.find(ve[i]) == se.end())
        {
            not_find++;
        }
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "run_time: " << diff.count() << " s, not find: " << not_find << "\n";
    return 0;
}

