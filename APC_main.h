#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef enum{
      success,
      failure,
}Status;

typedef struct {
      char *op1;
      char* op2;
      char operator;
      char *result_array;
      int op1_neg_flag;
      int op2_neg_flag;
}calculator;

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;


Status validate_arguments(char *argv[],calculator* cal);
Status create_dll_nodes_operands(char op[],Dlist **head,Dlist** tail,int start);
Status perform_operation(calculator* cal);
Status dl_insert_first(Dlist **head, Dlist **tail, int data);
Status dl_insert_last(Dlist **head, Dlist **tail, int data);
void reset_list(Dlist **head, Dlist **tail);
Status addition( Dlist** tail1,Dlist** tail2,Dlist** headR,Dlist** tailR);
Status subtraction( Dlist** tail1,Dlist** tail2,Dlist** headR,Dlist** tailR);
Status multiplication(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR);
Status division(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR);
int compare_lists(Dlist *tail1, Dlist *tail2);
int get_length(Dlist *head);