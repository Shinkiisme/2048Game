#include "thu_vien_2048.h"

// Hàm lấy giá trị lớn nhất giữa 2 số.
int max(int a, int b){

    return (a > b) ? a : b;

}

// Hàm thêm tên người chơi, sắp xếp và in ra bảng xếp hạng.
void leaderboard(int point, std::string username, int size){

    // Thêm tên người chơi vào cơ sở dữ liệu người chơi sau khi đã hoàn thành game.
    std::ifstream file("players");
    std::string reading;
    bool name_found = false;

    // Nếu người chơi đã có tên thì bỏ qua.
    while(std::getline(file, reading)){
        if (reading == username){
            name_found = true;
            break;
        }
    }

    // Nếu chưa có thì thêm vào.
    if (!name_found){
            std::ofstream file_add("players", std::ios::app);

            file_add << username << '\n';

            file_add.close();
    }

    // Lưu bảng xếp hạng 4x4.
    if (size == 4){

        // Kiểm tra file lưu bảng xếp hạng 4x4.
        database("leaderboard4x4");

        std::ifstream input("leaderboard4x4");

        // Đếm số dòng của bảng xếp hạng.
        int line = 0;
        std::string reading;

        while (std::getline(input, reading))
            line++;

        // Đưa về đầu file.
        input.clear();
        input.seekg(0, std::ios::beg);

        // Cấp phát mảng lưu tên người chơi và điểm số.
        std::string* players = new std::string[line + 1];
        int* scores = new int[line + 1];

        // Gán giá 2 trị đầu tiên của 2 mảng là thông tin người chơi hiện tại.
        players[0] = username;
        scores[0] = point;

        // Đọc thông tin từ bảng xếp hạng cũ vào 2 mảng.
        for (int i = 1; i < line + 1; ++i)

            input >> players[i] >> scores[i];

        input.close();

        // Kiểm tra xem người chơi hiện tại đã có trong bảng xếp hạng chưa.
        // Nếu có thì lấy điểm số cao nhất gán cho điểm cũ.
        bool isNewHighScore = false;

        for (int i = 1; i < line + 1; ++i)
            if (players[i] == players[0]){
                scores[i] = max(scores[i], scores[0]);
                isNewHighScore = true;
            }

        // Nếu người chơi hiện tại chưa có trong bảng xếp hạng cũ.
        // Sắp xếp bảng xếp hạng từ lớn đến bé.
        if (!isNewHighScore){
            for (int i = 0; i < line + 1; i++) {
                int index = i;
                
                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }

            // Ghi đè bảng xếp hạng mới lên bảng xếp hạng cũ.
            // In ra bảng xếp hạng mới.
            std::ofstream output("leaderboard4x4", std::ios::out | std::ios::trunc);

            std::cout << "BANG XEP HANG 4x4\n";

            for (int i = 0; i < std::min(3, line + 1); ++i){
                output << players[i] << ' ' << scores[i] << '\n';
                std::cout << players[i] << std::setfill(' ') << std::setw(7) << scores[i] << '\n';
            }

            output.close();

            delete[] players;
            delete[] scores;

        }

        // Nếu người chơi hiện tại đã có trong bảng xếp hạng cũ.
        // Sắp xếp bảng xếp hạng từ lớn đến bé, loại người chơi hiện tại ra.
        else{

            for (int i = 1; i < line + 1; i++) {
                int index = i;
                
                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }

            // Tương tự.
            std::ofstream output("leaderboard4x4", std::ios::out | std::ios::trunc);

            std::cout << "BANG XEP HANG 4x4\n";

            for (int i = 1; i < std::min(3, line + 1); ++i){
                output << players[i] << ' ' << scores[i] << '\n';
                std::cout << players[i] << std::setw(7) << scores[i] << '\n';
            }

            output.close();

            delete[] players;
            delete[] scores;

        }
    
    }

    // Tương tự bảng xếp hạng 4x4.
    else{

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
            if (players[i] == players[0]){
                scores[i] = max(scores[i], scores[0]);
                isNewHighScore = true;
            }

        if (!isNewHighScore){
            for (int i = 0; i < line + 1; i++) {
                int index = i;
                
                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }

            std::ofstream output("leaderboard6x6", std::ios::out | std::ios::trunc);

            std::cout << "BANG XEP HANG 6x6\n";

            for (int i = 0; i < std::min(3, line + 1); ++i){
                output << players[i] << ' ' << scores[i] << '\n';
                std::cout << players[i] << std::setw(7) << scores[i] << '\n';
            }

            output.close();

            delete[] players;
            delete[] scores;

        }

        else{

            for (int i = 1; i < line + 1; i++) {
                int index = i;
                
                for (int j = i + 1; j < line + 1; j++)
                    if (scores[j] > scores[index])
                        index = j;

                std::swap(scores[i], scores[index]);
                std::swap(players[i], players[index]);
            }

            std::ofstream output("leaderboard6x6", std::ios::out | std::ios::trunc);

            std::cout << "BANG XEP HANG 6x6\n";

            for (int i = 1; i < std::min(3, line + 1); ++i){
                output << players[i] << ' ' << scores[i] << '\n';
                std::cout << players[i] <<  std::setw(7) << scores[i] << '\n';
            }

            output.close();

            delete[] players;
            delete[] scores;

        }

    }

}