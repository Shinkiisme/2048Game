#include "thu_vien_2048.h"

std::string player_name(){

    std::string username;

    database("players");

    bool isName = true;

    while (isName){

        bool check_name = false;

        char tiep_tuc;

        char quit;

        do{

            std::cout << "Ban co muon tiep tuc tro choi cu khong ? [Y/N]\n";
            tiep_tuc = _getch();
            std::cout << '\n';
        
        } while(tiep_tuc != 'y'&& tiep_tuc != 'Y' && tiep_tuc != 'n' && tiep_tuc != 'N');


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

                std::cout << "Ban co muon quay lai khong ? [Y/N]";
                do
                    quit = _getch();
                while (!(quit == 'y' || quit == 'Y' || quit == 'n' || quit == 'N'));

                if (quit == 'y' || quit == 'Y') break;

            } while(!check_name);

            std::ofstream file_add("players", std::ios::app);

            file_add << username << '\n';

            file_add.close();
        
        }

        else{

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

                if (!name_found){

                    std::cout << "Khong ton tai nguoi choi!\nXin nhap lai.\n";
                    check_name = false;
                
                }

                if (check_name){
                    isName = false;
                    break;
                }

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

    return username;
}

