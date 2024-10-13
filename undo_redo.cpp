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

void undo(int** bang, int size, Node* &current_node){

    if (current_node != nullptr && current_node->prev != nullptr){
        current_node = current_node->prev;

        for (int i = 0; i < size; ++i)

            for (int j = 0; j < size; ++j)
                bang[i][j] = current_node->game_state[i * size + j];
    
    }

    else std::cout << "Khong the Undo!\n";

}

void redo(int** bang, int size, Node* &current_node){

    if (current_node != nullptr && current_node->next != nullptr){
        current_node = current_node->next;

        for (int i = 0; i < size; ++i)

            for (int j = 0; j < size; ++j)
                bang[i][j] = current_node->game_state[i * size + j];

    }

    else std::cout << "Khong the Redo!\n";
}


