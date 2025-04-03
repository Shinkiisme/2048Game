#include "Graphics.h"

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
    title.setFillColor(sf::Color(119, 110, 97));
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f, // Canh giữa màn hình theo chiều ngang
        window.getSize().y / 3.0f                                        // Đặt vị trí theo chiều dọc khoảng 1/3 màn hình
    );

    // Tạo văn bản hướng dẫn
    sf::Text text("Press Any Key Or Click To Continue...", font, 30); // Hướng dẫn nhấn phím bất kỳ với kích thước font là 30
    text.setFillColor(sf::Color(119, 110, 97)); // Màu chữ vàng
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

            // Thoát màn hình chào khi nhấn bất kỳ phím nào hoặc click chuột trái
            if (event.type == sf::Event::KeyPressed || 
               (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left))
                return; // Kết thúc hàm khi người dùng nhấn phím
        }

        // Vẽ màn hình chào mừng
        window.clear(sf::Color(251, 249, 240)); // Màu nền xám tối
        window.draw(title);                  // Vẽ tiêu đề
        window.draw(text);                   // Vẽ văn bản hướng dẫn
        window.display();                    // Hiển thị nội dung mới
    }
}

// Hàm hiển thị menu chính và xử lý lựa chọn
int Menu(sf::RenderWindow& window, const sf::Font& font) {
    // Tạo tiêu đề trò chơi
    sf::Text title("2048 Game", font, 60);
    title.setFillColor(sf::Color(119, 110, 97));
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
    menu[0].setFillColor(sf::Color(119, 110, 97));
    menu[0].setPosition(
        window.getSize().x / 2.0f - menu[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    // Thiết lập mục thứ hai
    menu[1].setFont(font);
    menu[1].setString("Tiep tuc tro choi cu");
    menu[1].setCharacterSize(30);
    menu[1].setFillColor(sf::Color(119, 110, 97));
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

            if (event.type == sf::Event::MouseMoved){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < 2; ++i)
                    if (menu[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        selected = i;
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

            // Xử lý sự kiện chuột
            else if (event.type == sf::Event::MouseButtonPressed)

                // Cho phép người dùng nhấn chuột trái để chọn
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < 2; ++i)
                        if (menu[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                            return i + 1;
                }
        }

        // Cập nhật màu sắc và hộp nền của các mục menu
        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menu[i].setFillColor(sf::Color::White); // Đặt màu vàng cho mục được chọn

                // Thiết lập hộp nền xung quanh mục được chọn
                box.setSize(sf::Vector2f(menu[i].getLocalBounds().width + 20, menu[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(187, 174, 158)); 
                box.setPosition(
                    menu[i].getPosition().x - 10,
                    menu[i].getPosition().y
                );
            }
            
            else
                menu[i].setFillColor(sf::Color(119, 110, 97)); // Đặt màu trắng cho mục không được chọn   
        }

        // Vẽ menu
        window.clear(sf::Color(251, 249, 240));
        window.draw(title);
        window.draw(box);

        for (int i = 0; i < 2; ++i) 
            window.draw(menu[i]); // Vẽ các mục menu
        
        window.display();
    }

    return -1; // Trả về -1 nếu cửa sổ bị đóng
}

// Hàm nhập tên người chơi từ giao diện
void nameInput(sf::RenderWindow& window, const sf::Font& font, char* username) {
    username[0] = '\0'; // Khởi tạo chuỗi rỗng

    // Thiết lập hướng dẫn nhập tên
    sf::Text text("Nhap ten nguoi choi (khong co khoang trang):", font, 30);
    text.setFillColor(sf::Color(119, 110, 97));
    text.setPosition(
        window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f
    );

    // Tạo hộp nhập tên
    sf::RectangleShape box;
    box.setFillColor(sf::Color(187, 174, 158));
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);
    box.setSize(sf::Vector2f(500, 50));
    box.setPosition(
        window.getSize().x / 2.0f - box.getSize().x / 2.0f,
        window.getSize().y / 2.0f - box.getSize().y / 2.0f
    );

    // Thiết lập text hiển thị tên đang nhập
    sf::Text nameInputText;
    nameInputText.setFont(font);
    nameInputText.setCharacterSize(30);
    nameInputText.setFillColor(sf::Color::White);

    bool isTyping = true;

    while (isTyping && window.isOpen()) {
        sf::Event event;

        // Xử lý sự kiện
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                username[0] = '\0'; // Trả về chuỗi rỗng
                return;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Xóa ký tự "Backspace"
                    unsigned int len = std::strlen(username);
                    if (len > 0) {
                        username[len - 1] = '\0';
                    }
                }
                
                else if (event.text.unicode == '\r') { // Nhấn Enter
                    if (std::strlen(username) > 0 && std::strchr(username, ' ') == nullptr) {
                        isTyping = false; // Kết thúc nhập nếu hợp lệ
                    }
                }
                
                else if (event.text.unicode < 128) { // Chỉ nhận ký tự ASCII
                    unsigned int len = std::strlen(username);
                    if (len < MAXLEN - 1) { // Kiểm tra không vượt quá kích thước mảng
                        username[len] = static_cast<char>(event.text.unicode);
                        username[len + 1] = '\0'; // Kết thúc chuỗi
                    }
                }
            }
        }

        // Cập nhật vị trí và nội dung của text hiển thị tên
        nameInputText.setString(username);
        float x = box.getPosition().x + (box.getSize().x - nameInputText.getLocalBounds().width) / 2.0f;
        float y = box.getPosition().y + (box.getSize().y - nameInputText.getLocalBounds().height) / 2.0f - nameInputText.getLocalBounds().top;
        nameInputText.setPosition(x, y);

        // Vẽ giao diện
        window.clear(sf::Color(251, 249, 240));
        window.draw(text);
        window.draw(box);
        window.draw(nameInputText);
        window.display();
    }
}

// Hàm hiển thị giao diện chọn nhân vật và trả về lựa chọn của người chơi
int characterChoose(sf::RenderWindow& window, const sf::Font& font) {
    // Tiêu đề của menu
    sf::Text title("Nhan vat", font, 50);
    title.setFillColor(sf::Color(119, 110, 97));
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 5.0f
    );

    const int characterNumber = 5; // Số lượng nhân vật

    // Mảng chứa tên file ảnh các nhân vật
    const char* characterImgs[characterNumber] = {
        "pikachu.png",
        "chamander.png",
        "squirtle.png",
        "bulbasaur.png",
        "evee.png"
    };

    // Mảng texture để lưu hình ảnh và sprite để hiển thị
    sf::Texture textures[characterNumber];
    sf::Sprite sprites[characterNumber];

    char filePath[MAXLEN]; // Bộ đệm cho đường dẫn đầy đủ

    // Nạp các file ảnh vào texture và gán texture vào sprite
    for (int i = 0; i < characterNumber; ++i) {
        std::sprintf(filePath, "../assets/Texture/%s", characterImgs[i]);
        if (!textures[i].loadFromFile(filePath)) { // Kiểm tra nếu không tải được ảnh
            std::cerr << "Khong the tai anh: " << filePath << '\n';
            exit(0); // Thoát chương trình nếu gặp lỗi
        }

        sprites[i].setTexture(textures[i]); // Gán texture cho sprite
        sprites[i].setPosition(
            window.getSize().x / 2.0f - sprites[i].getLocalBounds().width / 2.0f,
            window.getSize().y / 2.0f - sprites[i].getLocalBounds().height / 2.0f
        );
    }

    // Tạo mũi tên trái
    sf::ConvexShape leftArrow;
    leftArrow.setPointCount(3);
    leftArrow.setFillColor(sf::Color(119, 110, 97));
    leftArrow.setPoint(0, sf::Vector2f(window.getSize().x / 2.0f - 250, window.getSize().y / 2.0f));
    leftArrow.setPoint(1, sf::Vector2f(window.getSize().x / 2.0f - 200, window.getSize().y / 2.0f - 30));
    leftArrow.setPoint(2, sf::Vector2f(window.getSize().x / 2.0f - 200, window.getSize().y / 2.0f + 30));

    // Tạo mũi tên phải
    sf::ConvexShape rightArrow;
    rightArrow.setPointCount(3);
    rightArrow.setFillColor(sf::Color(119, 110, 97));
    rightArrow.setPoint(0, sf::Vector2f(window.getSize().x / 2.0f + 250, window.getSize().y / 2.0f));
    rightArrow.setPoint(1, sf::Vector2f(window.getSize().x / 2.0f + 200, window.getSize().y / 2.0f - 30));
    rightArrow.setPoint(2, sf::Vector2f(window.getSize().x / 2.0f + 200, window.getSize().y / 2.0f + 30));

    // Tạo nút xác nhận chọn nhân vật
    sf::Text chooseButton("Choose", font, 30);

    // Hình chữ nhật bao quanh nút "Choose"
    sf::RectangleShape rec;
    rec.setFillColor(sf::Color(187, 174, 158));
    rec.setSize(sf::Vector2f(chooseButton.getLocalBounds().width + 20, chooseButton.getLocalBounds().height + 20));
    rec.setPosition(
        window.getSize().x / 2.0f - rec.getSize().x / 2.0f,
        window.getSize().y / 1.3f
    );

    // Đặt nút "Choose" vào giữa hình chữ nhật
    chooseButton.setFillColor(sf::Color::White);
    chooseButton.setPosition(
        rec.getPosition().x + (rec.getSize().x - chooseButton.getLocalBounds().width) / 2.0f,
        rec.getPosition().y + (rec.getSize().y - chooseButton.getLocalBounds().height) / 2.0f - 7.0f
    );

    int selected = 0; // Chỉ số nhân vật đang được chọn

    // Vòng lặp chính
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { // Nếu người dùng đóng cửa sổ
                window.close();
                return -1; // Kết thúc hàm và trả về -1
            }

            // Xử lý chuột
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { // Nhấn chuột trái
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Lấy vị trí chuột

                    // Kiểm tra nếu nhấn vào mũi tên phải
                    if (rightArrow.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        selected = (selected + 1) % 5; // Chuyển sang nhân vật tiếp theo
                    
                    // Kiểm tra nếu nhấn vào mũi tên trái
                    else if (leftArrow.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        selected = (selected - 1 + 5) % 5; // Chuyển về nhân vật trước đó

                    // Kiểm tra nếu nhấn vào nút "Choose"
                    else if (rec.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        return selected + 1; // Trả về chỉ số nhân vật được chọn
                }
            }

            // Xử lý bàn phím
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) // Nhấn phím D hoặc mũi tên phải
                    selected = (selected + 1) % 5;
                    
                else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) // Nhấn phím A hoặc mũi tên trái
                    selected = (selected - 1 + 5) % 5;

                else if (event.key.code == sf::Keyboard::Enter) // Nhấn Enter
                    return selected + 1; // Trả về chỉ số nhân vật được chọn
            }
        }

        // Vẽ các thành phần lên màn hình
        window.clear(sf::Color(251, 249, 240));
        window.draw(title);
        window.draw(leftArrow);
        window.draw(rightArrow);
        window.draw(rec);
        window.draw(chooseButton);

        // Vẽ nhân vật đang được chọn
        for (int i = 0; i < characterNumber; ++i)
            if (i == selected)
                window.draw(sprites[i]);

        window.display(); // Hiển thị nội dung 
    }

    return -1; // Trả về -1 nếu vòng lặp bị thoát mà không chọn
}

// Hàm hiển thị menu quay lại menu chính và xử lý lựa chọn
int Return(sf::RenderWindow& window, const sf::Font& font) {

    // Tiêu đề của menu
    sf::Text title("Ban co muon quay lai ?", font, 50);
    title.setFillColor(sf::Color(119, 110, 97));
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
    menuReturn[0].setFillColor(sf::Color(119, 110, 97));
    menuReturn[0].setPosition(
        window.getSize().x / 2.0f - menuReturn[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    menuReturn[1].setFont(font);
    menuReturn[1].setString("Khong");
    menuReturn[1].setCharacterSize(30);
    menuReturn[1].setFillColor(sf::Color(119, 110, 97));
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

            if (event.type == sf::Event::MouseMoved){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < 2; ++i)
                    if (menuReturn[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        selected = i;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)

                    selected = (selected + 1) % 2;

                else if (event.key.code == sf::Keyboard::Enter)
                    return selected + 1;
            }

            else if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < 2; ++i)
                        if (menuReturn[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                            return i + 1;
                }
        }

        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menuReturn[i].setFillColor(sf::Color::White);

                box.setSize(sf::Vector2f(menuReturn[i].getLocalBounds().width + 20, menuReturn[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(187, 174, 158));
                box.setPosition(
                    menuReturn[i].getPosition().x - 10,
                    menuReturn[i].getPosition().y
                );
            }
            
            else
                menuReturn[i].setFillColor(sf::Color(119, 110, 97));
        }

        window.clear(sf::Color(251, 249, 240));
        window.draw(title);
        window.draw(box);

        for (int i = 0; i < 2; ++i)
            window.draw(menuReturn[i]);

        window.display();
    }

    return -1;
}


int customizeSize(sf::RenderWindow& window, const sf::Font& font) {
    sf::RectangleShape box;
    box.setFillColor(sf::Color(187, 174, 158));
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);
    box.setSize(sf::Vector2f(500, 50));
    box.setPosition(
        window.getSize().x / 2.0f - box.getSize().x / 2.0f,
        window.getSize().y / 2.0f - box.getSize().y / 2.0f
    );

    sf::Text customSize;
    customSize.setFont(font);
    customSize.setCharacterSize(30);
    customSize.setFillColor(sf::Color::White);

    char size[MAXLEN] = ""; // Mảng ký tự để lưu kích thước
    int sizeLength = 0; // Độ dài của chuỗi
    bool isTyping = true;

    while (isTyping && window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace
                    if (sizeLength > 0) {
                        size[--sizeLength] = '\0'; // Xóa ký tự cuối cùng
                    }
                }

                else if (event.text.unicode == '\r') { // Enter
                    if (sizeLength > 0 && strchr(size, ' ') == nullptr) { // Kiểm tra chuỗi không rỗng và không chứa khoảng trắng
                        isTyping = false;
                    }
                }

                else if (event.text.unicode >= '0' && event.text.unicode <= '9') { // Ký tự số
                    if (sizeLength < sizeof(size) - 1) { // Kiểm tra tràn mảng
                        size[sizeLength++] = static_cast<char>(event.text.unicode);
                        size[sizeLength] = '\0'; // Thêm ký tự kết thúc chuỗi
                    }
                }
            }
        }

        customSize.setString(size);
        float x = box.getPosition().x + (box.getSize().x - customSize.getLocalBounds().width) / 2.0f;
        float y = box.getPosition().y + (box.getSize().y - customSize.getLocalBounds().height) / 2.0f - customSize.getLocalBounds().top;
        customSize.setPosition(x, y);
        
        window.clear(sf::Color(251, 249, 240));
        window.draw(box);
        window.draw(customSize);
        window.display();
    }

    return std::atoi(size); // Chuyển mảng ký tự thành số nguyên
}

// Hàm chọn kích thước bảng chơi từ giao diện
int sizeInput(sf::RenderWindow& window, const sf::Font& font) {

    // Tương tự các menu khác
    sf::Text title("Chon kich thuoc", font, 50);
    title.setFillColor(sf::Color(119, 110, 97));
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 4.0f
    );

    sf::RectangleShape box;
    sf::Text menuSize[3];

    menuSize[0].setFont(font);
    menuSize[0].setString("4 x 4");
    menuSize[0].setCharacterSize(30);
    menuSize[0].setFillColor(sf::Color(119, 110, 97));
    menuSize[0].setPosition(
        window.getSize().x / 2.0f - menuSize[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    menuSize[1].setFont(font);
    menuSize[1].setString("6 x 6");
    menuSize[1].setCharacterSize(30);
    menuSize[1].setFillColor(sf::Color(119, 110, 97));
    menuSize[1].setPosition(
        window.getSize().x / 2.0f - menuSize[1].getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f
    );

    menuSize[2].setFont(font);
    menuSize[2].setString("Khac");
    menuSize[2].setCharacterSize(30);
    menuSize[2].setFillColor(sf::Color(119, 110, 97));
    menuSize[2].setPosition(
        window.getSize().x / 2.0f - menuSize[2].getLocalBounds().width / 2.0f,
        window.getSize().y / 2.0f + 50
    );

    int selected = 0;
    char size[MAXLEN] = ""; // Mảng ký tự để lưu kích thước
    int sizeLength = 0; // Độ dài chuỗi nhập

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < 3; ++i)
                    if (menuSize[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        selected = i;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                    selected = (selected - 1 + 3) % 3;

                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                    selected = (selected + 1) % 3;

                else if (event.key.code == sf::Keyboard::Enter) {
                    if (selected == 0) return 4;
                    if (selected == 1) return 6;
                    if (selected == 2) break;
                }
            }

            else if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < 3; ++i)
                        if (menuSize[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            if (i == 0) return 4;
                            if (i == 1) return 6;
                            if (i == 2) {
                                selected = i;
                                break;
                            }
                        }
                }
        }

        for (int i = 0; i < 3; ++i) {
            if (i == selected) {
                menuSize[i].setFillColor(sf::Color::White);

                box.setSize(sf::Vector2f(menuSize[i].getLocalBounds().width + 20, menuSize[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(187, 174, 158));
                box.setPosition(
                    menuSize[i].getPosition().x - 10,
                    menuSize[i].getPosition().y
                );

                if (selected == 2) {
                    sf::RectangleShape sizeBox;
                    sizeBox.setFillColor(sf::Color(187, 174, 158));
                    sizeBox.setOutlineColor(sf::Color::Black);
                    sizeBox.setOutlineThickness(1);
                    sizeBox.setSize(sf::Vector2f(box.getSize().x, 50));
                    sizeBox.setPosition(
                        box.getPosition().x,
                        window.getSize().y / 2.0f + 100
                    );

                    sf::Text customSize;
                    customSize.setFont(font);
                    customSize.setCharacterSize(30);
                    customSize.setFillColor(sf::Color::White);

                    sf::Text cautionText("Nhap so lon hon 4, be hon 9 va khac 6 de dam bao trai nghiem choi tot nhat (ban co the nhap size lon hon)", font, 10);
                    cautionText.setFillColor(sf::Color::Red);
                    cautionText.setPosition(
                        window.getSize().x / 2.0f - cautionText.getLocalBounds().width / 2.0f,
                        box.getPosition().y + box.getLocalBounds().height + customSize.getLocalBounds().height + 70
                    );

                    window.clear(sf::Color(251, 249, 240));
                    window.draw(title);
                    window.draw(box);
                    window.draw(sizeBox);
                    window.draw(customSize);
                    window.draw(cautionText);

                    for (int i = 0; i < 3; ++i)
                        window.draw(menuSize[i]);

                    window.display();

                    bool isTyping = true;

                    while (isTyping && window.isOpen()) {
                        sf::Event event;

                        while (window.pollEvent(event)) {
                            if (event.type == sf::Event::Closed) {
                                window.close();
                                return -1;
                            }

                            if (selected != 2) {
                                isTyping = false;
                                break;
                            }

                            if (event.type == sf::Event::MouseMoved){
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                                for (int i = 0; i < 3; ++i)
                                    if (menuSize[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                                        selected = i;
                            }

                            if (event.type == sf::Event::KeyPressed) {
                                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                                    selected = (selected - 1 + 3) % 3;
                                
                                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                                    selected = (selected + 1) % 3;
                            }

                            if (event.type == sf::Event::TextEntered) {
                                if (event.text.unicode == '\b') { // Backspace
                                    if (sizeLength > 0) {
                                        size[--sizeLength] = '\0';
                                    }
                                } else if (event.text.unicode == '\r') { // Enter
                                    int enteredSize = std::atoi(size);
                                    if (enteredSize > 4 && enteredSize != 6)
                                        return enteredSize;
                                } else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                                    if (sizeLength < 19) { // Giới hạn số ký tự
                                        size[sizeLength++] = static_cast<char>(event.text.unicode);
                                        size[sizeLength] = '\0';
                                    }
                                }
                            }
                        }

                        customSize.setString(size);
                        float x = sizeBox.getPosition().x + (sizeBox.getSize().x - customSize.getLocalBounds().width) / 2.0f;
                        float y = sizeBox.getPosition().y + (sizeBox.getSize().y - customSize.getLocalBounds().height) / 2.0f - customSize.getLocalBounds().top;
                        customSize.setPosition(x, y);

                        window.clear(sf::Color(251, 249, 240));
                        window.draw(title);
                        window.draw(box);
                        window.draw(sizeBox);
                        window.draw(customSize);
                        window.draw(cautionText);

                        for (int i = 0; i < 3; ++i)
                            window.draw(menuSize[i]);

                        window.display();
                    }
                }
            } else
                menuSize[i].setFillColor(sf::Color(119, 110, 97));
        }

        window.clear(sf::Color(251, 249, 240));
        window.draw(title);
        window.draw(box);

        for (int i = 0; i < 3; ++i)
            window.draw(menuSize[i]);

        window.display();
    }

    return -1;
}

// Hàm điều chỉnh kích thước cửa sổ dựa vào kích thước bảng
void playWindow(sf::RenderWindow& window, const int &size) {
    const float baseCellSize = 100.0f;
    float cellSize;

    if (size >= 9)
        cellSize = static_cast<int>(baseCellSize * (8.0f / size)); // Tỉ lệ giảm kích thước ô khi size tăng

    else
        cellSize = static_cast<int>(baseCellSize);

    
    // Kích thước của toàn bộ bảng chơi
    int playSize = size * cellSize;

    // Thay đổi kích thước cửa sổ sao cho đủ hiển thị bảng và thêm viền ngoài
    // Thêm 250 pixel chiều rộng và 150 pixel chiều cao để chứa giao diện phụ (điểm số, điều khiển, ...)
    window.setSize(sf::Vector2u(playSize + 250, playSize + 150));

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int screenWidth = desktop.width;
    int screenHeight = desktop.height;

    window.setPosition(sf::Vector2i((screenWidth - playSize - 250) / 2, (screenHeight - playSize - 150) / 2));

    // Cập nhật chế độ nhìn (view) để giữ tỷ lệ hiển thị trên cửa sổ
    // Tạo view mới bao phủ toàn bộ vùng hiển thị, đảm bảo nội dung không bị méo
    sf::View view(sf::FloatRect(0, 0, playSize + 250, playSize + 150));
    window.setView(view);
}

// Hàm in bảng chơi ra giao diện
void printGrid(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character) {
    // Điều chỉnh kích thước ô vuông và chữ bên trong ô dựa trên kích thước bảng
    const float baseCellSize = 100.0f; // Kích thước ô vuông cơ bản
    const int baseNumSize = 24; // Kích thước chữ trong ô cơ bản

    float cellSize;
    int cellNumSize;

    if (size >= 9){
        cellSize = baseCellSize * (8.0f / size); // Tỉ lệ giảm kích thước ô khi size tăng
        cellNumSize = static_cast<int>(baseNumSize * (8.0f / size)); // Tỉ lệ giảm kích thước chữ trong ô
    }

    else{
        cellSize = baseCellSize;
        cellNumSize = 24;
    }

    // Xóa cửa sổ và đặt màu nền
    window.clear(sf::Color(251, 249, 240));

    // Vẽ các ô và giá trị trong bảng
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize + 1, i * cellSize + 1);
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black);

            // Đặt màu nền cho ô dựa trên giá trị trong bảng
            cell.setFillColor(cellColor(bang[i][j]));
            window.draw(cell);

            // Vẽ số trong ô nếu khác 0
            if (bang[i][j] != 0) {
                sf::Text text;
                text.setFont(font);

                // Chuyển giá trị thành chuỗi
                char valueStr[MAXLEN];
                snprintf(valueStr, sizeof(valueStr), "%d", bang[i][j]);
                text.setString(valueStr);

                text.setCharacterSize(cellNumSize); // Kích thước chữ trong ô
                text.setFillColor(numberColor(bang[i][j]));

                // Căn giữa số trong ô
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

    // Tính điểm người chơi
    int point = score(bang, size);
    char pointText[MAXLEN];
    snprintf(pointText, sizeof(pointText), "Diem cua ban: %d", point);

    // Hiển thị điểm
    sf::Text text(pointText, font, 24); // Giữ nguyên kích thước chữ điểm
    text.setFillColor(sf::Color::White);
    text.setPosition(
        size * cellSize + (window.getSize().x - size * cellSize) / 2.0f - text.getLocalBounds().width / 2.0f + 1,
        1
    );

    // Tải và hiển thị nhân vật
    const int characterNumber = 5;
    const char* characterImgs[characterNumber] = {
        "pikachu.png",
        "chamander.png",
        "squirtle.png",
        "bulbasaur.png",
        "evee.png"
    };

    sf::Texture texture;
    sf::Sprite sprite;

    char filePath[MAXLEN];
    strcpy(filePath, "../assets/Texture/");
    strcat(filePath, characterImgs[character - 1]);

    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Khong the tai anh: " << characterImgs[character - 1] << '\n';
        exit(0);
    }

    sprite.setTexture(texture);
    sprite.setPosition(
        size * cellSize + (window.getSize().x - size * cellSize) / 2.0f - sprite.getLocalBounds().width / 2.0f + 1,
        text.getPosition().y + 150.0f
    );

    // Hiển thị khung viền và thông tin
    sf::RectangleShape rec(sf::Vector2f(text.getLocalBounds().width + 20, text.getLocalBounds().height + 20));
    rec.setFillColor(sf::Color(187, 174, 158));
    rec.setPosition(text.getPosition().x - 10, text.getPosition().y - 5);

    window.draw(rec);
    window.draw(text);
    window.draw(sprite);

    // Hiển thị các hướng dẫn nút bấm (không thay đổi kích thước chữ)
    const char* newGameText = "N: New game";
    const char* controlText = "W: Len   S: Xuong   A: Trai   D: Phai";
    const char* undoRedoText = "U: Undo   R: Redo";
    const char* quitPauseText = "Q: Thoat   P: Luu va thoat";

    sf::Text textNewGame(newGameText, font, 24);
    sf::Text textControl(controlText, font, 24);
    sf::Text textUndoRedo(undoRedoText, font, 24);
    sf::Text textQuitPause(quitPauseText, font, 24);

    textNewGame.setFillColor(sf::Color(119, 110, 97));
    textNewGame.setPosition(1, size * cellSize + 10);

    textControl.setFillColor(sf::Color(119, 110, 97));
    textControl.setPosition(1, size * cellSize + textNewGame.getLocalBounds().height + 25);

    textUndoRedo.setFillColor(sf::Color(119, 110, 97));
    textUndoRedo.setPosition(1, size * cellSize + textNewGame.getLocalBounds().height + textControl.getLocalBounds().height + 40);

    textQuitPause.setFillColor(sf::Color(119, 110, 97));
    textQuitPause.setPosition(1, size * cellSize + textNewGame.getLocalBounds().height + textControl.getLocalBounds().height + textUndoRedo.getLocalBounds().height + 55);

    sf::RectangleShape instructRec(sf::Vector2f(size * cellSize, window.getSize().y - size * cellSize - 6));
    instructRec.setPosition(1, size * cellSize + 8);
    instructRec.setOutlineColor(sf::Color(187, 174, 158));
    instructRec.setOutlineThickness(2);
    instructRec.setFillColor(sf::Color(255, 255, 224));

    window.draw(instructRec);
    window.draw(textNewGame);
    window.draw(textControl);
    window.draw(textUndoRedo);
    window.draw(textQuitPause);

    // Cập nhật cửa sổ
    window.display();
}

// Hàm in màn hình thắng ra giao diện và xử lý lựa chọn
int winScreen(sf::RenderWindow& window, const sf::Font& font) {

    // Tạo tiêu đề "Bạn đã thắng"
    sf::Text title("Ban da thang", font, 60);
    title.setFillColor(sf::Color(119, 110, 97));
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 5.0f + 50
    );

    // Tạo câu hỏi "Bạn có muốn chơi tiếp không?"
    sf::Text text("Ban co muon choi tiep khong ?", font, 30);
    text.setFillColor(sf::Color(119, 110, 97));
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
    menuWin[0].setFillColor(sf::Color(119, 110, 97));
    menuWin[0].setPosition(
        window.getSize().x / 2.0f - menuWin[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 100
    );

    // Cài đặt mục "Không"
    menuWin[1].setFont(font);
    menuWin[1].setString("Khong");
    menuWin[1].setCharacterSize(30);
    menuWin[1].setFillColor(sf::Color(119, 110, 97));
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

            if (event.type == sf::Event::MouseMoved){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < 2; ++i)
                    if (menuWin[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        selected = i;
            }

            // Xử lý sự kiện phím
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)

                    selected = (selected + 1) % 2; // Di chuyển giữa các mục menu

                else if (event.key.code == sf::Keyboard::Enter) 
                    return selected + 1; // Trả về 1 (chơi tiếp) hoặc 2 (thoát)
            }

            // Xử lý sự kiện chuột
            else if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < 2; ++i)
                        if (menuWin[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                            return i + 1;
                }
        }

        // Cập nhật màu sắc của các tùy chọn
        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menuWin[i].setFillColor(sf::Color::White); // Mục được chọn sẽ có màu vàng

                // Thiết lập kích thước hộp bao quanh mục
                box.setSize(sf::Vector2f(menuWin[i].getLocalBounds().width + 20, menuWin[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(187, 174, 158));
                box.setPosition(menuWin[i].getPosition().x - 10, menuWin[i].getPosition().y);
            }

            else
                menuWin[i].setFillColor(sf::Color(119, 110, 97));
        }

        // Vẽ menu
        window.clear(sf::Color(251, 249, 240));
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
int loseScreen(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character) {
    // Tạo hiệu ứng mờ khi hiển thị màn hình thua
    sf::RectangleShape blurScreen;
    blurScreen.setFillColor(sf::Color(250, 250, 250, 100));
    blurScreen.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    // Tạo tiêu đề "GAME OVER"
    sf::Text title("GAME OVER", font, 60);
    title.setFillColor(sf::Color(119, 110, 97));
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        window.getSize().x / 2.0f - title.getLocalBounds().width / 2.0f,
        window.getSize().y / 5.0f + 50
    );

    // Hiển thị bàn cờ và tiêu đề "GAME OVER"
    printGrid(window, font, bang, size, 1);
    window.draw(blurScreen);
    window.draw(title);
    window.display();

    // Vòng lặp chờ người dùng nhấn phím hoặc chuột để tiếp tục
    while (window.isOpen()) {
        sf::Event event;
        bool flag = false;

        while (window.pollEvent(event)) {
            // Đóng cửa sổ nếu người dùng nhấn vào nút đóng
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            // Kiểm tra nếu người dùng nhấn phím hoặc chuột
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
                flag = true;    
        }

        // Thoát khỏi vòng lặp nếu có thao tác
        if (flag) break;
    }

    // Tạo thông báo hỏi người dùng có muốn chơi mới không
    sf::Text text("Ban co muon choi moi khong ?", font, 30);
    text.setFillColor(sf::Color(119, 110, 97));
    text.setStyle(sf::Text::Bold);
    text.setPosition(
        window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f
    );

    // Tạo các nút lựa chọn "Có" và "Không"
    sf::RectangleShape box;
    sf::Text menuLose[2];

    menuLose[0].setFont(font);
    menuLose[0].setString("Co");
    menuLose[0].setCharacterSize(30);
    menuLose[0].setFillColor(sf::Color(119, 110, 97));
    menuLose[0].setPosition(
        window.getSize().x / 2.0f - menuLose[0].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 50
    );

    menuLose[1].setFont(font);
    menuLose[1].setString("Khong");
    menuLose[1].setCharacterSize(30);
    menuLose[1].setFillColor(sf::Color(119, 110, 97));
    menuLose[1].setPosition(
        window.getSize().x / 2.0f - menuLose[1].getLocalBounds().width / 2.0f,
        window.getSize().y / 3.0f + 100
    );

    int selected = 0; // Biến lưu lựa chọn của người dùng

    // Vòng lặp xử lý lựa chọn
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            // Đóng cửa sổ nếu người dùng nhấn nút đóng
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::MouseMoved){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (int i = 0; i < 2; ++i)
                    if (menuLose[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        selected = i;
            }

            // Xử lý các phím điều hướng và Enter
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W ||
                    event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                    selected = (selected + 1) % 2;

                else if (event.key.code == sf::Keyboard::Enter) 
                    return selected + 1;
            }

            // Xử lý chuột nhấn
            else if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < 2; ++i)
                        if (menuLose[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                            return i + 1;
                }
        }

        // Hiển thị nút được chọn
        for (int i = 0; i < 2; ++i) {
            if (i == selected) {
                menuLose[i].setFillColor(sf::Color::White);

                box.setSize(sf::Vector2f(menuLose[i].getLocalBounds().width + 20, menuLose[i].getLocalBounds().height + 20));
                box.setFillColor(sf::Color(187, 174, 158));
                box.setPosition(menuLose[i].getPosition().x - 10, menuLose[i].getPosition().y);
            }

            else
                menuLose[i].setFillColor(sf::Color(119, 110, 97));
        }

        // Vẽ các thành phần lên màn hình
        window.clear(sf::Color(251, 249, 240));
        window.draw(text);
        window.draw(box);

        for (int i = 0; i < 2; ++i)
            window.draw(menuLose[i]);

        window.display();
    }
    return -1;
}

void displayLeaderboard(sf::RenderWindow& window, const sf::Font& font, const int& size, char** players, const int* scores, int curBoardSize, int maxDisplay) {
    window.clear(sf::Color(251, 249, 240));

    // Tiêu đề bảng xếp hạng
    char title[MAXLEN];
    std::sprintf(title, "Leaderboard %dx%d", size, size);

    sf::Text titleText(title, font, 60);
    titleText.setFillColor(sf::Color(119, 110, 97));
    titleText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 2.0f, 0);
    window.draw(titleText);

    sf::Text usernameText("Username", font, 40);
    usernameText.setFillColor(sf::Color(119, 110, 97));
    usernameText.setPosition(
        window.getSize().x / 2.0f - titleText.getLocalBounds().width / 4.0f - usernameText.getLocalBounds().width / 2.0f,
        titleText.getLocalBounds().height + 25
    ); 

    sf::Text pointText("Point", font, 40);
    pointText.setFillColor(sf::Color(119, 110, 97));
    pointText.setPosition(
        window.getSize().x / 2.0f + titleText.getLocalBounds().width / 4.0f - pointText.getLocalBounds().width / 2.0f,
        titleText.getLocalBounds().height + 25
    );

    window.draw(usernameText);
    window.draw(pointText);

    int leaderboardSize = (maxDisplay > curBoardSize) ? curBoardSize : maxDisplay;

    // Hiển thị từng người chơi
    for (int i = 0; i < leaderboardSize; ++i) {
        sf::Text playerText(players[i], font, 40);
        playerText.setFillColor(sf::Color(119, 110, 97));
        playerText.setPosition(
            usernameText.getPosition().x + usernameText.getLocalBounds().width / 2.0f - playerText.getLocalBounds().width / 2.0f,
            titleText.getLocalBounds().height + usernameText.getLocalBounds().height + 50 + i * 80
        );

        char score[MAXLEN];
        std::sprintf(score, "%d", scores[i]);

        sf::Text scoreText(score, font, 40);
        scoreText.setFillColor(sf::Color(119, 110, 97));
        scoreText.setPosition(
            pointText.getPosition().x + pointText.getLocalBounds().width / 2.0f - scoreText.getLocalBounds().width / 2.0f,
            titleText.getLocalBounds().height + usernameText.getLocalBounds().height + 50 + i * 80
        );

        window.draw(playerText);
        window.draw(scoreText);
    }

    window.display();

    // Chờ người dùng nhấn phím để tiếp tục
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::KeyPressed)
                return;
        }
    }
}