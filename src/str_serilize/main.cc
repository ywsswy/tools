#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

std::string Dom2String(rapidjson::Document &d)
{
     rapidjson::StringBuffer buffer;
     rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
     d.Accept(writer);
     return buffer.GetString();
}

std::string Value2String(rapidjson::Value &d)
{
     rapidjson::StringBuffer buffer;
     rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
     d.Accept(writer);
     return buffer.GetString();
}

void CreateString(const std::string &name, const std::string &value, rapidjson::Document &doc)
{
    doc.AddMember(rapidjson::Value().SetString(name.c_str(), name.size(), doc.GetAllocator()),
                  rapidjson::Value().SetString(value.c_str(), value.size(), doc.GetAllocator()),
                  doc.GetAllocator());
}

std::string GetString(const std::string &raw_str, const std::string &key)
{
    rapidjson::Document doc;
    doc.Parse(raw_str.c_str());
    if (doc.IsObject())
    {
        auto it = doc.FindMember(key.c_str());
        if (it != doc.MemberEnd())
        {
            if (it->value.IsString())
            {
                return it->value.GetString();
            }
        }
    }
    return "YWS Error";
}

std::string UnSerialize(const std::string &raw_str)
{
    std::string s = "{\"a\":\"" + raw_str + "\"}";
    return GetString(s, "a");
}

std::string Serialize(const std::string &raw_str)
{
    rapidjson::Document a(rapidjson::kObjectType);
    CreateString("a", raw_str, a);
    std::string s = Dom2String(a);
    if (s.size() <= 8)
    {
        return "YWS Error";
    }
    return s.substr(6, s.size() - 8);
}

class Args
{
public:
    Args() {}
    bool help();
    bool ParseArgs(int argc, char* argv[]);
    std::string input;
    std::string type;
};

bool Args::help()
{
    std::cout << "usage: ./main [-h] [-t type(en/de)] [-f filename]" << std::endl;
    return false;
}
bool Args::ParseArgs(int argc, char* argv[])
{
    int ch;
    while ((ch = getopt(argc, argv, "t:f:")) != -1)
    {
        switch (ch)
        {
        case 't':
            type = optarg;
            break;
        case 'f':
            input = optarg;
            break;
        default:
            return help();
        }
    }
    if (type != "en" && type != "de")
    {
        return help();
    }
    return true;
}

int main(int argc, char* argv[])
{
    Args info;
    if (!info.ParseArgs(argc, argv))
    {
        exit(-1);
    }
    std::ifstream ifs(info.input.c_str());
    if (ifs.is_open())
    {
        std::string line_data;
        getline(ifs, line_data);
        if (info.type == "en")
        {
            std::cout << Serialize(line_data) << std::endl;
        }
        else
        {
            std::cout << UnSerialize(line_data) << std::endl;
        }
    }
    else
    {
        std::cout << "open file failed: " << info.input << std::endl;
    }
    return 0;
}
//g++ main.cc -I /mnt/d/software/rapidjson-master/include -g -O0 -std=c++11

