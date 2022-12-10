#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void Read(struct List *head){
    FILE *ptr = NULL;
    char filename[255];
    do{
        printf("Enter a valid data filename ending with .txt\n");
        scanf("%s", &filename);
        if(!Is_txt(filename))
            printf("The file does not end with \".txt\".\n");
        else{
            ptr = fopen(filename, "r");
            if(ptr == NULL)
                printf("File does not exist.\n");
        }
    }while(ptr == NULL || !Is_txt(filename));
    printf("Data filename is valid\n");

    int count, count_numbers, number;
    char character = (char)getc(ptr);
    char *word;

    struct List *current_node = head, *previous;

    while(character != EOF){
        word = malloc(BUFFER_SIZE); //we allocate the memory that will be reallocated and assigned
        current_node->item = malloc(sizeof(struct Shoe_store));
        count = 0;
        count_numbers = 0;
        while(character != '\n' && character != EOF){
            if(count != 0 && count_numbers < 2 && *(word + count - 1) != ' ' && character == ' '){
                *(word + count) = '\0';
                 number = Valid(word);
                if(number >= 0){
                    if(count_numbers == 0){
                        current_node->item->amount = number;
                        ++count_numbers;
                        count = 0;
                    }
                    else{
                        if(number >= 30 && number <= 60) {
                            current_node->item->size = number;
                            ++count_numbers;
                            count = 0;
                        }
                        else{
                            printf("The numbers in the data file were entered incorrectly.\n");
                            printf("Check if the amount is a whole number between 0 and 99999.\n");
                            printf("And check if the size is a whole number between 30 and 60.\n");
                            printf("We do not accept any other amounts or sizes.\n");
                            exit(1);
                        }
                    }
                }
                else{
                    printf("The data file was formed incorrectly.\n");
                    exit(1);
                }
            }
            *(word + count) = character;
            ++count;
            if(character == ' ' && count_numbers < 2)
                count = 0;
            character = (char)getc(ptr);
        }
        *(word + count) = '\0';
        word = realloc(word, count + 1);
        count = 0;
        while(*(word + count) == ' ')
            ++count;
        current_node->item->Brand_name = (word + count);
        previous = current_node;
        //printf( "%d     %d     %s \t%d     %d     %s\n", head->item->amount, head->item->size, head->item->Brand_name, current_node->item->amount, current_node->item->size, current_node->item->Brand_name);
        if((character = (char)getc(ptr)) != EOF){
            current_node->next = malloc(sizeof(struct List));
            current_node = current_node->next;
            current_node->previous = previous;
        }
        else
            current_node->next = NULL;
    }
    fclose(ptr);
    Menu(head);
}

bool Is_txt(char filename[]){ //return 0 if not txt
    if(filename[strlen(filename) - 1] == 't')
        if(filename[strlen(filename) - 2] == 'x')
            if(filename[strlen(filename) - 3] == 't')
                if(filename[strlen(filename) - 4] == '.')
                    return 1;
    return 0;
}
