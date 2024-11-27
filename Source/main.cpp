#include "2048Lib.hpp"

int main() {

    // Khởi tạo các biến kiểm tra trạng thái trò chơi
    bool isNewGame = true;        // Kiểm tra xem có phải trò chơi mới hay không
    bool isGameOver = false;      // Kiểm tra xem trò chơi đã kết thúc hay chưa
    bool isGameContinue = false;  // Kiểm tra xem trò chơi có đang tiếp tục không
    bool afterWin = false;        // Kiểm tra trạng thái sau khi thắng

    // Thiết lập font chữ
    sf::Font font;
    font.loadFromFile("ClearSans-Bold.ttf");

    // Tạo cửa sổ trò chơi
    sf::RenderWindow window(sf::VideoMode(800, 600), "2048 Game", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // Vòng lặp chính duy trì cửa sổ trò chơi
    while (window.isOpen()) {
        while (!isGameContinue) {
            // Khởi tạo các biến liên quan đến trò chơi
            std::string username;  // Tên người chơi
            int point = 0;         // Điểm hiện tại của người chơi
            int size;              // Kích thước bảng chơi
            int** bang = nullptr;  // Mảng lưu bảng chơi
            Node* head = new Node; // Node đầu tiên để lưu trạng thái undo/redo
            head->next = nullptr;
            head->prev = nullptr;
            Node* currentNode = head;

            // Nếu là trò chơi mới, khởi tạo lại từ đầu
            if (isNewGame)
                newGame(window, font, bang, size, currentNode, username, isNewGame);

            // Biến kiểm tra thắng/thua
            bool win = false;
            bool lose = false;

            // Điều chỉnh kích thước cửa sổ dựa vào kích thước bảng
            playWindow(window, size);

            // Vòng lặp xử lý trò chơi chính
            while (!isNewGame) {
                // Vòng lặp duy trì trò chơi cho đến khi thắng hoặc thua
                while (!isGameOver) {
                    
                    // Hiển thị bảng chơi lên màn hình
                    printGrid(window, font, bang, size);

                    // Lấy thao tác của người dùng
                    sf::Keyboard::Key button = control(window, bang, size, head);

                    // Di chuyển hàng (trái/phải)
                    if (button == sf::Keyboard::A || button == sf::Keyboard::Left ||
                        button == sf::Keyboard::D || button == sf::Keyboard::Right) {

                        mergeRow(bang, size, button);      // Gộp các hàng
                        randNumber(bang, size);            // Thêm số ngẫu nhiên vào bảng
                        newState(bang, size, currentNode); // Lưu trạng thái mới

                    }

                    // Di chuyển cột (lên/xuống)
                    else if (button == sf::Keyboard::W || button == sf::Keyboard::Up ||
                             button == sf::Keyboard::S || button == sf::Keyboard::Down) {

                        mergeCol(bang, size, button);
                        randNumber(bang, size);
                        newState(bang, size, currentNode);

                    }

                    // Thao tác undo (quay lại trạng thái trước đó)
                    else if (button == sf::Keyboard::U) {

                        undo(window, font, bang, size, currentNode);
                        point = score(bang, size);
                        printGrid(window, font, bang, size);

                    }
                    
                    // Thao tác redo (phục hồi trạng thái sau undo)
                    else if (button == sf::Keyboard::R) {

                        redo(window, font, bang, size, currentNode);
                        point = score(bang, size);
                        printGrid(window, font, bang, size);

                    }

                    // Lưu trò chơi và thoát
                    else if (button == sf::Keyboard::P) {

                        saveGame(bang, size, username); // Lưu trạng thái hiện tại
                        freeMemory(bang, size, head);   // Giải phóng bộ nhớ

                        return 0;
                    }

                    // Thoát trò chơi
                    else if (button == sf::Keyboard::Q) {

                        freeMemory(bang, size, head);

                        return 0;
                    }

                    // Bắt đầu trò chơi mới
                    else if (button == sf::Keyboard::N) {
                        isNewGame = true;
                        afterWin = false;

                        freeMemory(bang, size, head);

                        break;
                    }

                    // Kiểm tra điều kiện thắng/thua
                    win = winCheck(bang, size, afterWin);
                    lose = loseCheck(bang, size);

                    // Kết thúc trò chơi nếu thắng hoặc thua
                    if (win || lose)
                        isGameOver = true;
                }

                // Xử lý khi thắng trò chơi
                if (win) {
                    int wantContinue = winScreen(window, font); // Màn hình thắng

                    // Tiếp tục trò chơi sau khi thắng
                    if (wantContinue == 1) {
                        afterWin = true;
                        isGameOver = false;
                    }

                    // Thoát trò chơi sau khi thắng
                    else if (wantContinue == 2) {

                        point = score(bang, size);
                        leaderboard(window, font, point, username, size); // Cập nhật và hiển thị bảng xếp hạng
                        freeMemory(bang, size, head);

                        return 0;
                    }

                    else return 0;
                }

                // Xử lý khi thua trò chơi
                if (lose) {
                    int wantNewGame = loseScreen(window, font); // Màn hình thua

                    point = score(bang, size);
                    leaderboard(window, font, point, username, size);
                    freeMemory(bang, size, head);

                    // Nếu người dùng không muốn chơi lại
                    if (wantNewGame != 1) 
                        return 0;

                    isNewGame = true;   // Bắt đầu trò chơi mới
                    isGameOver = false;
                }
            }
        }
    }
    return 0;
}