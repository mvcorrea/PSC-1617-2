/***
 *
 * ISEL, LEIC, Computer Systems Programming (PSC)
 *
 * Self-referential structures
 *
 * Compute word frequency in a file using a binary tree to store the pairs (word, frequency)
 *
 * Generate executable with: gcc -o wf-tree wf-tree.c
 *
 * Carlos Martins, April 2017
 *
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* the tree node structure */
struct tnode {
    char *word;				/* points to the word */
    int count;				/* number of occurrences */
    struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};

/* maximum length of a word */
#define MAXWORD 100

/* auxiliary functions */
int getword(FILE *f, char *word, int limit);
struct tnode *addtree(struct tnode *node, char *word);
void printtree(struct tnode *root);
void freetree(struct tnode *root);

/* word frequency count */
int main(int argc, const char *argv[])
{
	struct tnode *root;
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
    root = NULL;
    while (getword(infile, word, MAXWORD) != EOF)
		if (isalpha(word[0]))
        	root = addtree(root, word);
	/* release file resources */
	fclose(infile);
    printtree(root);
    freetree(root);
    return 0;
}

/* auxiliary function */
char *_strdup(const char *s);

/* addtree: add a node with w, at or below p */

struct tnode *addtree(struct tnode *p, char *w) {
	int cond;

    if (p == NULL) {		/* a new word has arrived */
    	/* allocate memory and make a new node */
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = _strdup(w);
        p->count = 1;
        /* this is always a leaf node */
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;		/* repeated word */
    else if (cond < 0)	/* less than into left subtree */
        p->left = addtree(p->left, w);
    else /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}

/* printtree: in-order print of a tree */
void printtree(struct tnode *p)
{
    if (p != NULL) {
		printtree(p->left);
        printf("%4d %s\n", p->count, p->word);
        printtree(p->right);
    }
}

/* freetree: frees all nodes of a tree */ 
void freetree(struct tnode *root)
{
	if (root != NULL) {
		freetree(root->left);
        freetree(root->right);
        free(root->word);
        free(root);
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
