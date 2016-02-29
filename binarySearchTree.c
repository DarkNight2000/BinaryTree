#include <stdio.h>
#include <stdlib.h>

/* setup binary search tree */
struct Node {
    long long data;
    struct Node *left;
    struct Node *right;
};

/* initialize the node for binary search tree */
struct Node *createNode(long long x){

    struct Node *newNode = (struct Node*)malloc(1 * sizeof(struct Node));
    
    if(newNode == NULL){
   	 printf("Failed to allocate memory for a new node !\n");
   	 return;
    }else{
   	 newNode->data = x;
   	 newNode->left = NULL;
   	 newNode->right = NULL;
   	 return newNode;
    }    

}

/* insert node function */
void insertNode(struct Node **root, long long x){

    struct Node *newNode;
    
    if(*root == NULL){
   	 *root = createNode(x);
   	 return;
    }
    
    newNode = *root;
    
    while(1){
   	 /* insert to the left child */
   	 if((newNode->data) >= x){
   		 if((newNode->left) == NULL){
   			 newNode->left = createNode(x);
   			 break;
   		 }else{
   			 newNode = newNode->left;
   		 }
   		 
   	 /* insert to the right child */
   	 }else if((newNode->data) < x){
   		 if((newNode->right) == NULL){
   			 newNode->right = createNode(x);
   			 break;
   		 }else{
   			 newNode = newNode->right;
   		 }
   	 /* the node exists in the tree */
   	 }
   	 
    }
}

/* inorder print out the node in the tree */
void printNode(struct Node *n){
    
    if(n != NULL){
   	 printNode(n->left);
   	 printf(" %Ld ", n->data );
   	 printNode(n->right);
    }
    
}

/* print out the binary tree */
void printTree(struct Node **rootRef){

    struct Node *current = *rootRef;
    printNode(current);
}

/* compute the sum value of root node, its left child and its right child */
long long countValue(struct Node *n){
    long long result = 0;
    if(n != NULL){
   	 result = result + n->data;
    
   	 if(n->left != NULL){
   		 result = result + countValue(n->left);
   	 }
   	 if(n->right != NULL){
   		 result = result + countValue(n->right);
   	 }
    }
    
    return result;
}

/* compute the sum value of node that is less than or equal to k */
long long countLessThan(struct Node *n, long long k){
    long long result = 0;
    while(n != NULL){
   	 if(n->data <= k){
   		 result = result + n->data;
   		 if(n->left != NULL){
   			 result = result + countValue(n->left);
   		 }
   		 n = n->right;
   	 }else{
   		 n = n->left;
   	 }
    }
    return result;
}

/* compute the range value */
long long rangeCompute(struct Node **root, long long min, long long max){
    long long result = 0;
    struct Node *n = *root;
    
    if(n != NULL){
   	 result = countLessThan(n, max) - countLessThan(n, min);
    }    
    return result;
}

int main(int argc, char**argv){

    long long element;
    long long min = 0;
    long long max = 0;
    long long sum = 0;
    
    struct Node **root= (struct Node**)malloc(1 * sizeof(struct Node*)); /* construct the head node */
    
    /* read the array from file dataX */
    
    FILE *data  = fopen(argv[1], "r");
    
    if (data == NULL) {
     	 fprintf(stderr, "Can't open input file in.list!\n");
		 exit(1);
    }
    
    *root = NULL;
    
    while(fscanf(data, "%Ld", &element)!= EOF){
   	 insertNode(root, element);
    }
    printf("The binary search tree is: \n");
    printTree(root);
    printf("\n");
    fclose(data);
    
    
    /* read the array from file rangeX */
    
    
    FILE *range = fopen(argv[2], "r");
    if (range == NULL) {
     	 fprintf(stderr, "Can't open input file in.list!\n");
		 exit(1);
    }
    while(fscanf(range, "%Ld %Ld", &min, &max)!= EOF){
   	 sum = rangeCompute(root, min, max);
   	 printf("Range[%Ld, %Ld]. Sum: %Ld.\n", min, max, sum);
   	 
    }
    
    fclose(range);
    return 0;

}
