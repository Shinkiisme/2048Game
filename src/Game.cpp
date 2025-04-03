#include "Game.h"

// Hàm khởi tạo
Game::Game() {
    // Tải font chữ
    font.loadFromFile("../assets/Font/ClearSans-Bold.ttf");

    // Tạo cửa sổ trò chơi
    window.create(sf::VideoMode(800, 600), "2048 Game", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Khởi tạo trạng thái undo/redo
    head = new Node();
    head->next = nullptr;
    head->prev = nullptr;
    currentNode = head;
}

// Hàm giải phóng bộ nhớ
Game::~Game() {
    freeMemory(bang, size, head, player.username);
}

// Phương thức chính chạy trò chơi
void Game::run() {
    while (window.isOpen()) {
        while (!isGameContinue) {
            if (isNewGame)
                newGame(window, font, bang, size, currentNode, player.username, player.character, isNewGame);

            bool win = false, lose = false;

            playWindow(window, size);

            while (!isNewGame) {
                // Vòng lặp chính của trò chơi cho đến khi người chơi thắng hoặc thua
                while (!isGameOver) {
                    printGrid(window, font, bang, size, player.character); // Vẽ bảng chơi

                    // Lấy phím người dùng nhấn
                    sf::Keyboard::Key button = control(window, bang, size, head, player.username);

                    // Xử lý di chuyển theo hàng (trái/phải)
                    if (button == sf::Keyboard::A || button == sf::Keyboard::Left ||
                        button == sf::Keyboard::D || button == sf::Keyboard::Right) {
                        mergeRow(bang, size, button);
                        randNumber(bang, size);
                        newState(bang, size, currentNode);
                    }
                    // Xử lý di chuyển theo cột (lên/xuống)
                    else if (button == sf::Keyboard::W || button == sf::Keyboard::Up ||
                             button == sf::Keyboard::S || button == sf::Keyboard::Down) {
                        mergeCol(bang, size, button);
                        randNumber(bang, size);
                        newState(bang, size, currentNode);
                    }
                    // Thực hiện thao tác Undo
                    else if (button == sf::Keyboard::U) {
                        undo(window, font, bang, size, player.character, currentNode);
                        player.point = score(bang, size);
                        printGrid(window, font, bang, size, player.character);
                    }
                    // Thực hiện thao tác Redo
                    else if (button == sf::Keyboard::R) {
                        redo(window, font, bang, size, player.character, currentNode);
                        player.point = score(bang, size);
                        printGrid(window, font, bang, size, player.character);
                    }
                    // Lưu trò chơi và thoát
                    else if (button == sf::Keyboard::P) {
                        saveGame(head, size, player.username, player.character);
                        return;
                    }
                    // Thoát trò chơi
                    else if (button == sf::Keyboard::Q) {
                        return;
                    }
                    // Yêu cầu bắt đầu trò chơi mới
                    else if (button == sf::Keyboard::N) {
                        isNewGame = true;
                        afterWin = false;
                        break; // Thoát vòng lặp hiện tại để khởi tạo game mới
                    }

                    // Kiểm tra trạng thái thắng và thua
                    win = winCheck(bang, size, afterWin);
                    lose = loseCheck(bang, size);
                    if (win || lose)
                        isGameOver = true;
                }

                // Nếu người chơi thắng
                if (win) {
                    int wantContinue = winScreen(window, font);
                    if (wantContinue == 1) { // Chơi tiếp sau thắng
                        afterWin = true;
                        isGameOver = false;
                    }
                    else if (wantContinue == 2) { // Hiển thị bảng xếp hạng và thoát
                        player.point = score(bang, size);
                        leaderboard(window, font, size, player.username, player.point);
                        return;
                    }
                    else return;
                }

                // Nếu người chơi thua
                if (lose) {
                    int wantNewGame = loseScreen(window, font, bang, size, player.character);
                    player.point = score(bang, size);
                    leaderboard(window, font, size, player.username, player.point);
                    if (wantNewGame != 1) // Nếu không muốn chơi lại, thoát
                        return;
                    isNewGame = true;
                    isGameOver = false;
                }
            }
        }
    }
}