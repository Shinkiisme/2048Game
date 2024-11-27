#include "2048Lib.hpp"

// Hàm giải phóng bộ nhớ động của bảng chơi và danh sách liên kết đôi
void freeMemory(int**& bang, const int& size, Node*& head) {
   
    // Kiểm tra nếu mảng bang không phải là null
    if (bang != nullptr) {

        // Duyệt qua tất cả các dòng của mảng 2 chiều và giải phóng bộ nhớ
        for (int i = 0; i < size; ++i)
            delete[] bang[i]; // Giải phóng bộ nhớ của từng dòng mảng

        // Giải phóng bộ nhớ của mảng chính
        delete[] bang;
        bang = nullptr; // Đặt con trỏ bang thành null sau khi giải phóng
    }

    // Duyệt qua danh sách liên kết và giải phóng bộ nhớ của từng node
    while (head != nullptr) {
        Node* nextNode = head->next; // Lưu trữ con trỏ tới node tiếp theo

        delete[] head->gameState; // Giải phóng bộ nhớ của mảng gameState trong node
        delete head; // Giải phóng bộ nhớ của node hiện tại

        head = nextNode; // Di chuyển con trỏ head tới node tiếp theo
    }

    head = nullptr; // Đặt con trỏ head thành null sau khi giải phóng tất cả bộ nhớ
}