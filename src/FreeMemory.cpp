#include "FreeMemory.h"

// Hàm giải phóng bộ nhớ động của bảng chơi và danh sách liên kết đôi
void freeMemory(int**& bang, const int& size, Node*& head, char*& username) {
    // Giải phóng mảng bang
    if (bang != nullptr) {
        for (int i = 0; i < size; ++i)
            delete[] bang[i];
        delete[] bang;
        bang = nullptr;
    }

    // Giải phóng danh sách liên kết
    while (head != nullptr) {
        Node* nextNode = head->next;
        delete[] head->gameState;
        delete head;
        head = nextNode;
    }
    head = nullptr;

    // Giải phóng username nếu không null
    if (username != nullptr) {
        delete[] username;
        username = nullptr;
    }
}