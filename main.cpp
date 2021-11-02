#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
/*
 * skapa Node med hjälp av strack (vilekn ha en int index för sensor nummer  , bool data  )
 */
typedef struct node_t{
    int index;
    bool bool_data;
    struct node_t *next;
}Node;

/*
 * definera data typer vilka vi behöver
 */
Node *head = NULL;
Node *tail = NULL;

/*
 * här printa vi Node detaljer vilken var index av sensor och bool data
 */
void print_list(){
    Node *node = head;

    while (node != NULL){
        char bool_data =  node->bool_data ? 'true' : 'false';
        printf("%d, %c",node->index, bool_data);
        if(node->next == NULL){
            printf(" -| ");
        }
        else {
            printf(" -> ");
        }
        node = node->next;
    }
    printf("\n");
}
/*
 * här räknar vi längd eller antal av vår Node vilka i den case är antal av sensorer
 */

int length(){
    int l = 0;
    Node *current = head;
    while (current != NULL){
        current = current->next;
        l++;
    }
    return l;
}

/*
 * här mata vi in vår funktion vilken skapar mera Node under procesen och allokerin minne
 * för vår Node
 */


Node* push_at (int index , bool bool_data){

    Node *current = head;
    Node *new_node = NULL;
    int i = 1 ;


    if(index == 0){        //push_head  till första
        new_node = (Node *) malloc(sizeof (Node));
        new_node->index = index;
        new_node->bool_data = bool_data;
        new_node->next = NULL;
        head = new_node;
        tail = new_node;
        return new_node;
    }

    if(index > length()){
        printf("index is out of the range = %d ",index);
        return NULL;
    }

    while (i < index){
        current = current->next;
        i++;
    }

    new_node = (Node *) malloc(sizeof (Node));
    new_node->index = index;
    new_node->bool_data = bool_data;
    new_node->next = current->next;
    current->next = new_node;
    return new_node;


}
/*
 * här skapa vi data vilken ska skickas ifrån sensorer
 */

void Create_value(){
    int number ;
    const char *str_tabel [] = {"true", "false"};
    int size_tabel = 2;
    FILE *file;

    file = fopen("file.txt","w");
    fclose(file);
    srand(time(NULL));

    for (int i = 1; i < 237 ; ++i) {

        file = fopen("file.txt", "a");
        const char *rand_string = str_tabel[rand() % size_tabel];
        number = rand() % 237 ;
        fprintf(file, "%d;%s;", number,rand_string);
        fclose(file);

    }

}
/*
 * här skulle egentliga läsa ifrån filen och splitra data men det gick inte
 * C språk är vikdigt svårt med string och splitt
 * här gav jag up mig :/
 */
void Reader_file(){
    FILE *file ;
    int line = 0;
    char input [10];

    file = fopen("file.txt","r");

    while ( fgets( input ,sizeof (input), file) != NULL){
        const char* val1 = strtok(input , ";");
        const char* val2 = strtok(NULL , ";");

        push_at(val1,val2);
    }
    fclose(file);

}


/*
 * här sker allting :D
 */
int main() {

    while (1) {

        Create_value();
        Reader_file();
        sleep(2);
    }
    return 0;
}