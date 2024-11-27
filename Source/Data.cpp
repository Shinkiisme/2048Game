#include "2048Lib.hpp"

// Hàm kiểm tra xem file lưu trữ đã tồn tại hay chưa, nếu chưa sẽ tự động tạo file mới
void database(const std::string& fileName) {
    std::ifstream file(fileName); // Mở file ở chế độ đọc để kiểm tra sự tồn tại

    if (!file) { // Nếu không mở được file (file chưa tồn tại)
        std::ofstream fileNew(fileName); // Tạo một file mới với tên fileName
        fileNew.close(); // Đóng file ngay sau khi tạo
    }
}

// Hàm nhập và kiểm tra tên người chơi, đảm bảo không trùng lặp
std::string playerName(sf::RenderWindow& window, const sf::Font& font) {
    std::string username;

    // Đảm bảo file lưu tên người chơi "players" tồn tại
    database("players");

    // Biến điều khiển vòng lặp để nhập tên
    bool isName = true;
    while (isName) {
        int menu = Menu(window, font); // Hiển thị menu và nhận lựa chọn từ người chơi

        // Nếu người chơi đóng cửa sổ, kết thúc hàm
        if (menu == -1) {
            window.close();
            return "";
        }

        // Nếu người chơi chọn bắt đầu trò chơi mới
        else if (menu == 1) {
            bool checkName = false;

            do {
                username = nameInput(window, font); // Yêu cầu người chơi nhập tên

                if (username == "") return ""; // Nếu người chơi không nhập tên, thoát

                checkName = true;

                std::ifstream file("players"); // Mở file "players" để kiểm tra tên trùng lặp
                std::string reading;

                // Kiểm tra xem tên đã tồn tại trong danh sách chưa
                while (std::getline(file, reading)) {
                    if (reading == username) { // Nếu tên đã tồn tại
                        sf::Text text("Ten da ton tai!", font, 30); // Hiển thị thông báo

                        text.setFillColor(sf::Color::Red);
                        text.setPosition(window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f, window.getSize().y / 1.5f);

                        checkName = false; // Đặt lại biến kiểm tra để yêu cầu nhập lại

                        window.draw(text);
                        window.display();

                        sf::sleep(sf::seconds(1)); // Dừng một giây để người chơi đọc thông báo

                        break;
                    }
                }
                file.close();

                // Nếu tên không hợp lệ, quay lại menu chính nếu người chơi chọn
                if (!checkName) {
                    int returnChoice = Return(window, font);

                    if (returnChoice == 1)
                        break; 
                }
            } while (!checkName);

            // Nếu tên hợp lệ, thoát khỏi vòng lặp chính
            if (checkName)
                isName = false;
        }

        // Nếu người chơi chọn tiếp tục trò chơi cũ
        if (menu == 2) {
            bool checkName = false;

            do {
                username = nameInput(window, font); // Yêu cầu nhập tên

                if (username == "") return ""; // Nếu người chơi không nhập tên, thoát

                checkName = true;

                std::ifstream file("players"); // Mở file "players" để kiểm tra tên
                std::string reading;
                bool nameFound = false;

                // Kiểm tra xem tên có tồn tại trong danh sách không
                while (std::getline(file, reading)) {
                    if (reading == username) { // Nếu tìm thấy tên
                        sf::Text text("Xin moi choi tiep", font, 30); // Hiển thị thông báo tiếp tục

                        text.setFillColor(sf::Color::Yellow);
                        text.setPosition(window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f, window.getSize().y / 1.5f);

                        nameFound = true; // Đánh dấu là tên đã được tìm thấy
                        checkName = true;

                        window.draw(text);
                        window.display();

                        sf::sleep(sf::seconds(1)); // Dừng một giây để người chơi đọc thông báo

                        break;
                    }
                }
                file.close();

                // Nếu không tìm thấy tên, hiển thị thông báo
                if (!nameFound) {
                    sf::Text text("Khong ton tai nguoi choi!", font, 30);

                    text.setFillColor(sf::Color::Red);
                    text.setPosition(window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f, window.getSize().y / 1.5f);

                    checkName = false; // Đặt lại biến kiểm tra để yêu cầu nhập lại

                    window.draw(text);
                    window.display();

                    sf::sleep(sf::seconds(1)); // Dừng một giây để người chơi đọc thông báo
                }

                // Nếu tên không hợp lệ, quay lại menu chính nếu người chơi chọn
                if (!checkName) {
                    int returnChoice = Return(window, font);

                    if (returnChoice == 1) 
                        break;
                }
            } while (!checkName);

            // Nếu tên hợp lệ, thoát khỏi vòng lặp chính
            if (checkName)
                isName = false;
        }
    }
    
    // Trả về tên người chơi hợp lệ
    return username;
}



// Hàm đọc dữ liệu trò chơi đã lưu từ file và trả về trạng thái bảng chơi
int** loadSave(int& size, std::string username) {

    // Đường dẫn đến file lưu dựa trên tên người chơi
    std::ifstream fileSave("Saves/" + username);
    std::string reading;

    // Nếu không mở được file (không có bản lưu), trả về nullptr
    if (!fileSave.is_open()) return nullptr;

    // Đọc kích thước bảng từ dòng đầu tiên của file và gán cho biến 'size'
    std::getline(fileSave, reading);
    std::istringstream(reading) >> size;

    // Khởi tạo mảng động hai chiều 'bang' có kích thước 'size x size'
    int** bang = new int* [size];
    for (int i = 0; i < size; ++i)
        bang[i] = new int[size];

    // Đọc dữ liệu từng dòng trong file để thiết lập giá trị cho bảng
    for (int i = 0; i < size; ++i) {
        std::getline(fileSave, reading); // Đọc từng dòng chứa dữ liệu của bảng
        std::istringstream load(reading);

        for (int j = 0; j < size; ++j)
            load >> bang[i][j]; // Gán giá trị từng ô trong bảng từ dòng đọc được
    }

    // Đóng file sau khi đọc xong dữ liệu
    fileSave.close();

    // Trả về con trỏ hai chiều đại diện cho bảng đã đọc được
    return bang;
}

// Hàm lưu trạng thái trò chơi hiện tại vào file, bao gồm tên người chơi, kích thước bảng chơi và bảng chơi
void saveGame(int** bang, const int& size, const std::string& username) {

    // Kiểm tra xem tên người chơi đã tồn tại trong file "players" hay chưa
    std::ifstream file("players");
    std::string reading;
    bool nameFound = false;

    while (std::getline(file, reading)) {
        if (reading == username) {
            nameFound = true; // Nếu tìm thấy tên, dừng kiểm tra
            break;
        }
    }

    // Nếu tên người chơi chưa tồn tại, thêm vào file "players"
    if (!nameFound) {
        std::ofstream fileAdd("players", std::ios::app);

        fileAdd << username << '\n'; // Thêm tên người chơi vào cuối file

        fileAdd.close();
    }

    file.close();

    // Kiểm tra và tạo thư mục "Saves" nếu chưa tồn tại
    if (!std::filesystem::exists("Saves")) std::filesystem::create_directory("Saves");

    // Mở file lưu trữ trạng thái trò chơi với tên người chơi.
    std::ofstream save("Saves/" + username);

    // Ghi kích thước bảng vào dòng đầu tiên của file
    save << size << '\n';

    // Ghi trạng thái bảng trò chơi vào file
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            save << bang[i][j] << ' ';

        save << '\n';
    }
    
    // Đóng file sau khi ghi xong
    save.close();
}

// Hàm trả về giá trị lớn nhất giữa hai số nguyên
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Hàm thêm thông tin người chơi, sắp xếp bảng xếp hạng và hiển thị lên giao diện
void leaderboard(sf::RenderWindow &window, const sf::Font& font, const int& size, const std::string& username, const int& point) {
    
    // Mở tệp chứa danh sách người chơi
    std::ifstream file("players");
    std::string reading;
    bool nameFound = false;

    // Kiểm tra nếu tên người chơi đã tồn tại trong danh sách
    while (std::getline(file, reading)) {
        if (reading == username) {
            nameFound = true;
            break; // Nếu tìm thấy tên, thoát khỏi vòng lặp
        }
    }
    
    // Nếu tên chưa có, thêm tên người chơi vào danh sách
    if (!nameFound) {
        std::ofstream fileAdd("players", std::ios::app);
        fileAdd << username << '\n';
        fileAdd.close();
    }

    // Nếu kích thước bảng xếp hạng là 4x4
    if (size == 4) {
       
        // Kiểm tra bảng xếp hạng đã lưu
        database("leaderboard4x4");

        std::ifstream input("leaderboard4x4");

        int line = 0;
        std::string reading;

        // Đếm số dòng trong bảng xếp hạng
        while (std::getline(input, reading))
            line++;

        // Quay lại đầu file để đọc lại thông tin
        input.clear();
        input.seekg(0, std::ios::beg);

        // Tạo mảng để lưu tên người chơi và điểm số
        std::string* players = new std::string[line + 1];
        int* scores = new int[line + 1];

        // Gán tên và điểm số người chơi hiện tại vào phần tử đầu tiên
        players[0] = username;
        scores[0] = point;

        // Đọc các tên và điểm số từ file vào mảng
        for (int i = 1; i < line + 1; ++i)
            input >> players[i] >> scores[i];

        input.close();

        bool isNewHighScore = false;

        // Kiểm tra xem người chơi hiện tại đã có trong bảng xếp hạng chưa
        for (int i = 1; i < line + 1; ++i)
            if (players[i] == players[0]) {
                scores[i] = max(scores[i], scores[0]); // Cập nhật điểm cao nhất nếu có
                isNewHighScore = true;
            }

        // Nếu người chơi chưa có trong bảng xếp hạng
        if (!isNewHighScore) {
            
            // Sắp xếp bảng xếp hạng theo điểm từ cao xuống thấp
            for (int i = 0; i < line + 1; i++) {
                int index = i;

                // Tìm điểm cao nhất để hoán đổi vị trí
                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }
            
            // Ghi lại bảng xếp hạng mới vào file
            std::ofstream output("leaderboard4x4", std::ios::out | std::ios::trunc);

            window.clear(sf::Color(30, 30, 30));

            // Vẽ tiêu đề cho bảng xếp hạng
            sf::Text titleText("Leaderboard 4 x 4", font, 60);
            titleText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 2.0f, 0);
            titleText.setFillColor(sf::Color::Yellow);

            window.draw(titleText);

            // Lựa chọn số lượng top 5 hoặc ít hơn để hiển thị
            int leaderboardSize = (5 < line + 1) ? 5 : line + 1;

            sf::Text* leaderboardName = new sf::Text[leaderboardSize];
            sf::Text* leaderboardPoint = new sf::Text[leaderboardSize];
            
            // Vẽ các tiêu đề phụ của bảng xếp hạng
            sf::Text userNameText("Username", font, 40);
            userNameText.setFillColor(sf::Color::White);
            userNameText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 4.0f - userNameText.getLocalBounds().width / 2.0f,
                                     titleText.getLocalBounds().height + 25);

            window.draw(userNameText);

            sf::Text pointText("Point", font, 40);
            pointText.setFillColor(sf::Color::White);
            pointText.setPosition(window.getSize().x / 2.0f + titleText.getLocalBounds().width / 4.0f - pointText.getLocalBounds().width / 2.0f,
                                  titleText.getLocalBounds().height + 25);

            window.draw(pointText);

            // Hiển thị bảng xếp hạng
            for (int i = 0; i < leaderboardSize; ++i) {
                output << players[i] << ' ' << scores[i] << '\n';

                leaderboardName[i].setFont(font);
                leaderboardName[i].setString(players[i]);
                leaderboardName[i].setCharacterSize(40);
                leaderboardName[i].setFillColor(sf::Color::White);
                leaderboardName[i].setPosition(userNameText.getPosition().x + userNameText.getLocalBounds().width / 2.0f - leaderboardName[i].getLocalBounds().width / 2.0f,
                                               titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardName[i]);

                leaderboardPoint[i].setFont(font);
                leaderboardPoint[i].setString(std::to_string(scores[i]));
                leaderboardPoint[i].setCharacterSize(40);
                leaderboardPoint[i].setFillColor(sf::Color::White);
                leaderboardPoint[i].setPosition(pointText.getPosition().x + pointText.getLocalBounds().width / 2.0f - leaderboardPoint[i].getLocalBounds().width / 2.0f,
                                                titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardPoint[i]);
            }

            output.close();

            window.display();

            sf::Event event;
            bool quit = false;

            // Thoát khi nhấn phím bất kỳ
            while (!quit && window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        exit(0);
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        quit = true;
                    }
                }
            }

            delete[] players;
            delete[] scores;
            delete[] leaderboardName;
            delete[] leaderboardPoint;
        }

        // Nếu người chơi hiện tại đã có trong bảng xếp hạng cũ, cập nhật điểm
        else {
            
            // Sắp xếp bảng xếp hạng và ghi lại
            // Các bước tiếp theo tương tự như trên
            for (int i = 1; i < line + 1; i++) {
                int index = i;

                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }

            std::ofstream output("leaderboard4x4", std::ios::out | std::ios::trunc);

            window.clear(sf::Color(30, 30, 30));

            sf::Text titleText("Leaderboard 4 x 4", font, 60);
            titleText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 2.0f, 0);
            titleText.setFillColor(sf::Color::Yellow);

            window.draw(titleText);

            int leaderboardSize = (5 < line + 1) ? 5 : line + 1;

            sf::Text* leaderboardName = new sf::Text[leaderboardSize];
            sf::Text* leaderboardPoint = new sf::Text[leaderboardSize];

            sf::Text userNameText("Username", font, 40);
            userNameText.setFillColor(sf::Color::White);
            userNameText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 4.0f - userNameText.getLocalBounds().width / 2.0f,
                titleText.getLocalBounds().height + 25);

            window.draw(userNameText);

            sf::Text pointText("Point", font, 40);
            pointText.setFillColor(sf::Color::White);
            pointText.setPosition(window.getSize().x / 2.0f + titleText.getLocalBounds().width / 4.0f - pointText.getLocalBounds().width / 2.0f,
                titleText.getLocalBounds().height + 25);

            window.draw(pointText);

            for (int i = 0; i < leaderboardSize; ++i) {
                output << players[i] << ' ' << scores[i] << '\n';

                leaderboardName[i].setFont(font);
                leaderboardName[i].setString(players[i]);
                leaderboardName[i].setCharacterSize(40);
                leaderboardName[i].setFillColor(sf::Color::White);
                leaderboardName[i].setPosition(userNameText.getPosition().x + userNameText.getLocalBounds().width / 2.0f - leaderboardName[i].getLocalBounds().width / 2.0f,
                    titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardName[i]);

                leaderboardPoint[i].setFont(font);
                leaderboardPoint[i].setString(std::to_string(scores[i]));
                leaderboardPoint[i].setCharacterSize(40);
                leaderboardPoint[i].setFillColor(sf::Color::White);
                leaderboardPoint[i].setPosition(pointText.getPosition().x + pointText.getLocalBounds().width / 2.0f - leaderboardPoint[i].getLocalBounds().width / 2.0f,
                    titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardPoint[i]);
            }

            output.close();

            window.display();

            sf::Event event;
            bool quit = false;

            while (!quit && window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        exit(0);
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        quit = true;
                    }
                }
            }

            delete[] players;
            delete[] scores;
            delete[] leaderboardName;
            delete[] leaderboardPoint;
        }
    }

    // Tương tự bảng xếp hạng 4x4
    else {
        database("leaderboard6x6");

        std::ifstream input("leaderboard6x6");

        int line = 0;
        std::string reading;

        while (std::getline(input, reading))
            line++;

        input.clear();
        input.seekg(0, std::ios::beg);

        std::string* players = new std::string[line + 1];
        int* scores = new int[line + 1];

        players[0] = username;
        scores[0] = point;

        for (int i = 1; i < line + 1; ++i)
            input >> players[i] >> scores[i];

        input.close();

        bool isNewHighScore = false;

        for (int i = 1; i < line + 1; ++i)
            if (players[i] == players[0]) {
                scores[i] = max(scores[i], scores[0]);
                isNewHighScore = true;
            }

        if (!isNewHighScore) {
            for (int i = 0; i < line + 1; i++) {
                int index = i;

                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }

            std::ofstream output("leaderboard6x6", std::ios::out | std::ios::trunc);

            window.clear(sf::Color(30, 30, 30));

            sf::Text titleText("Leaderboard 6 x 6", font, 60);
            titleText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 2.0f, 0);
            titleText.setFillColor(sf::Color::Yellow);

            window.draw(titleText);

            int leaderboardSize = (5 < line + 1) ? 5 : line + 1;

            sf::Text* leaderboardName = new sf::Text[leaderboardSize];
            sf::Text* leaderboardPoint = new sf::Text[leaderboardSize];

            sf::Text userNameText("Username", font, 40);
            userNameText.setFillColor(sf::Color::White);
            userNameText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 4.0f - userNameText.getLocalBounds().width / 2.0f,
                                     titleText.getLocalBounds().height + 25);

            window.draw(userNameText);

            sf::Text pointText("Point", font, 40);
            pointText.setFillColor(sf::Color::White);
            pointText.setPosition(window.getSize().x / 2.0f + titleText.getLocalBounds().width / 4.0f - pointText.getLocalBounds().width / 2.0f,
                                  titleText.getLocalBounds().height + 25);

            window.draw(pointText);

            for (int i = 0; i < leaderboardSize; ++i) {
                output << players[i] << ' ' << scores[i] << '\n';

                leaderboardName[i].setFont(font);
                leaderboardName[i].setString(players[i]);
                leaderboardName[i].setCharacterSize(40);
                leaderboardName[i].setFillColor(sf::Color::White);
                leaderboardName[i].setPosition(userNameText.getPosition().x + userNameText.getLocalBounds().width / 2.0f - leaderboardName[i].getLocalBounds().width / 2.0f,
                                               titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardName[i]);

                leaderboardPoint[i].setFont(font);
                leaderboardPoint[i].setString(std::to_string(scores[i]));
                leaderboardPoint[i].setCharacterSize(40);
                leaderboardPoint[i].setFillColor(sf::Color::White);
                leaderboardPoint[i].setPosition(pointText.getPosition().x + pointText.getLocalBounds().width / 2.0f - leaderboardPoint[i].getLocalBounds().width / 2.0f,
                                                titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardPoint[i]);
            }

            output.close();

            window.display();

            sf::Event event;
            bool quit = false;

            while (!quit && window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        exit(0);
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        quit = true;
                    }
                }
            }

            delete[] players;
            delete[] scores;
            delete[] leaderboardName;
            delete[] leaderboardPoint;
        }

        else {

            for (int i = 1; i < line + 1; i++) {
                int index = i;

                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }

            std::ofstream output("leaderboard6x6", std::ios::out | std::ios::trunc);

            window.clear(sf::Color(30, 30, 30));

            sf::Text titleText("Leaderboard 6 x 6", font, 60);
            titleText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 2.0f, 0);
            titleText.setFillColor(sf::Color::Yellow);

            window.draw(titleText);

            int leaderboardSize = (5 < line + 1) ? 5 : line + 1;

            sf::Text* leaderboardName = new sf::Text[leaderboardSize];
            sf::Text* leaderboardPoint = new sf::Text[leaderboardSize];

            sf::Text userNameText("Username", font, 40);
            userNameText.setFillColor(sf::Color::White);
            userNameText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 4.0f - userNameText.getLocalBounds().width / 2.0f,
                                     titleText.getLocalBounds().height + 25);

            window.draw(userNameText);

            sf::Text pointText("Point", font, 40);
            pointText.setFillColor(sf::Color::White);
            pointText.setPosition(window.getSize().x / 2.0f + titleText.getLocalBounds().width / 4.0f - pointText.getLocalBounds().width / 2.0f,
                                  titleText.getLocalBounds().height + 25);

            window.draw(pointText);

            for (int i = 0; i < leaderboardSize; ++i) {
                output << players[i] << ' ' << scores[i] << '\n';

                leaderboardName[i].setFont(font);
                leaderboardName[i].setString(players[i]);
                leaderboardName[i].setCharacterSize(40);
                leaderboardName[i].setFillColor(sf::Color::White);
                leaderboardName[i].setPosition(userNameText.getPosition().x + userNameText.getLocalBounds().width / 2.0f - leaderboardName[i].getLocalBounds().width / 2.0f,
                                               titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardName[i]);

                leaderboardPoint[i].setFont(font);
                leaderboardPoint[i].setString(std::to_string(scores[i]));
                leaderboardPoint[i].setCharacterSize(40);
                leaderboardPoint[i].setFillColor(sf::Color::White);
                leaderboardPoint[i].setPosition(pointText.getPosition().x + pointText.getLocalBounds().width / 2.0f - leaderboardPoint[i].getLocalBounds().width / 2.0f,
                                                titleText.getLocalBounds().height + userNameText.getLocalBounds().height + 50 + i * 80);

                window.draw(leaderboardPoint[i]);
            }

            output.close();

            window.display();

            sf::Event event;
            bool quit = false;

            while (!quit && window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        exit(0);
                    }

                    if (event.type == sf::Event::KeyPressed)
                        quit = true;    
                }
            }
            
            delete[] players;
            delete[] scores;
            delete[] leaderboardName;
            delete[] leaderboardPoint;
        }
    }
}

