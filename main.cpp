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
        Node* save_state = new Node;
        save_state->next = nullptr;
        save_state->prev = nullptr;
        Node* current_node = save_state;

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

                rand_number(bang, size);
                
            }
        }

        current_node->game_state = new int[size * size];

        for (int i = 0; i < size; ++i)

            for (int j = 0; j < size; ++j)
                current_node->game_state[i * size + j] = bang[i][j];

        system("cls");

        bool win = false;
        bool lose = false;
        bool random = false;

        while (!isGameOver){ 
            
            if (random)
                rand_number(bang, size);
            
            else random = true;

            system("cls");

            point = score(bang, size);

            print_grid(bang, size);

            char button = control();

            if (button == 'a' || button == 'A' || button == 'd' || button == 'D'){              
                
                new_state(bang, size, current_node);

                merge_row(bang, size, button);

            }

            else if (button == 'w' || button == 'W' || button == 's' || button == 'S'){              
                
                new_state(bang, size, current_node);

                merge_col(bang, size, button);

            }       
                

            else if (button == 'u' || button == 'U'){

                save_before_undo(bang, size, current_node);

                undo(bang, size, current_node);

                system("cls");

                point = score(bang, size);

                print_grid(bang, size);

                random = false;

            }

            else if (button == 'r' || button == 'R'){

                redo(bang, size, current_node);

                system("cls");

                point = score(bang, size);

                print_grid(bang, size);

                random = false;

            }

            else if (button == 'p' || button == 'P'){
                system("cls");
                save_game(bang, size, username);

                for (int i = 0; i < size; ++i) 
                    delete[] bang[i];

                delete[] bang;

                return 0;
            }

            // Kết thúc trò chơi.
            else if (button == 'q' || button == 'Q'){
                system("cls");

                for (int i = 0; i < size; ++i) 
                    delete[] bang[i];

                delete[] bang;

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

                leaderboard(point, username, size);
            }

        }

        if (lose){
            system("cls");

            std::cout << "\nBan da thua!\n";

            _getch();

            leaderboard(point, username, size);

            isNewGame = true;
            isGameOver = true;
        }

    for (int i = 0; i < size; ++i) 
        delete[] bang[i];

    delete[] bang;

    Node* delete_list = save_state;

    while (delete_list != nullptr){
        Node* next_node = delete_list->next;

        delete[] delete_list->game_state;
        delete delete_list;

        delete_list = next_node;
    }

    delete save_state;

    }

    return 0;
}