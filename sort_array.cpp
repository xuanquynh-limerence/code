#include <iostream>

using namespace std;

void Input(int *a, int n)
{
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

void Output (int *a, int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}

void Swap (int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//Sắp xếp nổi bọt
void BubbleSort (int *a, int n)
{
    int dem;
    for (int i = 0; i < n - 1; i++)
    {
        dem = 0;
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j+1])
            {
                Swap(a[j],a[j+1]);
                dem++;
            }
        if (!dem)
            break;
    }
}

//Sắp xếp chọn
void SelectionSort (int *a, int n)
{
    int min = 0;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        if (min != i)
            Swap(a[i],a[min]);
    }
}

//Sắp xếp chèn
void InsertionSort (int *a, int n)
{
    int pos, x;
    for (int i = 1; i < n; i++)
    {
        x = a[i];
        pos = i - 1;
        while ((pos >= 0) && (a[pos] > x))
        {
            a[pos+1] = a[pos];
            pos--;
        }
        a[pos+1] = x;
    }
}

//Sắp xếp vun đống
void Heapify (int *a, int n, int i)
{
    int min = i;
    int l = i*2 + 1;
    int r = i*2 + 2;

    if ((l < n) && (a[l] > a[min]))
        min = l;
    if ((r < n) && (a[r] > a[min]))
        min = r;
    
    if (min != i)
    {
        Swap(a[i],a[min]);
        Heapify(a,n,min);
    }
}

void HeapSort (int *a, int n)
{
    for (int i = n/2 - 1; i >= 0; i--)
        Heapify(a,n,i);
    
    for (int j = n - 1; j > 0; j--)
    {
        Swap(a[0],a[j]);
        Heapify(a,j,0);
    }
}

//Sắp xếp nhanh
void QuickSort (int *a, int m, int n)
{
    if (m >= n)
        return;
    int mid, left, right;
    left = m;
    right = n - 1;
    mid = (left + right)/2;
    
    int x = a[mid];
    int i = left; 
    int j = right;
    while (i <= j)
    {
        while (a[i] < x)
            i++;
        while (a[j] > x)
            j--;

        if (i <= j)
        {
            if (i < j)
                Swap(a[i],a[j]);
            i++;
            j--;
        }
    }
    
    QuickSort(a,left,j+1);
    QuickSort(a,i,right+1);
}

//Sắp xếp trộn
void Merge (int *a, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = new int[n1];
    int *R = new int[n2];

    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;

    while ((i < n1) && (j < n2))
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else 
            a[k++] = R[j++];

    while (i < n1)
        a[k++] = L[i++];
    while (k < n2)
        a[k++] = R[j++];
}

void MergeSort (int *a, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l)/2;
        MergeSort(a,l,m);
        MergeSort(a,m+1,r);
        Merge(a,l,m,r);
    }
}

int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    Input(a,n);

    BubbleSort(a,n);
    SelectionSort(a,n);
    InsertionSort(a,n);
    HeapSort(a,n);
    QuickSort(a,0,n);
    MergeSort(a,0,n-1);

    Output(a,n);
    return 0;
}