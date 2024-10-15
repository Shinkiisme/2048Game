#include "thu_vien_2048.h"

// Hàm lưu lại trạng thái của bảng chơi vào một nút mới trên danh sách liên kết khi người chơi di chuyển.
void new_state(int** bang, int size, Node* &current_node){

    // Xoá những trạng thái redo nếu đã từng undo.
    Node* check_redo = current_node->next;

    while (check_redo != nullptr){
        Node* delete_redo = check_redo;
        check_redo = check_redo->next;
        
        delete[] delete_redo->game_state;
        delete[] delete_redo;

    }

    current_node->next = nullptr;

    // Lưu trạng thái mới của bảng chơi.
    Node* new_node = new Node;
    new_node->game_state = new int[size * size];

    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j)
            new_node->game_state[i * size + j] = bang[i][j];

    new_node->next = nullptr;
    new_node->prev = current_node;

    current_node->next = new_node;
    current_node = new_node;

}


// Khai báo hàm lưu lại trạng thái của bảng chơi trước khi undo.
void save_before_undo(int** bang, int size, Node* &current_node){

    if (current_node == nullptr) return;

    // Kiểm tra node hiện tại có giống bảng chơi và có phải node cuối không.
    bool isLastNode = false;

    for (int i =0; i < size; ++i){

        if (isLastNode) break;
        
        for (int j = 0; j < size; ++j)
            if (current_node->game_state[i * size + j] != bang[i][j] && current_node->next == nullptr){
                isLastNode = true;
                break;
            }
    }

    // Nếu thoả điều kiện thì tạo node mới để lưu trạng thái trước khi undo.
    if (isLastNode){

        Node* new_node = new Node;
        new_node->game_state = new int[size * size];

        for (int i = 0; i < size; ++i)

            for (int j = 0; j < size; ++j)
                new_node->game_state[i * size + j] = bang[i][j];

        new_node->next = nullptr;
        new_node->prev = current_node;

        current_node->next = new_node;
        current_node = new_node;

    }
}

// Khai báo hàm để thực hiện tính năng undo.
void undo(int** bang, int size, Node* &current_node){

    // Kiểm tra node có hợp lệ không.
    if (current_node == nullptr || current_node->prev == nullptr){
        std::cout << "\nKhong the Undo!\n";
        _getch();
        return;
    }

    // Thay thế bảng chơi hiện tại bằng bảng chơi ở node trước.
    current_node = current_node->prev;

    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j)
            bang[i][j] = current_node->game_state[i * size + j];

}

// Khai báo hàm để thực hiện tính năng redo.
void redo(int** bang, int size, Node* &current_node){

    // Kiểm tra node có hợp lệ không.
    if (current_node == nullptr || current_node->next == nullptr){
        std::cout << "\nKhong the Redo!\n";
        _getch();
        return;
    }

    // Thay thế bảng chơi hiện tại bằng bảng chơi ở node sau.
    current_node = current_node->next;

    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j)
            bang[i][j] = current_node->game_state[i * size + j];

}


