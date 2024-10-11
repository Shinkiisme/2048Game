#include "thu_vien_2048.h"
// Hàm yêu cầu nhập và trả về nút - điều khiển của người chơi.
char control(){
    char button;

    std::cout << "n: new game\n" << "w: len\n" << "s: xuong\n" << "a: trai\n" << "d: phai\n" << "q: thoat\n" << "p: luu va thoat";
    do{
        std::cout << "\nMoi ban nhap: ";
        button = _getch();
    } while (button != 'n' && button != 'N' && button != 'w' && button != 'W' && button != 's' && button != 'S' && button != 'a' && button != 'A' && button != 'd' && button != 'D' && button != 'q' && button != 'Q' && button != 'p' && button != 'P');

   return button;
}