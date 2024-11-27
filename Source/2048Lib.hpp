#ifndef _2048_Lib_H_
#define _2048_Lib_H_

#include <iostream>
#include <cstdlib> // Thư viện để sinh số ngẫu nhiên
#include <ctime> // Thư viện để lấy seed thời gian thực
#include <fstream> // Thư viện để tương tác với file: đọc, ghi, lưu kết quả, ...
#include <sstream> // Thư viện để chuyển đổi dữ liệu string thành int
#include <string> // Thư viện để xử lý các xâu ký tự
#include <utility> // Thư viện để sử dụng swap
#include <filesystem> // Thư viện để tạo thư mục lưu game
#include <SFML/Graphics.hpp> // Thư viện tạo giao diện đồ họa
#include <SFML/Window.hpp> // Thư viện quản lý cửa sổ và các sự kiện của cửa sổ (đóng cửa sổ, nhập liệu từ bàn phím, chuột)
#include <SFML/System.hpp> // Thư viện hỗ trợ các thao tác về thời gian


// Cấu trúc Node để lưu trạng thái bảng chơi trong danh sách liên kết đôi
struct Node {
    int* gameState; // Con trỏ lưu trạng thái bảng chơi hiện tại
    Node* next;     // Con trỏ trỏ tới nút tiếp theo
    Node* prev;     // Con trỏ trỏ tới nút trước đó
};

// Cấu trúc lưu tọa độ trên bảng chơi
struct ToaDo {
    int x; // Tọa độ dòng
    int y; // Toạ độ cột
};



/* ================= DATA.CPP ================= */



/**
 * Hàm kiểm tra xem file lưu trữ đã tồn tại hay chưa, nếu chưa sẽ tự động tạo file mới
 * @param file: Tên file cần kiểm tra hoặc tạo mới
 */
void database(const std::string& file);


/**
 * Hàm nhập và kiểm tra tên người chơi, đảm bảo không trùng lặp
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @return Tên người chơi được nhập
 */
std::string playerName(sf::RenderWindow& window, const sf::Font& font);


/**
 * Hàm đọc dữ liệu trò chơi đã lưu từ file và trả về trạng thái bảng chơi
 * @param size: Biến tham chiếu để lưu kích thước bảng chơi được đọc từ file
 * @param username: Tên người chơi, được sử dụng để tìm file lưu tương ứng trong thư mục "Saves"
 * @return Con trỏ cấp 2 đại diện cho bảng trò chơi đã lưu. Trả về nullptr nếu không tìm thấy file lưu
 */
int** loadSave(int& size, std::string username);


/**
 * Hàm lưu trạng thái trò chơi hiện tại vào file, bao gồm tên người chơi, kích thước bảng chơi và bảng chơi
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param username: Tên người chơi, dùng để đặt tên file lưu
 */
void saveGame(int** bang, const int& size, const std::string& username);


/**
 * Hàm lấy giá trị lớn nhất giữa hai số nguyên
 * @param a: Số nguyên thứ nhất
 * @param b: Số nguyên thứ hai
 * @return Giá trị lớn nhất trong hai số a và b
 */
int max(int a, int b);


/**
 * Hàm thêm thông tin người chơi, sắp xếp bảng xếp hạng và hiển thị lên giao diện
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @param size: Kích thước bảng chơi
 * @param username: Tên người chơi
 * @param point: Điểm số của người chơi
 */
void leaderboard(sf::RenderWindow &window, const sf::Font& font, const int& size, const std::string& username, const int& point);



/* ================= NEWGAME.CPP ================= */



/**
 * Hàm khởi tạo trò chơi mới
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @param bang: Con trỏ lưu trạng thái bảng chơi
 * @param size: Kích thước bảng chơi
 * @param currentNode: Con trỏ trỏ tới node hiện tại của danh sách liên kết (node đầu tiên)
 * @param username: Tên người chơi
 * @param isNewGame: Cờ kiểm tra trạng thái khởi tạo trò chơi mới
 */
void newGame(sf::RenderWindow& window, const sf::Font& font, int**& bang, int& size, Node*& currentNode, std::string& username, bool& isNewGame);



/* ================= GIAODIEN.CPP ================= */



/**
 * Hàm lấy màu ô vuông dựa trên giá trị số bên trong
 * @param number: Giá trị số trong ô
 * @return Màu sắc tương ứng
 */
sf::Color cellColor(const int& number);


/**
 * Hàm lấy màu chữ dựa trên giá trị số bên trong ô
 * @param number: Giá trị số trong ô
 * @return Màu sắc của chữ
 */
sf::Color numberColor(const int& number);


/**
 * Hàm in màn hình chào mừng người chơi
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 */
void printWelcomeScreen(sf::RenderWindow& window, const sf::Font& font);


/**
 * Hàm hiển thị menu chính và xử lý lựa chọn
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @return Lựa chọn của người chơi
 */
int Menu(sf::RenderWindow& window, const sf::Font& font);


/**
 * Hàm nhập tên người chơi từ giao diện
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @return Tên người chơi nhập vào
 */
std::string nameInput(sf::RenderWindow& window, const sf::Font& font);


/**
 * Hàm hiển thị menu quay lại menu chính và xử lý lựa chọn
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @return Lựa chọn của người chơi
 */
int Return(sf::RenderWindow& window, const sf::Font& font);


/**
 * Hàm chọn kích thước bảng chơi từ giao diện
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @return Kích thước bảng chơi
 */
int sizeInput(sf::RenderWindow& window, const sf::Font& font);


/**
 * Hàm điều chỉnh kích thước cửa sổ dựa vào kích thước bảng
 * @param window: Cửa sổ giao diện
 * @param size: Kích thước bảng chơi
 */
void playWindow(sf::RenderWindow& window, const int& size);


/**
 * Hàm in bảng chơi ra giao diện
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 */
void printGrid(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size);


/**
 * Hàm in màn hình thắng ra giao diện và xử lý lựa chọn
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @return Lựa chọn của người chơi sau khi thắng
 */
int winScreen(sf::RenderWindow& window, const sf::Font& font);


/**
 * Hàm in màn hình thua ra giao diện và xử lý lựa chọn
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @return Lựa chọn của người chơi sau khi thua
 */
int loseScreen(sf::RenderWindow& window, const sf::Font& font);



/* ================= GAMELOGIC.CPP ================= */



/**
 * Hàm khởi tạo bảng chơi
 * @param size: Kích thước bảng chơi
 * @return Con trỏ trỏ đến mảng 2 chiều của bảng chơi
 */
int** makeGrid(const int& size);


/**
 * Hàm tạo số ngẫu nhiên trên một ô trống trong bảng
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 */
void randNumber(int** bang, const int& size);


/**
 * Hàm gộp các số theo hàng
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param button: Phím điều hướng (trái hoặc phải)
 */
void mergeRow(int** bang, const int& size, const char& button);


/**
 * Hàm gộp các số theo hàng
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param button: Phím điều hướng (lên hoặc xuống)
 */
void mergeCol(int** bang, const int& size, const char& button);


/**
 * Hàm kiểm tra điều kiện thắng
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param afterWin: Cờ kiểm tra trạng thái chơi tiếp sau khi thắng
 */
bool winCheck(int** bang, const int& size, const bool& afterWin);


/**
 * Hàm kiểm tra điều kiện thua
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 */
bool loseCheck(int** bang, const int& size);


/**
 * Hàm tính điểm
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 */
int score(int** bang, const int& size);



/* ================= DIEUKHIEN.CPP ================= */



/**
 * Hàm nhận sự kiện từ bàn phím và trả về phím được nhấn
 * @param window: Cửa sổ giao diện
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param currentNode: Con trỏ trỏ tới node hiện tại của danh sách liên kết
 * @return Phím mà người chơi nhấn
 */
sf::Keyboard::Key control(sf::RenderWindow& window, int** bang, const int& size, Node*& currentNode);



/* ================= UNDOREDO.CPP ================= */



/**
 * Hàm xoá các nút Redo cũ không hợp lệ và lưu trạng thái hiện tại của bảng chơi
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param currentNode: Con trỏ trỏ tới node hiện tại trong danh sách liên kết đôi
 * Sau khi thực thi, 'currentNode' sẽ trỏ tới nút mới được thêm vào
 */
void newState(int** bang, const int& size, Node*& currentNode);


/**
 * Hàm quay lại trạng thái bảng chơi trước đó (undo)
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param currentNode: Con trỏ trỏ tới nút hiện tại trong danh sách liên kết đôi
 * Nếu không có trạng thái trước đó để quay lại, hiển thị thông báo cho người chơi
 */
void undo(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, Node*& currentNode);


/**
 * Hàm phục hồi trạng thái bảng chơi sau khi thực hiện undo (redo)
 * @param window: Cửa sổ giao diện
 * @param font: Font chữ để hiển thị
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param currentNode: Con trỏ trỏ tới nút hiện tại trong danh sách liên kết đôi
 * Nếu không có trạng thái nào sau undo để phục hồi, hiển thị thông báo cho người chơi
 */
void redo(sf::RenderWindow &window, const sf::Font& font, int** bang, const int& size, Node*& currentNode);



/* =================GIAIPHONGBONHO.CPP ================= */



/**
 * Hàm giải phóng bộ nhớ động của bảng chơi và danh sách liên kết đôi
 * @param bang: Bảng chơi hiện tại
 * @param size: Kích thước bảng chơi
 * @param head: Con trỏ tới nút đầu tiên trong danh sách liên kết đôi
 * Sau khi thực thi, tất cả bộ nhớ động được cấp phát sẽ được giải phóng
 */
void freeMemory(int**& bang, const int& size, Node*& head);

#endif
