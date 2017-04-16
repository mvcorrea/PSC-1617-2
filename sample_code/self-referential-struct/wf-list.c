/***
 *
 * ISEL, LEIC, Computer Systems Programming (PSC)
 *
 * Self-referential structures
 *
 * Compute word frequency in a file using a list to store the pairs (word, frequency)
 *
 * Generate executable with: gcc -o wf-list wf-list.c
 *
 * Carlos Martins, April 2017
 *
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* the list node structure */
struct lnode {
    struct lnode *next;		/* points to the next node */
    char *word;				/* points to the word */
    int count;				/* number of occurrences */
};

/* maximum length of a word */
#define MAXWORD 100

/* auxiliary functions */
int getword(FILE *f, char *word, int limit);
struct lnode *addlist(struct lnode *node, char *word);
void printlist(struct lnode *list);
void freelist(struct lnode *root);

/* word frequency count */
int main(int argc, const char *argv[])
{
	struct lnode *list;
    char word[MAXWORD];
    FILE *infile;

	if (argc > 1) {
        if ((infile = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "***error: can't open \"%s\" file", argv[1]);
            return 1;
		}
    } else
    	infile = stdin;

	/* the tree starts empty */
    list = NULL;
    while (getword(infile, word, MAXWORD) != EOF)
		if (isalpha(word[0]))
        	list = addlist(list, word);
	/* release file resources */
	fclose(infile);
    printlist(list);
    freelist(list);
    return 0;
}

/* auxiliary function */
char *_strdup(const char *s);

/* addlist: add a node with w, at or below list */

struct lnode *addlist(struct lnode *list, char *w) {
	struct lnode *prev, *ptr, *np;
	
	for (prev = NULL, ptr = list; ptr != NULL; prev = ptr, ptr = ptr->next) {
		int cond;
		if ((cond = strcmp(ptr->word, w)) == 0) { /* repeated word */
			ptr->count++;
			return list;
		} else if (cond > 0)
			break;
	}
	/* a new word has arrived */
    np = (struct lnode *)malloc(sizeof(struct lnode));
    np->word = _strdup(w);
    np->count = 1;
	
	/* insert new node at list after prev ponter */
	np->next = ptr;
	if (prev == NULL)
		/* insert at head of list, np is the new head of list */
		list = np;
	 else
		/* insert at middle or tail of list */
		prev->next = np;
	return list; 
}

/* printlist: in-order print of a list */
void printlist(struct lnode *list)
{
    for (; list != NULL; list = list->next)
        printf("%4d %s\n", list->count, list->word);
}

/* freelist: frees all nodes of list */ 
void freelist(struct lnode *list)
{
	while (list != NULL) {
		struct lnode *next = list->next;
        free(list->word);
        free(list);
		list = next;
    }
}

/* _strdup: make a duplicate of s */
char *_strdup(const char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1); /* +1 for '\0' */
    if (p != NULL)
		strcpy(p, s);
    return p;
}

/* getword: get next word or character from file "f" */
int getword(FILE *file, char *word, int lim)
{
    int c;
    char *wp = word;

    while (isspace(c = fgetc(file)))
    	;
    if (c != EOF)
        *wp++ = c;
    if (!isalpha(c)) {
        *wp = '\0';
        return c;
    }
    for (; --lim > 0; wp++)
        if (!isalnum(*wp = fgetc(file))) {
            ungetc(*wp, file);
            break;
    	}
    *wp = '\0';
    return word[0];
}
