#include <stdio.h>
#include <stdlib.h>

// Cody Zheng
// Torosdagli
//Lab assignment 9
// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

struct HashType
{
    struct RecordType* r;
};

int hash(int x, int tableSize)
{
    return x % tableSize;
}

int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;

    *ppData = NULL;
    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }

        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name, &pRecord->order);
            pRecord->next = NULL;
        }

        fclose(inFile);
    }
    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords: \n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\n%d %c %d", pData[i].id, pData[i].name, pData[i].order);
    }
    printf(" \n");
}

void insertRecord(struct HashType hashTable[], struct RecordType record, int tableSize)
{
    // call the hash function to get the index
    int index = hash(record.id, tableSize);

    // if the RecordType at that index is NULL
    if (hashTable[index].r == NULL)
    {
        // set 'record' equal to the HashType pointer in the table at index
        hashTable[index].r = &record;
    }
    else
    {
        // else traverse to the end of the linkedlist and add 'record' to the end of it
        struct RecordType* curr = hashTable[index].r;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = &record;
    }
}

void displayRecordsInHash(struct HashType hashTable[], int tableSize)
{
    for (int i = 0; i < tableSize; ++i)
    {
        if (hashTable[i].r != NULL)
        {
            printf("Index %d -> ", i);
            struct RecordType* curr = hashTable[i].r;
            while (curr != NULL)
            {
                printf("%d %c %d -> ", curr->id, curr->name, curr->order);
                curr = curr->next;
            }
            printf("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    int hashTableSize = 10;
    struct HashType* hashTable = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));// Insert records into the hash table
    for (int i = 0; i < recordSz; ++i){
    insertRecord(hashTable, *(pRecords + i), hashTableSize);
    }

    // Display records in the hash table
    displayRecordsInHash(hashTable, hashTableSize);

    // Free memory
    free(pRecords);
    free(hashTable);
    return 0;
}
