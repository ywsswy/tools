#include <map>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

std::string DocumentToString(rapidjson::Document& d, const int indent = 0) { 
  rapidjson::StringBuffer buffer;
  if (indent == 0) {
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
  } else {
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', indent);
    d.Accept(writer);
    return buffer.GetString();
  }
}

std::string ValueToString(rapidjson::Value &d, const int indent = 0) {
  rapidjson::StringBuffer buffer;
  if (indent == 0) {
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
  } else {
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', indent);
    d.Accept(writer);
    return buffer.GetString();
  }
}

void CreateString(const std::string &name, const std::string& value, rapidjson::Document& doc) {
  doc.AddMember(rapidjson::Value().SetString(name.c_str(), name.size(), doc.GetAllocator()),
                rapidjson::Value().SetString(value.c_str(), value.size(), doc.GetAllocator()),
                doc.GetAllocator());
}

std::string GetString(const std::string& raw_str, const std::string& key) {
  rapidjson::Document doc;
  doc.Parse(raw_str.c_str());
  if (doc.IsObject()) {
    auto it = doc.FindMember(key.c_str());
    if (it != doc.MemberEnd()) {
      if (it->value.IsString()) {
        return it->value.GetString();
      }
    }
  }
  return "YWS Error";
}

std::string UnEscape(const std::string& raw_str) {
  std::string s = "{\"a\":\"" + raw_str + "\"}";
  return GetString(s, "a");
}

std::string Escape(const std::string& raw_str) {
  rapidjson::Document a(rapidjson::kObjectType);
  CreateString("a", raw_str, a);
  std::string s = DocumentToString(a);
  if (s.size() <= 8) {
    return "YWS Error";
  }
  return s.substr(6, s.size() - 8);
}

class GlobalConfig {
 private:
  GlobalConfig() {};
 public:
  static GlobalConfig& GetInstance() {
    static GlobalConfig instance;
    return instance;
  }
  void Init() {
    redis_escape_map_.insert({"\\x00", 0});
    redis_escape_map_.insert({"\\x01", 1});
    redis_escape_map_.insert({"\\x02", 2});
    redis_escape_map_.insert({"\\x03", 3});
    redis_escape_map_.insert({"\\x04", 4});
    redis_escape_map_.insert({"\\x05", 5});
    redis_escape_map_.insert({"\\x06", 6});
    redis_escape_map_.insert({"\\x07", 7});
    redis_escape_map_.insert({"\\a", 7});
    redis_escape_map_.insert({"\\x08", 8});
    redis_escape_map_.insert({"\\b", 8});
    redis_escape_map_.insert({"\\x09", 9});
    redis_escape_map_.insert({"\\t", 9});
    redis_escape_map_.insert({"\\x0a", 10});
    redis_escape_map_.insert({"\\n", 10});
    redis_escape_map_.insert({"\\x0b", 11});
    redis_escape_map_.insert({"\\x0c", 12});
    redis_escape_map_.insert({"\\x0d", 13});
    redis_escape_map_.insert({"\\r", 13});
    redis_escape_map_.insert({"\\x0e", 14});
    redis_escape_map_.insert({"\\x0f", 15});
    redis_escape_map_.insert({"\\x10", 16});
    redis_escape_map_.insert({"\\x11", 17});
    redis_escape_map_.insert({"\\x12", 18});
    redis_escape_map_.insert({"\\x13", 19});
    redis_escape_map_.insert({"\\x14", 20});
    redis_escape_map_.insert({"\\x15", 21});
    redis_escape_map_.insert({"\\x16", 22});
    redis_escape_map_.insert({"\\x17", 23});
    redis_escape_map_.insert({"\\x18", 24});
    redis_escape_map_.insert({"\\x19", 25});
    redis_escape_map_.insert({"\\x1a", 26});
    redis_escape_map_.insert({"\\x1b", 27});
    redis_escape_map_.insert({"\\x1c", 28});
    redis_escape_map_.insert({"\\x1d", 29});
    redis_escape_map_.insert({"\\x1e", 30});
    redis_escape_map_.insert({"\\x1f", 31});
    redis_escape_map_.insert({"\\x20", 32});
    redis_escape_map_.insert({"\\x21", 33});
    redis_escape_map_.insert({"\\x22", 34});
    redis_escape_map_.insert({"\\\"", 34});
    redis_escape_map_.insert({"\\x23", 35});
    redis_escape_map_.insert({"\\x24", 36});
    redis_escape_map_.insert({"\\x25", 37});
    redis_escape_map_.insert({"\\x26", 38});
    redis_escape_map_.insert({"\\x27", 39});
    redis_escape_map_.insert({"\\x28", 40});
    redis_escape_map_.insert({"\\x29", 41});
    redis_escape_map_.insert({"\\x2a", 42});
    redis_escape_map_.insert({"\\x2b", 43});
    redis_escape_map_.insert({"\\x2c", 44});
    redis_escape_map_.insert({"\\x2d", 45});
    redis_escape_map_.insert({"\\x2e", 46});
    redis_escape_map_.insert({"\\x2f", 47});
    redis_escape_map_.insert({"\\x30", 48});
    redis_escape_map_.insert({"\\x31", 49});
    redis_escape_map_.insert({"\\x32", 50});
    redis_escape_map_.insert({"\\x33", 51});
    redis_escape_map_.insert({"\\x34", 52});
    redis_escape_map_.insert({"\\x35", 53});
    redis_escape_map_.insert({"\\x36", 54});
    redis_escape_map_.insert({"\\x37", 55});
    redis_escape_map_.insert({"\\x38", 56});
    redis_escape_map_.insert({"\\x39", 57});
    redis_escape_map_.insert({"\\x3a", 58});
    redis_escape_map_.insert({"\\x3b", 59});
    redis_escape_map_.insert({"\\x3c", 60});
    redis_escape_map_.insert({"\\x3d", 61});
    redis_escape_map_.insert({"\\x3e", 62});
    redis_escape_map_.insert({"\\x3f", 63});
    redis_escape_map_.insert({"\\x40", 64});
    redis_escape_map_.insert({"\\x41", 65});
    redis_escape_map_.insert({"\\x42", 66});
    redis_escape_map_.insert({"\\x43", 67});
    redis_escape_map_.insert({"\\x44", 68});
    redis_escape_map_.insert({"\\x45", 69});
    redis_escape_map_.insert({"\\x46", 70});
    redis_escape_map_.insert({"\\x47", 71});
    redis_escape_map_.insert({"\\x48", 72});
    redis_escape_map_.insert({"\\x49", 73});
    redis_escape_map_.insert({"\\x4a", 74});
    redis_escape_map_.insert({"\\x4b", 75});
    redis_escape_map_.insert({"\\x4c", 76});
    redis_escape_map_.insert({"\\x4d", 77});
    redis_escape_map_.insert({"\\x4e", 78});
    redis_escape_map_.insert({"\\x4f", 79});
    redis_escape_map_.insert({"\\x50", 80});
    redis_escape_map_.insert({"\\x51", 81});
    redis_escape_map_.insert({"\\x52", 82});
    redis_escape_map_.insert({"\\x53", 83});
    redis_escape_map_.insert({"\\x54", 84});
    redis_escape_map_.insert({"\\x55", 85});
    redis_escape_map_.insert({"\\x56", 86});
    redis_escape_map_.insert({"\\x57", 87});
    redis_escape_map_.insert({"\\x58", 88});
    redis_escape_map_.insert({"\\x59", 89});
    redis_escape_map_.insert({"\\x5a", 90});
    redis_escape_map_.insert({"\\x5b", 91});
    redis_escape_map_.insert({"\\x5c", 92});
    redis_escape_map_.insert({"\\\\", 92});
    redis_escape_map_.insert({"\\x5d", 93});
    redis_escape_map_.insert({"\\x5e", 94});
    redis_escape_map_.insert({"\\x5f", 95});
    redis_escape_map_.insert({"\\x60", 96});
    redis_escape_map_.insert({"\\x61", 97});
    redis_escape_map_.insert({"\\x62", 98});
    redis_escape_map_.insert({"\\x63", 99});
    redis_escape_map_.insert({"\\x64", 100});
    redis_escape_map_.insert({"\\x65", 101});
    redis_escape_map_.insert({"\\x66", 102});
    redis_escape_map_.insert({"\\x67", 103});
    redis_escape_map_.insert({"\\x68", 104});
    redis_escape_map_.insert({"\\x69", 105});
    redis_escape_map_.insert({"\\x6a", 106});
    redis_escape_map_.insert({"\\x6b", 107});
    redis_escape_map_.insert({"\\x6c", 108});
    redis_escape_map_.insert({"\\x6d", 109});
    redis_escape_map_.insert({"\\x6e", 110});
    redis_escape_map_.insert({"\\x6f", 111});
    redis_escape_map_.insert({"\\x70", 112});
    redis_escape_map_.insert({"\\x71", 113});
    redis_escape_map_.insert({"\\x72", 114});
    redis_escape_map_.insert({"\\x73", 115});
    redis_escape_map_.insert({"\\x74", 116});
    redis_escape_map_.insert({"\\x75", 117});
    redis_escape_map_.insert({"\\x76", 118});
    redis_escape_map_.insert({"\\x77", 119});
    redis_escape_map_.insert({"\\x78", 120});
    redis_escape_map_.insert({"\\x79", 121});
    redis_escape_map_.insert({"\\x7a", 122});
    redis_escape_map_.insert({"\\x7b", 123});
    redis_escape_map_.insert({"\\x7c", 124});
    redis_escape_map_.insert({"\\x7d", 125});
    redis_escape_map_.insert({"\\x7e", 126});
    redis_escape_map_.insert({"\\x7f", 127});
    redis_escape_map_.insert({"\\x80", 128});
    redis_escape_map_.insert({"\\x81", 129});
    redis_escape_map_.insert({"\\x82", 130});
    redis_escape_map_.insert({"\\x83", 131});
    redis_escape_map_.insert({"\\x84", 132});
    redis_escape_map_.insert({"\\x85", 133});
    redis_escape_map_.insert({"\\x86", 134});
    redis_escape_map_.insert({"\\x87", 135});
    redis_escape_map_.insert({"\\x88", 136});
    redis_escape_map_.insert({"\\x89", 137});
    redis_escape_map_.insert({"\\x8a", 138});
    redis_escape_map_.insert({"\\x8b", 139});
    redis_escape_map_.insert({"\\x8c", 140});
    redis_escape_map_.insert({"\\x8d", 141});
    redis_escape_map_.insert({"\\x8e", 142});
    redis_escape_map_.insert({"\\x8f", 143});
    redis_escape_map_.insert({"\\x90", 144});
    redis_escape_map_.insert({"\\x91", 145});
    redis_escape_map_.insert({"\\x92", 146});
    redis_escape_map_.insert({"\\x93", 147});
    redis_escape_map_.insert({"\\x94", 148});
    redis_escape_map_.insert({"\\x95", 149});
    redis_escape_map_.insert({"\\x96", 150});
    redis_escape_map_.insert({"\\x97", 151});
    redis_escape_map_.insert({"\\x98", 152});
    redis_escape_map_.insert({"\\x99", 153});
    redis_escape_map_.insert({"\\x9a", 154});
    redis_escape_map_.insert({"\\x9b", 155});
    redis_escape_map_.insert({"\\x9c", 156});
    redis_escape_map_.insert({"\\x9d", 157});
    redis_escape_map_.insert({"\\x9e", 158});
    redis_escape_map_.insert({"\\x9f", 159});
    redis_escape_map_.insert({"\\xa0", 160});
    redis_escape_map_.insert({"\\xa1", 161});
    redis_escape_map_.insert({"\\xa2", 162});
    redis_escape_map_.insert({"\\xa3", 163});
    redis_escape_map_.insert({"\\xa4", 164});
    redis_escape_map_.insert({"\\xa5", 165});
    redis_escape_map_.insert({"\\xa6", 166});
    redis_escape_map_.insert({"\\xa7", 167});
    redis_escape_map_.insert({"\\xa8", 168});
    redis_escape_map_.insert({"\\xa9", 169});
    redis_escape_map_.insert({"\\xaa", 170});
    redis_escape_map_.insert({"\\xab", 171});
    redis_escape_map_.insert({"\\xac", 172});
    redis_escape_map_.insert({"\\xad", 173});
    redis_escape_map_.insert({"\\xae", 174});
    redis_escape_map_.insert({"\\xaf", 175});
    redis_escape_map_.insert({"\\xb0", 176});
    redis_escape_map_.insert({"\\xb1", 177});
    redis_escape_map_.insert({"\\xb2", 178});
    redis_escape_map_.insert({"\\xb3", 179});
    redis_escape_map_.insert({"\\xb4", 180});
    redis_escape_map_.insert({"\\xb5", 181});
    redis_escape_map_.insert({"\\xb6", 182});
    redis_escape_map_.insert({"\\xb7", 183});
    redis_escape_map_.insert({"\\xb8", 184});
    redis_escape_map_.insert({"\\xb9", 185});
    redis_escape_map_.insert({"\\xba", 186});
    redis_escape_map_.insert({"\\xbb", 187});
    redis_escape_map_.insert({"\\xbc", 188});
    redis_escape_map_.insert({"\\xbd", 189});
    redis_escape_map_.insert({"\\xbe", 190});
    redis_escape_map_.insert({"\\xbf", 191});
    redis_escape_map_.insert({"\\xc0", 192});
    redis_escape_map_.insert({"\\xc1", 193});
    redis_escape_map_.insert({"\\xc2", 194});
    redis_escape_map_.insert({"\\xc3", 195});
    redis_escape_map_.insert({"\\xc4", 196});
    redis_escape_map_.insert({"\\xc5", 197});
    redis_escape_map_.insert({"\\xc6", 198});
    redis_escape_map_.insert({"\\xc7", 199});
    redis_escape_map_.insert({"\\xc8", 200});
    redis_escape_map_.insert({"\\xc9", 201});
    redis_escape_map_.insert({"\\xca", 202});
    redis_escape_map_.insert({"\\xcb", 203});
    redis_escape_map_.insert({"\\xcc", 204});
    redis_escape_map_.insert({"\\xcd", 205});
    redis_escape_map_.insert({"\\xce", 206});
    redis_escape_map_.insert({"\\xcf", 207});
    redis_escape_map_.insert({"\\xd0", 208});
    redis_escape_map_.insert({"\\xd1", 209});
    redis_escape_map_.insert({"\\xd2", 210});
    redis_escape_map_.insert({"\\xd3", 211});
    redis_escape_map_.insert({"\\xd4", 212});
    redis_escape_map_.insert({"\\xd5", 213});
    redis_escape_map_.insert({"\\xd6", 214});
    redis_escape_map_.insert({"\\xd7", 215});
    redis_escape_map_.insert({"\\xd8", 216});
    redis_escape_map_.insert({"\\xd9", 217});
    redis_escape_map_.insert({"\\xda", 218});
    redis_escape_map_.insert({"\\xdb", 219});
    redis_escape_map_.insert({"\\xdc", 220});
    redis_escape_map_.insert({"\\xdd", 221});
    redis_escape_map_.insert({"\\xde", 222});
    redis_escape_map_.insert({"\\xdf", 223});
    redis_escape_map_.insert({"\\xe0", 224});
    redis_escape_map_.insert({"\\xe1", 225});
    redis_escape_map_.insert({"\\xe2", 226});
    redis_escape_map_.insert({"\\xe3", 227});
    redis_escape_map_.insert({"\\xe4", 228});
    redis_escape_map_.insert({"\\xe5", 229});
    redis_escape_map_.insert({"\\xe6", 230});
    redis_escape_map_.insert({"\\xe7", 231});
    redis_escape_map_.insert({"\\xe8", 232});
    redis_escape_map_.insert({"\\xe9", 233});
    redis_escape_map_.insert({"\\xea", 234});
    redis_escape_map_.insert({"\\xeb", 235});
    redis_escape_map_.insert({"\\xec", 236});
    redis_escape_map_.insert({"\\xed", 237});
    redis_escape_map_.insert({"\\xee", 238});
    redis_escape_map_.insert({"\\xef", 239});
    redis_escape_map_.insert({"\\xf0", 240});
    redis_escape_map_.insert({"\\xf1", 241});
    redis_escape_map_.insert({"\\xf2", 242});
    redis_escape_map_.insert({"\\xf3", 243});
    redis_escape_map_.insert({"\\xf4", 244});
    redis_escape_map_.insert({"\\xf5", 245});
    redis_escape_map_.insert({"\\xf6", 246});
    redis_escape_map_.insert({"\\xf7", 247});
    redis_escape_map_.insert({"\\xf8", 248});
    redis_escape_map_.insert({"\\xf9", 249});
    redis_escape_map_.insert({"\\xfa", 250});
    redis_escape_map_.insert({"\\xfb", 251});
    redis_escape_map_.insert({"\\xfc", 252});
    redis_escape_map_.insert({"\\xfd", 253});
    redis_escape_map_.insert({"\\xfe", 254});
    redis_escape_map_.insert({"\\xff", 255});
  }
  std::map<std::string, unsigned char> GetRedisEscapeMap() { return redis_escape_map_; }
 private:
  std::map<std::string, unsigned char> redis_escape_map_;
};

std::string UnSerialize(const std::string& raw_str) {
  std::string finals = raw_str;
  // 把全部可替换的进行搜索,直到搜不到为止
  std::map<std::string, unsigned char> redis_escape_map = GlobalConfig::GetInstance().GetRedisEscapeMap();
  for (const auto& item : redis_escape_map) {
    size_t loc = finals.find(item.first);
    while (loc != std::string::npos) {
      finals.replace(loc, item.first.size(), " ");
      finals[loc] = item.second;
      loc = finals.find(item.first, loc+1);
    }
  }
  return finals;
}

class Args {
 public:
  Args() {}
  bool help();
  bool ParseArgs(int argc, char* argv[]);
  std::string input;
  std::string type;
  std::string method;
};

bool Args::help() {
  std::cout << "usage: ./main [-h] -m method(json/redis) -t type(en/de) -f filename" << std::endl;
  return false;
}

bool Args::ParseArgs(int argc, char* argv[]) {
  int ch;
  while ((ch = getopt(argc, argv, "t:f:m:h")) != -1) {
    switch (ch) {
    case 't':
      type = optarg;
      break;
    case 'f':
      input = optarg;
      break;
    case 'm':
      method = optarg;
      break;
    case 'h':
    default:
      return help();
    }
  }
  if (type != "en" && type != "de") {
    return help();
  }
  if (method != "json" && method != "redis") {
    return help();
  }
  return true;
}

int main(int argc, char* argv[]) {
    GlobalConfig::GetInstance().Init();
    Args info;
    if (!info.ParseArgs(argc, argv)) {
        exit(-1);
    }
    std::ifstream ifs(info.input.c_str());
    if (ifs.is_open()) {
      if (info.method == "json") {
        if (info.type == "en") {
          std::string file_data;
          std::string line_data;
          while(getline(ifs, line_data)) {
            file_data.append(line_data).append("\n");
          }
          std::cout << Escape(file_data) << std::endl;
        } else {
          std::string line_data;
          getline(ifs, line_data);
          std::cout << UnEscape(line_data) << std::endl;
        }
      } else {  // redis
        if (info.type == "en") {
          std::cout << "unsupported" << std::endl;
        } else {
          std::string line_data;
          getline(ifs, line_data);
          std::cout << UnSerialize(line_data);
        }
      }
    } else {
        std::cout << "open file failed: " << info.input << std::endl;
    }
    return 0;
}
//g++ main.cc -I /mnt/d/software/rapidjson-master/include -g -O0 -std=c++11

