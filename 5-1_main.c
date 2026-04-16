#include "ds_q5.h"
#include <stdio.h>
#include <stdlib.h>

void freeList(ListNode *head) {
  ListNode *curr = head;
  while (curr) {
    ListNode *next = curr->next;
    free(curr);
    curr = next;
  }
}

int main() {
  ListNode *head = NULL;
  ListNode *dummyHead = (ListNode *)malloc(sizeof(ListNode));
  dummyHead->next = head;
  ListNode *curr = dummyHead;
  int val;

  int count = 0;
  while (scanf("%d", &val) == 1) {
    ListNode *tmp = (ListNode *)malloc(sizeof(ListNode));
    tmp->val = val;
    tmp->next = NULL;
    curr->next = tmp;
    curr = curr->next;
    count++;
  }

  ListNode *before_address[count];
  int before_value[count];
  ListNode *tmp = dummyHead->next;
  for (int i = 0; i < count; i++) {
    before_address[i] = tmp;
    before_value[i] = tmp->val;
    tmp = tmp->next;
  }

  head = dummyHead->next;
  ListNode *res = swapDancePairs(head);
  while (res) {
    printf("%d ", res->val);
    res = res->next;
  }

  // 驗證指標交換
  int isSwap = 1;
  for (int i = 0; i < count; i++) {
    ListNode *addr = before_address[i];

    // 確認這個位址還存在於結果中
    int found = 0;
    ListNode *node = res;
    while (node) {
      if (node == addr) {
        found = 1;
        break;
      }
      node = node->next;
    }

    if (!found) {
      isSwap = 0;
      break;
    }

    // 確認值沒有被竄改
    if (addr->val != before_value[i]) {
      isSwap = 0;
      break;
    }
  }

  if (!isSwap) {
    return 0;
  }

  free(dummyHead);
  freeList(res);

  return 0;
}
