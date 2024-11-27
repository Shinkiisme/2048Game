#include "2048Lib.hpp"

// Hàm xoá các nút Redo cũ không hợp lệ và lưu trạng thái hiện tại của bảng chơi
void newState(int** bang, const int& size, Node*& currentNode) {

    // Xoá các trạng thái redo khi thực hiện hành động mới nếu đã từng undo
    Node* checkRedo = currentNode->next;

    // Lặp qua các trạng thái redo và giải phóng bộ nhớ
    while (checkRedo != nullptr) {
        Node* deleteRedo = checkRedo; // Lưu trạng thái redo cần xóa
        checkRedo = checkRedo->next;  // Chuyển đến trạng thái tiếp theo

        delete[] deleteRedo->gameState; // Giải phóng bộ nhớ của gameState
        delete deleteRedo; // Giải phóng bộ nhớ của node
    }

    currentNode->next = nullptr; // Đặt next của currentNode về nullptr

    // Lưu trạng thái mới của bảng chơi vào một node mới
    Node* newNode = new Node; // Tạo node mới để lưu trạng thái mới
    newNode->gameState = new int[size * size]; // Cấp phát bộ nhớ cho gameState

    // Sao chép trạng thái từ bảng chơi vào gameState của node mới
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            newNode->gameState[i * size + j] = bang[i][j]; // Sao chép dữ liệu của bảng vào gameState

    newNode->next = nullptr; // Thiết lập next của node mới về nullptr
    newNode->prev = currentNode; // Thiết lập prev của node mới trỏ về currentNode

    currentNode->next = newNode; // Kết nối currentNode với node mới
    currentNode = newNode; // Cập nhật currentNode để trỏ về node mới
}

// Hàm quay lại trạng thái bảng chơi trước đó (undo)
void undo(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, Node*& currentNode) {

    // Kiểm tra xem node hiện tại và node trước có hợp lệ không
    // Nếu không có node trước, nghĩa là không thể undo được
    if (currentNode == nullptr || currentNode->prev == nullptr) {
        
        // Hiển thị thông báo "Không thể Undo"
        sf::Text text("Khong the Undo!", font, 24);
        text.setFillColor(sf::Color::Red);
        text.setPosition(
            size * 100 + (window.getSize().x - size * 100) / 2.0f - text.getLocalBounds().width / 2.0f,
            50
        );

        // In ra thêm thông báo
        printGrid(window, font, bang, size);
        window.draw(text); // Vẽ thông báo lên cửa sổ
        window.display(); // Cập nhật cửa sổ hiển thị

        sf::sleep(sf::seconds(0.5)); // Dừng 0.5 giây để người chơi có thể đọc thông báo

        return; // Nếu không thể undo, thoát khỏi hàm
    }

    // Nếu có thể undo, thay thế bảng chơi hiện tại bằng bảng chơi từ node trước
    currentNode = currentNode->prev; // Di chuyển con trỏ node về node trước

    // Sao chép trạng thái của bảng chơi từ gameState của node trước vào bảng chơi hiện tại
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            bang[i][j] = currentNode->gameState[i * size + j]; // Cập nhật bảng chơi từ gameState của node trước
}

// Hàm phục hồi trạng thái bảng chơi sau khi thực hiện undo (redo)
void redo(sf::RenderWindow &window, const sf::Font& font, int** bang, const int& size, Node*& currentNode) {

    // Kiểm tra xem node hiện tại và node sau có hợp lệ không
    // Nếu không có node sau, nghĩa là không thể redo được
    if (currentNode == nullptr || currentNode->next == nullptr) {

        // Hiển thị thông báo "Không thể Redo"
        sf::Text text("Khong the Redo!", font, 24);
        text.setFillColor(sf::Color::Red);
        text.setPosition(
            size * 100 + (window.getSize().x - size * 100) / 2.0f - text.getLocalBounds().width / 2.0f,
            50
        );

        // In ra thêm thông báo
        printGrid(window, font, bang, size);
        window.draw(text);
        window.display();

        sf::sleep(sf::seconds(0.5)); // Dừng 0.5 giây để người chơi có thể đọc thông báo
        
        return; // Nếu không thể redo, thoát khỏi hàm
    }

    // Nếu có thể redo, thay thế bảng chơi hiện tại bằng bảng chơi từ node sau
    currentNode = currentNode->next; // Di chuyển con trỏ node về node sau

    // Sao chép trạng thái của bảng chơi từ gameState của node sau vào bảng chơi hiện tại
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            bang[i][j] = currentNode->gameState[i * size + j]; // Cập nhật bảng chơi từ gameState của node sau
}