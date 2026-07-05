#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

// 1:ren
// 2:mei
// 3:jin
// 4:hong
// 5:bannei
// 6:banwai
// 7:lastyearmeipercent
// 8:lastyearjinp
// 9:lastyearhongp
// 10:lastyearbanneip
// 11:lastyearbanwaip

// ve[0]less -> ve[2]large
// type:
// 0 nnx
// 1 nzx
// 2 nxx
// 3 zzz
std::map<int, std::vector<std::pair<double, double>>> type2lesslargepercent;
std::map<int, std::string> type2str;
int type(std::vector<std::pair<double, int>>& ve) {
  double gap12 = (ve[1].first - ve[0].first) / ve[1].first * 100;
  double gap23 = (ve[2].first - ve[1].first) / ve[2].first * 100;
  std::cout << gap12 << std::endl;
  std::cout << gap23 << std::endl;
  bool same12 = false;
  bool same23 = false;
  if (gap12 <= 4) {
    same12 = true;
  }
  if (gap23 <= 4) {
    same23 = true;
  }
  if (same23) {
    if (same12) {
      return 3;
    }
    return 0;
  }
  if (same12) {
    return 2;
  }
  return 1;
}

void init_type2percent() {
  type2str[0] = "nnx";
  type2str[1] = "nzx";
  type2str[2] = "nxx";
  type2str[3] = "zzz";
  // 0
  std::vector<std::pair<double, double>> v1;
  v1.push_back(std::make_pair(33,42));
  v1.push_back(std::make_pair(33,42));
  v1.push_back(std::make_pair(23,27));
  type2lesslargepercent[0] = v1;
  v1.clear();
  v1.push_back(std::make_pair(40,44));
  v1.push_back(std::make_pair(31,35));
  v1.push_back(std::make_pair(23,27));
  type2lesslargepercent[1] = v1;
  v1.clear();
  v1.push_back(std::make_pair(40,44));
  v1.push_back(std::make_pair(25,33));
  v1.push_back(std::make_pair(25,33));
  type2lesslargepercent[2] = v1;
  v1.clear();
  v1.push_back(std::make_pair(25,42));
  v1.push_back(std::make_pair(25,42));
  v1.push_back(std::make_pair(25,42));
  type2lesslargepercent[3] = v1;
}

// check_sorted(little->large) ve is 
void checkValid(const int type/*cal by last year*/, const std::vector<std::pair<double, int>>& ve_last_year, const std::vector<std::pair<double, std::string>>& ve_now) {
  std::cout << "        check" << std::endl;
  std::string type_str = type2str[type];
  std::cout << "type:" << type_str << std::endl;
  double sum = 0;
  for(auto&& i : ve_now) {
    sum += i.first;
  }
  auto abcrange = type2lesslargepercent[type];
  int idx = ve_last_year[2].second;
  std::cout << idx << std::endl;
  std::cout << "1) " << type_str[0] << " should:[" << sum * abcrange[0].first/100 << ", " << sum*abcrange[0].second/100 << "], now:" << ve_now[idx].first << "(" << ve_now[idx].second << ")" << std::endl;
  std::cout << "2): [" << sum * abcrange[1].first/100 << ", " << sum*abcrange[1].second/100 << "]" << std::endl;
  std::cout << "3): [" << sum * abcrange[2].first/100 << ", " << sum*abcrange[2].second/100 << "]" << std::endl;
}

int main() {
  init_type2percent();
  double ren = 0;
  double mei = 0;
  double jin = 0;
  double hong =  0;
  double bannei = 0;
  double banwai = 0;
  double meilyp = 0;
  double jinlyp = 0;
  double honglyp =  0;
  double banneilyp = 0;
  double banwailyp = 0;
  std::cin >> ren >> mei >> jin >> hong >> bannei >> banwai
           >> meilyp >> jinlyp >> honglyp >> banneilyp >> banwailyp;
  std::cout << "ren:" << ren << std::endl
            << "mei:" << mei << std::endl
            << "jin:" << jin << std::endl
            << "hong:" << hong << std::endl
            << "bannei:" << bannei << std::endl
            << "banwai:" << banwai << std::endl
            << "meilyp:" << meilyp << std::endl
            << "jinlyp:" << jinlyp << std::endl
            << "honglyp:" << honglyp << std::endl
            << "banneilyp:" << banneilyp << std::endl
            << "banwailyp:" << banwailyp << std::endl;
  double sum_bx = mei + jin + hong;
  double sum_wl = bannei + banwai;
  double sum = ren + sum_bx + sum_wl;
  std::cout << "sum_bx:" << sum_bx << std::endl;
  std::cout << "sum_wl:" << sum_wl << std::endl;
  std::cout << "sum:" << sum << std::endl;
  // bigtype(cal by last year)
  std::vector<std::pair<double, int>> vebig;
  vebig.push_back(std::make_pair(1, 0));  // renlyp
  vebig.push_back(std::make_pair((meilyp*0.01 + jinlyp*0.01 + honglyp*0.01 + 3)/3, 1));
  vebig.push_back(std::make_pair((banneilyp*0.01 + banwailyp*0.01 + 2)/2, 2));
  std::sort(vebig.begin(), vebig.end());
  int bigtype = type(vebig);
  std::cout << "bigtype:" << type2str[bigtype] << std::endl;
  std::vector<std::pair<double, std::string>> vebignow;
  vebignow.push_back(std::make_pair(ren, "ren"));
  vebignow.push_back(std::make_pair(sum_bx, "sum_bx"));
  vebignow.push_back(std::make_pair(sum_wl, "sum_wl"));
  checkValid(bigtype, vebig, vebignow);
/*
  std::vector<std::pair<double, int>> ve;
  ve.push_back(std::make_pair(ren, 1));
  ve.push_back(std::make_pair(sum_bx, 2));
  ve.push_back(std::make_pair(sum_wl, 3));
  for (auto&& i : ve) {
    std::cout << i.second << ":" << i.first << std::endl;
  }
  std::sort(ve.begin(), ve.end());
  for (auto&& i : ve) {
    std::cout << i.second << ":" << i.first << std::endl;
  }
  std::cout << type(ve) << std::endl;
*/
}
