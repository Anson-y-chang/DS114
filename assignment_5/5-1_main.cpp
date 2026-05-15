#include "ds_q5.hpp"
#include <iostream>
#include <map>
#include <vector>

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

  vector<pair<ListNode *, int>> before;
  ListNode *tmp = dummyHead->next;
  while (tmp) {
    before.push_back({tmp, tmp->val});
    tmp = tmp->next;
  }

  ListNode *res = swapDancePairs(dummyHead->next);

  map<ListNode *, int> afterNodes;
  ListNode *node = res;
  while (node) {
    afterNodes[node] = node->val;
    node = node->next;
  }

  bool isSwap = true;

  for (int i = 0; i < before.size(); i++) {
    ListNode *addr = before[i].first;

    // 先確認這個位址還存在於結果中
    if (afterNodes.find(addr) == afterNodes.end()) {
      isSwap = false;
      break;
    }

    // 再比較值有沒有被改
    if (before[i].second != afterNodes[addr]) {
      isSwap = false;
      break;
    }
  }

  if (!isSwap) {
    return 0;
  }

  while (res) {
    cout << res->val << " ";
    res = res->next;
  }

  return 0;
}
