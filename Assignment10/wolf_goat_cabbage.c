/*
Compile: make wolf_goat_cabbage
Run: ./wolf_goat_cabbage
make wolf_goat_cabbage && ./wolf_goat_cabbage
*/

#include "base.h"

// Represents a single list node. The value is dynamically allocated. The node
// is the owner of the value and has to free it when itself is released.
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

// Prints the components of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(" %s", n->value);
        }
        printf("]");
    }
}

// Print list followed by a newline.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// Free all nodes of the list, including the values it contains.
void free_list(Node* list) {
    Node* current = list;
    while (current != NULL) {
        Node * next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    
}


bool test_equal_lists(int line, Node* list1, Node* list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, list1, list2);
    list1 = new_node("hello", NULL);
    list2 = list1;
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1);
    list1 = new_node("hello", NULL);
    list2 = new_node("hello", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("hello", NULL);
    list2 = new_node("you", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("hello", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
}

// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node* list1, Node* list2) {
    int node_number = 0;
    while (list1 != NULL && list2 != NULL) {
        if (!s_equals(list1->value, list2->value)) {
            printf("Line %d: The values at node %d differ: %s <-> %s.\n",line, node_number, list1->value, list2->value);
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
        node_number++;
    }
    if (list1 == NULL && list2 == NULL) {
        printf("Line %d: The Lists are equal.\n", line);
        return true;
    }
    else if (list1 == NULL) {
        printf("Line %d: list 1 is shorter than list2.\n",line);
        return false;
    }
    else {
        printf("Line %d: list 1 is longer than list2.\n",line);
        return false;
    }
}

int length_list(Node* list);

// Example calls for length_list (below).
void length_list_test(void) {
    Node* list = NULL;
    test_equal_i(length_list(list), 0);
    free_list(list);
    list = new_node("hello", NULL);
    test_equal_i(length_list(list), 1);
    free_list(list);
    list = new_node("first", new_node("second", NULL));
    test_equal_i(length_list(list), 2);
    free_list(list);
}

// Number of elements of the list.
int length_list(Node* list) {
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next) n++;
    return n;
}

int index_list(Node* list, String s);

// Example calls for index_list (below).
void index_list_test(void) {
    Node* list = NULL;
    String string = "hello";
    test_equal_i(index_list(list, string), -1);
    free_list(list);
    list = new_node("first", new_node("second", NULL));
    string = "first";
    test_equal_i(index_list(list, string), 0);
    free_list(list);
    list = new_node("first", new_node("second", NULL));
    string = "second";
    test_equal_i(index_list(list, string), 1);
    free_list(list);
}

// Return index of s in list, or -1 if s is not in list.
int index_list(Node* list, String s) {
    require_not_null(s);
    int mode_number = 0;
    while (list != NULL) {
        if (s_equals(list->value, s)) {
            return mode_number;
        }
        list = list->next;
        mode_number++;
    }
    return -1;
}

// Check whether list contains s.
bool contains_list(Node* list, String s) {
    return index_list(list, s) >= 0;
}

Node* remove_list(Node* list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, remove_list(list1, 1), list2);
    free_list(list1);
    free_list(list2);
    
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("third", NULL));
    test_equal_lists(__LINE__, remove_list(list1, 1), list2);
    free_list(list1);
    free_list(list2);
    
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, remove_list(list1, 2), list2);
    free_list(list1);
    free_list(list2);
    
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    print_list(remove_list(list1, 1));
    test_equal_lists(__LINE__, remove_list(list1, 5), list2);
    free_list(list1);
    free_list(list2);
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    require("valid index", index >= 0);
    
    int initial_length = length_list(list);
    
    if (index == 0) {
        Node* new = list->next;
        free(list->value);
        free(list);
        ensure_code(length_list(new) == initial_length - 1);
        return new;
    }

    Node* current = list;
    Node* previous = NULL;
    int current_index = 0;

    while (current != NULL && current_index < index) {
        previous = current;
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        return list;
    }

    previous->next = current->next;
    free(current->value);
    free(current);

    ensure_code(length_list(list) == initial_length - 1);
    return list;
}

///////////////////////////////////////////////////////////////////////////

// The boat may either be at the left or right river bank.
// We don't care for the transition (boat crossing the river).
enum Position {
    LEFT, RIGHT
};

// The data that represents the state of the puzzle.
typedef struct {
    // List of objects on the left river bank.
    Node* left;

    // List of objects on the right river bank.
    Node* right;

    // List of objects in the boat. The boat has a capacity of one object only.
    Node* boat;

    // Current boat position.
    enum Position position;
} Puzzle;

// Initialize the state of the puzzle.
Puzzle make_puzzle(void) {
    return (Puzzle){ new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))), NULL, NULL, LEFT };
}

// Print the current state of the puzzle.
void print_puzzle(Puzzle* p) {
    print_list(p->left);
    if (p->position == RIGHT) prints("     ");
    print_list(p->boat);
    if (p->position == LEFT)  prints("     ");
    println_list(p->right);
}

// Release memory and quit.
void finish_puzzle(Puzzle* p) {
    free_list(p->left);
    free_list(p->right);
    free_list(p->boat);
    exit(0);
}

void evaluate_puzzle(Puzzle* p) {
    if (p->position == RIGHT) {
        if (index_list(p->left, "Wolf") != -1 && index_list(p->left, "Ziege") != -1) {
            printsln("Wolf isst Ziege");
            finish_puzzle(p);
        }
        if (index_list(p->left, "Ziege") != -1 && index_list(p->left, "Kohl") != -1) {
            printsln("Ziege isst Kohl");
            finish_puzzle(p);
        }
    }
    else if (p->position == LEFT) {
        if (index_list(p->right, "Wolf") != -1 && index_list(p->right, "Ziege") != -1) {
            printsln("Wolf isst Ziege");
            finish_puzzle(p);
        }
        if (index_list(p->right, "Ziege") != -1 && index_list(p->right, "Kohl") != -1) {
            printsln("Ziege isst Kohl");
            finish_puzzle(p);
        }
    }
    else if (index_list(p->right, "Wolf") != -1 && index_list(p->right, "Ziege") != -1 && index_list(p->right, "Kohl") != -1) {
        printsln("Gewonnen");
        finish_puzzle(p);
        }
}

void play_puzzle(Puzzle* p) {
    
    print_puzzle(p);
    evaluate_puzzle(p);
    
    String *input = xmalloc(sizeof(s_input(1)));
    input[0] = s_input(1);
    printsln(input[0]);
    
    if (s_get(input[0],0) == 'l') {
        p->position = LEFT;
    }
    if (s_get(input[0],0) == 'r') {
        p->position = RIGHT;
    }
    if (s_equals(input[0], "w")) {
        if (p->position == LEFT) {
            if (index_list(p->left, "Wolf") != -1) {
                if (length_list(p->boat) < 1) {
                    p->boat = new_node("Wolf", p->boat);
                    p->left = remove_list(p->left,index_list(p->left, "Wolf"));
                }
            }
            else if (index_list(p->boat, "Wolf") != -1) {
                p->left = new_node("Wolf", p->left);
                p->boat = remove_list(p->boat, index_list(p->boat, "Wolf"));
            }
        }
        else {
            if (index_list(p->right, "Wolf") != -1) {
                if (length_list(p->boat) < 1) {
                    p->boat = new_node("Wolf", p->boat);
                    p->right = remove_list(p->right,index_list(p->right, "Wolf"));
                }
            }
            else if (index_list(p->boat, "Wolf") != -1) {
                p->right = new_node("Wolf", p->right);
                p->boat = remove_list(p->boat, index_list(p->boat, "Wolf"));
            }
        }
    }
    if (s_get(input[0],0) == 'z') {
        if (p->position == LEFT) {
            if (index_list(p->left, "Ziege") != -1) {
                if (length_list(p->boat) < 1) {
                    p->boat = new_node("Ziege", p->boat);
                    p->left = remove_list(p->left,index_list(p->left, "Ziege"));
                }
            }
            else if (index_list(p->boat, "Ziege") != -1) {
                p->left = new_node("Ziege", p->left);
                p->boat = remove_list(p->boat, index_list(p->boat, "Ziege"));
            }
        }
        else {
            if (index_list(p->right, "Ziege") != -1) {
                if (length_list(p->boat) < 1) {
                    p->boat = new_node("Ziege", p->boat);
                    p->right = remove_list(p->right,index_list(p->right, "Ziege"));
                }
            }
            else if (index_list(p->boat, "Ziege") != -1) {
                p->right = new_node("Ziege", p->right);
                p->boat = remove_list(p->boat, index_list(p->boat, "Ziege"));
            }
        }
    }
    if (s_get(input[0],0) == 'k') {
        if (p->position == LEFT) {
            if (index_list(p->left, "Kohl") != -1) {
                if (length_list(p->boat) < 1) {
                    p->boat = new_node("Kohl", p->boat);
                    p->left = remove_list(p->left,index_list(p->left, "Kohl"));
                }
            }
            else if (index_list(p->boat, "Kohl") != -1) {
                p->left = new_node("Kohl", p->left);
                p->boat = remove_list(p->boat, index_list(p->boat, "Kohl"));
            }
        }
        else {
            if (index_list(p->right, "Kohl") != -1) {
                if (length_list(p->boat) < 1) {
                    p->boat = new_node("Kohl", p->boat);
                    p->right = remove_list(p->right,index_list(p->right, "Kohl"));
                }
            }
            else if (index_list(p->boat, "Kohl") != -1) {
                p->right = new_node("Kohl", p->right);
                p->boat = remove_list(p->boat, index_list(p->boat, "Kohl"));
            }
        }
    }
    if (s_get(input[0],0) == 'q') {
        free(input[0]);
        free(input);
        finish_puzzle(p);
    }
    free(input[0]);
    free(input);
    play_puzzle(p);
}

///////////////////////////////////////////////////////////////////////////

int main(void) {
    report_memory_leaks(true);

    test_equal_lists_test();
    length_list_test();
    index_list_test();
    remove_list_test();
    
    Puzzle p = make_puzzle();
    play_puzzle(&p);
    return 0;
}












