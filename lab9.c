#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* records;

};

// Compute the hash function
int hash(int x)
{
	return x % 15;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i].records != NULL)
        {
            printf("index %d ->", i);
            int j = 0;
            while (pHashArray[i].records[j].id != 0)
            {
                printf(" %d %c %d ->", pHashArray[i].records[j].id, pHashArray[i].records[j].name, 
										pHashArray[i].records[j].order);
                j++;
            }
            printf("\n");
        }
    
		
		
	}
}

int main(void)
{
	// Your hash implementation
	struct RecordType *pRecords;
    int recordSz = 0;
    

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Create and initialize the hash table
    struct HashType *pHashArray = (struct HashType*)malloc(sizeof(struct HashType) * 15);
    for (int i = 0; i < 15; ++i)
    {
        pHashArray[i].records = NULL;
    }

    // Populate the hash table with the records
    for (int i = 0; i < recordSz; ++i)
    {
        int h = hash(pRecords[i].order);
        int j = 0;
        while (pHashArray[h].records != NULL && pHashArray[h].records[j].id != 0)
        {
            j++;
        }
        pHashArray[h].records = (struct RecordType*)realloc(pHashArray[h].records, sizeof(struct RecordType) * (j + 2));
        pHashArray[h].records[j] = pRecords[i];
        pHashArray[h].records[j + 1].id = 0; // Set the next ID to 0 as a terminator
    }

    displayRecordsInHash(pHashArray, 15);

    // Don't forget to free the allocated memory
    for (int i = 0; i < 15; ++i)
    {
        free(pHashArray[i].records);
    }
    free(pHashArray);
    free(pRecords);

    return 0;
}