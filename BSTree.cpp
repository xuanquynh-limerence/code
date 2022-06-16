#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

typedef Node* Tree;

void CreateTree (Tree &tree)
{
    tree = NULL;
}

Node* CreateNode (int x)
{
    Node* p = new Node();
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void AddNode (Tree &tree, Node* p)
{
    if (tree != NULL)
    {
        if (p->data == tree->data)
            return;

        if (p->data < tree->data)
            AddNode(tree->left,p);
        else 
            AddNode(tree->right,p);
    }
    else 
        tree = p;
}

void Input (Tree &tree)
{
    int x;
    Node* p;
    do
    {
        cin >> x;
        if (x)
        {
            p = CreateNode(x);
            AddNode(tree,p);
        }
    } while (x);
}

//Duyệt cây theo 6 cách: LNR, LRN, NLR, NRL, RNL, RLN
void LNR (Tree &tree)
{
    if (tree != NULL)
    {
        LNR(tree->left);
        cout << tree->data << " ";
        LNR(tree->right);
    }
    else 
        return;
}

//Tìm 1 nút có từ khóa x
bool SearchNode (Tree tree, int x)
{
    while (tree != NULL)
    {
        if (x == tree->data)
            return true;

        if (x < tree->data)
            tree = tree->left;
        else 
            tree = tree->right;
    }
    return false;
}

//Xóa 1 nút bằng x trên cây
void NodeTheMang (Node* p, Node* t)
{
    if (t->left !=NULL)
        NodeTheMang(p,t->left);
    else 
    {
        p->data = t->data;
        p = t;
        t = t->right;
    }
}

void DeleteNode (Tree &T, int x)
{
    if (T != NULL)
    {
        if (x == T->data)
        {
            Node *p = T;
            if (T->left == NULL)
                T = T->right;
            else 
                if (T->right == NULL)
                    T = T->left;
                else 
                    NodeTheMang(p,T->right);
        }
        else 
            if (x < T->data)
                DeleteNode(T->left,x);
            else 
                DeleteNode(T->right,x);
    }
    else 
        return;
}

//Đếm số nút trên cây
//Đếm số nút có đầy đủ 2 con
//Đếm số nút không có con (nút lá)
//Đếm số nút có bậc bất kỳ
//Tính chiều cao của cây
int FindMaxLevel(Tree tree, int &n)
{
    if (tree != NULL)
    {
        int MaxLevelLeft = FindMaxLevel(tree->left,n);
        int MaxLevelRight = FindMaxLevel(tree->right,n);
        if (MaxLevelLeft > MaxLevelRight)
            n = ++MaxLevelLeft;
        else 
            n = ++MaxLevelRight;
        return n;
    }
    return 0;
} 

int main()
{
    Tree T;
    CreateTree(T);
    int n;
    Input(T);
    cin >> n;
    DeleteNode(T,n);
    LNR(T);
    return 0;
}