#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

typedef struct Node Node;

// Student's implementations (declared)
Node *buildTree(int arr[], int n);
Node *insert_val(Node *root, int value);
Node *delete_val(Node *root, int value);
int closest_val(Node *root, int value);
Node *trim_BST(Node *root, int low, int high);

// TA's reference implementations for validation
static Node *ta_insert_val(Node *root, int value) {
  if (root == NULL) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }

  if (value < root->data)
    root->left = ta_insert_val(root->left, value);
  else if (value > root->data)
    root->right = ta_insert_val(root->right, value);

  return root;
}

static Node *ta_findMin(Node *node) {
  while (node->left != NULL)
    node = node->left;
  return node;
}

static Node *ta_delete_val(Node *root, int value) {
  if (root == NULL)
    return NULL;

  if (value < root->data) {
    root->left = ta_delete_val(root->left, value);
  } else if (value > root->data) {
    root->right = ta_delete_val(root->right, value);
  } else {
    // Found the node to delete
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    } else if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    } else {
      // Two children: get inorder successor
      Node *temp = ta_findMin(root->right);
      root->data = temp->data;
      root->right = ta_delete_val(root->right, temp->data);
    }
  }

  return root;
}

static int abs_int(int x) { return x < 0 ? -x : x; }

static int ta_closest_val(Node *root, int value) {
  int closest = root->data;

  while (root != NULL) {
    if (abs_int(root->data - value) < abs_int(closest - value) ||
        (abs_int(root->data - value) == abs_int(closest - value) &&
         root->data < closest)) {
      closest = root->data;
    }

    if (value < root->data)
      root = root->left;
    else if (value > root->data)
      root = root->right;
    else
      break;
  }

  return closest;
}

static Node *ta_trim_BST(Node *root, int low, int high) {
  if (root == NULL)
    return NULL;

  if (root->data < low)
    return ta_trim_BST(root->right, low, high);

  if (root->data > high)
    return ta_trim_BST(root->left, low, high);

  root->left = ta_trim_BST(root->left, low, high);
  root->right = ta_trim_BST(root->right, low, high);

  return root;
}

// Helper structures for validation
#define MAX_NODES 20000

typedef struct {
  int values[MAX_NODES];
  Node *nodes[MAX_NODES];
  int size;
} InorderResult;

static void collectInorder(Node *root, InorderResult *result) {
  if (root == NULL)
    return;

  collectInorder(root->left, result);
  result->values[result->size] = root->data;
  result->nodes[result->size] = root;
  result->size++;
  collectInorder(root->right, result);
}

static bool isSorted(int values[], int size) {
  for (int i = 1; i < size; i++) {
    if (values[i] <= values[i - 1])
      return false;
  }
  return true;
}

static void deleteTree(Node *root) {
  if (root == NULL)
    return;

  deleteTree(root->left);
  deleteTree(root->right);
  free(root);
}

static Node *copyTree(Node *root) {
  if (root == NULL)
    return NULL;

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = root->data;
  newNode->left = copyTree(root->left);
  newNode->right = copyTree(root->right);
  return newNode;
}

static Node *findNodeInArray(Node *nodes[], int size, int value) {
  for (int i = 0; i < size; i++) {
    if (nodes[i]->data == value)
      return nodes[i];
  }
  return NULL;
}

int main() {
  int n;
  scanf("%d", &n);

  int arr[10005];
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  Node *root = buildTree(arr, n);

  int operation;
  scanf("%d", &operation);

  if (operation == 1) {
    // Test insert_val
    int value;
    scanf("%d", &value);

    // Collect original node addresses
    InorderResult originalResult = {.size = 0};
    collectInorder(root, &originalResult);

    Node *studentRoot = insert_val(root, value);

    InorderResult studentResult = {.size = 0};
    collectInorder(studentRoot, &studentResult);

    // Check if inorder is sorted
    if (!isSorted(studentResult.values, studentResult.size)) {
      printf("FAILED: Tree is not a valid BST\n");
    } else {
      // Check if the value was inserted
      bool valueInserted = false;
      for (int i = 0; i < studentResult.size; i++) {
        if (studentResult.values[i] == value) {
          valueInserted = true;
          break;
        }
      }

      // Check if value already existed
      bool shouldInsert = true;
      for (int i = 0; i < originalResult.size; i++) {
        if (originalResult.values[i] == value) {
          shouldInsert = false;
          break;
        }
      }

      if (shouldInsert && !valueInserted) {
        printf("FAILED: Value not inserted\n");
      } else if (shouldInsert &&
                 studentResult.size != originalResult.size + 1) {
        printf("FAILED: Incorrect number of nodes\n");
      } else if (!shouldInsert && studentResult.size != originalResult.size) {
        printf("FAILED: Duplicate value should not change tree\n");
      } else {
        // Check that original nodes keep same address
        bool addressCorrect = true;
        for (int i = 0; i < originalResult.size; i++) {
          int val = originalResult.values[i];
          Node *originalAddr = originalResult.nodes[i];

          // Find this value in student result
          bool found = false;
          for (int j = 0; j < studentResult.size; j++) {
            if (studentResult.values[j] == val) {
              if (studentResult.nodes[j] != originalAddr) {
                addressCorrect = false;
              }
              found = true;
              break;
            }
          }

          if (!addressCorrect) {
            break;
          }
        }

        if (!addressCorrect) {
          printf("FAILED: Original nodes changed address\n");
        } else {
          printf("PASS\n");
        }
      }
    }

    deleteTree(studentRoot);

  } else if (operation == 2) {
    // Test delete_val
    int value;
    scanf("%d", &value);

    InorderResult originalResult = {.size = 0};
    collectInorder(root, &originalResult);

    Node *taRoot = copyTree(root);
    Node *studentRoot = delete_val(root, value);
    taRoot = ta_delete_val(taRoot, value);

    InorderResult studentResult = {.size = 0};
    InorderResult taResult = {.size = 0};

    collectInorder(studentRoot, &studentResult);
    collectInorder(taRoot, &taResult);

    if (!isSorted(studentResult.values, studentResult.size)) {
      printf("FAILED: Tree is not a valid BST\n");
    } else if (studentResult.size != taResult.size) {
      printf("FAILED: Incorrect number of nodes\n");
    } else {
      bool valuesMatch = true;
      for (int i = 0; i < studentResult.size; i++) {
        if (studentResult.values[i] != taResult.values[i]) {
          valuesMatch = false;
          break;
        }
      }

      if (!valuesMatch) {
        printf("FAILED: Incorrect values\n");
      } else {
        // For delete with two children, the implementation may reuse nodes
        // We only check that the tree structure is correct (values match in
        // order)
        printf("PASS\n");
      }
    }

    deleteTree(studentRoot);
    deleteTree(taRoot);

  } else if (operation == 3) {
    // Test closest_val
    int value;
    scanf("%d", &value);

    int studentResult = closest_val(root, value);
    int taResult = ta_closest_val(root, value);

    if (studentResult == taResult) {
      printf("PASS\n");
    } else {
      printf("FAILED: Expected %d, got %d\n", taResult, studentResult);
    }

    deleteTree(root);

  } else if (operation == 4) {
    // Test trim_BST
    int low, high;
    scanf("%d %d", &low, &high);

    InorderResult originalResult = {.size = 0};
    collectInorder(root, &originalResult);

    Node *taRoot = copyTree(root);
    Node *studentRoot = trim_BST(root, low, high);
    taRoot = ta_trim_BST(taRoot, low, high);

    InorderResult studentResult = {.size = 0};
    InorderResult taResult = {.size = 0};

    collectInorder(studentRoot, &studentResult);
    collectInorder(taRoot, &taResult);

    if (!isSorted(studentResult.values, studentResult.size)) {
      printf("FAILED: Tree is not a valid BST\n");
    } else if (studentResult.size != taResult.size) {
      printf("FAILED: Incorrect values\n");
    } else {
      bool valuesMatch = true;
      for (int i = 0; i < studentResult.size; i++) {
        if (studentResult.values[i] != taResult.values[i]) {
          valuesMatch = false;
          break;
        }
      }

      if (!valuesMatch) {
        printf("FAILED: Incorrect values\n");
      } else {
        // Check that nodes within range keep same address
        bool addressCorrect = true;
        for (int i = 0; i < studentResult.size; i++) {
          int val = studentResult.values[i];
          Node *originalNode =
              findNodeInArray(originalResult.nodes, originalResult.size, val);
          if (originalNode != NULL && studentResult.nodes[i] != originalNode) {
            addressCorrect = false;
            break;
          }
        }

        if (addressCorrect) {
          printf("PASS\n");
        } else {
          printf("FAILED: Incorrect node addresses\n");
        }
      }
    }

    deleteTree(studentRoot);
    deleteTree(taRoot);
  }

  return 0;
}