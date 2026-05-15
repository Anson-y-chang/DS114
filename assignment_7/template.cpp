#include <iostream>
#include <queue>
using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Build the binary tree from level-order input
// This function is provided for you to understand how a tree is built in this
// assignment
Node *buildTree(int arr[], int n) {
  if (n == 0 || arr[0] == -1)
    return nullptr;

  Node *root = new Node(arr[0]);
  queue<Node *> q;
  q.push(root);

  int i = 1;

  while (!q.empty() && i < n) {
    Node *current = q.front();
    q.pop();

    if (i < n && arr[i] != -1) {
      current->left = new Node(arr[i]);
      q.push(current->left);
    }
    i++;

    if (i < n && arr[i] != -1) {
      current->right = new Node(arr[i]);
      q.push(current->right);
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
