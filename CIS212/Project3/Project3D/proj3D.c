/*
 * I believe I have completed:
 *  Map based on linked lists: yes/no
 *  Double hashing: yes/no
 *  Performance study: yes/no 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct
{
    char    *symbol;
    char    *name;
    float    lastSale;
    float    marketCap;
    int      IPOyear;
} Company;



void PrintCompany(Company *c)
{
    printf("%s:\n", c->name);
    printf("\tSymbol: %s\n", c->symbol);
    /* .2f: only print two digits after the period. */
    printf("\tLast Sale: %.2f\n", c->lastSale);
    printf("\tMarket Capitalization: %.2f\n", c->marketCap);
    printf("\tYear of Initial Public Offering: %d\n", c->IPOyear);
}

void ReadFile(const char *filename, Company **companies_rv, int *numCompanies_rv)
{
    int  i, j;

    if (filename == NULL)
    {
        fprintf(stderr, "No filename specified!\n");
        exit(EXIT_FAILURE);
    }
    FILE *f_in = fopen(filename, "r");
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f_in, 0, SEEK_END);
    int numChars = ftell(f_in);
    // printf("The number of characters is %d\n", numChars);
    fseek(f_in, 0, SEEK_SET);

    char *file_contents = malloc(sizeof(char)*numChars+1);
    fread(file_contents, sizeof(char), numChars, f_in);
    file_contents[numChars] = '\0';
    fclose(f_in);
    /* Note: the memory for this array is used to populate
     * the fields of the companies.  If it is freed, then
     * the company structs all become invalid.  For the
     * context of this program, this array should not be 
     * freed. */

    // Find out how many lines there are
    int numLines = 0;
    for (i = 0 ; i < numChars ; i++)
        if (file_contents[i] == '\n')
            numLines++;
    // printf("Number of lines is %d\n", numLines);

    int      numCompanies = numLines-1; // first line is header info 
    Company *companies    = malloc(sizeof(Company)*numCompanies);

    /* strtok will parse the file_contents array.  
     * The first time we call it, it will replace every '"' with '\0'.
     * It will also return the first word before a 
     */
    int numColumns = 9;
    int numberOfQuotesPerColumn = 2;
    strtok(file_contents, "\"");
    for (i = 0 ; i < numberOfQuotesPerColumn*numColumns-1 ; i++)
         strtok(NULL, "\"");
    for (i = 0 ; i < numCompanies ; i++)
    {
         companies[i].symbol = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].name = strtok(NULL, "\"");
         strtok(NULL, "\"");
         companies[i].lastSale = atof(strtok(NULL, "\""));
         strtok(NULL, "\"");
         companies[i].marketCap = atof(strtok(NULL, "\""));
         strtok(NULL, "\""); 

         /* Skip ADR TSO */
         strtok(NULL, "\"");
         strtok(NULL, "\"");

         companies[i].IPOyear = atoi(strtok(NULL, "\""));
         strtok(NULL, "\"");

         /* Skip Sector, Industry, Summary Quote */
         for (j = 0 ; j < 6 ; j++)
             strtok(NULL, "\"");

         //PrintCompany(companies+i);
    }

    /* Set parameters to have output values */
    *companies_rv    = companies;
    *numCompanies_rv = numCompanies;
}

int hash(char *name, long array_size)
{
    int hashval = 0;
    char *p = name;
    while (*p != '\0')
    {
        hashval = 31*hashval + *p;
        p++;
    }

    return hashval%array_size;
}
#define A 31L
long hash2(char *key , long N) {
	unsigned long sum = 0L;
	char *p;

	for (p = key; *p != '\0'; p++)
		sum = A * sum + (unsigned long) (*p);
	return (long)(sum % N);
}
struct node {
	char *symbol;
	struct node *next;
	Company *company;
};

typedef struct 
{
    int         numElements;
    char      **keys;
    Company    *companies;
} MapBasedOnHashTable;
typedef struct
{
	struct node* head;
} MapBasedonLinkedlist;


void InitializeMapBasedOnHashTable(MapBasedOnHashTable *map, int numElements)
{
    map->numElements = numElements;
    map->keys = malloc(sizeof(char *)*numElements);
    map->companies = malloc(sizeof(Company)*numElements);
    for (int i = 0 ; i < numElements ; i++)
        map->keys[i] = NULL;
}





void StoreTo_MapBasedOnHashTable(MapBasedOnHashTable *map, Company *c)
{
    int hashval = hash(c->symbol, map->numElements);
    int hashval2 = hash2(c->symbol, map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval+i*hashval2)%(map->numElements) ;
        if (idx < 0) 
		idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            map->keys[idx]      = c->symbol;
            map->companies[idx] = *c;
            return;
        }
    }
}

void StoreTo_LinkedList(struct node** head, Company *c) {
	struct node *new = (struct node *)malloc(sizeof(struct node));
	new->symbol = c->symbol;
	new->next = NULL;
	new->company = c;
	struct node *p = *head;

	if (p != NULL) {
		while (p->next != NULL)
			p = p->next;
	}
	if (p !=NULL) {
		p->next = new;
	}
	else 
		*head = new;
}

Company *FetchFrom_MapBasedOnHashTable(MapBasedOnHashTable *map, char *key)
{
    int hashval = hash(key, map->numElements);
    int hashval2 = hash2(key,map->numElements);
    for (int i = 0 ; i < map->numElements ; i++)
    {
        int idx = (hashval+i*hashval2)%(map->numElements);
        if (idx < 0) 
		idx+= map->numElements;
        if (map->keys[idx] == NULL)
        {
            return NULL;
        }

        if (strcmp(map->keys[idx], key) == 0)
        {
            return &(map->companies[idx]);
        }
    }
    
    return NULL;
}

Company *FetchFromLinkedList(struct node** head, char *symbol) {
	struct node *p;

	for (p = *head; p != NULL; p = p->next) {
		if (strcmp(p->symbol, symbol) == 0) {
			return p->company;
		}
	}
	return NULL;
}
void FetchAndPrint(MapBasedOnHashTable *mfht, char *key) {
    Company *c = FetchFrom_MapBasedOnHashTable(mfht, key);
    if (c == NULL)
    {
        printf("Key %s has no corresponding company\n", key);
    }
    else
    {
        PrintCompany(c);
    }

}
void FetchandPrintLL(struct node **head, char *key) {
	Company *c = FetchFromLinkedList(head,key);
	if (c ==  NULL)
	{
		printf("Key %s has no corresponding company\n", key);
	}
	else
	{
		PrintCompany(c);
	}
}

int main(int argc, char *argv[])
{
    Company *companies = NULL;
    struct node *head = NULL;
    int      numCompanies;
    ReadFile(argv[1], &companies, &numCompanies);
    MapBasedOnHashTable mfht;
    InitializeMapBasedOnHashTable(&mfht, numCompanies*2);
    for (int i = 0 ; i < numCompanies ; i++)
    {
        StoreTo_MapBasedOnHashTable(&mfht, companies+i);
    }
    for (int t = 0; t < numCompanies; t++)
    {
	    StoreTo_LinkedList(&head, companies+t);
    } 

    FetchAndPrint(&mfht, "ZNWAA");
    FetchAndPrint(&mfht, "Z");
    FetchAndPrint(&mfht, "ZIOP");
    FetchAndPrint(&mfht, "ZIOQ");
    FetchAndPrint(&mfht, "YIOQ");
    FetchAndPrint(&mfht, "QIOQ");
    FetchAndPrint(&mfht, "WIOQ");
    FetchAndPrint(&mfht, "XIOQ");
    FetchAndPrint(&mfht, "TIOQ");
    FetchAndPrint(&mfht, "UIOQ");
    FetchAndPrint(&mfht, "VIOQ");

    FetchandPrintLL(&head, "ZNWAA");
    FetchandPrintLL(&head, "Z");
    FetchandPrintLL(&head, "ZIOP");
    FetchandPrintLL(&head, "ZIOQ");
    FetchandPrintLL(&head, "YIOQ");
    FetchandPrintLL(&head, "QIOQ");
    FetchandPrintLL(&head, "WIOQ");
    FetchandPrintLL(&head, "XIOQ");
    FetchandPrintLL(&head, "TIOQ");
    FetchandPrintLL(&head, "UIOQ");
    FetchandPrintLL(&head, "VIOQ");

    struct timeval startTime;
    gettimeofday(&startTime,0);
    for (int i = 0; i < numCompanies ; i++)
	    StoreTo_MapBasedOnHashTable(&mfht,companies + i);
    struct timeval endtime;
    gettimeofday(&endtime, 0);
    double seconds = (double) (endtime.tv_sec - startTime.tv_sec) + (double)(endtime.tv_usec - startTime.tv_usec) / 100000.;
    printf ("Store to Hash Table done executing, took %f\n", seconds);


    struct timeval starttime;
    gettimeofday(&starttime,0);
    for (int i = 0; i < numCompanies ; i++)
	   FetchFrom_MapBasedOnHashTable(&mfht , (companies+i)->symbol);
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double secondss = (double) (endTime.tv_sec - starttime.tv_sec) + (double)(endTime.tv_usec - starttime.tv_usec) / 100000.;
    printf ("Fetch From Hash Table done executing, took %f\n", secondss);


    struct timeval startTimes;
    gettimeofday(&startTimes,0);
    for (int i = 0; i < numCompanies ; i++)
	   StoreTo_LinkedList(&head, companies + i);
    struct timeval endtimes;
    gettimeofday(&endtimes, 0);
    double tseconds = (double) (endtimes.tv_sec - startTimes.tv_sec) + (double )(endtimes.tv_usec - startTimes.tv_usec) / 100000.;
    printf ("Store to Linked List done executing, took %f\n", tseconds);

    struct timeval startTimez;
    gettimeofday(&startTimez,0);
    for (int i = 0; i < numCompanies ; i++)
	   FetchFromLinkedList(&head , (companies+i)->symbol);
    struct timeval endtimez;
    gettimeofday(&endtimez, 0);
    double secondz = (double) (endtimez.tv_sec - startTimez.tv_sec) + (double )(endtimez.tv_usec - startTimez.tv_usec) / 100000.;
    printf ("Fetch From Linked List done executing, took %f\n", secondz);





}

/* YOUR PERFORMANCE STUDY WRITEUP GOES HERE:
 * After doing a runtime of both functions I discover that Linked lists have a longer time executing its functions then
 * a Hash table does a quicker O time complexity than a linked list and this is probably exuberated further by using
 * a double hash function. Also for my double has I used the example in Sventek's book about polynomial hashing and 
 * that is the function I used to create my double hashing.
 
 */
