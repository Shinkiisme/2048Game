#ifndef thu_vien_2048
#define thu_vien_2048

#include <iostream>
#include <iomanip> // Thư viện để căn chỉnh lề.
#include <cmath> // Thư viện để tính toán.
#include <cstdlib> // Thư viện để sinh số ngẫu nhiên.
#include <ctime> // Thư viện để lấy seed thời gian thực.
#include <utility> // Thư viện để dùng kiểu dữ liệu pair.
#include <conio.h> // Thư viện để dùng hàm đọc ký tự từ bàn phím mà không cần Enter.
#include <fstream> // Thư viện để tương tác với file: đọc, ghi, lưu kết quả, ...
#include <sstream> // Thư viện để chuyển đổi dữ liệu string thành int.
#include <string> // Thư viện để xử lý các xâu ký tự.
#include <filesystem> // Thư viện để tạo thư mục lưu game.

// Khai báo cấu trúc Node để sử dụng cho danh sách liên kết đôi.
struct Node{
    
    int* game_state;
    Node* next;
    Node* prev;

};

// Khai báo hàm xoá màn hình theo hệ điều hành.
void clear_screen();

// Khai báo hàm để kiểm tra xem đã tồn tại file lưu hay chưa, nếu chưa thì tạo mới.
void database(const std::string &file);

// Khai báo hàm nhập và kiểm tra trùng lặp tên người chơi.
std::string player_name();

// Khai báo hàm load lại bản lưu cũ mà người chơi đã lưu.
int** load_save(std::string username, int &size);

// Khai báo hàm nhập kích thước khu vực chơi.
int size_input();

// Khai báo hàm tạo khu vực chơi như mong muốn của người dùng.
int** make_grid(int size);

// Khai báo hàm in ra màn hình khu vực chơi.
void print_grid(int** bang, int size);

// Khai báo hàm tạo ra số mới.
void rand_number(int** bang, int size);

// Khai báo hàm gộp số theo hàng.
void merge_row(int** bang, int size, char button);

// Khai báo hàm gộp số theo cột.
void merge_col(int** bang, int size, char button);

// Khai báo hàm kiểm tra thắng thua.
bool win_check(int** bang, int size, bool afterWin);

bool lose_check(int** bang, int size);

// Khai báo hàm điều khiển của người chơi.
char control();

// Khai báo hàm tính điểm.
int score(int** bang, int size);


// Khai báo hàm thêm tên người chơi, sắp xếp và in ra bảng xếp hạng.
void leaderboard(int point, std::string username, int size);


// Khai báo hàm lưu lại trạng thái trò chơi nếu người chơi muốn lưu để lần sau chơi tiếp.
void save_game(int** bang, int size, std::string username);


// Khai báo hàm lưu lại trạng thái của bảng chơi vào một nút mới trên danh sách liên kết.
void new_state(int** bang, int size, Node* &current_node);


// Khai báo hàm lưu lại trạng thái của bảng chơi trước khi undo (tương tự new_state nhưng chỉ gọi khi undo ở nút cuối để không xoá các trạng thái redo mỗi khi undo).
void save_before_undo(int** bang, int size, Node* &current_node);


// Khai báo hàm để thực hiện tính năng undo.
void undo(int** bang, int size, Node* &current_node);


// Khai báo hàm để thực hiện tính năng redo.
void redo(int** bang, int size, Node* &current_node);

#endif
