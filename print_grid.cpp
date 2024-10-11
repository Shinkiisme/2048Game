#include "thu_vien_2048.h"

// Hàm lấy giá trị lớn nhất của hai số.
int max(int a, int b){
    return (a > b) ? a : b;
}

// Hàm in ra bảng chơi của trò chơi.
void print_grid(int** bang, int size){
    
    // Khởi tạo biến đếm số chữ số lớn nhất.
    int chu_so = 1;

    // Duyệt qua toàn bộ giá trị.
    for (int i = 0; i < size; ++i){

        for (int j = 0; j < size; ++j){

                // Tìm số chữ số lớn nhất của các giá trị trong bảng.
                if (bang[i][j] == 0) continue;
                chu_so = max(chu_so, floor(log10(bang[i][j])) + 1);
        }
    }

    // Duyệt qua bảng để in ra.
    for (int i = 0; i < size; ++i){

        for (int j = 0; j < size; ++j)

            // Tạo biên trên và dòng ngăn cách giữa các hàng dựa theo số chữ số lớn nhất.
            std::cout << '+' << std::setfill('-') << std::setw(7 + chu_so);

        std::cout << '+' << '\n';

        // In ra các giá trị của từng phần tử và biên trái phải ngăn cách giữa các cột theo số chữ số lớn nhất.
        for (int k = 0; k < size; ++k){
            std::cout << '|' << std::setfill(' ') <<  std::setw(3 + chu_so);
            
            // Nếu giá trị phần tử bằng 0 thì không in ra.
            if (bang[i][k] == 0) std::cout << ' ';
            else std::cout << bang[i][k];
           
            std::cout << "   ";
        }
        std::cout << "|\n";
    }    

    // Tạo biên dưới của bảng.
    for (int j = 0; j < size; ++j)
        std::cout << '+' << std::setfill('-') << std::setw(7 + chu_so);

    std::cout << '+' << '\n';
}
