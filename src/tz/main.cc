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

std::vector<std::string> SplitString(const std::string& raw, const std::string& inter, const bool ignore_empty) {
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
  std::cout << "sum:" << sum << std::endl;
  auto abcrange = type2lesslargepercent[type];
  for (int i = 0; i < 3; ++i) {
    int idx = ve_last_year[2-i].second;
    double should_min = sum * abcrange[i].first/100;
    double should_max = sum * abcrange[i].second/100;
    double now = ve_now[idx].first;
    std::cout << i+1 << ") " << type_str[i] << " should:[" << should_min << ", " << should_max << "], now:" << now << "(" << ve_now[idx].second << ")";
    if (now < should_min) {
      std::cout << " NEED MORE(at least " << should_min - now << ")";
    } else if (now > should_max) {
      std::cout << " NEED LESS(at least " << now - should_max << ")";
    }
    std::cout << std::endl;
  }
}

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
double sum_bx = mei + jin + hong;
double sum_wl = bannei + banwai;
double sum = ren + sum_bx + sum_wl;

double change_ren = 0;
double change_mei = 0;
double change_jin = 0;
double change_hong =  0;
double change_bannei = 0;
double change_banwai = 0;


void PrintNow(const std::string& info) {
  std::cout << "=================  " << info << std::endl;
  std::cout << "1 ren:" << ren+change_ren << std::endl
            << "2 mei:" << mei+change_mei << std::endl
            << "3 jin:" << jin+change_jin << std::endl
            << "4 hong:" << hong+change_hong << std::endl
            << "5 bannei:" << bannei+change_bannei << std::endl
            << "6 banwai:" << banwai+change_banwai << std::endl
            << "meilyp:" << meilyp << std::endl
            << "jinlyp:" << jinlyp << std::endl
            << "honglyp:" << honglyp << std::endl
            << "banneilyp:" << banneilyp << std::endl
            << "banwailyp:" << banwailyp << std::endl;
  sum_bx = mei + jin + hong + change_mei + change_jin + change_hong;
  sum_wl = bannei + banwai + change_bannei + change_banwai;
  sum = ren + change_ren + sum_bx + sum_wl;
  std::cout << "sum_bx:" << sum_bx << std::endl;
  std::cout << "sum_wl:" << sum_wl << std::endl;
  std::cout << "sum:" << sum << std::endl;
  // bigtype(cal by last year) ren sum_bx sum_wl
  std::vector<std::pair<double, int>> vebig;
  vebig.push_back(std::make_pair(1, 0));  // renlyp
  vebig.push_back(std::make_pair((meilyp*0.01 + jinlyp*0.01 + honglyp*0.01 + 3)/3, 1));
  vebig.push_back(std::make_pair((banneilyp*0.01 + banwailyp*0.01 + 2)/2, 2));
  std::sort(vebig.begin(), vebig.end());
  int bigtype = type(vebig);
  std::cout << "bigtype:" << type2str[bigtype] << std::endl;
  std::vector<std::pair<double, std::string>> vebignow;
  vebignow.push_back(std::make_pair(ren + change_ren, "ren"));
  vebignow.push_back(std::make_pair(sum_bx, "sum_bx"));
  vebignow.push_back(std::make_pair(sum_wl, "sum_wl"));
  checkValid(bigtype, vebig, vebignow);
  // smalltype(cal by last year) mei jin hong
  std::vector<std::pair<double, int>> vesmalllyp;
  vesmalllyp.push_back(std::make_pair(meilyp*0.01 + 1, 0));
  vesmalllyp.push_back(std::make_pair(jinlyp*0.01 + 1, 1));
  vesmalllyp.push_back(std::make_pair(honglyp*0.01 + 1, 2));
  std::sort(vesmalllyp.begin(), vesmalllyp.end());
  int smalltype = type(vesmalllyp);
  std::cout << "smalltype:" << type2str[smalltype] << std::endl;
  std::vector<std::pair<double, std::string>> vesmallnow;
  vesmallnow.push_back(std::make_pair(mei + change_mei, "mei"));
  vesmallnow.push_back(std::make_pair(jin + change_jin, "jin"));
  vesmallnow.push_back(std::make_pair(hong + change_hong, "hong"));
  checkValid(smalltype, vesmalllyp, vesmallnow);
  std::cout << "please input your change:" << std::endl;
}

void resetChange() {
  change_ren = 0;
  change_mei = 0;
  change_jin = 0;
  change_hong =  0;
  change_bannei = 0;
  change_banwai = 0;
}

void updateChange(const std::string& type, const double change) {
  if (type == "1") {
    change_ren += change;
  } else if (type == "2") {
    change_mei += change;
  } else if (type == "3") {
    change_jin += change;
  } else if (type == "4") {
    change_hong += change;
  } else if (type == "5") {
    change_bannei += change;
  } else if (type == "6") {
    change_banwai += change;
  } else {
    std::cout << "WTFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" << std::endl;
  }
}


int main() {
  init_type2percent();
  std::cin >> ren >> mei >> jin >> hong >> bannei >> banwai
           >> meilyp >> jinlyp >> honglyp >> banneilyp >> banwailyp;
  PrintNow("now");
  // change_eg: 1->3,3.5;4->2,2.7
  std::string input;
  while(getline(std::cin, input)) {
    if (input.size() == 0) {
      continue;
    }
    std::vector<std::string> sp1 = SplitString(input, ";", true);
    resetChange();
    for (auto&& input2 : sp1) {
      std::vector<std::string> sp2 = SplitString(input2, "->", true);
      if (sp2.size() != 2) {
        std::cout << "err_input" << std::endl;
        return 0;
      }
      std::vector<std::string> sp3 = SplitString(sp2[1], ",", true);
      if (sp3.size() != 2) {
        std::cout << "err_input" << std::endl;
        return 0;
      }
      double change = std::stod(sp3[1]);
      std::cout << change << std::endl;
      updateChange(sp2[0], -change);
      updateChange(sp3[0], change);
    }
    PrintNow("after change" + input);
  }
}
