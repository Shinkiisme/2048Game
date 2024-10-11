#include "thu_vien_2048.h"

// Hàm nhập kích thước khu vực chơi.
int size_input(){
    int size;

    std::cout << "Chon kich thuoc: \n";
    std::cout << "1. 4 x 4 \t" << "2. 6 x 6";

    // Nếu người chơi nhập sai thì nhập lại.
    do {
        std::cout << "\nXin moi nhap 1 hoac 2 de chon: ";
        size = _getch();
    } while (size != '1' && size != '2');

    // Trả về kích thước 4 x 4 hoặc 6 x 6.
    return (size == '1') ? 4 : 6;
}