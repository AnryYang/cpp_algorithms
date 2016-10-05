/*************************************************************************
    > File Name: tree_travesal.cpp
    > Author: anryyang
    > Mail: anryyang@gmail.com 
    > Created Time: Wed Oct  5 22:49:48 2016
 ************************************************************************/

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct TreeNode{
    int index;
    struct TreeNode* leftchild;
    struct TreeNode* rightchild;
};

void visit(TreeNode* stNode){
    cout<<stNode->index<<"->";
}

void PreOrderTraversal(TreeNode *p){
    if(p==NULL) return;
    visit(p);
    PreOrderTraversal(p->leftchild);
    PreOrderTraversal(p->rightchild);
}

void InOrderTraversal(TreeNode *p){
    if(p==NULL) return;
    InOrderTraversal(p->leftchild);
    visit(p);
    InOrderTraversal(p->rightchild);
}

void PostOrderTraversal(TreeNode* p){
    if(p==NULL) return;
    PreOrderTraversal(p->leftchild);
    PreOrderTraversal(p->rightchild);
    visit(p);
}

int main(){
    int n=20;
    vector<TreeNode*> vecNodes;
    for(int i=0;i<n;i++){
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->index=i;
        node->leftchild=NULL;
        node->rightchild=NULL;
        vecNodes.push_back(node);
    }

    int i = 0;
    while(2*i+2<n){
        vecNodes[i]->leftchild = vecNodes[2*i+1];
        vecNodes[i]->rightchild = vecNodes[2*i+2];
        i++;
    }

    cout<<"Pre Order Traversal"<<endl;
    PreOrderTraversal(vecNodes[0]);
    cout<<endl;

    cout<<"In Order Traversal"<<endl;
    InOrderTraversal(vecNodes[0]);
    cout<<endl;

    cout<<"Post Order Traversal"<<endl;
    PostOrderTraversal(vecNodes[0]);
    cout<<endl;
}

