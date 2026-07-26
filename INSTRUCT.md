# Blockchain Miner

Demo Blockchain Miner C++ sử dụng **Crypto++**, kết hợp **SHA-256**, **Proof of Work (PoW)**, **RSA Digital Signature** và mạng **P2P** cho phép nhiều Node cùng tham gia đào.

- **Ngôn ngữ:** C++
- **Hoàn thành:** 26/07/2026
- **Tác giả:** Nguyễn Trường Chinh (NTC++)
- **Giấy phép:** MIT License

---

# Blockchain hoạt động như thế nào?

## Hash SHA-256 là gì?
SHA-256 là thuật toán băm biến dữ liệu đầu vào thành chuỗi băm dài **256 bit (64 ký tự)**.

### Đặc điểm
- Hàm băm một chiều, tất là không thể giải mã ngược.
- Chỉ cần thay đổi một ký tự ở dữ liệu đầu vào thì kết quả băm sẽ thay đổi hoàn toàn.
- Trong demo:
  - MD5 dùng để tạo Transaction Code.
  - SHA-256 dùng để băm toàn bộ block nhằm bảo vệ chuỗi blockchain.

---

## Chữ ký số RSA (RSA Digital Signature)
Mỗi người dùng tham gia mạng sẽ sở hữu:
- Public Key (Khóa công khai - địa chỉ ví)
- Private key (Khóa riêng)

Quy trình hoạt động:
1. Người gửi ký giao dịch bằng **Private Key**.
2. Sinh ra một **Digital Signature**.
3. Các node khác sử dụng **Public Key** để xác minh chữ ký.

### Lợi ích
- Xác thực người gửi.
- Chống giả mạo giao dịch.
- Bảo vệ tính toàn vẹn của dữ liệu.

---

# Quy trình tạo Block
Khi một Block được tạo, hệ thống sẽ chuẩn bị:
- Danh sách Transaction đã xác thực
- Previous Hash
- Timestamp
- Nonce

Ví dụ dữ liệu được băm:

```text
SHA256(
    block_id +
    transactions +
    previous_hash +
    timestamp +
    nonce
)
```

---

# Proof of Work (PoW)
Miner sẽ liên tục thử các giá trị Nonce:
```text
nonce = 0
nonce = 1
nonce = 2
nonce = 3
...
```

Mỗi lần thử sẽ băm lại:
```text
Hash = SHA256(Block Data)
```

Cho tới khi mã hash thỏa điều kiện độ khó.
Ví dụ:

```text
Difficulty = 4

Hash:
a6957asd...
=> Không hợp lệ

000089a5...
=> Hợp lệ (vì có 4 số 0 ở đầu mã hash)
```

---

# Đua đào giữa nhiều Node (P2P Mining Race)

Trong demo này, việc đào không chỉ diễn ra ở 1 máy — mà nhiều Node kết nối qua mạng P2P sẽ cùng đào chung 1 lúc:

1. Khi 1 Node bấm đào, nó gửi yêu cầu cho toàn mạng, rủ các Node khác cùng tham gia.
2. Mọi Node bắt đầu thử nonce từ 0, chạy độc lập, không ai biết ai đang tới đâu.
3. Node nào tìm ra Nonce hợp lệ đầu tiên sẽ gửi block đã đào (kèm Nonce, Hash thật) cho cả mạng.
4. Các Node còn lại nhận được tin sẽ dừng đào ngay lập tức, tự băm lại block nhận được để kiểm tra đúng chưa, rồi mới đồng bộ vào blockchain của mình.

Đây là cách demo mô phỏng việc "ai đào nhanh hơn thì thắng" giống việc đào coin thật trên mạng lưới bitcoin, chỉ khác là quy mô nhỏ, chạy trên vài Node local thay vì hàng triệu máy trên toàn cầu.

---

# Difficulty

Difficulty quy định số lượng số 0 ở đầu Hash.
Ví dụ:
```text
Difficulty = 5

00000abfd8...
```

Difficulty càng cao:
- Càng nhiều phép tính.
- Càng mất nhiều thời gian đào.
- Càng tốn tài nguyên máy móc.

---

# Sau khi Mine thành công

Khi tìm được Nonce phù hợp:
- Block được đào thành công.
- Block được thêm vào Blockchain.
- Block được lưu lại vào file lịch sử để tra cứu sau này.

> **Lưu ý:** Đây là bản demo học tập, chưa cài đặt cơ chế thưởng coin như các Blockchain thật. Node đào thắng chỉ đơn giản là được ghi nhận block vào chuỗi, chưa có phần thưởng gì thêm cho miner.

Quá trình này thường được gọi là đào coin.

---

# Genesis Block

Genesis block là block đầu tiên của blockchain.
Đặc điểm:
- Index = 0
- Previous Hash = 64 ký tự '0'
- Chứa thông điệp khởi tạo của Blockchain.

Ví dụ:

```text
Previous Hash

0000000000000000000000000000000000000000000000000000000000000000
```

---

# Tính chất của Blockchain

## Không thể đoán trước Hash
Không có công thức để dự đoán Hash.
Chỉ có thể:
- Dò tuân tự 
- Thử liên tục các giá trị nonce

---

## Khó tạo nhưng dễ kiểm tra
Đây là đặc điểm quan trọng của PoW.
- Tạo Block hợp lệ rất tốn thời gian.
- Kiểm tra Hash chỉ cần một phép tính SHA-256.

---

## Tính bất biến
Nếu chỉ sửa 1 ký tự trong một block cũ:
- Hash của block đó thay đổi.
- Previous hash của block kế tiếp không còn đúng.
- Toàn bộ blockchain phía sau bị vô hiệu.

---

# Ứng dụng

Blockchain được sử dụng trong:
- Bitcoin
- Ethereum
- Smart Contract
- Chữ ký điện tử
- Bảo mật mật khẩu
- Kiểm tra toàn vẹn phần mềm
- Kiểm tra file tải về

---

# Tóm lại

**Mining là tìm nonce để hash thỏa điều kiện của hệ thống đã cho**
Đảm bảo tính **bảo mật**, **toàn vẹn dữ liệu** và **phi tập trung** của Blockchain.

---

## Tác giả
**Nguyễn Trường Chinh (NTC++)**<br>
**GitHub:** [https://github.com/trgchinhh](https://github.com/trgchinhh)

---

> 📌 Dự án nhỏ được phát triển với mục đích học tập và nghiên cứu. Mọi góp ý và đóng góp đều được hoan nghênh. Nếu thấy hữu ích thì cho mình xin 1 sao cho repo này !!!
