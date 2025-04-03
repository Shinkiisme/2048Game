#ifndef NODE_H
#define NODE_H

struct Node {
    int* gameState; // Con trỏ lưu trạng thái bảng chơi hiện tại
    Node* next;     // Con trỏ trỏ tới nút tiếp theo
    Node* prev;     // Con trỏ trỏ tới nút trước đó
};

#endif
