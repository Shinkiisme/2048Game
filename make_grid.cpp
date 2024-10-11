#include "thu_vien_2048.h"

// Hàm khai báo và tạo bảng theo kích thước lấy từ nhap_size().
int** make_grid(int size){
    // Cấp phát động mảng 2 chiều.
    int** bang = new int*[size];

    for (int i = 0; i < size; ++i)
        bang[i] = new int[size];

    // Gán tất cả phần tử trong mảng ban đầu bằng 0.
    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j)

            bang[i][j] = 0;


    // Lấy seed thời gian thực.
    srand(time(0));

    int ti_le = 1 + rand() % 10;
    int so;

    if (ti_le == 1) so = 4;
    else so = 2;
    
    // Lấy ngẫu nhiên một hàng để tạo số khởi đầu.
    int row_trong = rand() % (size - 1);
    int col_trong;

    // Lấy ngẫu nhiên một cột sao cho không trùng với hàng.
    do col_trong = rand() % (size - 1);
    while (col_trong == row_trong);

    // Tạo số để khởi đầu trò chơi.
    bang[row_trong][col_trong] = so;

    return bang;
}