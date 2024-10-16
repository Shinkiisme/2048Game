#include "thu_vien_2048.h"

int main(){

    // Khởi tạo các biến:
    // + Kiểm tra bắt đầu trò chơi mới
    // + Kiểm tra kết thúc một trò chơi.
    // + Kiểm tra tiếp tục trò chơi.
    // + Kiểm tra chế độ chơi sau khi thắng.
    bool isNewGame = true;
    bool isGameOver = false;
    bool isGameContinue = false;
    bool afterWin = false;

    // Vòng lặp duy trì trò chơi.
    while (!isGameContinue){

        // Khởi tạo:
        // + Tên người chơi.
        // Khai báo:
        // + Kích thước bảng chơi.
        // + Mảng lưu bảng chơi.
        // + Điểm.
        // + Node đầu tiên.
        std::string username;
        int size;
        int** bang;
        int point;
        Node* save_state = new Node;
        save_state->next = nullptr;
        save_state->prev = nullptr;
        Node* current_node = save_state;

        // Tạo trò chơi mới.
        if (isNewGame){
            clear_screen();
            
            // Người chơi nhấn nút bất kì để bắt đầu trò chơi.
            std::cout << "        2048 GAME\n";
            std::cout << "PRESS ANY KEY TO CONTINUE!";
            _getch();

            clear_screen();

            isNewGame = false;
            isGameOver = false;

            clear_screen();

            // Lưu tên người chơi vào biến.
            username = player_name();

            clear_screen();

            // Kiểm tra lưu của người chơi cũ.
            bang = load_save(username, size);

            // Nếu không có bản lưu cũ thì tạo mới.
            if (bang == nullptr){
                size = size_input();
                
                bang = make_grid(size);

                rand_number(bang, size);
                
            }
        }

        // Lưu bảng chơi vào node đầu tiên.
        current_node->game_state = new int[size * size];

        for (int i = 0; i < size; ++i)

            for (int j = 0; j < size; ++j)
                current_node->game_state[i * size + j] = bang[i][j];

        clear_screen();

        // Biến kiểm tra thắng, thua, random số.
        bool win = false;
        bool lose = false;
        bool random = false;

        // Vòng lặp duy trì khu vực bảng chơi cho tới khi thắng hoặc thua.
        while (!isGameOver){ 
            
            // Nếu undo thì random = false, giúp không tạo số mới khi undo;
            if (random)
                rand_number(bang, size);
            
            else random = true;

            clear_screen();

            // Tính và in ra điểm.
            point = score(bang, size);
            
            // In ra bảng chơi.
            print_grid(bang, size);

            // Nhận và gán thao tác của người dùng vào biến.
            char button = control();

            // Kiểm tra thao tác của người dùng để thực hiện các module hợp lí.
            if (button == 'a' || button == 'A' || button == 'd' || button == 'D'){              
                
                // Lưu bảng hiện tại rồi gộp hàng.
                new_state(bang, size, current_node);

                merge_row(bang, size, button);

            }

            else if (button == 'w' || button == 'W' || button == 's' || button == 'S'){              
                
                // Lưu bảng hiện tại rồi gộp cột.
                new_state(bang, size, current_node);

                merge_col(bang, size, button);

            }       
                

            else if (button == 'u' || button == 'U'){
                
                // Lưu lại bảng hiện tại nếu chưa được lưu rồi quay lại trạng thái bảng lúc trước.
                save_before_undo(bang, size, current_node);

                undo(bang, size, current_node);

                clear_screen();

                point = score(bang, size);

                print_grid(bang, size);

                random = false;

            }

            else if (button == 'r' || button == 'R'){

                // Về lại trạng thái trước khi undo.
                redo(bang, size, current_node);

                clear_screen();

                point = score(bang, size);

                print_grid(bang, size);

                random = false;

            }

            else if (button == 'p' || button == 'P'){

                clear_screen();

                // Thoát và lưu lại trạng thái hiện tại.
                save_game(bang, size, username);

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

                return 0;
            }

            // Kết thúc trò chơi.
            else if (button == 'q' || button == 'Q'){
                clear_screen();

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

                return 0;
            }
            
            // Bắt đầu trò chơi mới.
            else if (button == 'n' || button == 'N'){
                isNewGame = true;
                isGameOver = true;
                afterWin = false;
            }

            // Kiểm tra thắng, thua.
            win = win_check(bang, size, afterWin);
            lose = lose_check(bang, size);

            // Thắng hoặc thua thì kết thúc trò chơi.
            if (win || lose) isGameOver = true;
        }

        if (win){
            clear_screen();

            char wantContinue;

            // Cho người chơi lựa chọn chơi tiếp hoặc dừng lại sau khi đã thắng.
            std::cout << "Ban da thang!\n";
            std::cout << "Ban co  muon choi tiep khong? [Y/N]";

            do wantContinue = _getch();
            while (wantContinue != 'y' && wantContinue != 'Y' && wantContinue != 'n' && wantContinue != 'N');

            // Nếu chọn chơi tiếp thì tiếp tục trò chơi.
            if (wantContinue == 'y' || wantContinue == 'Y'){
                afterWin = true;
                isGameOver = false;
            }

            // Nếu không thì lưu lại điểm và sắp xếp bảng xếp hạng, kết thúc trò chơi.
            else{
                clear_screen();

                leaderboard(point, username, size);

                
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

            }

        }

        // Nếu thua thì lưu lại điểm và sắp xếp bảng xếp hạng, kết thúc trò chơi.
        if (lose){
            clear_screen();

            std::cout << "Ban da thua!\n";

            leaderboard(point, username, size);

            _getch();

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

            std::cout << "Nhan q de thoat tro choi!";
            char out = _getch();

            if (out == 'q' || out == 'Q'){ 
                clear_screen();

                return 0;
            
            }
            isNewGame = true;
        }

    }

    return 0;
}