// Header file for assignment 5.
/* ---------------- DO NOT MODIFY THIS FILE. ---------------- */
#ifndef DS_Q5_HPP
#define DS_Q5_HPP

struct ListNode {
  int val;
  struct ListNode *next;
  ListNode(int val) : val(val), next(nullptr) {}
};

ListNode *swapDancePairs(ListNode *head);

#endif