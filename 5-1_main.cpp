#include "ds_q5.hpp"
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int val;
  cin >> val;

  ListNode *head = nullptr;

  if (val) {
    head = new ListNode(val);
    while (cin >> val) {
      head->next = new ListNode(val);
      head = head->next;
    }
  }

  ListNode *res = swapDancePairs(head);
  while (res) {
    cout << res->val << " ";
    res = res->next;
  }

  return 0;
}
