#include "thu_vien_2048.h"

// Hàm xoá màn hình theo hệ điều hành.
void clear_screen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}