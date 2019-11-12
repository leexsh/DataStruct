#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct trie{
	int nCount;
	char *str;
	struct trie *pCharacter[26];
}TrieTree;

TrieTree *GetNode(){
	TrieTree *pTemp = NULL;
	pTemp = (TrieTree*)malloc(sizeof(TrieTree));
	memset(pTemp, 0, sizeof(TrieTree));
	
	return pTemp;
}

void AddNode(TrieTree *pNode, char *pStr){
	int i = 0;
	while(i < strlen(pStr)){
		if(pNode->pCharacter[pStr[i] - 97] == NULL){
			pNode->pCharacter[pStr[i] - 97] = GetNode();	
		}
		pNode = pNode->pCharacter[pStr[i] - 97];
		i++;
	}
	pNode->nCount++;
	pNode->str = pStr;
}
TrieTree *CreateTrieTree(char *str[], int nLen){
	if(str == NULL || nLen <= 0)
		return NULL;
	TrieTree *pRoot = NULL;
	pRoot = GetNode();
	int i;
	for(i = 0; i < nLen; i++){
		AddNode(pRoot, str[i]);	
	}
	return pRoot;
}


void Search(TrieTree *pRoot, char *str){
	if(pRoot == NULL || str == NULL)
		return;
	int i = 0;
	while(i < strlen(str)){
		if(pRoot->pCharacter[str[i] - 97] == NULL){
			printf("mei you\n");
			return;
		}
		pRoot = pRoot->pCharacter[str[i] - 97];
		i++;
	}
	if(pRoot->nCount != 0){
		printf("%s\n", pRoot->str);	
	}
	else{
		printf("No!\n");	
	}
}

void PreOrder(TrieTree *pRoot){
	if(pRoot == NULL)
		return ;
	if(pRoot->nCount != 0){
		printf("%s\n", pRoot->str);	
	}
	int i = 0;
	for(i; i < 26; i++){
		PreOrder(pRoot->pCharacter[i]);	
	}
}
int main(){
	char *str[] = {"nike", "addais","apple", "mi", "huawei", "puma", "dell", "lining"};
	TrieTree *pRoot = NULL;
	pRoot = CreateTrieTree(str,8);
	PreOrder(pRoot);
	Search(pRoot, "mi");
	return 0;	
}
