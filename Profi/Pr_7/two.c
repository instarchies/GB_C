#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find the maximum element in the tree
int findMax(struct Node* root) {
    if (root == NULL)
        return INT_MIN;
    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);
    int max = root->data > leftMax ? root->data : leftMax;
    max = max > rightMax ? max : rightMax;
    return max;
}

// Function to find the minimum element in the tree
int findMin(struct Node* root) {
    if (root == NULL)
        return INT_MAX;
    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);
    int min = root->data < leftMin ? root->data : leftMin;
    min = min < rightMin ? min : rightMin;
    return min;
}

int main() {
    // Create the tree as shown in the image
    struct Node* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->left = newNode(13);
    root->right->right = newNode(18);
    root->left->left->left = newNode(1);
    root->left->right->right = newNode(6);

    // Find the maximum and minimum elements
    int maxElement = findMax(root);
    int minElement = findMin(root);

    // Calculate and print the difference
    int difference = maxElement - minElement;
    printf("Результат %d\n", difference);

    return 0;
}
