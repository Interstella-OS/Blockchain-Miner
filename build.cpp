// #ifdef _WIN32               
//     #define NOMINMAX
//     #include <windows.h>
//     #include <conio.h>
//     #include <mmsystem.h>       
// #else                       
//     #include <sys/ioctl.h>
//     #include <unistd.h> 
//     #include <termios.h>
// #endif

// #include <iostream>
// #include <exception>
// #include <filesystem>
// #include <thread>
// #include <atomic>
// #include <chrono>

// using namespace std;
// namespace fs = filesystem;
// using namespace chrono;
// using namespace this_thread;

// #define RESET   "\033[0m"
// #define RED     "\033[38;2;255;120;120m"

// #ifdef _WIN32
//     const string program_name = "bin\\main.exe";
//     const string compile_command = string("g++ src\\*.cpp")
//                                  + " -IC:\\OpenSSL-Win64\\include"
//                                  + " -LC:\\OpenSSL-Win64\\lib -o "
//                                  + program_name + 
//                                  " -lwinmm -lssl -lcrypto -lcryptopp -lcurl -lws2_32 -w -std=c++17";
// #else
//     const string program_name = "bin/main";
//     const string compile_command = string("g++ src/*.cpp")
//                                  + " -o " 
//                                  + program_name + 
//                                  " -lssl -lcrypto -lcryptopp -lcurl -w -std=c++17";
// #endif

// bool needs_recompilation() {
//     if(!fs::exists(program_name))
//         return true;
//     auto exe_last_write = fs::last_write_time(program_name);
//     for(auto &p : fs::recursive_directory_iterator("src")){
//         if(p.path().extension() == ".cpp" || p.path().extension() == ".h" || p.path().extension() == ".hpp"){
//             if(fs::last_write_time(p) > exe_last_write)
//                 return true;
//         }
//     }
//     return false;
// }

// void set_cursor_visibility(bool visible){
//     #ifdef _WIN32
//         HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//         CONSOLE_CURSOR_INFO cursorInfo;
//         GetConsoleCursorInfo(hConsole, &cursorInfo);
//         cursorInfo.bVisible = visible;
//         SetConsoleCursorInfo(hConsole, &cursorInfo);
//     #else
//         if (visible) cout << "\033[?25h"; 
//         else cout << "\033[?25l";
//     #endif
// }

// void show_waiting_effect(atomic<bool>& stop){
//     set_cursor_visibility(false);
//     const char* spinner[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
//     int i = 0;
//     while(!stop){
//         cout << "\r" << spinner[i] 
//              << RESET << " Vui lòng chờ ! Đang biên dịch..." << flush;
//         i = (i + 1) % 10;
//         sleep_for(milliseconds(100));
//     }
//     cout << "\r                                               \r";
//     set_cursor_visibility(true);
// }

// void clear_screen(){
//     #ifdef _WIN32 
//         system("cls");
//     #else 
//         system("clear");
//     #endif
// }

// int get_display_width(const char* s){
//     int width = 0;
//     for(int i = 0; s[i] != '\0'; ){
//         unsigned char c = s[i];
//         if(c < 128){ 
//             width += 1; i += 1; 
//         } else{ 
//             width += 1; 
//             i += 2; 
//         }
//     }
//     return width;
// }

// int read_key() {
//     #ifdef _WIN32
//         int c = _getch();
//         if (c == 0 || c == 224) {
//             switch (_getch()) {
//                 case 72: return 72; 
//                 case 80: return 80; 
//                 case 75: return 75; 
//                 case 77: return 77; 
//             }
//         }
//         if (c == 13) 
//             return 13;
//         return c;
//     #else
//         termios oldt, newt;
//         tcgetattr(STDIN_FILENO, &oldt);
//         newt = oldt;
//         newt.c_lflag &= ~(ICANON | ECHO);
//         newt.c_cc[VMIN]  = 1;
//         newt.c_cc[VTIME] = 0;
//         tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//         int c = getchar();
//         if (c == 27) {
//             int c1 = getchar();
//             if (c1 == '[') {
//                 int c2 = getchar();
//                 switch (c2) {
//                     case 'A': c = 72; break; 
//                     case 'B': c = 80; break; 
//                     case 'C': c = 77; break; 
//                     case 'D': c = 75; break; 
//                 }
//             }
//         }
//         if (c == 10) 
//             c = 13;
//         tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//         return c;
//     #endif
// }

// void show_build_menu(){
//     const int item_count = 2;
//     const char* menu[item_count] = {
//         "Chạy file",
//         "Thoát"
//     };
//     int choice = 0;
//     while(true){
//         clear_screen();
//         cout << "Không có thay đổi -> Sử dụng file cũ" << RESET << endl;
//         cout << "┌───────────────┐" << RESET << endl;

//         for (int i = 0; i < item_count; i++) {
//             if (i == choice) {
//                 cout << "│" << RED << " ● " << RESET << menu[i];
//                 int spaces = 12 - get_display_width(menu[i]);
//                 cout << RESET << string(spaces, ' ') << "│" << endl;
//             } else {
//                 cout << "│   " << menu[i];
//                 int spaces = 12 - get_display_width(menu[i]);
//                 cout << RESET << string(spaces, ' ') << "│" << endl;
//             }
//         }
//         cout << "└───────────────┘" << RESET << "\n";
//         int key = read_key();
//         if (key == 72) 
//             choice = (choice - 1 + item_count) % item_count;
//         else if (key == 80)
//             choice = (choice + 1) % item_count;
//         else if (key == 13) {
//             if(choice == 0){
//                 #ifdef _WIN32
//                     system("cd bin && main.exe");
//                 #else
//                     system("cd bin && ./main");
//                 #endif
//                 set_cursor_visibility(true);
//                 exit(0);
//             } 
//             else if(choice == 1){
//                 set_cursor_visibility(true);
//                 exit(0);
//             }
//         }
//     }
// }

// int main(){
//     set_cursor_visibility(false);
//     try {
//         #ifdef _WIN32
//             system("if not exist bin mkdir bin");
//         #else
//             system("mkdir -p bin");
//         #endif
//         if(needs_recompilation()){
//             atomic<bool> stop(false);
//             thread loading(show_waiting_effect, ref(stop));
//             int result = system(compile_command.c_str());
//             stop = true;
//             loading.join();
//             if(result != 0){
//                 throw runtime_error(RED "Biên dịch thất bại !");
//             }
//             cout << "Biên dịch thành công !" << endl;
//             #ifdef _WIN32
//                 system("cd bin && main.exe");
//             #else
//                 system("cd bin && ./main");
//             #endif
//         } 
//         else{
//             show_build_menu();
//         } 
//     } catch(const exception& e){
//         cout << RED << "\nLỗi: " << e.what() << RESET << endl;
//     }
//     set_cursor_visibility(true);
//     return 0;
// }





#ifdef _WIN32               
    #define NOMINMAX
    #include <windows.h>
    #include <conio.h>
    #include <mmsystem.h>       
#else                       
    #include <sys/ioctl.h>
    #include <unistd.h> 
    #include <termios.h>
#endif

#include <iostream>
#include <exception>
#include <filesystem>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
namespace fs = filesystem;
using namespace chrono;
using namespace this_thread;

#define RESET   "\033[0m"
#define RED     "\033[38;2;255;120;120m"

#ifdef _WIN32
    const string program_name = "bin\\main.exe";
    const string include_flags = " -IC:\\OpenSSL-Win64\\include";
    const string link_flags = " -LC:\\OpenSSL-Win64\\lib -lwinmm -lssl -lcrypto -lcryptopp -lcurl -lws2_32 -w -std=c++17";
#else
    const string program_name = "bin/main";
    const string include_flags = "";
    const string link_flags = " -lssl -lcrypto -lcryptopp -lcurl -w -std=c++17";
#endif

fs::file_time_type latest_header_time() {
    fs::file_time_type latest = fs::file_time_type::min();
    for (auto& p : fs::recursive_directory_iterator("src")) {
        auto ext = p.path().extension();
        if (ext == ".h" || ext == ".hpp") {
            auto t = fs::last_write_time(p);
            if (t > latest){
                latest = t;                
            } 
        }
    }
    return latest;
}

vector<string> get_source_files() {
    vector<string> files;
    for (auto& p : fs::recursive_directory_iterator("src")) {
        if (p.path().extension() == ".cpp"){
            files.push_back(p.path().string());
        }
    }
    return files;
}

bool compile_object(const string& cpp_file, const string& obj_file) {
    string cmd = "g++ -c \"" + cpp_file + "\" -o \"" + obj_file + "\""
               + include_flags + " -w -std=c++17";
    return system(cmd.c_str()) == 0;
}

bool link_all(const vector<string>& objects) {
    string cmd = "g++ ";
    for (auto& o : objects){
        cmd += "\"" + o + "\" ";        
    } 
    cmd += "-o " + program_name + link_flags;
    return system(cmd.c_str()) == 0;
}

enum class BuildStatus { 
    NOTHING_TO_DO, 
    SUCCESS, 
    FAILED
};

BuildStatus build_incremental() {
    fs::create_directories("obj");
    fs::create_directories("bin");
    auto header_time = latest_header_time();
    vector<string> sources = get_source_files();
    vector<string> objects, to_compile;
    for (auto& src : sources) {
        fs::path src_path(src);
        string obj_path = "obj/" + src_path.stem().string() + ".o";
        objects.push_back(obj_path);
        bool need_build = true;
        if (fs::exists(obj_path)) {
            auto obj_time = fs::last_write_time(obj_path);
            auto src_time = fs::last_write_time(src_path);
            if (obj_time > src_time && obj_time > header_time){
                need_build = false;
            }
        }
        if (need_build){
            to_compile.push_back(src);            
        } 
    }
    if (to_compile.empty() && fs::exists(program_name)) {
        return BuildStatus::NOTHING_TO_DO;
    }
    vector<thread> workers;
    atomic<bool> all_ok{true};
    for (auto& src : to_compile) {
        fs::path src_path(src);
        string obj_path = "obj/" + src_path.stem().string() + ".o";
        workers.emplace_back([src, obj_path, &all_ok]() {
            if (!compile_object(src, obj_path)){
                all_ok = false;                
            } 
        });
    }
    for (auto& w : workers){
        w.join();        
    } 
    if (!all_ok){
        return BuildStatus::FAILED;        
    } 
    return link_all(objects) ? BuildStatus::SUCCESS : BuildStatus::FAILED;
}

void set_cursor_visibility(bool visible){
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    #else
        if (visible) cout << "\033[?25h"; 
        else cout << "\033[?25l";
    #endif
}

void show_waiting_effect(atomic<bool>& stop){
    set_cursor_visibility(false);
    const char* spinner[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
    int i = 0;
    while(!stop){
        cout << "\r" << spinner[i] 
             << RESET << " Vui lòng chờ ! Đang biên dịch..." << flush;
        i = (i + 1) % 10;
        sleep_for(milliseconds(100));
    }
    cout << "\r                                               \r";
}

void clear_screen(){
    #ifdef _WIN32 
        system("cls");
    #else 
        system("clear");
    #endif
}

int get_display_width(const char* s){
    int width = 0;
    for(int i = 0; s[i] != '\0'; ){
        unsigned char c = s[i];
        if(c < 128){ 
            width += 1; i += 1; 
        } else{ 
            width += 1; 
            i += 2; 
        }
    }
    return width;
}

int read_key() {
    #ifdef _WIN32
        int c = _getch();
        if (c == 0 || c == 224) {
            switch (_getch()) {
                case 72: return 72; 
                case 80: return 80; 
                case 75: return 75; 
                case 77: return 77; 
            }
        }
        if (c == 13) 
            return 13;
        return c;
    #else
        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN]  = 1;
        newt.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int c = getchar();
        if (c == 27) {
            int c1 = getchar();
            if (c1 == '[') {
                int c2 = getchar();
                switch (c2) {
                    case 'A': c = 72; break; 
                    case 'B': c = 80; break; 
                    case 'C': c = 77; break; 
                    case 'D': c = 75; break; 
                }
            }
        }
        if (c == 10) 
            c = 13;
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return c;
    #endif
}

void show_build_menu(){
    const int item_count = 2;
    const char* menu[item_count] = {
        "Chạy file",
        "Thoát"
    };
    int choice = 0;
    while(true){
        clear_screen();
        cout << "Không có thay đổi -> Sử dụng file cũ" << RESET << endl;
        cout << "┌───────────────┐" << RESET << endl;

        for (int i = 0; i < item_count; i++) {
            if (i == choice) {
                cout << "│" << RED << " ● " << RESET << menu[i];
                int spaces = 12 - get_display_width(menu[i]);
                cout << RESET << string(spaces, ' ') << "│" << endl;
            } else {
                cout << "│   " << menu[i];
                int spaces = 12 - get_display_width(menu[i]);
                cout << RESET << string(spaces, ' ') << "│" << endl;
            }
        }
        cout << "└───────────────┘" << RESET << "\n";
        int key = read_key();
        if (key == 72) 
            choice = (choice - 1 + item_count) % item_count;
        else if (key == 80)
            choice = (choice + 1) % item_count;
        else if (key == 13) {
            if(choice == 0){
                #ifdef _WIN32
                    system("cd bin && main.exe");
                #else
                    system("cd bin && ./main");
                #endif
                set_cursor_visibility(true);
                exit(0);
            } 
            else if(choice == 1){
                set_cursor_visibility(true);
                exit(0);
            }
        }
    }
}

int main(){
    set_cursor_visibility(false);
    try {
        #ifdef _WIN32
            system("if not exist bin mkdir bin");
            system("if not exist obj mkdir obj");
        #else
            system("mkdir -p bin obj");
        #endif
        atomic<bool> stop(false);
        thread loading(show_waiting_effect, ref(stop));
        BuildStatus status = build_incremental();
        stop = true;
        loading.join();
        if (status == BuildStatus::FAILED) {
            throw runtime_error(RED "Biên dịch thất bại !");
        }
        else if (status == BuildStatus::SUCCESS) {
            cout << "Biên dịch thành công !" << endl;
            #ifdef _WIN32
                system("cd bin && main.exe");
            #else
                system("cd bin && ./main");
            #endif
        }
        else {
            show_build_menu();
        }
    } catch(const exception& e){
        cout << RED << "\nLỗi: " << e.what() << RESET << endl;
    }
    set_cursor_visibility(true);
    return 0;
}
