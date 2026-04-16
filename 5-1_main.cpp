#include "ds_q5.hpp"
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int val;
  ListNode *dummyHead = new ListNode(0);
  ListNode *curr = dummyHead;

  while (cin >> val) {
    curr->next = new ListNode(val);
    curr = curr->next;
  }

  ListNode *res = swapDancePairs(dummyHead->next);
  while (res) {
    cout << res->val << " ";
    res = res->next;
  }

  return 0;
}
