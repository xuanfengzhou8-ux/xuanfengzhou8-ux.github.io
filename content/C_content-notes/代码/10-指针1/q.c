int Partition(int a[] , int low, int high)
{
    int pivotkey;
    pivotkey = a[low];
    while(low < high)
    {
        while(low < high && a[high] >= pivotkey)
            high--;
        swap(a,low,high);
        while(low < high && a[low] <= pivotkey)
            low++;
        swap(a,low,high);
    }
    return low;
}