#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const string banner = R"(╔══════════════════════════════════╗
║         Block Mining C++         ║
║  C++ block mining simulation     ║
║  Version: 0.0.1                  ║
║  Author : Truong Chinh           ║
║  Github : Github.com/trgchinhh   ║
╚══════════════════════════════════╝

)";

inline void printbanner(const string banner){
    stringstream ss(banner);
    string line;
    while(getline(ss, line)){
        cout << line << endl;
    }
}