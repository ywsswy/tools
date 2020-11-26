// 遗留功能，0补齐日期，博客分享

#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
//#define YWATCH
class YPrint
{
public:
    static int indent_;
    template<typename T> static void W(const std::string &info, const T &x, bool clr = false)
    {
#ifdef YWATCH
        if (clr) system("clear"); //system("cls"); in windows
        std::cout << "\n\\******************\n" << info << "\n" << x << "*\\\n";
#endif
    }
};
int YPrint::indent_ = 0;
#define YOVERLOAD typename T> std::ostream &operator << (std::ostream &os, const std::
#define YPRINT(...) YOVERLOAD __VA_ARGS__ > &st){\
    YPrint::indent_++;\
    os << "OBJECT(size=" << st.size() << ")\n";\
    typename std:: __VA_ARGS__ >::const_iterator it = st.begin();\
    for (size_t i = 0; i < st.size(); i++, it++){\
        for(int j=0;j<YPrint::indent_;j++){os << "\t";}\
        os << "[" << i << "]=" << *it << "*\n";\
    }YPrint::indent_--;\
    return os;\
}
template<typename S, YOVERLOAD pair<S, T> &st) { return os << "{" << st.first << "}" << st.second; }
template<typename S, YPRINT(map<S, T)
template<YPRINT(list<T)
template<YPRINT(vector<T)


class Args
{
public:
    Args() : filename("yin.txt"), output_filename("yout.txt"), unique_time(0) {}
    std::string filename;
    std::string output_filename;
    int unique_time;
};

bool help()
{
    std::cout << "usage: ./main [-h] [-f input_filename] [-o output_filename] [-u unique_time]" << std::endl
    << "optional arguments:" << std::endl
    << "  -u UNIQUE_TIME\t" << "list.unique() before timestamp(s)" << std::endl;
    return false;
}
bool ParseArgs(int argc, char* argv[], Args &info)
{
    int ch;
    while ((ch = getopt(argc, argv, "o:u:f:h")) != -1)
    {
        switch (ch)
        {
        case 'u':
            info.unique_time = atoi(optarg);
            break;
        case 'f':
            info.filename = optarg;
            break;
        case 'o':
            info.output_filename = optarg;
            break;
        case 'h':
            return help();
        default:
            return help();
        }
    }
    return true;
}

std::vector<std::string> StringSplit(const std::string &raw, const std::string &inter, const bool ignore_empty)
{
    std::vector<std::string> vec;
    size_t n = 0;
    size_t old = 0;
    while (n != std::string::npos)
    {
        n = raw.find(inter, n);
        if (n != std::string::npos)
        {
            if (!ignore_empty || n != old)
            {
                vec.push_back(raw.substr(old, n - old));
            }
            n += inter.size();
            old = n;
        }
    }
    if (!ignore_empty || old < raw.size())
    {
        vec.push_back(raw.substr(old, raw.size() - old));
    }
    return vec;
}

bool ReadTextFile(const std::string &filename, std::vector<std::string> &data)
{
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open())
    {
        std::cerr << "file open failed, " << filename << std::endl;
        return false;
    }
    else
    {
        std::string line_data;
        while(getline(ifs, line_data))
        {
            data.push_back(line_data);
        }
        ifs.close();
        return true;
    }
}

bool SortHistory(const std::vector<std::string> &filename, const std::string &output_filename, const int unique_time)
{
    std::vector<std::string> raw_data;
    for (auto && file_name : filename)
    {
        if (!ReadTextFile(file_name, raw_data))
        {
            return false;
        }
    }
    std::map<int, std::list<std::string> > cmd;
    int last_time = 0;
    for (size_t i = 0; i < raw_data.size(); ++i)
    {
        std::string &cur = raw_data[i];
        int cur_time = 0;
        if (cur.find_first_of('#') == 0 && (cur_time = atoi(cur.substr(1).c_str())))
        {
            if (cur_time > 1420041600 && cur_time <=time(NULL))
            {
                last_time = cur_time;
                continue;
            }
        }
        cmd[last_time].push_back(cur);
    }
    std::ofstream ofs(output_filename.c_str());
    if (!ofs.is_open())
    {
        std::cerr << "file open failed, " << output_filename << std::endl;
    }
    else
    {
        for (std::map<int, std::list<std::string> >::iterator it = cmd.begin(); it != cmd.end(); it++)
        {
            if (it->first < unique_time)
            {
                it->second.unique();
            }
            time_t timet = it->first;
            tm tmtime = *localtime(&timet);
            for (std::list<std::string>::iterator iter = it->second.begin(); iter != it->second.end(); iter++)
            {
                ofs << '#' << it->first <<
                ' ' << tmtime.tm_year+1900 << '-' << tmtime.tm_mon+1 << '-' << tmtime.tm_mday <<
                ' ' << tmtime.tm_hour << ':' << tmtime.tm_min << ':' << tmtime.tm_sec <<
                std::endl << *iter << std::endl;
            }
        }
        ofs.close();
        return true;
    }
}
int main(int argc, char* argv[])
{
    Args info;
    if (!ParseArgs(argc, argv, info))
    {
        exit(-1);
    }
    if (!SortHistory(StringSplit(info.filename, ":", false), info.output_filename, info.unique_time))
    {
        exit(-1);
    }
    return 0;
}
