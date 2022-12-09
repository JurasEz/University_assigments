#include <stdio.h>
#include <stdlib.h>

void Sort (struct List *head) {
    if (head == NULL)
        return ;
    else {
        struct List *current_node = head->next;
        int *amount = malloc(sizeof(struct Shoe_store));
        *amount = head->item->amount;
        while (current_node != NULL) {  //Finds the largest amount (If there are many equal it picks the first one to swap)
            if (*amount > current_node->item->amount)
                *amount = current_node->item->amount;
            current_node = current_node->next;
        }
        current_node = head->next;
        while (current_node != NULL && amount != (int*)head->item) {  //Goes to its place and switches head's and current_node's data addresses
            if (*amount == current_node->item->amount) {
                amount = (int*)current_node->item;
                current_node->item = head->item;
                head->item = (struct Shoe_store*)amount;
            }
            current_node = current_node->next;
        }
        Sort(head->next);
    }
}
