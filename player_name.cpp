#include "thu_vien_2048.h"

// Hàm nhập và kiểm tra trùng lặp tên người chơi.
std::string player_name(){

    std::string username;

    // Kiểm tra và tạo mới file lưu tên các người chơi.
    database("players");

    bool isName = true;

    while (isName){

        bool check_name = false;

        char tiep_tuc;

        char quit;

        // Tiếp tục trò chơi cũ hay chơi mới.
        do{
            system("cls");

            std::cout << "Ban co muon tiep tuc tro choi cu khong ? [Y/N]\n";
            tiep_tuc = _getch();
            std::cout << '\n';
        
        } while(tiep_tuc != 'y'&& tiep_tuc != 'Y' && tiep_tuc != 'n' && tiep_tuc != 'N');

        // Chơi trò chơi mới thì tên không chứa kí tự ' ' và không trùng tên người chơi khác.
        if (tiep_tuc == 'n' || tiep_tuc == 'N'){
            
            do{
                system("cls");

                std::cout << "\nKhong nhap ki tu ' '\n" << "Nhap ten nguoi choi: ";
                std::getline(std::cin, username);

                if (username.find(' ') != std::string::npos || username.empty()){
                    std::cout << "Ten nhap khong hop le!\n";
                    check_name = false;
                    continue;
                }

                else check_name = true;

                std::ifstream file("players");
                std::string reading;

                // Kiểm tra tên đã tồn tại chưa.
                while(std::getline(file, reading)){
                    if (reading == username){
                    
                        std::cout << "Ten da ton tai!\nXin nhap ten khac.\n";
                        check_name = false;
                        break;
            
                    }
                }

                file.close();

                if (check_name){
                    isName = false;
                    break;
                }
                
                // Cho phép người chơi chọn lại chơi mới hay tiếp tục trò chơi cũ.
                std::cout << "Ban co muon quay lai khong ? [Y/N]";
                do
                    quit = _getch();
                while (!(quit == 'y' || quit == 'Y' || quit == 'n' || quit == 'N'));

                if (quit == 'y' || quit == 'Y') break;

            } while(!check_name);
        
        }

        // Tiếp tục trò chơi cũ.
        else{
            
            // Tên không được có kí tự ' ' và nhập đúng tên đã được lưu trong cơ sở dữ liệu.
            do{
                system("cls");

                std::cout << "\nKhong nhap ki tu ' '\n" << "Nhap ten nguoi choi: ";
                std::getline(std::cin, username);

                if (username.find(' ') != std::string::npos || username.empty()){
                    std::cout << "Ten nhap khong hop le!\n";
                    check_name = false;
                    continue;
                }

                else check_name = true;

                std::ifstream file("players");
                std::string reading;
                bool name_found = false;

                while(std::getline(file, reading)){
                    if (reading == username){
                    
                        std::cout << "Xin moi choi tiep.";
                        name_found = true;
                        check_name = true;
                        break;
            
                    }
                }

                file.close();

                // Kiểm tra tên đã tồn tại chưa.
                if (!name_found){

                    std::cout << "Khong ton tai nguoi choi!\nXin nhap lai.\n";
                    check_name = false;
                
                }

                if (check_name){
                    isName = false;
                    break;
                }

                // Cho phép người chơi chọn lại chơi mới hay chơi cũ.
                std::cout << "Ban co muon quay lai khong ? [Y/N]";
                do
                    quit = _getch();
                while (!(quit == 'y' || quit == 'Y' || quit == 'n' || quit == 'N'));

                if (quit == 'y' || quit == 'Y'){
                    system("cls");
                    break;
                }

            } while(!check_name);

        }
    
    }

    // Trả về tên người chơi.
    return username;
}

