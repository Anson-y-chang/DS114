#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node *buildTree(int arr[], int n);
Node *insert_val(Node *root, int value);
Node *delete_val(Node *root, int value);
int closest_val(Node *root, int value);
Node *trim_BST(Node *root, int low, int high);

// TA's reference implementations for validation
static Node *ta_insert_val(Node *root, int value) {
  if (root == nullptr)
    return new Node(value);

  if (value < root->data)
    root->left = ta_insert_val(root->left, value);
  else if (value > root->data)
    root->right = ta_insert_val(root->right, value);

  return root;
}

static Node *ta_findMin(Node *node) {
  while (node->left != nullptr)
    node = node->left;
  return node;
}

static Node *ta_delete_val(Node *root, int value) {
  if (root == nullptr)
    return nullptr;

  if (value < root->data) {
    root->left = ta_delete_val(root->left, value);
  } else if (value > root->data) {
    root->right = ta_delete_val(root->right, value);
  } else {
    // Found the node to delete
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      return nullptr;
    } else if (root->left == nullptr) {
      Node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      Node *temp = root->left;
      delete root;
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

static int ta_closest_val(Node *root, int value) {
  int closest = root->data;

  while (root != nullptr) {
    if (abs(root->data - value) < abs(closest - value) ||
        (abs(root->data - value) == abs(closest - value) &&
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
  if (root == nullptr)
    return nullptr;

  if (root->data < low)
    return ta_trim_BST(root->right, low, high);

  if (root->data > high)
    return ta_trim_BST(root->left, low, high);

  root->left = ta_trim_BST(root->left, low, high);
  root->right = ta_trim_BST(root->right, low, high);

  return root;
}

// Helper functions for validation
static void collectInorder(Node *root, vector<int> &values,
                           map<int, Node *> &valueToNode) {
  if (root == nullptr)
    return;

  collectInorder(root->left, values, valueToNode);
  values.push_back(root->data);
  valueToNode[root->data] = root;
  collectInorder(root->right, values, valueToNode);
}

static bool isSorted(const vector<int> &values) {
  for (int i = 1; i < values.size(); i++) {
    if (values[i] <= values[i - 1])
      return false;
  }
  return true;
}

static void deleteTree(Node *root) {
  if (root == nullptr)
    return;

  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

static Node *copyTree(Node *root) {
  if (root == nullptr)
    return nullptr;

  Node *newNode = new Node(root->data);
  newNode->left = copyTree(root->left);
  newNode->right = copyTree(root->right);
  return newNode;
}

int main() {
  int n;
  cin >> n;

  int arr[105];
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  Node *root = buildTree(arr, n);

  int operation;
  cin >> operation;

  if (operation == 1) {
    // Test insert_val
    int value;
    cin >> value;

    // Collect original node addresses
    vector<int> originalValues;
    map<int, Node *> originalMap;
    collectInorder(root, originalValues, originalMap);

    Node *studentRoot = insert_val(root, value);

    vector<int> studentValues;
    map<int, Node *> studentMap;
    collectInorder(studentRoot, studentValues, studentMap);

    // Check if inorder is sorted
    if (!isSorted(studentValues)) {
      cout << "FAILED: Tree is not a valid BST\n";
    } else {
      // Check if the value was inserted
      bool valueInserted = false;
      for (int val : studentValues) {
        if (val == value) {
          valueInserted = true;
          break;
        }
      }

      // If value already existed, tree should be unchanged
      bool shouldInsert = originalMap.find(value) == originalMap.end();

      if (shouldInsert && !valueInserted) {
        cout << "FAILED: Value not inserted\n";
      } else if (shouldInsert &&
                 studentValues.size() != originalValues.size() + 1) {
        cout << "FAILED: Incorrect number of nodes\n";
      } else if (!shouldInsert &&
                 studentValues.size() != originalValues.size()) {
        cout << "FAILED: Duplicate value should not change tree\n";
      } else {
        // Check that original nodes keep same address
        bool addressCorrect = true;
        for (auto &pair : originalMap) {
          int val = pair.first;
          Node *originalAddr = pair.second;

          if (studentMap.find(val) != studentMap.end()) {
            if (studentMap[val] != originalAddr) {
              addressCorrect = false;
              break;
            }
          }
        }

        if (!addressCorrect) {
          cout << "FAILED: Original nodes changed address\n";
        } else {
          cout << "PASS\n";
        }
      }
    }

    deleteTree(studentRoot);

  } else if (operation == 2) {
    // Test delete_val
    int value;
    cin >> value;

    map<int, Node *> originalMap;
    vector<int> dummy;
    collectInorder(root, dummy, originalMap);

    Node *taRoot = copyTree(root);
    Node *studentRoot = delete_val(root, value);
    taRoot = ta_delete_val(taRoot, value);

    vector<int> studentValues, taValues;
    map<int, Node *> studentMap, taMap;

    collectInorder(studentRoot, studentValues, studentMap);
    collectInorder(taRoot, taValues, taMap);

    if (!isSorted(studentValues)) {
      cout << "FAILED: Tree is not a valid BST\n";
    } else if (studentValues != taValues) {
      cout << "FAILED: Incorrect values\n";
    } else {
      // Check that unchanged nodes keep same address
      bool addressCorrect = true;
      for (int val : studentValues) {
        if (originalMap.count(val) && studentMap[val] != originalMap[val]) {
          addressCorrect = false;
          break;
        }
      }

      if (addressCorrect) {
        cout << "PASS\n";
      } else {
        cout << "FAILED: Incorrect node addresses\n";
      }
    }

    deleteTree(studentRoot);
    deleteTree(taRoot);

  } else if (operation == 3) {
    // Test closest_val
    int value;
    cin >> value;

    int studentResult = closest_val(root, value);
    int taResult = ta_closest_val(root, value);

    if (studentResult == taResult) {
      cout << "PASS\n";
    } else {
      cout << "FAILED: Expected " << taResult << ", got " << studentResult
           << "\n";
    }

    deleteTree(root);

  } else if (operation == 4) {
    // Test trim_BST
    int low, high;
    cin >> low >> high;

    map<int, Node *> originalMap;
    vector<int> dummy;
    collectInorder(root, dummy, originalMap);

    Node *taRoot = copyTree(root);
    Node *studentRoot = trim_BST(root, low, high);
    taRoot = ta_trim_BST(taRoot, low, high);

    vector<int> studentValues, taValues;
    map<int, Node *> studentMap, taMap;

    collectInorder(studentRoot, studentValues, studentMap);
    collectInorder(taRoot, taValues, taMap);

    if (!isSorted(studentValues)) {
      cout << "FAILED: Tree is not a valid BST\n";
    } else if (studentValues != taValues) {
      cout << "FAILED: Incorrect values\n";
    } else {
      // Check that nodes within range keep same address
      bool addressCorrect = true;
      for (int val : studentValues) {
        if (originalMap.count(val) && studentMap[val] != originalMap[val]) {
          addressCorrect = false;
          break;
        }
      }

      if (addressCorrect) {
        cout << "PASS\n";
      } else {
        cout << "FAILED: Incorrect node addresses\n";
      }
    }

    deleteTree(studentRoot);
    deleteTree(taRoot);
  }

  return 0;
}