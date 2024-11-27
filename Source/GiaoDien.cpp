#include "2048Lib.hpp"

// Hàm lấy màu ô vuông dựa trên giá trị số bên trong
sf::Color cellColor(const int& number) {
    // Sử dụng câu lệnh switch để xác định màu sắc cho từng giá trị cụ thể
    switch (number) {
    case 0: return sf::Color(204, 192, 179);   // Màu nền cho ô trống
    case 2: return sf::Color(238, 228, 218);   // Màu nền cho ô chứa giá trị 2
    case 4: return sf::Color(237, 224, 200);   // Màu nền cho ô chứa giá trị 4
    case 8: return sf::Color(242, 177, 121);   // Màu nền cho ô chứa giá trị 8
    case 16: return sf::Color(245, 149, 99);   // Màu nền cho ô chứa giá trị 16
    case 32: return sf::Color(246, 124, 95);   // Màu nền cho ô chứa giá trị 32
    case 64: return sf::Color(246, 94, 59);    // Màu nền cho ô chứa giá trị 64
    case 128: return sf::Color(237, 207, 114); // Màu nền cho ô chứa giá trị 128
    case 256: return sf::Color(237, 204, 97);  // Màu nền cho ô chứa giá trị 256
    case 512: return sf::Color(237, 200, 80);  // Màu nền cho ô chứa giá trị 512
    case 1024: return sf::Color(237, 197, 63); // Màu nền cho ô chứa giá trị 1024
    case 2048: return sf::Color(237, 194, 46); // Màu nền cho ô chứa giá trị 2048
    default: return sf::Color(60, 58, 50);     // Màu nền mặc định cho các giá trị lớn hơn 2048
    }
}

// Hàm lấy màu chữ dựa trên giá trị số bên trong ô
sf::Color numberColor(const int& number) {
    switch (number) {
    case 2: return sf::Color(119, 110, 101);  // Màu chữ cho ô chứa giá trị 2
    case 4: return sf::Color(119, 110, 101);  // Màu chữ cho ô chứa giá trị 4
    default: return sf::Color(255, 255, 255); // Màu chữ mặc định cho các giá trị khác
    }
}

// Hàm in màn hình chào mừng người chơi
void printWelcomeScreen(sf::RenderWindow& window, const sf::Font& font) {

    // Tạo tiêu đề cho trò chơi
    sf::Text title("2048 Game", font, 60); // Tiêu đề với kích thước font là 60
    title.setFillColor(sf::Color::White);  // Màu chữ trắng
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f, // Canh giữa màn hình theo chiều ngang
        window.getSize().y / 3.0f                                        // Đặt vị trí theo chiều dọc khoảng 1/3 màn hình
    );

    // Tạo văn bản hướng dẫn
    sf::Text text("Press Any Key To Continue...", font, 30); // Hướng dẫn nhấn phím bất kỳ với kích thước font là 30
    text.setFillColor(sf::Color::Yellow); // Màu chữ vàng
    text.setPosition(
        window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f, // Canh giữa màn hình theo chiều ngang
        window.getSize().y / 2.0f                                       // Đặt vị trí theo chiều dọc khoảng 1/2 màn hình
    );

    // Vòng lặp xử lý sự kiện và hiển thị màn hình chào mừng
    while (window.isOpen()) {
        sf::Event event;

        // Kiểm tra sự kiện trong cửa sổ
        while (window.pollEvent(event)) {

            // Đóng cửa sổ nếu nhận sự kiện đóng
            if (event.type == sf::Event::Closed) {
                window.close(); // Đóng cửa sổ
                exit(0);        // Dừng chương trình
            }

            // Thoát màn hình chào khi nhấn bất kỳ phím nào
            if (event.type == sf::Event::KeyPressed)
                return; // Kết thúc hàm khi người dùng nhấn phím
            
        }

        // Vẽ màn hình chào mừng
        window.clear(sf::Color(30, 30, 30)); // Màu nền xám tối
        window.draw(title);                  // Vẽ tiêu đề
        window.draw(text);                   // Vẽ văn bản hướng dẫn
        window.display();                    // Hiển thị nội dung mới
    }
}

// Hàm hiển thị menu chính và xử lý lựa chọn
int Menu(sf::RenderWindow& window, const sf::Font& font) {

    // Tạo tiêu đề trò chơi
    sf::Text title("2048 Game", font, 60);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 4.0f
    );

    // Tạo các mục menu
    sf::RectangleShape box; // Hộp nền xung quanh mục được chọn
    sf::Text menu[2];       // Mảng chứa hai mục menu

    // Thiết lập mục đầu tiên
    menu[0].setFont(font);
    menu[0].setString("Bat dau tro choi moi");
    menu[0].setCharacterSize(30);
    menu[0].setFillColor(sf::Color::Yellow);
    menu[0].setPosition(
        window.getSize().x / 2.0f - menu[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    // Thiết lập mục thứ hai
    menu[1].setFont(font);
    menu[1].setString("Tiep tuc tro choi cu");
    menu[1].setCharacterSize(30);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setPosition(
        window.getSize().x / 2.0f - menu[1].getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f
    );

    int selected = 0; // Mục được chọn ban đầu (0: "Bắt đầu trò chơi mới")

    // Vòng lặp chính của menu
    while (window.isOpen()) {
        sf::Event event;

        // Kiểm tra các sự kiện
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1; // Trả về -1 nếu người dùng đóng cửa sổ
            }

            // Xử lý sự kiện phím
            if (event.type == sf::Event::KeyPressed) {

                // Chuyển đổi giữa các mục menu khi nhấn phím mũi tên hoặc W/S
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)

                    selected = (selected + 1) % 2; // Chuyển qua lại giữa hai mục

                // Người dùng nhấn Enter để chọn
                else if (event.key.code == sf::Keyboard::Enter)
                    return selected + 1; // Trả về 1 hoặc 2 tương ứng với mục được chọn  
            }
        }

        // Cập nhật màu sắc và hộp nền của các mục menu
        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menu[i].setFillColor(sf::Color::Yellow); // Đặt màu vàng cho mục được chọn

                // Thiết lập hộp nền xung quanh mục được chọn
                box.setSize(sf::Vector2f(menu[i].getLocalBounds().width + 20, menu[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(50, 50, 50)); 
                box.setPosition(
                    menu[i].getPosition().x - 10,
                    menu[i].getPosition().y
                );
            }
            
            else
                menu[i].setFillColor(sf::Color::White); // Đặt màu trắng cho mục không được chọn   
        }

        // Vẽ menu
        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(box);

        for (int i = 0; i < 2; ++i) 
            window.draw(menu[i]); // Vẽ các mục menu
        
        window.display();
    }

    return -1; // Trả về -1 nếu cửa sổ bị đóng
}

// Hàm nhập tên người chơi từ giao diện
std::string nameInput(sf::RenderWindow& window, const sf::Font& font) {

    // Thiết lập hướng dẫn nhập tên
    sf::Text text("Nhap ten nguoi choi (khong co khoang trang):", font, 30);
    text.setFillColor(sf::Color::White);
    text.setPosition(
        window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f
    );

    // Tạo hộp nhập tên
    sf::RectangleShape box;
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(3);
    box.setSize(sf::Vector2f(400, 50));
    box.setPosition(
        window.getSize().x / 2.0f - box.getSize().x / 2.0f,
        window.getSize().y / 2.0f - box.getSize().y / 2.0f
    );

    // Thiết lập text hiển thị tên đang nhập
    sf::Text nameInput;
    nameInput.setFont(font);
    nameInput.setCharacterSize(30);
    nameInput.setFillColor(sf::Color::Black);

    std::string username; // Chuỗi lưu tên người chơi
    bool isTyping = true; // Biến kiểm tra trạng thái nhập

    while (isTyping && window.isOpen()) {
        sf::Event event;

        // Xử lý sự kiện
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return ""; // Trả về chuỗi rỗng nếu người dùng đóng cửa sổ
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Xóa ký tự (Backspace)
                    if (!username.empty())
                        username.pop_back();
                }
                else if (event.text.unicode == '\r') { // Nhấn Enter
                    if (!username.empty() && username.find(' ') == std::string::npos)
                        isTyping = false; // Kết thúc nhập nếu hợp lệ
                }
                else if (event.text.unicode < 128) // Chỉ nhận ký tự ASCII
                    username += static_cast<char>(event.text.unicode);
            }
        }

        // Cập nhật vị trí và nội dung của text hiển thị tên
        nameInput.setString(username);
        float x = box.getPosition().x + (box.getSize().x - nameInput.getLocalBounds().width) / 2.0f;
        float y = box.getPosition().y + (box.getSize().y - nameInput.getLocalBounds().height) / 2.0f - nameInput.getLocalBounds().top;
        nameInput.setPosition(x, y);

        // Vẽ giao diện
        window.clear(sf::Color(30, 30, 30));
        window.draw(text);
        window.draw(box);
        window.draw(nameInput);
        window.display();
    }

    return username; // Trả về tên người chơi
}

// Hàm hiển thị menu quay lại menu chính và xử lý lựa chọn
int Return(sf::RenderWindow& window, const sf::Font& font) {

    // Tiêu đề của menu
    sf::Text title("Ban co muon quay lai ?", font, 50);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 4.0f
    );

    // Tạo các mục menu (Có và Không)
    sf::RectangleShape box; // Hộp bao quanh mục đang chọn
    sf::Text menuReturn[2]; // Mảng chứa các mục menu

    // Tương tự menu chính
    menuReturn[0].setFont(font);
    menuReturn[0].setString("Co");
    menuReturn[0].setCharacterSize(30);
    menuReturn[0].setFillColor(sf::Color::White);
    menuReturn[0].setPosition(
        window.getSize().x / 2.0f - menuReturn[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    menuReturn[1].setFont(font);
    menuReturn[1].setString("Khong");
    menuReturn[1].setCharacterSize(30);
    menuReturn[1].setFillColor(sf::Color::Yellow);
    menuReturn[1].setPosition(
        window.getSize().x / 2.0f - menuReturn[1].getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f
    );

    int selected = 0;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)

                    selected = (selected + 1) % 2;

                else if (event.key.code == sf::Keyboard::Enter)
                    return selected + 1;
            }
        }

        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menuReturn[i].setFillColor(sf::Color::Yellow);

                box.setSize(sf::Vector2f(menuReturn[i].getLocalBounds().width + 20, menuReturn[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(50, 50, 50));
                box.setPosition(
                    menuReturn[i].getPosition().x - 10,
                    menuReturn[i].getPosition().y
                );
            }
            
            else
                menuReturn[i].setFillColor(sf::Color::White);
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(box);

        for (int i = 0; i < 2; ++i)
            window.draw(menuReturn[i]);

        window.display();
    }

    return -1;
}

// Hàm chọn kích thước bảng chơi từ giao diện
int sizeInput(sf::RenderWindow& window, const sf::Font& font) {

    // Tương tự các menu khác
    sf::Text title("Chon kich thuoc", font, 50);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 4.0f
    );

    sf::RectangleShape box;
    sf::Text menuSize[2];

    menuSize[0].setFont(font);
    menuSize[0].setString("4 x 4");
    menuSize[0].setCharacterSize(30);
    menuSize[0].setFillColor(sf::Color::White);
    menuSize[0].setPosition(
        window.getSize().x / 2.0f - menuSize[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    menuSize[1].setFont(font);
    menuSize[1].setString("6 x 6");
    menuSize[1].setCharacterSize(30);
    menuSize[1].setFillColor(sf::Color::Yellow);
    menuSize[1].setPosition(
        window.getSize().x / 2.0f - menuSize[1].getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f
    );

    int selected = 0;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)

                    selected = (selected + 1) % 2;

                else if (event.key.code == sf::Keyboard::Enter)
                    return (!selected) ? 4 : 6; 
            }
        }

        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menuSize[i].setFillColor(sf::Color::Yellow);

                box.setSize(sf::Vector2f(menuSize[i].getLocalBounds().width + 20, menuSize[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(50, 50, 50));
                box.setPosition(
                    menuSize[i].getPosition().x - 10,
                    menuSize[i].getPosition().y
                );
            }

            else
                menuSize[i].setFillColor(sf::Color::White);
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(box);

        for (int i = 0; i < 2; ++i)
            window.draw(menuSize[i]);

        window.display();
    }

    return -1;
}

// Hàm điều chỉnh kích thước cửa sổ dựa vào kích thước bảng
void playWindow(sf::RenderWindow& window, const int &size) {
    
    // Kích thước mỗi ô vuông trên bảng
    const int cellSize = 100;
    
    // Kích thước của toàn bộ bảng chơi
    int playSize = size * cellSize;

    // Thay đổi kích thước cửa sổ sao cho đủ hiển thị bảng và thêm viền ngoài
    // Thêm 250 pixel chiều rộng và 150 pixel chiều cao để chứa giao diện phụ (điểm số, điều khiển, ...)
    window.setSize(sf::Vector2u(playSize + 250, playSize + 150));

    // Cập nhật chế độ nhìn (view) để giữ tỷ lệ hiển thị trên cửa sổ
    // Tạo view mới bao phủ toàn bộ vùng hiển thị, đảm bảo nội dung không bị méo
    sf::View view(sf::FloatRect(0, 0, playSize + 250, playSize + 150));
    window.setView(view);
}

// Hàm in bảng chơi ra giao diện
void printGrid(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size) {
    
    // Kích thước mỗi ô vuông trên bảng
    const float cellSize = 100.0f;

    window.clear(sf::Color::White);

    // Vẽ các ô của bảng
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            // Tạo một ô vuông với kích thước xác định
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black);

            // Đặt màu nền cho ô dựa trên giá trị trong bảng
            cell.setFillColor(cellColor(bang[i][j]));

            window.draw(cell);

            // Vẽ giá trị trong ô nếu giá trị khác 0
            if (bang[i][j] != 0) {
                sf::Text text;

                text.setFont(font);
                text.setString(std::to_string(bang[i][j]));
                text.setCharacterSize(24);
                text.setFillColor(numberColor(bang[i][j]));

                // Căn giữa giá trị trong ô
                float width = text.getLocalBounds().width;
                float height = text.getLocalBounds().height;
                text.setPosition(
                    j * cellSize + (cellSize - width) / 2.0f,
                    i * cellSize + (cellSize - height) / 2.0f
                );

                window.draw(text);
            }
        }
    }

    // Tính điểm hiện tại của người chơi
    int point = score(bang, size);

    sf::Text text("Diem cua ban: " + std::to_string(point), font, 24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(
        size * cellSize + (window.getSize().x - size * cellSize) / 2.0f - text.getLocalBounds().width / 2.0f,
        0
    );

    // Hiển thị hướng dẫn
    sf::Text textNewGame("N: New game", font, 24);
    sf::Text textControl("W: Len   S: Xuong   A: Trai   D: Phai", font, 24);
    sf::Text textUndoRedo("U: Undo   R: Redo", font, 24);
    sf::Text textQuitPause("Q: Thoat   P: Luu va thoat", font, 24);

    // Đặt màu chữ cho các hướng dẫn
    textNewGame.setFillColor(sf::Color::Black);
    textNewGame.setPosition(0, size * cellSize + 15);

    textControl.setFillColor(sf::Color::Black);
    textControl.setPosition(0, size * cellSize + textNewGame.getLocalBounds().height + 30);

    textUndoRedo.setFillColor(sf::Color::Black);
    textUndoRedo.setPosition(0, size * cellSize + textNewGame.getLocalBounds().height + textControl.getLocalBounds().height + 45);

    textQuitPause.setFillColor(sf::Color::Black);
    textQuitPause.setPosition(0, size * cellSize + textNewGame.getLocalBounds().height + textControl.getLocalBounds().height + textUndoRedo.getLocalBounds().height + 60);

    // Vẽ các thông tin hướng dẫn và điểm số lên cửa sổ
    window.draw(textNewGame);
    window.draw(textControl);
    window.draw(textUndoRedo);
    window.draw(textQuitPause);
    window.draw(text);

    // Cập nhật nội dung trên cửa sổ
    window.display();
}

// Hàm in màn hình thắng ra giao diện và xử lý lựa chọn
int winScreen(sf::RenderWindow& window, const sf::Font& font) {

    // Tạo tiêu đề "Bạn đã thắng"
    sf::Text title("Ban da thang", font, 60);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 5.0f + 50
    );

    // Tạo câu hỏi "Bạn có muốn chơi tiếp không?"
    sf::Text text("Ban co muon choi tiep khong ?", font, 30);
    text.setFillColor(sf::Color::White);
    text.setPosition(
        window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    // Tạo các mục menu
    sf::RectangleShape box;
    sf::Text menuWin[2];

    // Cài đặt mục "Có"
    menuWin[0].setFont(font);
    menuWin[0].setString("Co");
    menuWin[0].setCharacterSize(30);
    menuWin[0].setFillColor(sf::Color::White);
    menuWin[0].setPosition(
        window.getSize().x / 2.0f - menuWin[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 100
    );

    // Cài đặt mục "Không"
    menuWin[1].setFont(font);
    menuWin[1].setString("Khong");
    menuWin[1].setCharacterSize(30);
    menuWin[1].setFillColor(sf::Color::Yellow);
    menuWin[1].setPosition(
        window.getSize().x / 2.0f - menuWin[1].getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f + 50
    );

    int selected = 0; // Mặc định mục "Có" được chọn

    // Vòng lặp chính của màn hình chiến thắng
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1; // Trả về -1 nếu cửa sổ bị đóng
            }

            // Xử lý sự kiện phím
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)

                    selected = (selected + 1) % 2; // Di chuyển giữa các mục menu

                else if (event.key.code == sf::Keyboard::Enter) 
                    return selected + 1; // Trả về 1 (chơi tiếp) hoặc 2 (thoát)
            }
        }

        // Cập nhật màu sắc của các tùy chọn
        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menuWin[i].setFillColor(sf::Color::Yellow); // Mục được chọn sẽ có màu vàng

                // Thiết lập kích thước hộp bao quanh mục
                box.setSize(sf::Vector2f(menuWin[i].getLocalBounds().width + 20, menuWin[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(50, 50, 50));
                box.setPosition(menuWin[i].getPosition().x - 10, menuWin[i].getPosition().y);
            }

            else
                menuWin[i].setFillColor(sf::Color::White);
        }

        // Vẽ menu
        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(text);
        window.draw(box);

        for (int i = 0; i < 2; ++i)
            window.draw(menuWin[i]);

        window.display();
    }

    return -1; // Trả về -1 nếu cửa sổ bị đóng
}

// Hàm in màn hình thua ra giao diện và xử lý lựa chọn
int loseScreen(sf::RenderWindow& window, const sf::Font& font) {

    // Tương tự hàm winScreen
    sf::Text title("Ban da thua", font, 60);
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 5.0f + 50
    );

    sf::Text text("Ban co muon choi moi khong ?", font, 30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(
        window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    sf::RectangleShape box;
    sf::Text menuLose[2];

    menuLose[0].setFont(font);
    menuLose[0].setString("Co");
    menuLose[0].setCharacterSize(30);
    menuLose[0].setFillColor(sf::Color::White);
    menuLose[0].setPosition(
        window.getSize().x / 2.0f - menuLose[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 100
    );

    menuLose[1].setFont(font);
    menuLose[1].setString("Khong");
    menuLose[1].setCharacterSize(30);
    menuLose[1].setFillColor(sf::Color::Yellow);
    menuLose[1].setPosition(
        window.getSize().x / 2.0f - menuLose[1].getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f + 50
    );

    int selected = 0;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)

                    selected = (selected + 1) % 2;

                else if (event.key.code == sf::Keyboard::Enter) 
                    return selected + 1;
            }
        }

        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menuLose[i].setFillColor(sf::Color::Yellow);

                box.setSize(sf::Vector2f(menuLose[i].getLocalBounds().width + 20, menuLose[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(50, 50, 50));
                box.setPosition(menuLose[i].getPosition().x - 10, menuLose[i].getPosition().y);
            }

            else
                menuLose[i].setFillColor(sf::Color::White);
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(text);
        window.draw(box);

        for (int i = 0; i < 2; ++i)
            window.draw(menuLose[i]);

        window.display();
    }

    return -1;
}
