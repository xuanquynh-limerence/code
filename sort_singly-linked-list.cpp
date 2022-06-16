#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

struct List
{
    Node *pHead;
    Node *pTail;
};

void CreateList (List &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

Node* CreateNode (int x)
{
    Node* p = new Node();
    if (p == NULL)
        exit(1);
    p->data = x;
    p->next = NULL;
    return p;
}

void AddHead (List &l, Node* p)
{
    if (l.pHead == NULL)
    {
        l.pHead = p;
        l.pTail = p;
    }
    else 
    {
        p->next = l.pHead;
        l.pHead = p;
    }
}

void AddTail (List &l, Node* p)
{
    if (l.pHead == NULL)
    {
        l.pHead = p;
        l.pTail = p;
    }
    else
    {
        l.pTail->next = p;
        l.pTail = p;
    }
}

void Input(List &l, int n)
{
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        Node* p = CreateNode(x);
        AddTail(l,p);
    }
}

void Output (List l, int n)
{
    for (Node* p = l.pHead; p != NULL; p = p->next)
        cout << p->data << " ";
}

void Swap (int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//Sap xep noi bot
void BubbleSort (List &l)
{
    int swapped;
    Node* p = NULL;
    Node* q;
    do
    {
        swapped = 0;
        for (q = l.pHead; q->next != NULL; q = q->next)
        {
            if (q->data > q->next->data)
            {
                Swap(q->data,q->next->data);
                swapped++;
            }
        }
        p = q;
    } while (swapped);
}

//Sắp xếp chọn
void SelectionSort (List &l)
{
    for (Node* p = l.pHead; p->next != NULL; p = p->next)
    {
        Node* min = p;
        for (Node* q = p->next; q != NULL; q = q->next)
            if (min->data > q->data)
                min = q;
        Swap(p->data,min->data);
    }
}

//Sắp xếp chèn
void InsertionSort (List &l)
{
    if (l.pHead->next == NULL)
        return;
    for (Node* p = l.pHead->next; p != NULL; p = p->next)
    {
        int x = p->data;
        int found = 0;
        Node* q;
        for (q = l.pHead; q != p; q = q->next)
        {
            if ((q->data > p->data) && (found == 0))
            {
                x = q->data;
                q->data = p->data;
                found++;
            }
            else 
                if (found)
                    Swap(x,q->data);
        }
        q->data = x;
    }
}

//Sắp xếp nhanh
void QuickSort (List &l)
{
    Node *x, *p;
    List L, R;
    CreateList(L);
    CreateList(R);

    if (l.pHead == l.pTail)
        return;
    x = l.pHead;
    l.pHead = l.pHead->next;
    x->next = NULL;

    while (l.pHead)
    {
        p = l.pHead;
        l.pHead = l.pHead->next;
        p->next = NULL;
        if (p->data < x->data)
            AddTail(L,p);
        else 
            AddTail(R,p);
    }

    QuickSort(L);
    QuickSort(R);

    if (L.pHead)
    {
        l.pHead = L.pHead;
        L.pTail->next = x;
    }
    else 
        l.pHead = x;
    
    x->next = R.pHead;

    if (R.pHead)
        l.pTail = R.pTail;
    else 
        l.pTail = x;

}

//Sắp xếp trộn
Node* Merge (List &L, List &R)
{
    Node *a, *b, *temp;

    if (L.pHead == NULL)
        return R.pHead;
    if (R.pHead == NULL)
        return L.pHead;
    
    a = L.pHead;

    while (R.pHead)
    {
        b = R.pHead;
        R.pHead = R.pHead->next;
        b->next = NULL;

        if (L.pHead->data > b->data)
        {
            b->next = L.pHead;
            L.pHead = b;
            a = L.pHead;
        }

        if (a->next == NULL)
        {
            a->next = b;
            a = a->next;
        }
        else 
            if (a->next->data <= b->data)
                a = a->next;
            else 
            {
                temp = a->next;
                a->next = b;
                b->next = temp;
            }
    }
    return L.pHead;
} 

void MergeSort (List &l)
{
    List L, R;
    CreateList(L);
    CreateList(R);
    Node* temp;
    
    L.pHead = l.pHead;
    temp = l.pHead;

    if (L.pHead->next == NULL)
        return;
    else 
    {
        while (L.pHead->next)
        {
            L.pHead = L.pHead->next;
            if (L.pHead->next)
            {
                temp = temp->next;
                L.pHead = L.pHead->next;
            }
        }
        R.pHead = temp->next;
        temp->next = NULL;
        L.pHead = l.pHead;
    }

    MergeSort(L);
    MergeSort(R);
    l.pHead = Merge(L,R);
}

int main()
{
    int n;
    cin >> n;
    List l;
    CreateList(l);
    Input(l,n);

    BubbleSort(l);
    SelectionSort(l);
    InsertionSort(l);
    QuickSort(l);
    MergeSort(l);

    Output(l,n);
    return 0;
}