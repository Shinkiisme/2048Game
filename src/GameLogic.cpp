#include "GameLogic.h"

// Hàm khởi tạo bảng chơi
int** makeGrid(const int& size) {

    // Cấp phát động mảng 2 chiều
    int** bang = new int* [size]();

    // Cấp phát bộ nhớ cho từng hàng trong mảng với tất cả phần tử có giá trị là 0
    for (int i = 0; i < size; ++i)
        bang[i] = new int[size]();

    // Lấy seed thời gian thực để đảm bảo các giá trị ngẫu nhiên khác nhau trong mỗi lần chạy
    srand(time(0));

    // Tương tự cơ chế hàm randNumber
    int numberChance = 1 + rand() % 10;
    int number;

    if (numberChance == 1) number = 4;
    else number = 2;

    int emptyRow = rand() % (size - 1);
    int emptyCol;

    do emptyCol = rand() % (size - 1);
    while (emptyCol == emptyRow);

    bang[emptyRow][emptyCol] = number;

    return bang;
}

// Hàm tạo số ngẫu nhiên trên một ô trống trong bảng
void randNumber(int** bang, const int& size) {

    // Random khởi tạo số 2 hay 4 cho trò chơi
    // 2: 90%
    // 4: 10%
    int numberChance = 1 + rand() % 10; // Tạo số ngẫu nhiên từ 1 đến 10
    int number;

    // Nếu numberChance == 1 thì chọn số 4, nếu không thì chọn số 2
    if (numberChance == 1) number = 4;
    else number = 2;

    // Khai báo mảng chứa các cặp tọa độ ô trống
    ToaDo* emptyCell = new ToaDo[size * size];

    // Thêm các cặp tọa độ của ô trống vào mảng
    int k = 0; // Biến k để đếm số ô trống

    for (int i = 0; i < size; ++i) 
        for (int j = 0; j < size; ++j) 
            if (bang[i][j] == 0) { // Nếu ô trống
                emptyCell[k] = {i, j};  // Lưu tọa độ ô trống vào mảng
                ++k; // Tăng biến đếm ô trống
            }

    // Nếu không có ô trống nào (k == 0), trả về
    if (k == 0) {
        delete[] emptyCell; // Giải phóng bộ nhớ đã cấp phát cho mảng emptyCell
        return;
    }

    // Random một ô trống ngẫu nhiên
    int randomEmptyCell = rand() % k; // Chọn ngẫu nhiên một ô trống trong mảng emptyCell
    
    // Gán giá trị số vào ô trống ngẫu nhiên được chọn
    bang[emptyCell[randomEmptyCell].x][emptyCell[randomEmptyCell].y] = number;

    // Giải phóng bộ nhớ đã cấp phát cho mảng emptyCell
    delete[] emptyCell;
}


// Hàm gộp các số theo hàng
void mergeRow(int** bang, const int& size, const char& button) {

    // Duyệt qua từng hàng một
    for (int i = 0; i < size; ++i) {

        // Kiểm tra nếu nút bấm là A hoặc Left (mũi tên sang trái)
        if (button == sf::Keyboard::A || button == sf::Keyboard::Left) {
            int index = 0; // Biến index để theo dõi vị trí dồn các số không phải 0

            // Dồn các số khác 0 về phía đầu hàng
            for (int j = 0; j < size; ++j)
                if (bang[i][j] != 0) std::swap(bang[i][index++], bang[i][j]);

            // Gộp các số giống nhau theo thứ tự từ trái qua phải
            for (int j = 0; j < size - 1; ++j) 
                if (bang[i][j] == bang[i][j + 1]) {
                    bang[i][j] *= 2;    // Gộp các số giống nhau
                    bang[i][j + 1] = 0; // Đặt ô tiếp theo thành 0 sau khi gộp
                }

            // Dồn lại các số đã được gộp về phía bên trái
            index = 0;

            for (int j = 0; j < size; ++j)
                if (bang[i][j] != 0) std::swap(bang[i][index++], bang[i][j]);
        }

        // Nếu nút bấm là D hoặc Right (mũi tên sang phải)
        else {
            int index = size - 1; // Khởi tạo index từ cuối hàng

            // Dồn các số khác 0 về phía cuối của hàng
            for (int j = size - 1; j >= 0; --j)
                if (bang[i][j] != 0) std::swap(bang[i][index--], bang[i][j]);

            // Gộp các số giống nhau theo thứ tự từ phải qua trái
            for (int j = size - 1; j > 0; --j) 
                if (bang[i][j] == bang[i][j - 1]) {
                    bang[i][j] *= 2;    // Gộp các số giống nhau
                    bang[i][j - 1] = 0; // Đặt ô trước đó thành 0 sau khi gộp
                }

            // Dồn lại các số đã được gộp về phía bên phải
            index = size - 1;

            for (int j = size - 1; j >= 0; --j)
                if (bang[i][j] != 0) std::swap(bang[i][index--], bang[i][j]);
        }
    }
}

// Hàm gộp các số theo hàng
void mergeCol(int** bang, const int& size, const char& button) {

    // Tương tự hàm mergeRow
    for (int i = 0; i < size; ++i) {
        if (button == sf::Keyboard::W || button == sf::Keyboard::Up) {
            int index = 0;

            for (int j = 0; j < size; ++j)
                if (bang[j][i] != 0) std::swap(bang[index++][i], bang[j][i]);

            for (int j = 0; j < size - 1; ++j) {
                if (bang[j][i] == bang[j + 1][i]) {
                    bang[j][i] *= 2;
                    bang[j + 1][i] = 0;
                }
            }

            index = 0;

            for (int j = 0; j < size; ++j)
                if (bang[j][i] != 0) std::swap(bang[index++][i], bang[j][i]);
        }

        else {
            int index = size - 1;

            for (int j = size - 1; j >= 0; --j)
                if (bang[j][i] != 0) std::swap(bang[index--][i], bang[j][i]);

            for (int j = size - 1; j > 0; --j) {
                if (bang[j][i] == bang[j - 1][i]) {
                    bang[j][i] *= 2;
                    bang[j - 1][i] = 0;
                }
            }

            index = size - 1;

            for (int j = size - 1; j >= 0; --j)
                if (bang[j][i] != 0) std::swap(bang[index--][i], bang[j][i]);
        }
    }
}

// Hàm kiểm tra điều kiện thắng
bool winCheck(int** bang, const int& size, const bool& afterWin) {
    // Nếu đang trong chế độ chơi tiếp sau khi thắng
    // Bỏ qua kiểm tra thắng
    if (afterWin) return false;

    // Duyệt qua từng phần tử trong mảng bang
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            // Nếu có ô nào có giá trị bằng 2048, người chơi đã thắng
            if (bang[i][j] == 2048) return true;

    // Nếu không có ô nào có giá trị 2048, người chơi chưa thắng
    return false;
}

// Hàm kiểm tra điều kiện thua
bool loseCheck(int** bang, const int& size) {
    // Duyệt qua các ô trong mảng bang
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            // Nếu có ô trống, trò chơi chưa thua
            if (bang[i][j] == 0) return false;

            // Nếu có ô nào có giá trị bằng với ô bên dưới, có thể gộp, trò chơi chưa thua
            if (i < size - 1 && bang[i][j] == bang[i + 1][j]) return false;

            // Nếu có ô nào có giá trị bằng với ô bên phải, có thể gộp, trò chơi chưa thua
            if (j < size - 1 && bang[i][j] == bang[i][j + 1]) return false;
        }

    // Nếu không có ô trống và không thể gộp nữa, người chơi thua
    return true;
}

// Hàm tính điểm
int score(int** bang, const int& size) {
    int point = 0;

    // Duyệt qua tất cả các ô trong ma trận
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            point += bang[i][j]; // Cộng giá trị của ô vào điểm

    return point; // Trả về tổng điểm
}