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

  while (scanf("%d", &val) == 1) {
    ListNode *tmp = (ListNode *)malloc(sizeof(ListNode));
    tmp->val = val;
    tmp->next = NULL;
    curr->next = tmp;
    curr = curr->next;
  }

  head = dummyHead->next;
  ListNode *res = swapDancePairs(head);
  while (res) {
    printf("%d ", res->val);
    res = res->next;
  }

  free(dummyHead);
  freeList(res);

  return 0;
}
