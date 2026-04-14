// Header file for assignment 5.
/* ---------------- DO NOT MODIFY THIS FILE. ---------------- */
#ifndef DS_Q5_H
#define DS_Q5_H

typedef struct DamageNode {
  int damage;
  struct DamageNode *next;
} DamageNode_t;

int *mapDamage(DamageNode_t *head, int m, int n);

int *mapRotatingDamage(DamageNode_t *head, int m, int n, int k);

#endif