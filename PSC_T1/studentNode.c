#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_node { 
    unsigned number;
    const char *name;
    unsigned class;
    struct student_node *next;
} StudentNode;

void printStd(StudentNode *s) { 
    printf(" number: %d\n name: %s\n class: %d\n\n", s->number, s->name, s->class); 
}

void printLst(StudentNode *classes[], int index){
  //for (int x = 0; x < 5; x++) printStd(classes[x]);
   StudentNode *tmp = classes[index];
   while (tmp != NULL) {
     printStd(tmp);
     tmp = tmp->next;
   } 
}

char *_strdup(const char *s){ // implementação do prof.
	char *p;
	p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
		strcpy(p, s);
    return p;
}

void freeList(StudentNode *node) { 
    while (node != NULL) {
      StudentNode* nxt = node->next;
      free((char*)node->name);
      free(node);
      node = nxt;
    }
}

void groupStudentyClass(StudentNode * classes[], StudentNode students[], size_t num_students) {
      StudentNode *pos;
      for (int i = 0; i < num_students; i++) {
        int idx = students[i].class;
        pos = (StudentNode *)malloc(sizeof(StudentNode));
        pos->name = _strdup(students[i].name);
        pos->number = students[i].number;
        pos->class = idx;

        if (classes[idx] != NULL) pos->next = classes[idx];
        classes[idx] = pos;
      }
}

int main(int argc, char *argv[]) {
  int cls = 1; // id = 2 gives segfault ????

  StudentNode in[6];
  in[0] = (StudentNode){111, "jose", 2, NULL};  // ASK: porque tenho de fazer o cast?
  in[1] = (StudentNode){222, "joao", 2, NULL};
  in[2] = (StudentNode){333, "toze", 1, NULL};
  in[3] = (StudentNode){444, "maze", 1, NULL};
  in[4] = (StudentNode){555, "toni", 2, NULL};
  in[5] = (StudentNode){666, "tina", 3, NULL};

  StudentNode *out[6];

  groupStudentyClass(out, in, 6);
  printLst(out, cls);
  freeList(out[cls]);
}
