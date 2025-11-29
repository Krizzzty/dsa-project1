#include "APC_main.h"

Status validate_arguments(char *argv[], calculator *cal)
{
    char operators[] = "+-*/";
    if (argv[1][0] == '-' || argv[1][0] == '+' || isdigit(argv[1][0]))
    {
        if (argv[1][0] == '-')
        {
            cal->op1_neg_flag = 1;
        }
        else
        {
            cal->op1_neg_flag = 0;
        }
        for (int i = 1; argv[1][i] != '\0'; i++)
        {
            if ((!isdigit(argv[1][i])))
            {
                return failure;
            }
        }
    }
    cal->op1 = malloc(sizeof(char) * strlen(argv[1]) + 1);
    strcpy(cal->op1, argv[1]);
    if (argv[3][0] == '-' || argv[3][0] == '+' || isdigit(argv[3][0]))
    {
        if (argv[3][0] == '-')
        {
            cal->op2_neg_flag = 1;
        }
        else
        {
            cal->op2_neg_flag = 0;
        }
        for (int i = 1; argv[3][i] != '\0'; i++)
        {
            if ((!isdigit(argv[3][i])))
            {
                return failure;
            }
        }
    }
    cal->op2 = malloc(sizeof(char) * strlen(argv[3]) + 1);
    strcpy(cal->op2, argv[3]);
    if (strlen(argv[2]) == 1 && strchr(operators, argv[2][0]))
    {
        cal->operator= argv[2][0];
        return success;
    }
    return failure;
}
Status dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    new_node->data = data;
    if (*head == NULL)
    {
        *head = *tail = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
        return success;
    }
    new_node->next = *head;
    new_node->prev = NULL;
    (*head)->prev = new_node;
    *head = new_node;
    return success;
}
void print_list(Dlist *head)
{
    /* Cheking the list is empty or not */
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        printf("Head -> ");
        while (head)
        {
            /* Printing the list */
            printf("%d <-", head->data);

            /* Travering in forward direction */
            head = head->next;
            if (head)
                printf("> ");
        }
        printf(" Tail\n");
    }
}
void strrev(char arr[])
{
    int start = 0;
    int end = strlen(arr) - 1;
    while (start < end)
    {
        char temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}
Status create_dll_nodes_operands(char op[], Dlist **head, Dlist **tail,int start)
{
    int count = 0;
    int len;
    char temp[4] = {0};
    int flag = 0;

    for (int i = strlen(op) - 1; i >= start; i--)
    {
        int num_digit = 0;
        int zeros;
        temp[count++] = op[i];
        if (count == 4 || i == start)
        {
            count = 0;
            strrev(temp);
            if (dl_insert_first(head, tail, atoi(temp)) == failure)
            {
                printf("INFO : Insertion Failure\n");
                return failure;
            }
            memset(temp, '\0', sizeof(temp));
        }
    }
    print_list(*head);
    return success;
}

Status addition(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int d1 = temp1->data, d2 = temp2->data;
    int carry = 0;
    while (temp1 != NULL || temp2 != NULL)
    {
        int result = d1 + d2 + carry;
        carry = result / 10000;
        result = result % 10000;
        int num = result;
        int num_digit = 0;

        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
            if (temp1 != NULL)
                d1 = temp1->data;
            else
                d1 = 0;
        }

        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
            if (temp2 != NULL)
                d2 = temp2->data;
            else
                d2 = 0;
        }
        if (num == 0)
        {
            num_digit = 1;
        }
        else
        {
            while (num > 0)
            {
                num_digit++;
                num = num / 10;
            }
        }

        dl_insert_first(headR, tailR, result);
        if (temp1 != NULL || temp2 != NULL)
        {
            for (int i = 0; i < (4 - num_digit); i++)
            {
                dl_insert_first(headR, tailR, 0);
            }
        }
    }
    if (carry != 0)
    {
        dl_insert_first(headR, tailR, 0);
    }
    // print_list(headR);
}
Status subtraction(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int d1 = temp1->data, d2 = temp2->data;
    int result,digit_count=4;
    while (temp1 != NULL || temp2 != NULL)
    {
        for(int i=0;i<4-digit_count;i++){
            dl_insert_first(headR, tailR, 0);
        }
        if (d1 < d2)
        {
            if(temp1->prev){
            temp1->prev->data--;
            result = d1 + 10000 - d2;
            }
        }
        else
        {
            result = d1 - d2;
        }
        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
            if (temp1 != NULL)
                d1 = temp1->data;
            else
                d1 = 0;
        }

        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
            if (temp2 != NULL)
                d2 = temp2->data;
            else
                d2 = 0;
        }
        dl_insert_first(headR, tailR, result);
        digit_count=1;
        while(result>0){
            result/=10;
            digit_count++;
        }
    }
}
void reset_list(Dlist **head, Dlist **tail)
{
    Dlist *current = *head;
    while (current != NULL)
    {
        Dlist *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    *tail = NULL;
}

Status dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    new_node->data = data;
    if (*head == NULL)
    {
        *head = *tail = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
        return success;
    }
    (*tail)->next = new_node;
    new_node->prev = *tail;
    new_node->next = NULL;
    *tail = new_node;
    return success;
}
int get_length(Dlist *head)
{
    if (!head)
        return 0;

    int length = 0;
    int is_first_node = 1;

    while (head)
    {
        if (is_first_node)
        {
            // First node: 1 to 4 digits
            int digits = 0;
            int temp = head->data;
            if (temp == 0)
                digits = 1; // Special case for "0"
            else
            {
                while (temp > 0)
                {
                    digits++;
                    temp /= 10;
                }
            }
            length += digits;
            is_first_node = 0; // Subsequent nodes will have fixed digits
        }
        else
        {
            // Remaining nodes: Always 4 digits
            length += 4;
        }

        head = head->next;
    }

    return length;
}

int compare_lists(Dlist *tail1, Dlist *tail2)
{
    // Find the head node for both lists by traversing to the first node
    Dlist *head1 = tail1;
    Dlist *head2 = tail2;

    while (head1 && head1->prev) // Traverse back to the head for the first list
        head1 = head1->prev;

    while (head2 && head2->prev) // Traverse back to the head for the second list
        head2 = head2->prev;

    // Compare lengths
    int len1 = get_length(head1);
    int len2 = get_length(head2);
    if (len1 != len2)
        return len1 - len2;

    // Compare digit by digit from the head node
    while (head1 && head2)
    {
        if (head1->data != head2->data)
            return head1->data - head2->data;

        head1 = head1->next;
        head2 = head2->next;
    }
    return 0; // Both lists are equal
}

Status division(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int count = 0;
    Dlist *temp1_res = *tail1;
    Dlist *temp2_res_head = NULL;
    Dlist *temp2_res_tail = NULL;
    while (compare_lists(temp1_res, *tail2) >= 0)
    {
        subtraction(&temp1_res, tail2, &temp2_res_head, &temp2_res_tail);
        temp1_res = temp2_res_tail;
        temp2_res_head = NULL;
        temp2_res_tail = NULL;
        count++;
    }
    printf("%d", count);
}
Status multiplication(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp2 = *tail2;
    int shift = 0;

    // Initialize the result list
    *headR = NULL;
    *tailR = NULL;

    while (temp2)
    {
        Dlist *temp1 = *tail1, *partial_result = NULL, *partial_tail = NULL;
        int carry = 0;

        // Calculate the partial product for the current node of tail2
        while (temp1)
        {
            long long product = (long long)temp1->data * temp2->data + carry;
            carry = product / 10000;
            product %= 10000;

            if (dl_insert_first(&partial_result, &partial_tail, (int)product) == failure)
                return failure;

            temp1 = temp1->prev;
        }

        // Add remaining carry, if any
        if (carry)
        {
            if (dl_insert_first(&partial_result, &partial_tail, carry) == failure)
                return failure;
        }

        // Add trailing zeros for the current shift
        for (int i = 0; i < shift; i++)
        {
            if (dl_insert_last(&partial_result, &partial_tail, 0) == failure)
                return failure;
        }

        // Add the partial result to the final result
        if (*headR == NULL) // First partial result
        {
            *headR = partial_result;
            *tailR = partial_tail;
        }
        else
        {
            // Add current partial result to the accumulated result
            Dlist *temp_headR = NULL, *temp_tailR = NULL;
            if (addition(tailR, &partial_tail, &temp_headR, &temp_tailR) == failure)
                return failure;

            // Update the result list
            reset_list(headR, tailR); // Free previous result
            *headR = temp_headR;
            *tailR = temp_tailR;
        }

        temp2 = temp2->prev; // Move to the next node in tail2
        shift++;             // Increment shift for trailing zeros
    }
   

   // print_list(*headR); // Optional: detailed list printout
    return success;
}

Status perform_operation(calculator *cal)
{
    Dlist *head1 = NULL; // initialize the header to NULL
    Dlist *tail1 = NULL;
    Dlist *head2 = NULL; // initialize the header to NULL
    Dlist *tail2 = NULL;
    Dlist *headR = NULL; // initialize the header to NULL
    Dlist *tailR = NULL;
    Dlist *temp;
    printf("Double linked list for operand 1 : ");
    if (create_dll_nodes_operands(cal->op1, &head1, &tail1,cal->op1_neg_flag) == success)
    {
        printf("Double linked list for operand 2 : ");
        if (create_dll_nodes_operands(cal->op2, &head2, &tail2,cal->op2_neg_flag) == success)
        {
            switch (cal->operator)
            {
            case '+':
                printf("Result \n%s + %s = ", cal->op1, cal->op2);
                //if either of the operands are negative
                if(cal->op1_neg_flag==1 ^ cal->op2_neg_flag==1){
                   if(compare_lists(tail1,tail2)>=0){
                     subtraction(&tail1, &tail2, &headR, &tailR);
                     if(cal->op1_neg_flag==1){
                        printf("-");
                     }
                   }
                   else{
                     subtraction(&tail2, &tail1, &headR, &tailR);
                     if(cal->op2_neg_flag==1){
                        printf("-");
                     }
                   }
                }
                //if both are postive or both are negative
                else{
                    addition(&tail1, &tail2, &headR, &tailR);
                }
                //if both are negative,add '-' sign
                if(cal->op1_neg_flag==1 && cal->op2_neg_flag==1){
                    printf("-");
                }
                break;
            case '-':
                printf("Result \n%s - %s = ", cal->op1, cal->op2);
                 //if either of the operands are negative
                if(cal->op1_neg_flag==1 ^ cal->op2_neg_flag==1){
                    addition(&tail1, &tail2, &headR, &tailR);
                    if(cal->op1_neg_flag==1){
                        printf("-");
                    }
                }
                //if both are negative
                else if(cal->op1_neg_flag==1 && cal->op2_neg_flag==1){
                    if(compare_lists(tail1,tail2)>=0){
                     subtraction(&tail1, &tail2, &headR, &tailR);
                     if(cal->op1_neg_flag==1){
                        printf("-");
                      }
                   }
                   else{
                     subtraction(&tail2, &tail1, &headR, &tailR);
                   }
                }
                //if both are positive
                else{
                   if(compare_lists(tail1,tail2)>=0){
                     subtraction(&tail1, &tail2, &headR, &tailR);
                     
                   }
                   else{
                     subtraction(&tail2, &tail1, &headR, &tailR);
                     printf("-");
                   }
                }
                break;
            case '*':
                printf("Result \n%s * %s = ", cal->op1, cal->op2);
                if(cal->op1_neg_flag==1 ^ cal->op2_neg_flag==1){
                    printf("-");
                }
                multiplication(&tail1, &tail2, &headR, &tailR);
                break;
            case '/':
                printf("Result \n%s / %s = ", cal->op1, cal->op2);
                if(compare_lists(tail1,tail2)<0){
                    dl_insert_first(&headR,&tailR,0);
                    break;
                }
                else if(cal->op1_neg_flag==1 ^ cal->op2_neg_flag==1){
                    printf("-");
                }
                division(&tail1, &tail2, &headR, &tailR);
                break;
            }
            free(cal->op1);
            free(cal->op2);
            temp = headR;
                while (temp != NULL)
                {
                    printf("%d", temp->data);
                    temp = temp->next;
                }
                printf("\n");
            return success;
        }
        else
        {
            return failure;
        }
    }
    else
    {
        return failure;
    }
}