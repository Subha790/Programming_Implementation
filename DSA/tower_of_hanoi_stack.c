#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Stack
{
    struct Node *top;
};

// Create Stack
struct Stack* createStack()
{
    struct Stack *s = (struct Stack*)malloc(sizeof(struct Stack));
    s->top = NULL;
    return s;
}

// Push
void push(struct Stack *s, int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

// Pop
int pop(struct Stack *s)
{
    if (s->top == NULL)
        return -1;

    struct Node *temp = s->top;
    int data = temp->data;

    s->top = s->top->next;
    free(temp);

    return data;
}

// Peek
int peek(struct Stack *s)
{
    if (s->top == NULL)
        return -1;

    return s->top->data;
}

// Display Stack
void displayStack(struct Stack *s)
{
    struct Node *temp = s->top;

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

// Move Disk
void moveDisk(struct Stack *from, struct Stack *to,
              char source, char destination)
{
    int disk = pop(from);
    push(to, disk);

    printf("\nMove Disk %d from %c to %c\n",
           disk, source, destination);
}

// Display all three stacks
void displayAll(struct Stack *A, struct Stack *B, struct Stack *C)
{
    printf("A : ");
    displayStack(A);

    printf("B : ");
    displayStack(B);

    printf("C : ");
    displayStack(C);
}

// Tower of Hanoi
void towerOfHanoi(int n,
                  struct Stack *A,
                  struct Stack *B,
                  struct Stack *C,
                  char source,
                  char auxiliary,
                  char destination)
{
    if (n == 0)
        return;

    towerOfHanoi(n - 1, A, C, B,
                 source, destination, auxiliary);

    moveDisk(A, C, source, destination);
    displayAll(A, B, C);

    towerOfHanoi(n - 1, B, A, C,
                 auxiliary, source, destination);
}

int main()
{
    int n;

    struct Stack *A = createStack();
    struct Stack *B = createStack();
    struct Stack *C = createStack();

    printf("Enter number of disks: ");
    scanf("%d", &n);

    // Push disks into Source stack
    for (int i = n; i >= 1; i--)
    {
        push(A, i);
    }

    printf("\nInitial\n");
    displayAll(A, B, C);

    towerOfHanoi(n, A, B, C, 'A', 'B', 'C');

    return 0;
}
