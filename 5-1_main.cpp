#include "ds_q5.hpp"
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  ListNode *head = nullptr;

  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;

    head->next = new ListNode(val);
    head->val = val;
  }

  ListNode *res = swapDancePairs(head);
  while (res) {
    cout << res->val << " ";
    res = res->next;
  }

  return 0;
}
