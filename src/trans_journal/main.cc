/*
观察是否存在PUST FIRST THING FIRST，有的话就手动修正一下
第一行是顺序日期，第一列忽略,第二列忽略
第二行忽略
第三行～第n行是每个时间段j，第一列是时间标题
二维数组即可
*/

#define YLOFI
#define YDELO
#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<map>
#include<list>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#ifdef YDELO
int ydelon = 0;
template<typename T,typename S>
ostream &operator<<(ostream &os,const pair<T,S> &it){
    return 	os << it.first << " " << it.second;
}
template<typename T,typename S>
ostream &operator<<(ostream &os,const map<T,S> &st){
	int n = (ydelon==0?st.size():ydelon);
	os << " size=" << st.size() << " show=" << n << endl;
	typename map<T,S>::const_iterator it = st.begin();
	for(int i = 0;i<n && i<st.size();i++,it++){
		os << i << " " << *it << "*" << endl;
	}
	return os;
}
template<typename T>
ostream &operator<<(ostream &os,const list<T> &st){
	int n = (ydelon==0?st.size():ydelon);
	os << " size=" << st.size() << " show=" << n << endl;
	typename list<T>::const_iterator it = st.begin();
	for(int i = 0;i<n && i<st.size();i++,it++){
		os << i << " " << *it << "*" << endl;
	}
	return os;
}
template<typename T>
ostream &operator<<(ostream &os,const vector<T> &st){
	int n = (ydelon==0?st.size():ydelon);
	os << " size=" << st.size() << " show=" << n << endl;
	typename vector<T>::const_iterator it = st.begin();
	for(int i = 0;i<n && i<st.size();i++,it++){
		os << i << " " << *it << "*" << endl;
	}
	return os;
}
//for built-in type(except c_array) & map & list & vector
template<typename T>
void yPrint(const string &info,const T &x,int n = 0,bool clr = true){
	ydelon = n;
	if(clr){
		system("clear");//"clear" in linux
	}
	cout << endl << "\\**********************" << endl;
	cout << info << endl;
	cout << x << "**********************\\" << endl;
	return;
}
#endif

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> SplitString(const std::string& raw,
                                     const std::string& inter,
                                     const bool ignore_empty) {
  std::vector<std::string> vec;
  size_t n = 0;
  size_t old = 0;
  while (n != std::string::npos) {
    n = raw.find(inter, n);
    if (n != std::string::npos) {
      if (!ignore_empty || n != old) {
        vec.push_back(raw.substr(old, n - old));
      }
      n += inter.size();
      old = n;
    }
  }
  if (!ignore_empty || old < raw.size()) {
    vec.push_back(raw.substr(old, raw.size() - old));
  }
  return vec;
}

int main() {
  std::vector<std::string> empty;
  std::vector<std::vector<std::string> > ve;
  std::string in;
  int line_num = 0;
  while(getline(std::cin, in)) {
    ++line_num;
    if (line_num == 2) {
       continue;
    }
    // in split
    std::vector<std::string> vs = SplitString(in, "|", false);
    if (line_num == 1) {
      if (vs.size() < 4 || vs[0] != "" || vs[1] != "-" || vs[vs.size()-1] != "") {
        std::cout << "invalid 1" << std::endl;
        std::cout << vs.size() << std::endl;
        std::cout << vs[0].size() << std::endl;
        std::cout << vs[vs.size()-1].size() << std::endl;
        return 1;
      }
      ve.push_back(empty);
      for (int i = 2; i <= vs.size() - 2; ++i) {
        // date
        ve[0].push_back(vs[i]);
      }
      continue;
    }
    if (vs.size() < 3) {
      std::cout << "END" << std::endl;
      break;
    }
    if (vs[0] != "" || vs[vs.size()-1] != "") {
        std::cout << "invalid 2" << std::endl;
        std::cout << vs[0].size() << std::endl;
        std::cout << vs[vs.size()-1].size() << std::endl;
        return 2;
    }
    ve.push_back(empty);
    for (int i = 1; i <= vs.size() - 2; ++i) {
      ve[line_num-2].push_back(vs[i]);
    }
    // 不够的要补齐，补到跟日期数量一样多
    // 3 个日期的话，ve[x].size() 就应该是4
    // 日期数 + 1 - ve[x].size() 就是要补充的数量
    int need = ve[0].size() + 1 - ve[line_num-2].size();
    for (int i = 0; i < need; ++i) {
      ve[line_num-2].push_back("-");
    }
  }
  std::cout << "=======DEBUG========" << std::endl;
  //yPrint("ve", ve, 0, false);
  std::cout << "=======SHOW========" << std::endl;
  std::cout << "|-|";
  for (int i = 0; i < ve.size() - 1; ++i) {
    std::cout << ve[i+1][0] << "|";
  }
  std::cout << std::endl;
  std::cout << "|-|";
  for (int i = 0; i < ve.size() - 1; ++i) {
    std::cout << "-|";
  }
  std::cout << std::endl;
  // ve[time][date]
  for (int i = 0; i < ve[0].size(); ++i) {  // date
    std::cout << "|" << ve[0][ve[0].size()-i-1] << "|";
    for (int j = 0; j < ve.size() - 1; ++j) {  // time
      std::cout << ve[j + 1][ve[0].size()-i];
      std::cout << "|";
    }
    std::cout << std::endl;
  }
  return 0;
}
