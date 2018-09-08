#include <iostream>
#include <functional>
#include <sstream>

template<typename ...T>
auto sum(T &&...a) {
    return (a +...);
}

template<typename T1, typename T2>
auto min(T1 a, T2 b) {
    return a < b ? a : b;
}

template<typename T0, typename ...T>
auto min(T0 &&a0, T &&...a) {
    return min(a0, min(a...));
}


template<class F, class ...G>
auto composer(F &&f, G &&... g) {
    return [&f, &g...](auto &&...args) { return f(g(args)...); };
}

void sum2_helper(std::tuple<int, double>& base, int a) {
    std::get<int>(base) += a;
}


void sum2_helper(std::tuple<int, double>& base, double a) {
    std::get<double>(base) += a;
}

template<typename ...T>
std::tuple<int, double> sum2(T &&... args) {
    std::tuple<int, double> ans;
    (sum2_helper(ans,args),...);
    return ans;
}

int foo(int a, int b) {
    return a + b;
}

int g1(int a) {
    return a * 2;
}
//second = true if separator(str type), else - true;
template <typename T>
std::pair<std::string,bool> ToString_helper(T&& val){
    if constexpr (std::is_convertible<const char[2],T>::value){
        return std::make_pair(val,true);
    }
    else{
        std::stringstream ss;
        ss<<val;
        std::string str;
        ss>>str;
        return std::make_pair(str, false);
    }
}

template <typename T>
void ToString_adder(T&& val, std::string& str, std::string& separator){
    auto adding_struct=ToString_helper(val);
    if(adding_struct.second)
        separator=adding_struct.first;
    else {
        str+=adding_struct.first;
        str+=separator;
    }
}

template <typename ...T>
std::string ToString(T&& ... vals){
    std::string ans, separator;
    (ToString_adder(vals,ans,separator),...);
    return ans;
}
int main() {
    int n = 17;
    double x = 6.75;
    std::cout<<ToString(";", 25, 3.7, n,"$", x);
    return 0;
}