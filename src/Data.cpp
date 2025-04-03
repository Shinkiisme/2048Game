#include "Data.h"

// Hàm kiểm tra xem file lưu trữ đã tồn tại hay chưa, nếu chưa sẽ tự động tạo file mới
void database(const char* fileName) {
    // Kiểm tra và tạo thư mục "data" nếu chưa tồn tại
    if (!std::filesystem::exists("../data")) {
        std::filesystem::create_directory("../data");
    }

    // Tạo đường dẫn đầy đủ cho file
    char filePath[MAXLEN]; // Giới hạn kích thước chuỗi, đảm bảo đủ dài
    std::strcpy(filePath, "../data/");
    std::strcat(filePath, fileName);
    std::strcat(filePath, ".bin");

    // Mở file ở chế độ đọc để kiểm tra sự tồn tại
    std::ifstream file(filePath, std::ios::binary);
    if (!file) { // Nếu file chưa tồn tại
        std::ofstream fileNew(filePath, std::ios::binary); // Tạo file mới
        if (!fileNew) {
            std::cerr << "Loi tao file: " << filePath << std::endl;
        }
        fileNew.close(); // Đóng file ngay sau khi tạo
    }
}

//Hàm xử lý nhập tên người chơi và kiểm tra dữ liệu tồn tại
void playerName(sf::RenderWindow& window, const sf::Font& font, char* username) {
    const char* playersFile = "../data/players.bin";

    // Đảm bảo file lưu tên người chơi "players" tồn tại
    database("players");

    while (true) {
        int menu = Menu(window, font); // Hiển thị menu và nhận lựa chọn từ người chơi

        if (menu == -1) { // Nếu đóng cửa sổ
            window.close();
            username[0] = '\0'; // Đặt chuỗi rỗng để báo hiệu thoát
            return;
        }

        if (menu == 1) { // Bắt đầu trò chơi mới
            bool isNameDifferent = false;

            do {
                nameInput(window, font, username); // Nhập tên vào mảng `username`

                if (username[0] == '\0') return; // Nếu không nhập tên

                isNameDifferent = true;

                std::ifstream file("../data/players.bin", std::ios::binary);
                if (file) {
                    while (!file.eof()) {
                        int nameLength;
                        file.read((char*)&nameLength, sizeof(nameLength)); // Đọc độ dài tên
                        if (file.eof()) break; // Kiểm tra EOF tránh lỗi đọc

                        char existingName[MAXLEN];
                        file.read(existingName, nameLength); // Đọc tên

                        if (std::strcmp(existingName, username) == 0) { // Nếu trùng
                            sf::Text text("Ten da ton tai!", font, 30);
                            text.setFillColor(sf::Color::Red);
                            text.setPosition(
                                window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
                                window.getSize().y / 1.5f
                            );

                            isNameDifferent = false;

                            window.draw(text);
                            window.display();

                            sf::sleep(sf::seconds(1)); // Dừng một giây

                            break;
                        }
                    }
                    file.close();
                }

                if (!isNameDifferent) {
                    int returnChoice = Return(window, font);

                    if (returnChoice == 1) break; // Quay lại menu chính
                }
            } while (!isNameDifferent);
            
            if (isNameDifferent) break;
        } 

        else if (menu == 2) { // Tiếp tục trò chơi cũ
            bool isNameExisted = false;

            do {
                nameInput(window, font, username);

                if (username[0] == '\0') return;

                isNameExisted = false;

                std::ifstream file("../data/players.bin", std::ios::binary);
                if (file) {
                    while (!file.eof()) {
                        int nameLength;
                        file.read((char*)&nameLength, sizeof(nameLength)); // Đọc độ dài tên
                        if (file.eof()) break; // Kiểm tra EOF tránh lỗi đọc

                        char existingName[MAXLEN];
                        file.read(existingName, nameLength); // Đọc tên

                        if (std::strcmp(existingName, username) == 0) { // Nếu tên tồn tại
                            sf::Text text("Xin moi choi tiep", font, 30);
                            text.setFillColor(sf::Color::Red);
                            text.setPosition(
                                window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
                                window.getSize().y / 1.5f
                            );

                            isNameExisted = true;

                            window.draw(text);
                            window.display();

                            sf::sleep(sf::seconds(1)); // Dừng một giây

                            break;
                        }
                    }
                    file.close();
                }

                if (!isNameExisted) {
                    sf::Text text("Khong ton tai nguoi choi!", font, 30);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition(
                        window.getSize().x / 2.0f - text.getLocalBounds().width / 2.0f,
                        window.getSize().y / 1.5f
                    );

                    window.draw(text);
                    window.display();

                    sf::sleep(sf::seconds(1)); // Dừng một giây

                    int returnChoice = Return(window, font);
                    if (returnChoice == 1) break; // Quay lại menu chính
                }

            } while (!isNameExisted);

            if (isNameExisted) break;
        }
    }
}

// Hàm đọc dữ liệu trò chơi đã lưu từ file và trả về trạng thái bảng chơi
int** loadSave(Node *&currentNode, int& size, const char* username, int& character) {
    // Xây dựng đường dẫn file lưu dựa trên tên người chơi
    char filePath[MAXLEN];
    std::strcpy(filePath, "../data/Saves/");
    std::strcat(filePath, username);
    std::strcat(filePath, ".bin");

    // Mở file nhị phân để đọc
    std::ifstream fileSave(filePath, std::ios::binary);
    if (!fileSave) return nullptr; // Nếu không mở được file, trả về nullptr

    // Đọc nhân vật từ file
    fileSave.read((char*)& character, sizeof(character));

    // Đọc kích thước bảng từ file
    fileSave.read((char*)& size, sizeof(size));

    // Khởi tạo mảng động hai chiều để lưu trạng thái game
    int** bang = new int*[size];
    for (int i = 0; i < size; ++i)
        bang[i] = new int[size];

    currentNode->gameState = new int[size * size];
    fileSave.read(reinterpret_cast<char*>(currentNode->gameState), size * size * sizeof(int));

    // Đọc toàn bộ dữ liệu game từ file
    while (fileSave.peek() != EOF) {
        // Khởi tạo node mới
        Node* newNode = new Node();
        newNode->gameState = new int[size * size];
        newNode->next = nullptr;

        // Đọc dữ liệu vào `gameState`
        fileSave.read(reinterpret_cast<char*>(newNode->gameState), size * size * sizeof(int));
        
        // Liên kết danh sách liên kết
        currentNode->next = newNode;
        newNode->prev = currentNode;
        currentNode = newNode;
    }

    // Sao chép dữ liệu vào mảng `bang`
    for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                bang[i][j] = currentNode->gameState[i * size + j];

    fileSave.close();

    return bang; // Trả về mảng hai chiều chứa trạng thái game
}

// Hàm lưu trạng thái trò chơi hiện tại vào file, bao gồm tên người chơi, kích thước bảng chơi và bảng chơi
void saveGame(Node* head, const int& size, const char* username, const int& character) {
    // Kiểm tra và mở file players.bin để xem tên người chơi đã tồn tại chưa
    std::ifstream file("../data/players.bin", std::ios::binary);
    bool isNameFound = false;
    if (file) {
        while (!file.eof()) {
            int nameLength;
            file.read((char*)& nameLength, sizeof(nameLength)); // Đọc độ dài tên
            if (file.eof()) break; // Kiểm tra EOF tránh lỗi đọc

            char existingName[MAXLEN];
            file.read(existingName, nameLength); // Đọc tên

            if (std::strcmp(existingName, username) == 0) {
                isNameFound = true;
                break;
            }
        }
        file.close();
    }

    // Nếu tên người chơi chưa tồn tại, thêm vào file "players.bin"
    if (!isNameFound) {
        std::ofstream fileAdd("../data/players.bin", std::ios::binary | std::ios::app);

        int nameLen = std::strlen(username) + 1; // Độ dài chuỗi

        fileAdd.write((const char*)& nameLen, sizeof(nameLen)); // Ghi độ dài tên
        fileAdd.write(username, nameLen); // Ghi tên
        fileAdd.close();
    }

    // Kiểm tra và tạo thư mục "Saves" nếu chưa tồn tại
    if (!std::filesystem::exists("../data/Saves")) {
        std::filesystem::create_directory("../data/Saves");
    }

    // Tạo đường dẫn lưu trạng thái trò chơi
    char filePath[MAXLEN];
    std::strcpy(filePath, "../data/Saves/");
    std::strcat(filePath, username);
    std::strcat(filePath, ".bin");

    // Mở file lưu trạng thái trò chơi
    std::ofstream save(filePath, std::ios::binary);

    // Ghi nhân vật vào file
    save.write((const char*)& character, sizeof(character));

    // Ghi kích thước bảng vào file
    save.write((const char*)& size, sizeof(size));

    // Ghi dữ liệu bảng
    Node* currentNode = head;
    while (currentNode != nullptr) {
        save.write(reinterpret_cast<const char*>(currentNode->gameState), size * size * sizeof(int));
        currentNode = currentNode->next;
    }

    save.close();
}

// Hàm trả về giá trị lớn nhất giữa hai số nguyên
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Hàm kiểm tra và thêm người chơi mới vào danh sách
void addPlayerToList(const char* username, const char* playersFile) {
    std::ifstream file(playersFile, std::ios::binary);
    bool isNameFound = false;

    if (file) {
        while (!file.eof()) {
            // Đọc độ dài của tên người chơi
            int nameLength;
            file.read((char*)& nameLength, sizeof(nameLength));
            if (file.eof()) break; // Kiểm tra EOF sau khi đọc để tránh lỗi

            // Đọc tên người chơi từ file
            char* existingName = new char[nameLength + 1]();
            file.read(existingName, nameLength);
            existingName[nameLength] = '\0';

            // Kiểm tra nếu tên đã tồn tại
            if (std::strcmp(existingName, username) == 0) {
                isNameFound = true;
            }

            delete[] existingName;
            if (isNameFound) break;
        }
        file.close();
    }

    // Nếu chưa tồn tại, ghi thêm vào file nhị phân
    if (!isNameFound) {
        std::ofstream fileAdd(playersFile, std::ios::app | std::ios::binary);

        int nameLength = std::strlen(username);
        fileAdd.write((const char*)& nameLength, sizeof(nameLength)); // Ghi độ dài
        fileAdd.write(username, nameLength); // Ghi nội dung tên

        fileAdd.close();
    }
}

// Hàm đọc bảng xếp hạng từ file nhị phân
int readLeaderboard(const char* filePath, char**& players, int*& scores) {
    std::ifstream input(filePath, std::ios::binary);
    if (!input) return 0; // Nếu file không tồn tại, trả về 0

    int count = 0;
    input.read((char*)& count, sizeof(count)); // Đọc số lượng người chơi

    players = new char*[count];
    scores = new int[count];

    for (int i = 0; i < count; ++i) {
        int nameLength;
        input.read((char*)& nameLength, sizeof(nameLength)); // Đọc độ dài tên

        players[i] = new char[nameLength + 1];
        input.read(players[i], nameLength); // Đọc tên người chơi
        players[i][nameLength] = '\0';

        input.read(reinterpret_cast<char*>(&scores[i]), sizeof(scores[i])); // Đọc điểm số
    }

    input.close();
    return count;
}

// Hàm ghi bảng xếp hạng vào file nhị phân
void writeLeaderboard(const char* filePath, char** players, const int* scores, int curBoardSize) {
    std::ofstream output(filePath, std::ios::binary | std::ios::trunc);

    output.write((const char*)& curBoardSize, sizeof(curBoardSize)); // Ghi số lượng người chơi

    for (int i = 0; i < curBoardSize; ++i) {
        int nameLength = std::strlen(players[i]);
        output.write((const char*)& nameLength, sizeof(nameLength)); // Ghi độ dài tên
        output.write(players[i], nameLength); // Ghi tên
        output.write((const char*)& scores[i], sizeof(scores[i])); // Ghi điểm số
    }

    output.close();
}

// Hàm cập nhật điểm số của người chơi hoặc thêm người chơi mới vào bảng xếp hạng
void updateOrAddPlayer(char**& players, int*& scores, int& curBoardSize, const char* username, int point) {
    bool isPlayerExisted = false;

    // Kiểm tra nếu người chơi đã tồn tại và cập nhật điểm nếu cần
    for (int i = 0; i < curBoardSize; ++i) {
        if (std::strcmp(players[i], username) == 0) {
            scores[i] = (scores[i] > point) ? scores[i] : point;
            isPlayerExisted = true;
            break;
        }
    }

    // Nếu người chơi chưa tồn tại, thêm người chơi mới
    if (!isPlayerExisted) {
        // Tạo mảng mới với kích thước tăng thêm 1
        char** newPlayers = new char*[curBoardSize + 1];
        int* newScores = new int[curBoardSize + 1];

        // Sao chép dữ liệu hiện có
        for (int i = 0; i < curBoardSize; ++i) {
            int len = std::strlen(players[i]);
            newPlayers[i] = new char[len + 1];
            std::strcpy(newPlayers[i], players[i]);
            newScores[i] = scores[i];
        }

        // Thêm người chơi mới vào cuối mảng
        int nameLen = std::strlen(username);
        newPlayers[curBoardSize] = new char[nameLen + 1];
        std::strcpy(newPlayers[curBoardSize], username);
        newScores[curBoardSize] = point;

        // Giải phóng mảng cũ
        for (int i = 0; i < curBoardSize; ++i) 
            delete[] players[i];
        delete[] players;
        delete[] scores;

        // Cập nhật con trỏ và tăng số lượng người chơi
        players = newPlayers;
        scores = newScores;
        ++curBoardSize;
    }
}

// Hàm sắp xếp bảng xếp hạng theo thứ tự giảm dần của điểm số
void sortLeaderboard(char** players, int* scores, int curBoardSize) {
    for (int i = 0; i < curBoardSize; ++i) {
        int maxIdx = i;

        for (int j = i + 1; j < curBoardSize; ++j) {
            if (scores[j] > scores[maxIdx]) {
                maxIdx = j;
            }
        }
        std::swap(scores[i], scores[maxIdx]);
        std::swap(players[i], players[maxIdx]);
    }
}

// Hàm hiển thị bảng xếp hạng và cập nhật điểm số của người chơi
void leaderboard(sf::RenderWindow& window, const sf::Font& font, const int& size, const char* username, const int& point) {
    char playersFile[MAXLEN] = "../data/players.bin";
    char leaderboardFile[MAXLEN];
    std::sprintf(leaderboardFile, "../data/leaderboard%dx%d.bin", size, size);

    // Đảm bảo người chơi nằm trong danh sách
    addPlayerToList(username, playersFile);

    // Đọc dữ liệu bảng xếp hạng
    char** players = nullptr;
    int* scores = nullptr;
    int curBoardSize = readLeaderboard(leaderboardFile, players, scores);

    // Cập nhật hoặc thêm người chơi mới
    updateOrAddPlayer(players, scores, curBoardSize, username, point);

    // Sắp xếp bảng xếp hạng
    sortLeaderboard(players, scores, curBoardSize);

    // Ghi lại bảng xếp hạng
    writeLeaderboard(leaderboardFile, players, scores, curBoardSize);

    // Hiển thị bảng xếp hạng
    displayLeaderboard(window, font, size, players, scores, curBoardSize, 5);

    // Giải phóng bộ nhớ
    for (int i = 0; i < curBoardSize; ++i)
        delete[] players[i];
    delete[] players;
    delete[] scores;
}