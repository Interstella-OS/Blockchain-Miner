//  ____  _            _        _           _       
// |  _ \| |          | |      | |         (_)      
// | |_) | | ___   ___| | _____| |__   __ _ _ _ __  
// |  _ <| |/ _ \ / __| |/ / __| '_ \ / _` | | '_ \    Demo blockchain C++ (Nâng cấp RSA)
// | |_) | | (_) | (__|   < (__| | | | (_| | | | | |   Thư viện: Crypto++ 
// |____/|_|\___/ \___|_|\_\___|_| |_|\__,_|_|_| |_|   Tác giả: Nguyễn Trường Chinh
// 
// Bản quyền: MIT LICENSE 2026

#include "include.hpp"

void loading_bar(int seconds) {
    ProgressBar bar{
        BarWidth{40},
        Start{"["},
        Fill{"#"},
        Lead{"#"},
        Remainder{"-"},
        End{"]"},
        ShowPercentage{true},
        PrefixText{"Đang chuẩn bị giao dịch: "},
    };
    const int total = seconds * 25;
    for(int i = 0; i <= total; i++){
        bar.set_progress(i*100/total);
        this_thread::sleep_for(milliseconds(40));
    }
}

int main() {
    system("cls");
    printbanner(banner);

    show_console_cursor(false);
    UserBlockchain userblockchain;
    userblockchain.check_and_initialize_keys();

    cout << "\n\n";

    int number_blocks = 5;
    int difficulty = 2; 
    Blockchain blockchain(difficulty);
    TransactionManager ts_manager;

    loading_bar(3);
    cout << "Bắt đầu đào " << number_blocks << " block với độ khó " << difficulty << "\n";
    this_thread::sleep_for(seconds(2));

    cout << "\n\n";

    for(int i = 0; i < number_blocks; i++) {
        json blockdata = ts_manager.create_transaction();
        json ts_list = blockdata.contains("transactions") ? blockdata["transactions"] : blockdata;
        bool all_valid = true;

        for(size_t j = 0; j < ts_list.size(); j++){
            json single_ts = ts_list[j];
            if(!ts_manager.verify_transaction(single_ts)){
                cout << "Giao dịch " << (j + 1) << " trong block " << (i + 1) << " không hợp lệ !" << endl;
                all_valid = false;
                break;
            } 
        }
        if(all_valid){
            cout << "Đã xác thực 3 giao dịch trong block " << (i + 1) << endl;
            blockchain.add_block(blockdata);
        } else {
            cout << "Bỏ qua block " << (i + 1) << " do chứa giao dịch không hợp lệ" << endl;
        }
    }

    blockchain.isvalid_chain();
    cout << "Hoàn tất đào " << number_blocks 
         << " block với " << blockchain.total_time << " giây" << endl;

    show_console_cursor(false);
    return 0;
}