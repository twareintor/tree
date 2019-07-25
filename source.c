//Permanent link: http://rextester.com/PVXET49221
//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x86 [v]
//clang 3.7.0 [v]
//gcc 4.9.3 [v]

// Demo tree in C with getParent and getRoot
// code by Twareintor (2016)

#include <stdio.h>
#include <stdlib.h>


struct Data
{
    void** ppData;
    int size;
};

struct Node
{
    int id;
    struct Node* parent;
    struct Node** children;
    int childCount;
    struct Data* data;    
};

void initNode(struct Node*);

void dropNode(struct Node*);

void attachChildren(struct Node* nodParent, struct Node** nodChildren, int nHowMany);

struct Node* getParent(struct Node*);

struct Node* getRoot(struct Node*);

void printChildTree(struct Node*);

int main(void)
{
    const int nScenes = 1;
    const int nTrees = 7;
    const int nAnimals = 3;
    
    /** prepare the scene **/
    struct Node* nodWorld = (struct Node*)malloc(sizeof(struct Node));
    initNode(nodWorld);
    nodWorld->id = 0;
    struct Node* nodScene = (struct Node*)malloc(sizeof(struct Node));
    initNode(nodScene);
    attachChildren(nodWorld, (struct Node**)&nodScene, nScenes);
    nodScene->id = 10;
    struct Node** nodTrees = (struct Node**)malloc(sizeof(struct Node*)*nTrees);
    int i;
    for(i = 0; i<nTrees; i++)
    {
        nodTrees[i] = (struct Node*)malloc(sizeof(struct Node));
        initNode(nodTrees[i]);
        nodTrees[i]->id = 300+1;
    }
    struct Node** nodAnimals = (struct Node**)malloc(sizeof(struct Node*)*nAnimals);
    for(i = 0; i<nAnimals; i++)
    {
        nodAnimals[i] = (struct Node*)malloc(sizeof(struct Node));
        initNode(nodAnimals[i]);
        nodAnimals[i]->id = 100+i;
    }
    attachChildren(nodScene, nodAnimals, nAnimals);
    attachChildren(nodScene, nodTrees, nTrees);
    
    /** do whatever..... **/
    printChildTree(nodWorld);
    
    /** free resources **/
    for(i = 0; i<nTrees; i++)
    {
        dropNode(nodTrees[i]);
        /* free(nodTrees[i]); */
    }
    free(nodTrees);
    for(i = 0; i<nAnimals; i++)
    {
        dropNode(nodAnimals[i]);
        /* free(nodAnimals[i]); */
    }
    free(nodAnimals);
    dropNode(nodScene);
    free(nodScene);
    dropNode(nodWorld);
    free(nodWorld);
    printf("Hello, world!\n");
    return 0;
}

void initNode(struct Node* nod)
{
    nod->parent = 0;
    nod->childCount = 0;
    nod->children = 0;

}

void dropNode(struct Node* nod)
{
    if(nod->children) free(nod->children);
}

struct Node* getParent(struct Node* nod)
{
    return nod->parent;
}

struct Node* getRoot(struct Node* nod)
{
    struct Node* nodOut = nod; 
    while(nodOut->parent)
    {
        nodOut = nodOut->parent;
    }
    return nodOut;
}

void attachChildren(struct Node* nod, struct Node** nodChildren, int nHowMany)
{
    /*************
    if(!nod->children)
    {
        if(!(nod->children = (struct Node**)malloc(nHowMany*sizeof(struct Node*)))) return;        
    }
    else
    {
        if(!(realloc(nod->children, (nod->childCount+nHowMany)*sizeof(struct Node*)))) return;        
    }
    *************/
    nod->children = (struct Node**)realloc(nod->children, (nod->childCount+nHowMany)*sizeof(struct Node*));
    int i;
    for(i = 0; i<nHowMany; i++)
    {
        nod->children[nod->childCount+i] = nodChildren[i];
        /* nod->children[nod->childCount+i]->parent = nod; */
    }
    nod->childCount+=nHowMany;
    for(i = 0; i<nod->childCount; i++)
    {
        nod->children[i]->parent = nod;
    }
}

void printChildTree(struct Node* nod)
{
    if(nod)
    {
        printf("%d\t", nod->id);
        if(nod->parent) printf("parent = %d\t", nod->parent->id); else printf("no parent \t");
        if(getRoot(nod)) printf("root = %d", getRoot(nod)->id);
        printf("\n");
        if(nod->childCount)
        {
            int i;
            for(i = 0; i<nod->childCount; i++)
            {
                printChildTree(nod->children[i]);
            }
        }
    }
}


