#include <iostream>
#include <iomanip> // Thư viện để căn chỉnh lề.
#include <cmath> // Thư viện để tính toán.
#include <cstdlib> // Thư viện để sinh số ngẫu nhiên.
#include <ctime> // Thư viện để lấy seed thời gian thực.
#include <utility> // Thư viện để dùng kiểu dữ liệu pair.
#include <conio.h> // Thư viện để dùng hàm đọc ký tự từ bàn phím mà không cần Enter.
#include <fstream> // Thư viện để tương tác với file: đọc, ghi, lưu kết quả, ...
#include <sstream>
#include <string> // Thư viện để xử lý các xâu ký tự.


void database(const std::string &file);

// Khai báo hàm nhập và kiểm tra trùng lặp tên người chơi.
std::string player_name();

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


void leaderboard(int point, std::string username);

void save_game(int** bang, int size, std::string username);
