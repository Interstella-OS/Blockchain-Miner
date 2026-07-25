#include "lib//utils.hpp"

const vector<string> names = {
    "Truong Chinh", "Truong An", "Duy Minh", "Duy Quang", "Ngoc Tu",
    "Thanh Phuc", "Manh Hung", "The An", "Thien An", "Gia Bao", 
    "Khanh Dang", "Hai Dang", "Khanh Duy", "Bao Khanh", "Manh Cuong",
    "Minh Khoi", "Hoang Long", "Quoc Anh", "Bao Long", "Gia Huy",
    "Tuan Anh", "Duc Anh", "Huu Phuoc", "Minh Triet", "Viet Anh",
    "Thanh Tung", "Cong Vinh", "Van Duc", "Quang Hai", "Dinh Trong",
    "Minh Quan", "Nhat Minh", "Gia Minh", "Huu Thang", "Minh Duc",
    "Tien Dat", "Xuan Truong", "Hoang Minh", "Thanh Nam", "Duc Luong",
    "Bao Nam", "Anh Dung", "Huu Dat", "Chi Kien", "Dang Khoa",
    "Hoang Nam", "Phi Long", "Gia Khiem", "Trung Kien", "Bao Khang",
    "Phuc Lam", "Ha Long", "Gia Binh", "Duc Khiem", "Minh Nhat",
    "Tien Dung", "Quang Minh", "Hung Cuong", "Huu Trong", "Minh Hieu",
    "Tuan Kiet", "Tran Minh", "Hoang An", "Thien Nhan", "Khanh Linh"
};

string time_now() {
    return datetime::now().strftime("%H:%M:%S - %d/%m/%Y");
}