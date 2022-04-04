
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

typedef struct
{
	int front;
	int back;
	int num_elements;
	char *strings[QUEUE_SIZE];
} Queue;
void InitializeQueue(Queue *q)
{
	q->front = 0;
	q->back = 0;
	q->num_elements = 0;
	for (int i = 0; i < QUEUE_SIZE; i++)
		q->strings[i] = NULL;
}
void Enqueue(Queue *q, char *val)
{
	if (q->num_elements == QUEUE_SIZE) {
		printf("Queue Full");
		return;
	}
	q->strings[q->back] = val;
	q->back++;
	q->num_elements++;
	if (q->back == QUEUE_SIZE) {
		q->back = 0;
	}
}
char* Dequeue(Queue *q)
{
	char *rv = q->strings[q->front];
	q->strings[q->front] = NULL;
	q->front++;
	q->num_elements--;
	if (q->front == QUEUE_SIZE) {
		q->front = 0;
	}
	return rv;
}
char* Front(Queue *q) {
	char* pat = q->strings[q->front];
	return pat;
}



void PrintQueue(Queue *q)
{
    int i;
    printf("Printing queue %p\n", q);
    printf("\tThe index for the front of the queue is %d\n", q->front);
    printf("\tThe index for the back of the queue is %d\n", q->back);
    if (q->front == q->back)
    {
        printf("\tThe queue is empty.\n");
        return;
    }
    int back = q->back;
    if (q->back < q->front)
    {
        // wrapped around, so modify indexing 
        back += QUEUE_SIZE;
    }

    for (i = q->front ; i < back ; i++)
    {
        printf("\t\tEntry[%d] = \"%s\"\n", i%QUEUE_SIZE, q->strings[i%QUEUE_SIZE]);
    }
}

void PrettyPrintQueue(Queue *q, char *type)
{
    if (Front(q) == NULL)
    {
        printf("No unmatched entries for %s\n", type);
    }
    else
    {
        char *s;
        printf("Unmatched %s:\n", type);
        while ((s = Dequeue(q)))
        {
            printf("%s\n", s);
        }
    }
}

char *NewString(char *s)
{
    int len = strlen(s);
    char *rv = malloc(len+1);
    strcpy(rv, s);
    rv[len-1] = '\0'; /* take out newline */
    return rv;
}



int  main(int argc, char *argv[])
{

    /*Queue q;
    InitializeQueue(&q);
    PrintQueue(&q);
    Enqueue(&q, "hello");
    PrintQueue(&q);
    Enqueue(&q, "world");
    PrintQueue(&q);
    printf("Dequeue: %s\n", Dequeue(&q));
    PrintQueue(&q);
*/
/* Gives this output (with different pointers):
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 0
	The queue is empty.
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 1
		Entry[0] = "hello"
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 0
	The index for the back of the queue is 2
		Entry[0] = "hello"
		Entry[1] = "world"
Dequeue: hello
Printing queue 0x7fff5e6878a8
	The index for the front of the queue is 1
	The index for the back of the queue is 2
		Entry[1] = "world"
*/


/*** STEP #2: read in from the input file (argc/argv stuff). 
     NewString is likely helpful here.
 ***/
    Queue female_donors;
    InitializeQueue(&female_donors);
    Queue female_recipients;
    InitializeQueue(&female_recipients);
    Queue male_donors;
    InitializeQueue(&male_donors);
    Queue male_recipients;
    InitializeQueue(&male_recipients);
    Queue hospitals;
    InitializeQueue(&hospitals);
    FILE *f = fopen(argv[1], "r");
    char line[256];
    int linenum = 0;
    while (fgets(line , 256, f) != NULL) {
	     char *pat = NewString(line); 
	     if (pat[0] == 'R') {
		     if (pat[2] == 'F') {
			     Enqueue(&female_recipients,&pat[4]);
		     }
		     if (pat[2] == 'M')
			     Enqueue(&male_recipients,&pat[4]);
	     }
	     if (pat[0] == 'D') {
		     if (pat[2] == 'F')
			     Enqueue(&female_donors, &pat[4]);
		     if (pat[2] == 'M')
			     Enqueue(&male_donors, &pat[4]);
	     }
	     if (pat[0] == 'H') {
		     Enqueue(&hospitals, &pat[2]);
	     }
	     if ((Front(&female_recipients) != NULL) && (Front(&female_donors) != NULL) && (Front(&hospitals) != NULL)) { 
			  char *donor = Dequeue(&female_donors);
			  char *recip = Dequeue(&female_recipients);
			  char *hosp = Dequeue(&hospitals);
			  printf("MATCH: %s donates to %s at hospital %s\n",donor, recip, hosp);
		     }
	     else if ((Front(&male_recipients) != NULL) && (Front(&male_donors) != NULL) && (Front(&hospitals) != NULL)) {
			  char *donor = Dequeue(&male_donors);
			  char *recip = Dequeue(&male_recipients);
			  char *hosp = Dequeue(&hospitals);
			  printf("MATCH: %s donates to %s at hospital %s\n",donor,recip,hosp);
		     }     
	     
    }

    PrettyPrintQueue(&female_donors, "female donors");
    PrettyPrintQueue(&female_recipients, "female recipients");
    PrettyPrintQueue(&male_donors, "male donors");
    PrettyPrintQueue(&male_recipients, "male recipients");
    PrettyPrintQueue(&hospitals, "hospitals");
}
