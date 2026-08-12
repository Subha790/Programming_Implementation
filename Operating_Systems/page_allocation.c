#include <stdio.h>
#include <string.h>

#define MAX_FRAMES 8
#define MAX_PROCESSES 10
#define MAX_PAGES 10

typedef struct
{
    int page_number;
    int frame_number;
} PageTableEntry;

typedef struct
{
    char process_id[20];
    int page_count;
    PageTableEntry page_table[MAX_PAGES];
    int active;
} Process;

typedef struct
{
    int frame_number;
    int free;
    char process_id[20];
    int page_number;
} Frame;

Frame frames[MAX_FRAMES];
Process processes[MAX_PROCESSES];

void initializeMemory()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i].frame_number = i;
        frames[i].free = 1;
        strcpy(frames[i].process_id, "-");
        frames[i].page_number = -1;
    }

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        processes[i].active = 0;
    }
}

int findProcess(const char *process_id)
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processes[i].active &&
            strcmp(processes[i].process_id, process_id) == 0)
        {
            return i;
        }
    }

    return -1;
}

int findFreeProcess()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (!processes[i].active)
            return i;
    }

    return -1;
}

void displayMemory()
{
    printf("\nFrame Allocation Status\n");
    printf("---------------------------------------------\n");
    printf("Frame\tStatus\t\tProcess\tPage\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (frames[i].free)
        {
            printf("%d\tFree\t\t-\t-\n",
                   frames[i].frame_number);
        }
        else
        {
            printf("%d\tAllocated\t%s\t%d\n",
                   frames[i].frame_number,
                   frames[i].process_id,
                   frames[i].page_number);
        }
    }

    printf("---------------------------------------------\n");
}

void allocatePage()
{
    char process_id[20];
    int page_number;

    printf("Enter Process ID: ");
    scanf("%19s", process_id);

    printf("Enter Page Number: ");
    scanf("%d", &page_number);

    int process_index = findProcess(process_id);

    if (process_index == -1)
    {
        process_index = findFreeProcess();

        if (process_index == -1)
        {
            printf("Maximum number of processes reached.\n");
            return;
        }

        strcpy(processes[process_index].process_id, process_id);
        processes[process_index].page_count = 0;
        processes[process_index].active = 1;
    }

    if (processes[process_index].page_count >= MAX_PAGES)
    {
        printf("Maximum pages reached for this process.\n");
        return;
    }

    /* Check whether page already exists */
    for (int i = 0; i < processes[process_index].page_count; i++)
    {
        if (processes[process_index].page_table[i].page_number ==
            page_number)
        {
            printf("Page %d is already allocated to %s.\n",
                   page_number, process_id);
            return;
        }
    }

    /* Find first available free frame */
    int free_frame = -1;

    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (frames[i].free)
        {
            free_frame = i;
            break;
        }
    }

    if (free_frame == -1)
    {
        printf("Memory is full. No free frame available.\n");
        return;
    }

    frames[free_frame].free = 0;
    strcpy(frames[free_frame].process_id, process_id);
    frames[free_frame].page_number = page_number;

    int entry = processes[process_index].page_count;

    processes[process_index].page_table[entry].page_number =
        page_number;

    processes[process_index].page_table[entry].frame_number =
        free_frame;

    processes[process_index].page_count++;

    printf("Page %d of Process %s allocated to Frame %d.\n",
           page_number, process_id, free_frame);

    displayMemory();
}

void deallocatePage()
{
    char process_id[20];
    int page_number;

    printf("Enter Process ID: ");
    scanf("%19s", process_id);

    printf("Enter Page Number to deallocate: ");
    scanf("%d", &page_number);

    int process_index = findProcess(process_id);

    if (process_index == -1)
    {
        printf("Process not found.\n");
        return;
    }

    for (int i = 0; i < processes[process_index].page_count; i++)
    {
        if (processes[process_index].page_table[i].page_number ==
            page_number)
        {
            int frame_number =
                processes[process_index].page_table[i].frame_number;

            frames[frame_number].free = 1;
            strcpy(frames[frame_number].process_id, "-");
            frames[frame_number].page_number = -1;

            /* Remove page table entry */
            for (int j = i;
                 j < processes[process_index].page_count - 1;
                 j++)
            {
                processes[process_index].page_table[j] =
                    processes[process_index].page_table[j + 1];
            }

            processes[process_index].page_count--;

            printf("Page %d of Process %s deallocated from Frame %d.\n",
                   page_number, process_id, frame_number);

            if (processes[process_index].page_count == 0)
            {
                processes[process_index].active = 0;
            }

            displayMemory();
            return;
        }
    }

    printf("Page not found for Process %s.\n", process_id);
}

void displayPageTables()
{
    printf("\nPage Tables\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processes[i].active)
        {
            printf("Process: %s\n", processes[i].process_id);

            printf("Page\tFrame\n");

            for (int j = 0; j < processes[i].page_count; j++)
            {
                printf("%d\t%d\n",
                       processes[i].page_table[j].page_number,
                       processes[i].page_table[j].frame_number);
            }

            printf("\n");
        }
    }
}

int main()
{
    int choice;

    initializeMemory();

    while (1)
    {
        printf("\n===== Page Allocation =====\n");
        printf("1. Allocate Page\n");
        printf("2. Deallocate Page\n");
        printf("3. Display Memory\n");
        printf("4. Display Page Tables\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            allocatePage();
            break;

        case 2:
            deallocatePage();
            break;

        case 3:
            displayMemory();
            break;

        case 4:
            displayPageTables();
            break;

        case 5:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
