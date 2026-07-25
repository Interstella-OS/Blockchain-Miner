<p align="center">
  <img height="120" src="img/logo.png"/>
</p>

<p align="center">
  <a href="https://github.com/trgchinhh/miningblock-cpp">
    <img src="https://img.shields.io/badge/Language-C%2B%2B-blue.svg" alt="Language"/>
  </a>
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License"/>
  </a>
  <a href="https://github.com/trgchinhh">
    <img src="https://img.shields.io/badge/Author-Tr%C6%B0%E1%BB%9Dng%20Chinh-yellow" alt="Author"/>
  </a>
</p>

## Mining block C++ (Nâng cấp RSA)

Dự án này là một ứng dụng giả lập (mô phỏng) mạng lưới Blockchain phân tán viết bằng ngôn ngữ C++. Phiên bản nâng cấp này tích hợp cơ chế bảo mật ví điện tử bất đối xứng bằng thuật toán RSA (thông qua thư viện Crypto++) và cơ chế đồng thuận Proof of Work (PoW) dựa trên hàm băm mật mã học SHA-256

![Blockchain demo](docs/miningblock-demo.gif)

## Tổng quan kiến trúc & Quy trình vận hành
Hệ thống hoạt động như một chu trình khép kín bao gồm 4 giai đoạn chính từ lúc khởi tạo người dùng cho đến khi khối được đóng vào chuỗi:

```bash
  [Khởi tạo Ví] ──> [Tạo & Ký Giao dịch] ──> [Xác thực Chữ ký] ──> [Đào Khối PoW] ──> [Thêm vào Chuỗi]
   (RSA Keys)         (Private Key)            (Public Key)         (Tìm Nonce)       (Liên kết Hash)
```

## Chi tiết quy trình vận hành 
| Bước | Giai Đoạn | Hành Vi Hệ Thống & Logic Xử Lý | Kết Quả Đầu Ra (Output) |
| :---: | :--- | :--- | :--- |
| **1** | **Khởi Tạo Ví** *(Wallet Gen)* | Hệ thống duyệt danh sách Users. Gọi thư viện Crypto++ sinh cặp khóa RSA 2048-bit. Dùng `Base64Encoder` chuyển khóa nhị phân thành chuỗi văn bản. | Xuất hiện 2 file `private_keys.json` và `public_keys.json` chứa các chuỗi kết thúc bằng dấu `=`. |
| **2** | **Tạo Giao Dịch** *(TX Creation)* | Người dùng tạo lệnh chuyển tiền. Hệ thống gom các trường dữ liệu: `sender`, `recipient`, `amount`, `timestamp` rồi băm bằng MD5 để tạo mã định danh `tx_id`. | Một object `Transaction` được khởi tạo, trạng thái lúc này: *Chưa có chữ ký*. |
| **3** | **Ký Số Giao Dịch** *(Sign TX)* | Hệ thống lấy `PrivateKey` của người gửi từ JSON, dùng `RSASS<PKCS1v15, SHA256>::Signer` để ký lên chuỗi dữ liệu gốc, mã hóa qua `HexEncoder`. | Trường `signature` trong Transaction được điền một chuỗi Hex dài (Ví dụ: `A3F4E2...`). |
| **4** | **Xác Thực Chữ Ký** *(Verify TX)* | Validator tiếp nhận giao dịch. Trích xuất `PublicKey` của người gửi từ JSON, dùng `Verifier` để giải mã chữ ký và đối chiếu với dữ liệu gốc của giao dịch. | **Hợp lệ:** Giao dịch được đưa vào hàng đợi (Mempool). <br>**Thất bại (Bị sửa đổi):** Hủy bỏ giao dịch ngay lập tức. |
| **5** | **Đóng Gói Khối** *(Block Packaging)* | Gom toàn bộ giao dịch hợp lệ từ hàng đợi cho vào một `vector<Transaction>`. Lấy mã băm của khối trước đó (`previous_hash`) gán vào khối mới. | Khối mới (`Block`) được hình thành với `nonce = 0`, sẵn sàng để đào. |
| **6** | **Đồng Thuận PoW** *(Mining)* | Miner chạy vòng lặp `while(true)`. Thực hiện băm chuỗi liên kết: `Index + PreviousHash + Timestamp + Nonce + Data` bằng thuật toán SHA-256. | Kiểm tra mã băm: <br>- *Sai:* `nonce++` và băm lại. <br>- *Đúng:* (Đủ số `0` ở đầu) khóa số `nonce` và dừng đào. |
| **7** | **Liên Kết Chuỗi** *(Chain Append)* | Mã băm hợp lệ vừa tìm được sẽ gán thành `hash` chính thức của khối. Khối này được `push_back` vào vector chuỗi chính (`Blockchain`). | Khối mới được ghi nhận thành công, số dư tài khoản của các ví được cập nhật theo sổ cái. |

## Các tính năng nâng cấp nổi bật

* **Bảo mật ví điện tử (RSA Keypair):** Tự động sinh ngẫu nhiên cặp khóa Private Key (Bảo mật) và Public Key (Công khai) độ dài 1024-bit hoặc 2048-bit tùy chỉnh cho toàn bộ User, quản lý lưu trữ an toàn dưới dạng mã hóa Base64 trong tệp JSON
* **Chữ ký số giao dịch (RSA Signature):** Người gửi bắt buộc phải ký vào gói dữ liệu giao dịch bằng Private Key. Hệ thống sử dụng Public Key để verify, chống gian lận dữ liệu và mạo danh ví người khác
* **Mã hóa bất đối xứng:** Kết hợp bộ lọc mã hóa Crypto++ (`HexEncoder`, `Base64Decoder`) để đồng bộ hóa luồng dữ liệu nhị phân thô sang dạng chuỗi lưu trữ
* **Cơ chế Proof of Work (PoW):** Miner liên tục đào để tìm chỉ số `Nonce` để hàm băm SHA256 của toàn khối thỏa mãn độ khó (`Difficulty`) cấu hình trước.

---

## Mẫu public key và private key lưu vào file json
```json
"Truong Chinh": {
    "public_key": "MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQ..."
},
```

```json
"Truong Chinh": {
    "private_key": "MIICcwIBADANBgkqhkiG9w0BAQEFAASCAl0wg..."
},
```

---

## Yêu cầu hệ thống & Thư viện

Để biên dịch và chạy dự án này, hệ thống của bạn cần cài đặt các thư viện sau:

1.  **Crypto++ (cryptopp):** Thư viện mã hóa chuyên sâu phục vụ thuật toán ký RSA
2.  **OpenSSL (libssl & libcrypto):** Phục vụ cho các hàm băm cơ bản

### Hướng dẫn cài nhanh Crypto++ trên Windows (MinGW64 / MSYS2)

Mở terminal MSYS2 (UCRT64 hoặc MINGW64) trong bộ trình dịch MSYS2 và chạy lệnh:
```bash
# Đối với môi trường UCRT64 
pacman -S mingw-w64-ucrt-x86_64-cryptopp

# Đối với môi trường MINGW64 
pacman -S mingw-w64-x86_64-cryptopp
```

### Biên dịch và khởi chạy 
```bash
git clone https://github.com/trgchinhh/miningblock-cpp.git
cd miningblock-cpp
g++ build.cpp -o .\build.exe
.\build.exe
```
---

**Lưu ý về tính thực tiễn**

- Đây là phiên bản demo nhỏ giúp hiện thực hóa các khái niệm lý thuyết cốt lõi của Blockchain (Cấu trúc chuỗi, RSA, SHA-256) bằng ngôn ngữ C++.

- Trên thực tế, các kiến trúc Blockchain thương mại sở hữu độ phức tạp thâm sâu hơn rất nhiều. Từ góc độ của một Miner cho đến cấu trúc mật mã học, hệ thống thực tế đòi hỏi các công nghệ bảo mật tối tân, khả năng tối ưu hóa phần cứng và các giao thức đồng thuận nghiêm ngặt để đảm bảo an toàn tuyệt đối trước mọi cuộc tấn công mạng.

> Dự án được xây dựng với mục đích nghiên cứu, học tập nền tảng và không khuyến khích áp dụng trực tiếp vào các hệ thống thương mại thực tế.

---

## Tác giả
**Nguyễn Trường Chinh (NTC++)**<br>
**GitHub:** [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh.
