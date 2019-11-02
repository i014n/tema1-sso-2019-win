#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"compare.h"
#define BUFFER_SIZE 20000
#define BUFFER_READ 2
/*Queue operation code*/
#define START_OP_CODE 0
#define INSERT_OP_CODE (START_OP_CODE+1)
#define TOP_OP_CODE (START_OP_CODE+2)
#define POP_OP_CODE (START_OP_CODE+3)
#define UNDEFINED_OP_CODE 9999
#define MMIN_PRIORITY 1
#define ERROR_ALLOCATION "Error Allocation"
#define ERROR_OPENING_FILE -1
#define ERROR_MALLOC 12

//TO DO: Define delimiers 
static const char tokens[] = " ";

/*Define data structure for priority queue*/
typedef struct _priority_queue {
	/*String should be dynamically allocate*/
	char *String;
	int priority;
	struct _priority_queue *next;

} priority_queue;

/*define first and only elemnt of queue*/
static priority_queue *root;


/*TO DO3: Create proper functions for allocate/deallocate*/
/*queue objects and perform a clean exit, in case malloc*/
/*cannot allocate elemets. */

/*Forward definiton of function specialised in deallocate memory*/
void clean_memory(void);



/*TO DO4: Create a function to return exit code 12*/
/*Represend malloc failure exit code*/
void Safe_Exit(void *obj, int rCode)
{
	/*before deallocation check valability*/
	if (obj == NULL) {
		/* before exiting, deallocate heap memory used;*/
		clean_memory();
		exit(rCode);
	}
};


/*TO DO4: Allocate space for string*/
/*and check for value returned*/
void queue_alloc(priority_queue **bufer, int string_size)
{
	*bufer = (priority_queue *)malloc(sizeof(priority_queue));
	Safe_Exit(*bufer, ERROR_MALLOC);

	(*bufer)->String = (char *)malloc(BUFFER_SIZE * sizeof(char));
	Safe_Exit((*bufer)->String, ERROR_MALLOC);
	(*bufer)->next = NULL;
	(*bufer)->priority = MMIN_PRIORITY;

};
/*TO DO5: Deallocate elements*/
void my_free(priority_queue **buffer)
{
	/*Check before deallocate memory*/
	if ((*buffer)->String != NULL) {
		free((*buffer)->String);
		(*buffer)->String = NULL;
	}

	if ((*buffer) != NULL) {
		free(*buffer);
		(*buffer) = NULL;
	}
};

/* #pragma endregion*/

/* #pragma region COADA_PRIORITATI*/

/*test if any operations is valid and return code*/
int get_operation_code(char *command)
{
	char *command2 = (char *)malloc(BUFFER_SIZE * sizeof(char));
	Safe_Exit(command2, ERROR_MALLOC);
	
	strcpy(command2, command);
	/*define and initialised returned code*/
	int cod = UNDEFINED_OP_CODE;
	char *operation = strtok(command2, tokens);
	char *check = strtok(NULL, tokens);
	/*check if is a string and it is not empty*/
	if (operation != NULL) {
		if (strcmp("insert", operation) == 0)
			cod = INSERT_OP_CODE;
		if (strcmp("top", operation) == 0 && check == NULL)
			cod = TOP_OP_CODE;
		if (strcmp("pop", operation) == 0 && check == NULL)
			cod = POP_OP_CODE;
	}

	/*Deallocation*/
	free(command2);
	command2 = NULL;
	return cod;

};
/*TO DO:Implement a copy function for queue element*/
void duplicate_element(priority_queue **destination,
						 const priority_queue *source)
{
	/*Copy element from destination to source. Be careful of pointers.*/
	strcpy((*destination)->String, source->String);
	(*destination)->priority = source->priority;
};

/*TO DO:Make space for new element with big priority*/

void move_to_right(priority_queue **Start, char *name, int priority)
{
	
	priority_queue *tmp, *tmp_next;
	/*Make space for intermediate element neccesarly for swap*/
	queue_alloc(&tmp, BUFFER_SIZE);
	queue_alloc(&tmp_next, BUFFER_SIZE);
	duplicate_element(&tmp, *Start);
	priority_queue *pMove = *Start;

	strcpy(pMove->String, name);
	pMove->priority = priority;
	int change = 0;
	/*Find firt element with less priority*/
	while (pMove->next != NULL) {
		change = 1;
		/*Save element for swap*/
		duplicate_element(&tmp_next, pMove->next);
		pMove = pMove->next;
		duplicate_element(&pMove, tmp);
		duplicate_element(&tmp, tmp_next);
	}
	/*Initialised next element */
	queue_alloc(&pMove->next, BUFFER_SIZE);
	pMove = pMove->next;
	pMove->next = NULL;

	if (!change)
		duplicate_element(&tmp_next, tmp);
	/*Insert new element and shit the rest to right*/
	duplicate_element(&pMove, tmp_next);
	my_free(&tmp_next);
	my_free(&tmp);
};


/*DO TO: Insert name and priority*/
void insert(char *name, int priority)
{
	/*Create fisrt element */
	if (root == NULL) {
		queue_alloc(&root, BUFFER_SIZE);
		strcpy(root->String, name);
		root->priority = priority;
	} else {
		priority_queue *pMove = root;
	/*Find the element with low priority*/
		while (pMove->next != NULL &&
					compare(pMove->priority, priority) > 0)
			pMove = pMove->next;
		if (compare(pMove->priority, priority) > 0) {
			/*If new element has the lowest priority, insert at end:*/
			queue_alloc(&pMove->next, BUFFER_SIZE);
			pMove = pMove->next;
			strcpy(pMove->String, name);
			pMove->priority = priority;
			pMove->next = NULL;

		} else
			move_to_right(&pMove, name, priority);


	}
};



/*TO DO: pop, Eliminate first element*/
void pop(void)
{	if (root != NULL) {
	priority_queue *remove = root;
	/*Move to next element */
	root = root->next;
	my_free(&remove);
	}
};


/*TO DO: Implement top function*/
char *top(void)
{
	size_t Size = 0;

	char *rBuff = (char *)malloc(2 * sizeof(char) * BUFFER_SIZE);

	Safe_Exit(rBuff, ERROR_MALLOC);
	Size = sizeof(rBuff);
	memset(rBuff, 0, Size);
	/*Check if queue is empty*/
	if (root != NULL)
		strcpy(rBuff, root->String);
	else
		strcpy(rBuff, "");
	return rBuff;
};

int prepare_insert(const char *command)
{
	char *command2 = (char *)malloc(BUFFER_SIZE * sizeof(char));

	Safe_Exit(command2, ERROR_MALLOC);
	strcpy(command2, command);
	strtok(command2, tokens);
	/*Break string for checking operation valability*/
	char *name = strtok(NULL, tokens);
	char *s_priority = strtok(NULL, tokens);
	char *end = strtok(NULL, tokens);
	int priority = MMIN_PRIORITY;

if (s_priority != NULL)
	priority = atoi(s_priority);
else
	end = "skip";
/*If operation is insert check if is something after priority*/
	if (end == NULL)
		insert(name, priority);
/*Deallocate memory*/
	free(command2);
	return 0;
};
/*Checking for operation*/
void operation_priority_queue(char *command)
{
	unsigned int op_code = get_operation_code(command);
	char *tmp = NULL;
	/*Based on code returned there are 3 cases:*/
	switch (op_code) {
	case INSERT_OP_CODE:
		prepare_insert(command);
		break;
	case TOP_OP_CODE:
		tmp = top();
		printf("%s\n", tmp);
		/*Deallocate memory beacuse type of function top(char*) */
		free(tmp);
		tmp = NULL;
		break;
	case POP_OP_CODE:
		pop();
		break;
	default:
		break;
	}

};

void clean_memory(void)
{  /*Deallocate string and element*/
	if (root != NULL) {
		while (root->next != NULL) {
			priority_queue *tmp = root;

			root = root->next;
			my_free(&tmp);
		}
		my_free(&root);
	}
};
/*#pragma endregion*/

void read_command(FILE *fin)
{
	size_t Size = 0;
	char separators[] = "\n";
	char *outBuffer = (char *)malloc(sizeof(char) * BUFFER_READ);

	Safe_Exit(outBuffer, ERROR_MALLOC);
	char *command = (char *)malloc(2 * BUFFER_SIZE * sizeof(char));

	Safe_Exit(command, ERROR_MALLOC);
	Size = sizeof(command);
	memset(command, 0, Size);
	do {
		char c = fgetc(fin);
		/*Read chactacter with chactacter and make command*/
		outBuffer[0] = c;
		outBuffer[1] = '\0';
		if (strchr(separators, outBuffer[strlen(outBuffer) - 1]) != 0) {
			operation_priority_queue(command);
			Size = sizeof(command);
			memset(command, 0, Size);
		} else
			strcat(command, outBuffer);
	if (c == EOF)
		break;

	} while (!feof(fin));
	/*Deallocation*/
	free(command);
	command = NULL;
	/*Deallocation*/
	free(outBuffer);
	outBuffer = NULL;
};


int OpenFiles(char *fileIn)

{  /*Open file */
	FILE *fin = fopen(fileIn, "r");
	/*check if file exist*/
	if (fin == NULL)
		return ERROR_OPENING_FILE;
	read_command(fin);
	/*Close file*/
	fclose(fin);

	return 0;
};


int main(int argc, char *argv[])
{


	if (argc > 1)
		for (int i = 1; i < argc; i++)
			OpenFiles(argv[i]);
	else
		read_command(stdin);
	clean_memory();
return 0;
}
