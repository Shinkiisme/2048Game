#include "thu_vien_2048.h"

void leaderboard(int point, std::string username){

    database("leaderboard");

    std::ifstream input("leaderboard");

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

    for (int i = 0; i < line + 1; i++) {
        int index = i;
        
        for (int j = i + 1; j < line + 1; j++)
            if (scores[j] > scores[index])
                index = j;

        std::swap(scores[i], scores[index]);
        std::swap(players[i], players[index]);
    }

    std::ofstream output("leaderboard", std::ios::out | std::ios::trunc);

    std::cout << "BANG XEP HANG\n";

    for (int i = 0; i < std::min(3, line + 1); ++i){
        output << players[i] << ' ' << scores[i] << '\n';
        std::cout << players[i] << '\t' << scores[i] << '\n';
    }

    output.close();

    delete[] players;
    delete[] scores;

}