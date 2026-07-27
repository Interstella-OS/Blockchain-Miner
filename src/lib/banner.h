#ifndef BANNER_H
#define BANNER_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const string banner = R"(╔═════════════════════════════════════╗
║       Core Blockchain C++           ║
║  RSA - P2P - Mining - Logging - SC  ║
║  Version: 0.0.2                     ║
║  Author : Truong Chinh              ║
║  Github : github.com/trgchinhh      ║
╚═════════════════════════════════════╝

)";

inline void printbanner(const string banner){
    stringstream ss(banner);
    string line;
    while(getline(ss, line)){
        cout << line << endl;
    }
}

#endif