#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_MEMORY 1024
#define MAX_BLOCKS 100

typedef struct
{
    int start;
    int size;
    int allocated;
    char process_id[20];
} Block;

Block memory[MAX_BLOCKS];
int blockCount;

void initializeMemory()
{
    blockCount = 1;

    memory[0].start = 0;
    memory[0].size = TOTAL_MEMORY;
    memory[0].allocated = 0;
    strcpy(memory[0].process_id, "-");
}

void splitBlock(int index)
{
    if (memory[index].size <= 1)
        return;

    int newSize = memory[index].size / 2;
    int start = memory[index].start;

    memory[index].size = newSize;

    for (int i = blockCount; i > index + 1; i--)
        memory[i] = memory[i - 1];

    blockCount++;

    memory[index + 1].start = start + newSize;
    memory[index + 1].size = newSize;
    memory[index + 1].allocated = 0;
    strcpy(memory[index + 1].process_id, "-");

    memory[index].allocated = 0;
    strcpy(memory[index].process_id, "-");
}

int requiredBlockSize(int size)
{
    int blockSize = 1;

    while (blockSize < size)
        blockSize *= 2;

    return blockSize;
}

void allocateMemory()
{
    char processID[20];
    int requestedSize;

    printf("Enter Process ID: ");
    scanf("%19s", processID);

    printf("Enter Size (KB): ");
    scanf("%d", &requestedSize);

    if (requestedSize <= 0 || requestedSize > TOTAL_MEMORY)
    {
        printf("Invalid memory size.\n");
        return;
    }

    int requiredSize = requiredBlockSize(requestedSize);
    int index = -1;

    /* Find smallest free block that can accommodate request */
    for (int i = 0; i < blockCount; i++)
    {
        if (!memory[i].allocated &&
            memory[i].size >= requiredSize)
        {
            if (index == -1 || memory[i].size < memory[index].size)
                index = i;
        }
    }

    if (index == -1)
    {
        printf("Allocation failed.\n");
        return;
    }

    /* Split until required block size is obtained */
    while (memory[index].size > requiredSize)
        splitBlock(index);

    memory[index].allocated = 1;
    strcpy(memory[index].process_id, processID);

    printf("Allocated %d KB\n", memory[index].size);
    printf("Internal Fragmentation: %d KB\n",
           memory[index].size - requestedSize);
}

void mergeBuddy(int index)
{
    int currentStart = memory[index].start;
    int currentSize = memory[index].size;

    for (int i = 0; i < blockCount; i++)
    {
        if (i == index)
            continue;

        if (!memory[i].allocated &&
            memory[i].size == currentSize &&
            (memory[i].start / currentSize) % 2 !=
            (currentStart / currentSize) % 2)
        {
            int newStart = memory[i].start < currentStart
                               ? memory[i].start
                               : currentStart;

            memory[index].start = newStart;
            memory[index].size = currentSize * 2;
            memory[index].allocated = 0;
            strcpy(memory[index].process_id, "-");

            for (int j = i; j < blockCount - 1; j++)
                memory[j] = memory[j + 1];

            blockCount--;

            if (i < index)
                index--;

            mergeBuddy(index);
            return;
        }
    }
}

void freeMemory()
{
    char processID[20];

    printf("Enter Process ID to free: ");
    scanf("%19s", processID);

    for (int i = 0; i < blockCount; i++)
    {
        if (memory[i].allocated &&
            strcmp(memory[i].process_id, processID) == 0)
        {
            memory[i].allocated = 0;
            strcpy(memory[i].process_id, "-");

            printf("Memory freed for %s\n", processID);

            mergeBuddy(i);
            return;
        }
    }

    printf("Process ID not found.\n");
}

void displayMemory()
{
    printf("\nMemory Blocks\n");
    printf("------------------------------------------------------------\n");
    printf("%-12s %-16s %-16s %-12s %-12s\n",
           "Block Size", "Starting Address",
           "Ending Address", "Status", "Process ID");

    printf("------------------------------------------------------------\n");

    for (int i = 0; i < blockCount; i++)
    {
        printf("%-12d %-16d %-16d %-12s %-12s\n",
               memory[i].size,
               memory[i].start,
               memory[i].start + memory[i].size - 1,
               memory[i].allocated ? "Allocated" : "Free",
               memory[i].process_id);
    }

    printf("------------------------------------------------------------\n");
}

int main()
{
    int choice;

    initializeMemory();

    printf("Memory = %d KB\n", TOTAL_MEMORY);

    while (1)
    {
        printf("\n1. Allocate Memory\n");
        printf("2. Free Memory\n");
        printf("3. Display Memory Blocks\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            allocateMemory();
            break;

        case 2:
            freeMemory();
            break;

        case 3:
            displayMemory();
            break;

        case 4:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
