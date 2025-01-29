/*
Compile: make is_search_tree
Run: ./is_search_tree
Compile & run: make is_search_tree && ./is_search_tree
*/

#include "base.h"

typedef struct Node{
	int value;
	struct Node* left;
	struct Node* right;
}Node;

Node* new_node(Node* left, int value, Node* right){
	Node* node = xmalloc(sizeof(Node));
	node->left = left;
	node->value = value;
	node->right = right;
	return node;
}

void free_node(Node * node){
	if(node){
		free_node(node->left);
		free_node(node->right);
		node->left = NULL;
		node->right = NULL;
		free(node);
	}
}

void print_node(Node* node) {
	if (node == NULL) {
		printf("E");
	} else {
		printf("Node(");
		print_node(node->left);
		printf(", %d, ", node->value);
		print_node(node->right);
		printf(")");
	}
}

int min_int(int a, int b){
	if(a < b){
		return a;
	}
	return b;
}

int max_int(int a, int b){
	if(a > b){
		return a;
	}
	return b;
}




typedef struct{
	Node* root;
}Tree;

Tree* new_tree(Node* root){
	Tree* tree = xmalloc(sizeof(Tree));
	tree->root = root;
	return tree;
}

void free_tree(Tree* tree){
	if(tree){
		free_node(tree->root);
		tree->root = NULL;
		free(tree);
	}
}

void print_tree(Tree* tree){
	printf("Tree: ");
	if(tree)
		print_node(tree->root);
	printf("\n");
}


/** Returns true if this is a search tree. Returns false otherwise.
  * May need a helper method. */
bool is_search_tree(Tree* tree) {
	return false;
}


void test() {
	Tree* t = new_tree(NULL);
	test_equal_b(is_search_tree(t), true);
	free_tree(t);
		
	t = new_tree(new_node(NULL, 100, NULL));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);
	
	t = new_tree(new_node(new_node(NULL, 99, NULL), 100, new_node(NULL, 101, NULL)));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);
	
	t = new_tree(new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 99, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
		
	t = new_tree(new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 199, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
	
	t = new_tree(new_node(new_node(new_node(NULL, 6, NULL), 7, new_node(NULL, 9, NULL)), 8, NULL));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
	
	t = new_tree(new_node(new_node(NULL, 11, NULL), 100, new_node(NULL, 99, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
	
	t = new_tree(new_node(new_node(new_node(NULL, 25, NULL), 50, new_node(NULL,75, NULL)), 100, new_node(new_node(NULL,125, NULL), 150, new_node(NULL, 175, NULL))));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

	t = new_tree(new_node(new_node(new_node(NULL, 55, NULL), 50, new_node(NULL, 75, NULL)), 100, new_node(new_node(NULL, 125, NULL), 150, new_node(NULL, 175, NULL))));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
		
	t = new_tree(new_node(NULL, 101, new_node(NULL, 100, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
		
	t = new_tree(new_node(new_node(NULL, 50, NULL), 100, NULL));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

}
	
			
int main(void) {
	report_memory_leaks(true);
	test();
	return 0;
}
