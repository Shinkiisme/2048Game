#include "thu_vien_2048.h"

sf::Color number_color(int value){
    switch (value){
        case 0: return sf::Color(204, 192, 179);
        case 2: return sf::Color(238, 228, 218);
        case 4: return sf::Color(237, 224, 200);
        case 8: return sf::Color(242, 177, 121);
        case 16: return sf::Color(245, 149, 99);
        case 32: return sf::Color(246, 124, 95);
        case 64: return sf::Color(246, 94, 59);
        case 128: return sf::Color(237, 207, 114);
        case 256: return sf::Color(237, 204, 97);
        case 512: return sf::Color(237, 200, 80);
        case 1024: return sf::Color(237, 197, 63);
        case 2048: return sf::Color(237, 194, 46);
        default: return sf::Color(60, 58, 50);    
    }
}

// Hàm in ra bảng chơi của trò chơi.
void print_grid(sf::RenderWindow &window, int** bang, int size){
    // Kích thước ô.
    float cell_size = 100.0f; 

    // Thiết lập font chữ.
    sf::Font font;
    font.loadFromFile("ClearSans-Bold.ttf");

    // Vẽ các ô của bảng.
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){

            // Tạo ô vuông.
            sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
            cell.setPosition(j * cell_size, i * cell_size);
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black);

            // Đặt màu nền theo giá trị số.
            cell.setFillColor(sf::Color(number_color(bang[i][j])));

            window.draw(cell);

            // Vẽ giá trị trong ô
            if (bang[i][j] != 0) {
                sf::Text text;

                text.setFont(font);
                text.setString(std::to_string(bang[i][j]));
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Black);

                // Căn giữa giá trị trong ô
                float width = text.getLocalBounds().width;
                float height = text.getLocalBounds().height;
                text.setPosition(j * cell_size + (cell_size - width) / 2, i * cell_size + (cell_size - height) / 2);

                window.draw(text);
            }
        }
    }

    // Cập nhật cửa sổ.
    window.display();
}
