#include "ds_q5.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  DamageNode_t *head = NULL, *tail = NULL;
  int m, n, L;
  int *damage;

  scanf("%d %d %d", &m, &n, &L);

  for (int i = 0; i < L; i++) {
    int dmg;
    scanf("%d", &dmg);
    if (head == NULL) {
      head = (DamageNode_t *)malloc(sizeof(DamageNode_t));
      head->damage = dmg;
      head->next = NULL;
      tail = head;
    } else {
      tail->next = (DamageNode_t *)malloc(sizeof(DamageNode_t));
      tail = tail->next;
      tail->damage = dmg;
      tail->next = NULL;
    }
  }

  damage = mapDamage(head, m, n);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", damage[i * n + j]);
    }
    printf("\n");
  }
  for (int i = 0; i < L; i++) {
    DamageNode_t *tmp = head;
    head = head->next;
    free(tmp);
  }
  free(damage);

  return 0;
}
