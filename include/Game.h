#ifndef GAME_H
#define GAME_H

#include "2048Lib.h"

struct Game {
    // Biến trạng thái trò chơi
    bool isNewGame = true;
    bool isGameOver = false;
    bool isGameContinue = false;
    bool afterWin = false;

    // Biến liên quan đến font và cửa sổ
    sf::Font font;
    sf::RenderWindow window;

    // Biến lưu thông tin người chơi
    playerInfo player;

    // Biến liên quan đến bảng chơi
    int size;             // Kích thước bảng
    int** bang = nullptr; // Mảng lưu bảng chơi
    Node* head = nullptr; // Danh sách liên kết lưu trạng thái undo/redo
    Node* currentNode = nullptr;

    // Hàm khởi tạo
    Game();

    // Hàm giải phóng bộ nhớ
    ~Game();

    // Phương thức chính chạy trò chơi
    void run();
};

#endif
