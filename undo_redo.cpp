#include "thu_vien_2048.h"

void new_state(int** bang, int size, Node* &current_node){

    Node* check_redo = current_node->next;

    while (check_redo != nullptr){
        Node* delete_redo = check_redo;
        check_redo = check_redo->next;
        
        delete[] delete_redo->game_state;
        delete[] delete_redo;

    }

    current_node->next = nullptr;

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

void save_before_undo(int** bang, int size, Node* &current_node){

    if (current_node == nullptr) return;

    bool isLastNode = false;

    for (int i =0; i < size; ++i){

        if (isLastNode) break;
        
        for (int j = 0; j < size; ++j)
            if (current_node->game_state[i * size + j] != bang[i][j] && current_node->next == nullptr){
                isLastNode = true;
                break;
            }
    }

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

void undo(int** bang, int size, Node* &current_node){

    if (current_node == nullptr || current_node->prev == nullptr){
        std::cout << "\nKhong the Undo!\n";
        _getch();
        return;
    }

    current_node = current_node->prev;

    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j)
            bang[i][j] = current_node->game_state[i * size + j];

}

void redo(int** bang, int size, Node* &current_node){

    if (current_node == nullptr || current_node->next == nullptr){
        std::cout << "\nKhong the Redo!\n";
        _getch();
        return;
    }

    current_node = current_node->next;

    for (int i = 0; i < size; ++i)

        for (int j = 0; j < size; ++j)
            bang[i][j] = current_node->game_state[i * size + j];

}


