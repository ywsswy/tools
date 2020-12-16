//#define YLFILE
//#define YWATCH
#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<map>
#include<algorithm>
#include<cmath>
#define YINDEX(x) (x-1)
/*for built-in type(except c_array) & map & list & vector*/
class YPrint{
public:
    static int indent_;
    template<typename T> static void W(const std::string &info, const T &x, bool clr = false) {
        #ifdef YWATCH
        if (clr) system("clear"); //system("cls"); in windows
        std::cout << "\n\\**********************\n" << info << "\n" << x << "**********************\\\n";
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

class OutlineNode{
public:
    OutlineNode();
    int father_id_;//0: root
    int section_type_;//2: section, 3: aside, 4:article, 5:nav
    std::list<int> child_id_;
    bool enable_brother_;
    int brother_id_;//next little brother
    bool enable_title_;//false: "Untitled Section"
    std::string title_;
};
std::ostream & operator <<(std::ostream &os,const OutlineNode &yc){
    os << "father_id_:" << yc.father_id_ << '\t'
        << "child_id_:" << yc.child_id_ << '\n'
        << "title:";
    if(yc.enable_title_){
        os << yc.title_;
    }else{
        os << "Untitled Section";
    }
    os << '\n';
    if(yc.enable_brother_){
        os << "brother_id_:" << yc.brother_id_;
    }
    return os;
}
OutlineNode::OutlineNode(){
    this->father_id_ = 0;
    enable_brother_ = false;
    enable_title_ = false;
    section_type_ = 0;
}
void HtmlToStr(std::string &str){
    std::string buf_str;
    while(getline(std::cin,buf_str)){
        str += buf_str;
    }
}
int FindFromStr(std::string &str, std::string &data, size_t &start_loc){
    size_t first_loc = std::string::npos;
    int section_type = 0;
    size_t buf_loc;
    std::vector<std::string> find_str;
    find_str.push_back("<section");//section_type:2
    find_str.push_back("<aside");
    find_str.push_back("<article");
    find_str.push_back("<nav");
    find_str.push_back("</section>");
    find_str.push_back("</aside>");
    find_str.push_back("</article>");
    find_str.push_back("</nav>");
    for(size_t i = 1;i<=find_str.size();i++){
        buf_loc = str.find(find_str[YINDEX(i)],start_loc);
        if(buf_loc < first_loc){
            first_loc = buf_loc;
            section_type = i+1;
        }
    }
    buf_loc = str.find("<h1",start_loc);
    if(buf_loc < first_loc){
        first_loc = buf_loc;
        buf_loc = str.find("</h1>",first_loc);
        if(buf_loc == std::string::npos){
            return -1;
        }else{
            first_loc = str.find(">",first_loc);
            if(first_loc == std::string::npos || first_loc >= buf_loc){
                return -1;
            }else{
                data = str.substr(first_loc+1,buf_loc-first_loc-1);
                start_loc = buf_loc + 1;
                return 1;
            }
        }
    }
    if(first_loc == std::string::npos){
        return 0;
    }else{//(section_type >= 2)
        start_loc = first_loc + 1;
        return section_type;
    }
}
void OutputOutline(std::map<int,OutlineNode> &outline, int node_id, int layer, int rank){
    for(int i = 1;i<=layer;i++){
        std::cout << '\t';
    }
    std::cout << rank << ". ";
    if(outline[node_id].enable_title_){
        std::cout << outline[node_id].title_ << '\n';
    }else{
        std::cout << "Untitled Section" << '\n';
    }
    int i = 1;
    for(std::list<int>::iterator it = outline[node_id].child_id_.begin();it != outline[node_id].child_id_.end();it++,i++){
        OutputOutline(outline,*it,layer+1,i);
    }
    if(outline[node_id].enable_brother_){
        OutputOutline(outline,outline[node_id].brother_id_,layer,rank+1);
    }
}
int main() {
    std::cin.tie(0);
    #ifdef YLFILE
    std::cin.rdbuf((new std::ifstream("yin1.txt"))->rdbuf());
    //std::cout.rdbuf((new std::ofstream("yout1.txt"))->rdbuf());
    #endif
    std::string str = "";
    HtmlToStr(str);
    //std::cout << str;//
    int now_id = 0;//wanted can identified by this
    std::map<int,OutlineNode> outline;//id(1s),
    OutlineNode first_node;
    outline[outline.size()+1] = first_node;
    now_id = outline.size();
    size_t start_loc = 0;
    bool match_error = false;
    while(true){
        int result = 0;//0: end of file, -1: match error, 1: h1, 2: section, 3: aside, 4: article, 5:nav
                       //                                       6: /section, 7: /aside, 8: /article, 9: /nav
        std::string data;//store the <h1> title
        result = FindFromStr(str,data,start_loc);
        //std::cout << result << '\n';//
        if(result >= 2 && result <= 5){
            OutlineNode child_node;
            child_node.section_type_ = result;
            child_node.father_id_ = now_id;
            outline[outline.size()+1] = child_node;
            outline[now_id].child_id_.push_back(outline.size());
            now_id = outline.size();
        }else if(result >= 6 && result <= 9){
            if(result - outline[now_id].section_type_ != 4){//match failed
                match_error = true;
            }else{
                now_id = outline[now_id].father_id_;
            }
        }else if(result == 1){
            if(!outline[now_id].enable_title_){
                outline[now_id].enable_title_ = true;
                outline[now_id].title_ = data;
            }else/* if(!outline[now_id].enable_brother_)*/{
                outline[now_id].enable_brother_ = true;
                OutlineNode brother_node;
                brother_node.enable_title_ = true;
                brother_node.title_ = data;
                brother_node.section_type_ = outline[now_id].section_type_;
                brother_node.father_id_ = outline[now_id].father_id_;
                outline[outline.size()+1] = brother_node;
                outline[now_id].brother_id_ = outline.size();
                now_id = outline.size();
            }
        }
        if(result == 0){
            break;
        }
    }
    if(match_error){
        std::cout << "error exit." << '\n';
    }else{
        //output outline
        YPrint::W("outline",outline);
        OutputOutline(outline,1,0,1);
    }
    return 0;
}
