#include "SkipList.h"


/// <summary>
/// SkipList Pointer
/// </summary>
SkipList *list = NULL;

/// <summary>
/// node value updated
/// </summary>
int _val = 0;

/// <summary>
/// skiplist menu
/// </summary>
void sk_list_menu() {
    printf("----------------Menu--------------\n");
    printf("        1 - Insert Data\n");
    printf("        2 - Delete Data\n");
    printf("        3 - Update Data\n");
    printf("        4 - Search Data\n");
    printf("        5 - Print SkipList\n");
    printf("        0 - Exit System\n");
    printf("----------------------------------\n");
}

/// <summary>
/// print skiplist
/// </summary>
void print_skip_list() {
    SLNode *current;
    for (int i = list->level - 1; i >= 0; i--) {
        printf("Level %d : ", i);
        for (current = list->head->next[i]; current; current = current->next[i]) {
            printf("%d -> ", current->key);
        }
        printf("NULL\n");
    }
}

/// <summary>
/// add data
/// </summary>
void add_data() {
    int key;
    printf("Input Key:\n");
    scanf("%d", &key);
    bool success = SL_InsertNode(list, key, ++_val);
    if (success) {
        printf("Successfully Insert! Key = %d  Value = %d\n", key, _val);
    } else {
        printf("Insert Failed!\n");
    }
}

/// <summary>
/// delete data
/// </summary>
void delete_data() {
    int key, value;
    printf("Input Key:\n");
    scanf("%d", &key);
    bool success = SL_DeleteNode(list, key, &value);
    if (success) {
        printf("Successfully Delete! Key = %d  Value = %d\n", key, value);
    } else {
        printf("Delete Failed!\n");
    }
}

/// <summary>
/// update data
/// </summary>
void update_data() {
    int key, value;
    printf("Insert Key:\n");
    scanf("%d", &key);
    printf("Target Value:\n");
    scanf("%d", &value);
    bool success = SL_InsertNode(list, key, value);
    if (success) {
        printf("Successfully Update! Key = %d  Value = %d\n", key, value);
    } else {
        printf("Update Failed!\n");
    }
}

/// <summary>
/// search data
/// </summary>
void search_data() {
    int key, value;
    printf("Input Key£º\n");
    scanf("%d", &key);
    bool success = SL_SearchNode(list, key, &value);
    if (success) {
        printf("Successfully Search! Key = %d  Value = %d\n", key, value);
    } else {
        printf("Search Failed!\n");
    }
}

/// <summary>
/// main function
/// </summary>
/// <returns></returns>
int main() {
    setbuf(stdout, NULL);

    // Create SkipList
    list = SL_CreateList();

    // set random seed
    srand((unsigned int) time(0));

    // Create Random List
    for (size_t i = 0; i < 20; i++) {
        SL_InsertNode(list, rand() % 100, ++_val);
    }

    int option = 0;
    do {
        // show menu
        sk_list_menu();
        scanf("%d", &option);

        // switch option
        switch (option) {
            case 1:
                add_data();        // insert data into skiplist
                break;
            case 2:
                delete_data();        // delete data from skiplist
                break;
            case 3:
                update_data();        // update data to skiplist
                break;
            case 4:
                search_data();            // search data from skiplist
                break;
            case 5:
                print_skip_list();            // print skiplist data
                break;
            case 0:
                goto loop_end;            // exit system
            default:
                printf("wrong option!\n");        // wrong option
                break;
        }

    } while (option);
    SL_DestroyList(list);
    loop_end:
    return 0;
}
