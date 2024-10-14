#include "thu_vien_2048.h"

int max(int a, int b){

    return (a > b) ? a : b;

}

void leaderboard(int point, std::string username, int size){

    std::ifstream file("players");
    std::string reading;
    bool name_found = false;

    while(std::getline(file, reading)){
        if (reading == username){
            name_found = true;
            break;
        }
    }

    if (!name_found){
            std::ofstream file_add("players", std::ios::app);

            file_add << username << '\n';

            file_add.close();
    }

    if (size == 4){

        database("leaderboard4x4");

        std::ifstream input("leaderboard4x4");

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

            std::ofstream output("leaderboard4x4", std::ios::out | std::ios::trunc);

            std::cout << "BANG XEP HANG 4x4\n";

            for (int i = 0; i < std::min(3, line + 1); ++i){
                output << players[i] << ' ' << scores[i] << '\n';
                std::cout << players[i] << '\t' << scores[i] << '\n';
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

            std::ofstream output("leaderboard4x4", std::ios::out | std::ios::trunc);

            std::cout << "BANG XEP HANG 4x4\n";

            for (int i = 1; i < std::min(3, line + 1); ++i){
                output << players[i] << ' ' << scores[i] << '\n';
                std::cout << players[i] << '\t' << scores[i] << '\n';
            }

            output.close();

            delete[] players;
            delete[] scores;

        }
    
    }

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
                std::cout << players[i] << '\t' << scores[i] << '\n';
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
                std::cout << players[i] << '\t' << scores[i] << '\n';
            }

            output.close();

            delete[] players;
            delete[] scores;

        }

    }

}