#include <stdio.h>

void merge(int arr[], int low, int mid, int high)
{
    int temp[100];
    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        arr[i] = temp[k];

    printf("After Merge\n");
    for (i = low; i <= high; i++)
        printf("%d ", arr[i]);

    printf("\n\n");
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array\n");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n\n");

    mergeSort(arr, 0, n - 1);

    printf("Final Sorted Array\n");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    return 0;
}
