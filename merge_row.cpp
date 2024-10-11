#include "thu_vien_2048.h"

void merge_row(int** bang, int size, char button){

    for (int i = 0; i < size; ++i){


        if (button == 'a' || button == 'A'){
            
            int chi_so = 0;

            for (int j = 0; j < size; ++j)
                if (bang [i][j] != 0) std::swap(bang[i][chi_so++], bang[i][j]);

            for (int j = 0; j < size - 1; ++j){
                if (bang[i][j] == bang[i][j + 1]){
                    bang[i][j] *= 2;
                    bang[i][j + 1] = 0;
                }
            }   

            chi_so = 0;

            for (int j = 0; j < size; ++j)
                if (bang [i][j] != 0) std::swap(bang[i][chi_so++], bang[i][j]);
        }

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