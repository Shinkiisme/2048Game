#include "thu_vien_2048.h"

// Hàm gộp số theo hàng.
void merge_row(int** bang, int size, char button){

    // Duyệt qua từng hàng một.
    for (int i = 0; i < size; ++i){


        if (button == 'a' || button == 'A'){
            
            // Dồn các số khác 0 về phía bên trái của hàng.
            int chi_so = 0;

            for (int j = 0; j < size; ++j)
                if (bang [i][j] != 0) std::swap(bang[i][chi_so++], bang[i][j]);

            // Gộp các số giống nhau theo thứ tự từ trái qua phải.
            for (int j = 0; j < size - 1; ++j){
                if (bang[i][j] == bang[i][j + 1]){
                    bang[i][j] *= 2;
                    bang[i][j + 1] = 0;
                }
            }   

            // Dồn các số đã được gộp về phía bên trái.
            chi_so = 0;

            for (int j = 0; j < size; ++j)
                if (bang [i][j] != 0) std::swap(bang[i][chi_so++], bang[i][j]);
        }

        // Tương tự, gộp về phía bên phải.
        else{
            
            int chi_so = size - 1;

            for (int j = size - 1; j >= 0; --j)
                if (bang [i][j] != 0) std::swap(bang[i][chi_so--], bang[i][j]);

            for (int j = size - 1; j > 0; --j){
                if (bang[i][j] == bang[i][j - 1]){
                    bang[i][j] *= 2;
                    bang[i][j - 1] = 0;
                }
            }   

            chi_so = size - 1;

            for (int j = size - 1; j >= 0; --j)
                if (bang [i][j] != 0) std::swap(bang[i][chi_so--], bang[i][j]);
        }
    }
}