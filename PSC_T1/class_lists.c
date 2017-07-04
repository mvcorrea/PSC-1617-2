#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
/*
struct lnode {
  struct lnode *next;
  char *word;
  int count;
};

//int getword(file *p, char *word, int limit);
struct lnode *addList(struct lnode *list, char *word);
void printList(struct lnode *list);
void freeList(struct lnode *list);

struct lnode *addList(struct lnode *list, char *word){
  struct lnode *prv, *ptr, *np;
  for (prv = NULL, ptr = list; ptr != NULL; prv = ptr, ptr->next) {
    int cmp = 0;
    if (cmp == strcmp(ptr->word, word) == 0) {
      ptr->count += 1;
      return list;
    }
    else if (cmp > 0) break;
  }

  // create a new node
  np = (struct lnode *)malloc(sizeof(struct lnode));
  np->word = strdup(word);
  np->count = 1;
  np->next = ptr;
  
  if(prv == NULL){ // insert@head
    list = np;
    }else{
    prv->next = np;
    }
  return list;
}

void printList(struct lnode *list) { 
    for (; list != NULL; list = list->next) {
      printf("%d -> %s\n", list->count, list->word);
    }
}

void freeList(struct lnode *list){
    while(list != NULL){
      struct lnode *next = list->next;
      free(list->word);
      free(list);
      list = next;
    }
}
*/
/*
int main(int argc, char *argv[]) { 



}
*/