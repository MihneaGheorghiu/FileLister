#define _CRT_SECURE_NO_WARNINGS
#include "dirent.h"
#include <cstdio>
#include <cstdlib>
#include <string.h>



typedef struct nod
{
	struct dirent *val;
	int child_no;
	char* path; //saves path to the file location
	struct nod *pchild;//first child
	struct nod *pnext;//next brother
} Nod, *PNod;

//Global variables
int depth; //depth of the tree for printing

int isDirectory(struct dirent *ent)
{
	if (strstr(ent->d_name, ".") == NULL)
		return 1;
	return 0;
}

void addChild(Nod *root, struct dirent *ent)
{
	//printf("%s\n", ent->d_name);
	struct dirent *copiator = new struct dirent;
	copiator->d_name = (char*)malloc(_MAX_PATH);
	strcpy(copiator->d_name, ent->d_name);
	Nod *a = new Nod;
	a->child_no = 0;
	a->pnext = NULL;
	a->pchild = NULL;
	a->path = (char*)calloc(_MAX_PATH, sizeof(char));
	strcat(a->path, root->path);
	strcat(a->path, "\\");
	strcat(a->path, ent->d_name);
	a->val = copiator;
	if (root->child_no == 0) //it's the first element
	{
		root->pchild = a;
		root->child_no++;
		//printf("Adaug pe prima pozitie %s\n", a->val->d_name);
	}

	else
	{
		Nod *p = root->pchild;
		while (p->pnext != NULL)
			p = p->pnext; //going to the last element
		p->pnext = a;
		root->child_no++;
		//printf("Adaug pe ultima  pozitie %s\n", a->val->d_name);

	}
}

void updateTree(Nod *root)
{
	//printf("###### intra in updateTree pentru %s\n", root->val->d_name);
	Nod *p = root->pchild;
	while (p != NULL)
	{
		//printf("verificare pentru %s \n", p->val->d_name);
		if (isDirectory(p->val))
		{
			DIR *pdir;
			if ((pdir = opendir(p->path)) != NULL)
			{
				//printf("=====deschide subidrector %s\n", p->val->d_name);
				struct dirent *ent;
				while ((ent = readdir(pdir)) != NULL)
				{
					addChild(p, ent);
				}
				updateTree(p);
			}//if deschidere cu succes
			
		}//if director

		p = p->pnext;
	}//while
}

void print_tree(Nod *current_nod)
{
	if (current_nod == NULL)
		return;

	//ignore . and .., because dirent functions take them into consideration
	if (strcmp(current_nod->val->d_name, ".") == 0)
		return;
	if (strcmp(current_nod->val->d_name, "..") == 0)
		return;


	//first print the root
	if (isDirectory(current_nod->val))
	{
		if (depth == 1)
		{
			printf("%c", 195);
			for (int i = 0; i < depth; i++)
			{
				printf("%c%c%c", 196, 196, 197);
			}
		}//depth == 1
		if (depth > 1)
		{
			for (int j = depth; j > 1; j--)
				printf("%c  ", 179);
			printf("%c%c%c", 195, 196, 196);
		}
	}//printing a directory
	else//print files
	{
		
		for (int j = depth; j > 1; j--)
			printf("%c  ", 179);
		printf("%c  ", 179);
		/*for (int i = 0; i < depth; i++)
		{
			printf("   ");
		}*/
	}//printing a file
	printf("%s\n", current_nod->val->d_name);
	//now move on to his children
	Nod *call_child = current_nod->pchild;
	while (call_child != NULL)
	{
		depth++;
		print_tree(call_child);
		depth--;
		//all the children
		call_child = call_child->pnext;
	}



}

int main()
{
	DIR *dir;
	
	struct dirent *ent;

	printf("Give the root directory path:");
	char *root_name;
	root_name = (char*)malloc(_MAX_PATH);
	gets_s(root_name, _MAX_PATH);
	Nod *root = new Nod;
	if ( (dir = opendir(root_name) ) != NULL) 
	{
		
		root->child_no = 0;
		root->pnext = NULL;
		root->pchild = NULL;
		struct dirent first_val;
		first_val.d_name = root_name;
		root->val = &first_val;
		root->path = (char*)calloc(_MAX_PATH, sizeof(char));
		strcpy(root->path, root->val->d_name);
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) 
		{
			//if( isDirectory(ent) ) // to display only directories
				
				addChild(root, ent);
		}
		updateTree(root);
		closedir(dir);
		
	}
	else 
	{
		/* could not open directory */
		perror("");
		system("PAUSE");
		return EXIT_FAILURE;
	}

	//print the resulting tree
	depth = 0;
	print_tree(root);


	system("PAUSE");
	return 0;
}