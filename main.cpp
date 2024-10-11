#include "thu_vien_2048.h"

int main(){
    bool isNewGame = true;
    bool isGameOver = false;
    bool isGameContinue = false;

    while (!isGameContinue){

        std::string username;
        int size;
        int** bang;
        bool afterWin;
        int point;

        if (isNewGame){
            system("cls");
            
            // Người chơi nhấn nút bất kì để bắt đầu trò chơi.
            std::cout << "        2048 GAME\n";
            std::cout << "PRESS ANY KEY TO CONTINUE!";
            _getch();

            system("cls");

            isNewGame = false;
            isGameOver = false;

            system("cls");

            username = player_name();

            system("cls");

            bang = load_save(username, size);

            if (bang == nullptr){
                size = size_input();
                
                bang = make_grid(size);
                
            }
        }

        system("cls");

        bool win = false;
        bool lose = false;

        while (!isGameOver){

            rand_number(bang, size);
            
            system("cls");

            point = score(bang, size);

            print_grid(bang, size);

            char button = control();

            if (button == 'a' || button == 'A' || button == 'd' || button == 'D') merge_row(bang, size, button);
            
            else if (button == 'w' || button == 'W' || button == 's' || button == 'S') merge_col(bang, size, button);

            else if (button == 'p' || button == 'P'){
                system("cls");
                save_game(bang, size, username);
                return 0;
            }

            // Kết thúc trò chơi.
            else if (button == 'q' || button == 'Q'){
                system("cls");
                return 0;
            }
            
            // Bắt đầu trò chơi mới.
            else if (button == 'n' || button == 'N'){
                isNewGame = true;
                isGameOver = true;
            }

            win = win_check(bang, size, afterWin);
            lose = lose_check(bang, size);

            if (win || lose) isGameOver = true;
        }

        if (win){
            system("cls");

            char wantContinue;

            std::cout << "Ban da thang!\n";
            std::cout << "Ban co  muon choi tiep khong? [Y/N]";

            do wantContinue = _getch();
            while (wantContinue != 'y' && wantContinue != 'Y' && wantContinue != 'n' && wantContinue != 'N');

            if (wantContinue == 'y' || wantContinue == 'Y'){
                afterWin = true;
                isGameOver = false;
            }

            else{
                system("cls");

                leaderboard(point, username);
            }

        }

        else{
            system("cls");

            std::cout << "\nBan da thua!\n";

            _getch();

            leaderboard(point, username);

            isNewGame = true;
            isGameOver = true;
        }
    }

    return 0;
}