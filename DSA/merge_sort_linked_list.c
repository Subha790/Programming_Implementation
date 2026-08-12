#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node* insertNode(struct Node *head, int data)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    struct Node *temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;

    return head;
}

struct Node* createList(int n)
{
    struct Node *head = NULL;
    int data;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        head = insertNode(head, data);
    }

    return head;
}

void displayList(struct Node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);

        if (head->next != NULL)
            printf(" -> ");

        head = head->next;
    }

    printf("\n");
}

void splitList(struct Node *head,
               struct Node **front,
               struct Node **back)
{
    struct Node *slow = head;
    struct Node *fast = head->next;

    while (fast != NULL)
    {
        fast = fast->next;

        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

struct Node* mergeLists(struct Node *a, struct Node *b)
{
    if (a == NULL)
        return b;

    if (b == NULL)
        return a;

    struct Node *result = NULL;

    if (a->data <= b->data)
    {
        result = a;
        result->next = mergeLists(a->next, b);
    }
    else
    {
        result = b;
        result->next = mergeLists(a, b->next);
    }

    return result;
}

void mergeSort(struct Node **headRef)
{
    struct Node *head = *headRef;
    struct Node *left;
    struct Node *right;

    if (head == NULL || head->next == NULL)
        return;

    splitList(head, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    *headRef = mergeLists(left, right);
}

int main()
{
    struct Node *head = NULL;
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    head = createList(n);

    printf("\nOriginal List\n");
    displayList(head);

    mergeSort(&head);

    printf("\nSorted List\n");
    displayList(head);

    return 0;
}
