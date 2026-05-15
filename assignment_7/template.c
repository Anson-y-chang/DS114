#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

// Create a new tree node
Node *createNode(int val) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = val;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Build the binary tree from level-order input
// This function is provided for you to understand how a tree is built in this
// assignment
Node *buildTree(int arr[], int n) {
  if (n == 0 || arr[0] == -1)
    return NULL;

  Node *root = createNode(arr[0]);

  Node *queue[20000];
  int front = 0;
  int rear = 0;

  queue[rear++] = root;

  int i = 1;

  while (front < rear && i < n) {
    Node *current = queue[front++];

    if (i < n && arr[i] != -1) {
      current->left = createNode(arr[i]);
      queue[rear++] = current->left;
    }
    i++;

    if (i < n && arr[i] != -1) {
      current->right = createNode(arr[i]);
      queue[rear++] = current->right;
    }
    i++;
  }

  return root;
}

// Insert new value
Node *insert_val(Node *root, int value) {
  // TO DO
  return root;
}

// Delete a value, if value doesn't exist in tree, do nothing
Node *delete_val(Node *root, int value) {
  // TO DO
  return root;
}

// Find the closest value in the BST, if there is two closeest value, choose the
// smaller one
int closest_val(Node *root, int value) {
  // TO DO
  return 0;
}

// trim the BST in range [low, high]
Node *trim_BST(Node *root, int low, int high) {
  // TO DO
  return root;
}