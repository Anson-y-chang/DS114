// Header file for assignment 5.
/* ---------------- DO NOT MODIFY THIS FILE. ---------------- */
#ifndef DS_Q5_H
#define DS_Q5_H

typedef struct ListNode {
  int val;
  struct ListNode *next;
} ListNode;

ListNode *swapDancePairs(ListNode *head);

#endif