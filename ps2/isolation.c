#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct tree_elem {
struct tree_elem* left_elem;
struct tree_elem* right_elem;
int value;
};
typedef struct tree_elem tree_elem;

void add_elem(tree_elem ** full_tree, int digit) {
	tree_elem *temp_elem = NULL;
	if(!(*full_tree)) {
	temp_elem = (tree_elem *)malloc(sizeof(tree_elem));
	temp_elem->left_elem = temp_elem->right_elem = NULL;
	temp_elem->value = digit;
	*full_tree = temp_elem;
	return;
}
if(digit < (*full_tree)->value) {
	add_elem(&(*full_tree)->left_elem, digit);
}
else if(digit > (*full_tree)->value) {
	add_elem(&(*full_tree)->right_elem, digit);
 }
}

int isIdentical(struct tree_elem* tree1, struct tree_elem* tree2) {
if (tree1==NULL && tree2==NULL)
	return 1;
if (tree1!=NULL && tree2!=NULL) {
	return(1 &&
		isIdentical(tree1->left_elem, tree2->left_elem) &&
		isIdentical(tree1->right_elem, tree2->right_elem)
);
}
		return 0;
}

void freeAllTrees(struct tree_elem* elem) {
if (elem == NULL) return;
	freeAllTrees(elem->left_elem);
	freeAllTrees(elem->right_elem);
		free(elem);
}

int main(){
int amount, len, out;
scanf("%d %d", &amount, &len);
struct tree_elem **elems = malloc(sizeof(tree_elem)*(amount*len));
struct tree_elem **tmp_elems = malloc(sizeof(tree_elem)*(amount*len));
char *input;
int k, i, comp;

for(i = 0; i < amount; i++) {
	elems[i] = NULL;
	k = 0;
	while(k < len)
	{
	scanf("%ms", &input);
	k++;
	add_elem(&elems[i], atoi(input));
	free(input);
	}
}

out = 1;
tmp_elems[0] = elems[0];
for(i = 1; i < amount; i++)
{
	k = 0;
	comp = 0;
	while(k < out)
{
if(isIdentical(elems[i], tmp_elems[k]) == 0){
	comp++;
}
	k++;
}
if(comp == out){
	tmp_elems[out] = elems[i];
	out++;
}
}
printf("%d\n", out);
for (k = 0; k < amount; k++) freeAllTrees(elems[k]);
free(elems);
free(tmp_elems);
}
