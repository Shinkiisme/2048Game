#include "Controls.h"

// Hàm nhận sự kiện từ bàn phím và trả về phím được nhấn
sf::Keyboard::Key control(sf::RenderWindow& window, int** bang, const int& size, Node*& currentNode, char*& username) {
    sf::Event event;
    
    // Lặp cho đến khi nhận được sự kiện từ người dùng
    do {
        while (window.pollEvent(event)) {
            // Nếu cửa sổ bị đóng, giải phóng bộ nhớ và thoát chương trình
            if (event.type == sf::Event::Closed) {
                freeMemory(bang, size, currentNode, username);
                window.close();
                exit(0);
            }

            // Xử lý sự kiện khi một phím được nhấn
            if (event.type == sf::Event::KeyPressed) {
                // Kiểm tra các phím nhất định và trả về mã phím tương ứng nếu có
                if (event.key.code == sf::Keyboard::N ||
                    event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up ||
                    event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down ||
                    event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left ||
                    event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right ||
                    event.key.code == sf::Keyboard::U || event.key.code == sf::Keyboard::R ||
                    event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::P)

                    return event.key.code; // Trả về mã phím khi người dùng nhấn một phím hợp lệ
            }
        }
    } while (true);  // Lặp lại cho đến khi nhận được một phím
}