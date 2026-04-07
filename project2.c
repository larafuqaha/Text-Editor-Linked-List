/*
Name: Lara Foqaha
ID: 1220071
Section: 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//normal linked list implementation to load input file
struct node;
typedef struct node* ptrNode;
struct node 
{
    char str[50];
    ptrNode next;
};
typedef ptrNode linkedList;
linkedList L; //global linked list

//stack implementation 
struct stackNode;
typedef struct stackNode* ptrStackNode; //ptr to stack node
//same struct for undo and redo stacks
struct stackNode 
{
    ptrStackNode next; //ptr to next stack node
    int operation; // 0 for inset and 1 for delete
    int index;
    char str[50]; 
};
typedef ptrStackNode Stack;
// declaring global undo and redo stacks
Stack undoStack; 
Stack redoStack;

//queue implementation
struct queueNode;
typedef struct queueNode* ptrQueueNode; //ptr to queue node
struct  queueNode
{
    ptrQueueNode next; //ptr to next queue node
    char str[50]; 
};
typedef ptrQueueNode Queue;
Queue mainQueue;

void menu ();
linkedList createList();
void loadFile();
void insertLast(linkedList L, char word[]);
void printLoadedText();
Stack createStack();
Queue createQueue();
void push (Stack S, ptrStackNode pushedNode);
ptrStackNode top (Stack S);
void pop (Stack S);
void deleteStack (Stack S);
void enqueue(Queue Q, char word[]);
char* dequeue (Queue Q);
void insertString();
void insertBeginning(linkedList L, char word[], int counter);
void insertMiddle(linkedList L, char word[], ptrNode prev);
ptrNode findWord(linkedList L, char word[]);
int findIndex(linkedList L, char word[]);
void deleteString();
ptrNode findPrevious(linkedList L, ptrNode p);
void deleteWithIndex (linkedList L, int Index);
void undo();
void insertWithIndex (linkedList L, char word[], int Index);
void redo ();
void printStacks ();
void saveToFile ();
void deletelinkedList (linkedList L);
void deleteQueue (Queue Q);

int main()
{
    //creating all the needed lists (they are all global)
    L = createList(); 
    mainQueue = createQueue();
    undoStack = createStack();
    redoStack = createStack();
    int option, isLoaded =0, isInserted =0, isDeleted =0, isUndo =0, isPrinted =0;

    do 
    {
        menu();
        scanf("%d", &option);
        getchar();
        printf("\n");

        switch (option)
        {
        case 1:
            loadFile();
            isLoaded = 1; //now the other options can work
            break;
        case 2:
            if (isLoaded == 1)
            {
                if (isPrinted == 0)
                {
                    printLoadedText();
                    isPrinted =1;
                }
            else 
                printf("Loaded text has changed.\n\n");
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 3:
            if (isLoaded == 1)
            {
                insertString();
                isInserted =1;
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 4:
            if (isLoaded == 1)
            {
                deleteString();
                isDeleted = 1;
            }
            else
                printf("Please load the file first.\n\n");
            break;

        case 5:
            if (isLoaded == 1)
            {
                if (isDeleted == 1 || isInserted == 1) //if the user edited the text, they could undo
                    {
                        undo();
                        isUndo =1; //if the user made an undo, they can redo
                    }
                else 
                    printf("You didn't edit the text to undo it.\n\n"); //can't undo with no edit to the text
            }
                
            else 
                printf("Please load the file first.\n\n");
            break;

        case 6:
            if (isLoaded == 1)
            {
                if (isUndo == 1)
                    redo();
                else 
                    printf("You can't redo what you didn't undo.\n\n");
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 7:
            if(isLoaded == 1)
                printStacks();
            else 
                printf("Please load the file first.\n\n");
            break;

        case 8:
            if (isLoaded == 1)
                saveToFile();
            else 
                printf("Please load the file first.\n\n");
            break;

        case 9: 
            printf("Exited.\n");
            break;

        default: printf("No such option. Try again.\n\n");
            break;
        }
    }
    while (option != 9);

    deleteStack(undoStack);
    deleteStack(redoStack);
    deletelinkedList(L);
    deleteQueue(mainQueue);

    return 0;
}

void menu() //to display main menu
{
    printf("Choose an option from 1 to 9.\n");
    printf("1- Load the input file.\n");
    printf("2- Print the loaded text.\n");
    printf("3- Insert strings to the text.\n");
    printf("4- Remove strings from the text.\n");
    printf("5- Perform undo operation.\n");
    printf("6- Perform redo operation.\n");
    printf("7- Print the undo stack and the redo stack.\n");
    printf("8- Save the updated text to the output file.\n");
    printf("9- Exit.\n");
}

Stack createStack() //creates an empty stack
{
    Stack S = (Stack)malloc(sizeof(struct stackNode));
    if (S == NULL)
        printf("Out of memory.\n");
    S->next = NULL;
    return S;
}

Queue createQueue() // creates an empty queue
{
    Queue Q = (Queue)malloc(sizeof(struct queueNode));
    if (Q == NULL)
        printf("Out of memory.\n");
    Q->next = NULL;
    return Q;
}

void loadFile() //to load input file
{
    FILE* f = fopen("input.txt","r");
    if (f == NULL)
    {
        printf("Failed to open the file.\n\n");
        return;
    }
    printf("\nLoading the input file...\n\n");

    char line[700];
    while (fgets(line,700,f) != NULL) //reading the file until the end of it
    {
        char *word;
        word = strtok(line," "); //splitting the first word
        while (word != NULL)
        {
            insertLast(L,word); //inserting to the global linked list L
            word = strtok(NULL," "); //continue splitting the line from where it stopped 
        }
    }
    fclose(f);
    printf("Input file loaded.\n\n");

}

void printLoadedText() //prints the text in the global linked list L
{
    if (L->next == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    ptrNode tempNode = L->next;
    while(tempNode != NULL)
    {
        printf("%s",tempNode->str);
        printf(" "); //printing a space after each word
        tempNode = tempNode->next; //traversing through the list
    }

    printf("\n\n");
    
}

linkedList createList() //creates an empty linked list
{
    linkedList L = (linkedList)malloc(sizeof(struct node));
    L->next = NULL;
    return L;
}

void insertLast(linkedList L, char word[]) //to insert at the last of the text (linked list)
{
    if (L == NULL)
    {
        printf("List not found.\n");
        return;
    }

    //creating a new node for the added text
    ptrNode newNode = (ptrNode)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Out of memory.\n");
        return;
    }
    strcpy(newNode->str , word);

    if (L->next == NULL) // if the list is empty, add the new node after the head
    {
        L->next = newNode;
        newNode->next = NULL;
    }
    else //traverse through the list until the last node and isert after it
    {
        ptrNode last = L;
        while (last->next != NULL) //finding the last node to insert after it
            last = last->next;
        last->next = newNode;
        newNode->next = NULL;
    }
}

void push (Stack S, ptrStackNode pushedNode) // adds the new node after the head
{
    if (S == NULL)
    {
        printf("Stack not found.\n");
        return;
    }

    if(pushedNode == NULL)
    {
        printf("Pushing a NULL node.\n");
        return;
    }

    pushedNode->next = S->next;
    S->next = pushedNode;
}

ptrStackNode top (Stack S) // returns the top node without deleting it
{
    if (S == NULL)
    {
        printf("Stack not found.\n");
        return NULL;
    }

    if (S->next == NULL)
        return NULL;

    return S->next; //return first node after the head
}

void pop (Stack S) 
{
    if (S == NULL)
    {
        printf("Stack not found.\n");
        return;
    }

    if (S->next == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    ptrStackNode top = S->next;
    S->next = top->next; 
    //free(top);
}

void deleteStack (Stack S) 
{
    if (S == NULL)
    {
        printf("Stack not founf.\n");
        return;
    }
    ptrStackNode topNode = top(S);
    while (topNode != NULL) //while the stack is not empty, pop its elements
        {
            free(topNode);
            pop(S);
            topNode = top(S);
        }
    free(S); //delete the head
}

void enqueue(Queue Q, char word[]) //it inserts at the last of queue
{
    if (Q == NULL)
    {
        printf("Queue not found.\n");
        return;
    }

    //creating a new queue node to insert it at the end of the queue list
    ptrQueueNode addedNode = (ptrQueueNode)malloc(sizeof(struct queueNode));
    if (addedNode == NULL)
    {
        printf("Out of memory.\n");
        return;
    }
    strcpy(addedNode->str, word);

    if (Q->next == NULL) //if the list is empty, add the new node after the head
    {
        addedNode->next = NULL;
        Q->next = addedNode;
    }
    else //trverse throught the list and add the new node after the last one
    {
        ptrQueueNode last = Q;
        while (last->next != NULL) //to find the last node to enqueue after it
            last = last->next;
        addedNode->next = NULL;
        last->next = addedNode;
    }
}

char* dequeue (Queue Q) //FIFO returns the word in the first node of the queue
{
    if (Q == NULL)
    {
        printf("Queue not found.\n");
        return NULL;
    }

    if (Q->next == NULL) //if the list is empty
    {
        printf("The queue is empty.\n");
        return NULL;
    }

    ptrQueueNode front = Q->next;
    //copying the string in front node into word 
    char* word = strdup(front->str); // same thing as allocating memory (malloc) for word to have the same size as front->st,
                                    // then using strcpy to copy contents into word

    if (front->next == NULL) //if there is only one node
        {
            Q->next = NULL;
            free(front);
        }
    else 
        {
            Q->next = front->next;
            free(front);
        }
    
    return word; 
}

void insertString() //for option 3
{
    printf("Enter the string you want to insert.\n\n");
    char line[500];
    gets(line);

    char* word;
    word = strtok(line," "); 
    while (word != NULL) //inserting each word to the queue
    {
        enqueue(mainQueue, word);
        word = strtok(NULL," ");
    }

    printf("\nWhere do you want to insert the string? (Choose an option)\n");
    printf("1- End of text\t2- Beginning of text\t3-Middle of text\n\n");
    int op;
    scanf("%d",&op);
    getchar();
    printf("\n");

    int isInserted =0;

    //for insering in the middle
    int found =0; 
    ptrNode prev; //used in case 3 inside the switch
    if (op == 3)
    {
        printf("Enter the word to insert your string after it.\n\n");
        char enteredWord[50];
        scanf("%s",enteredWord);
        getchar();
        prev = findWord(L,enteredWord); //finding the previous node to insert after it
        if (prev == NULL)
            printf("Word %s does not exist in the text.\n\n",enteredWord);
        else 
            found =1; //finding the word
    }

    int counter=0; //used for inserting at the beginning and middle of the text

    while (mainQueue->next != NULL)
    {
        char* word2 = dequeue(mainQueue);
        ptrStackNode Snode = (ptrStackNode)malloc(sizeof(struct stackNode)); // to push to undo stack
        if (Snode == NULL)
        {
            printf("Out of memory.\n");
            continue;
        }

        strcpy(Snode->str, word2);
        Snode->operation = 0; // 0 for inserting
            
        switch (op)
        {
        case 1: 
            insertLast(L, word2); // to insert the string to the end of the initial text which is in the file
            Snode->index = -1; // -1 for inserting at last
        break;

        case 2:
            counter++; //counts the number of words (nodes) taken from the user
            insertBeginning(L,word2,counter); //to insert at the beginning of the initial text
            Snode->index = findIndex(L,word2);
        break;

        case 3:
            if (found == 1)
            {
                insertMiddle(L,word2,prev); //inserting at the middle of the text after the node prev
                prev = prev->next; // changing prev to the next node to insert after it
                Snode->index = findIndex(L,word2);
            }
            break;
        
        default: 
        printf("No such option.\n\n");
        free(Snode); // in case it is created first then not used
            return; // I added this /////////////////////////////////////////////////////////////////////////////////////////////////////
        }

        push(undoStack, Snode); //pushing the inserted word to undo stack
        isInserted = 1;
    }

    if (isInserted == 1)
    {
        printf("String has been inserted, updated text is:\n\n", line);
        printLoadedText();

    }  
}

int findIndex(linkedList L, char word[]) //to find the index of the first occurance of the word
{
    // first checking if the word is in the list or not
    ptrNode p = L->next;
    while (p != NULL)
    {
        if (strcmp(p->str, word) == 0) 
            break; //the word is found so break this loop
        p = p->next;
        if (p == NULL)
            return -2; // word not found in the list
    }
    
    //if the word is in the list, find its index (index of first letter of the word)
    int index=0;
    ptrNode temp = L->next;
    while(temp != NULL)
    {
        if (strcmp(temp->str,word) == 0)
            break;
        
        index = index + strlen(temp->str) +1; //+1 for the space character between words.
        temp = temp->next; //traversing through the list
    }
    return index;
}

void insertBeginning (linkedList L, char word[], int counter) //to insert at the beginning of the text for option 3
{
    if (L == NULL)
    {
        printf("List not found.\n");
        return;
    }
    
    //creating a new node with the word to insert it
    ptrNode addedNode = (ptrNode)malloc(sizeof(struct node));
    if (addedNode == NULL)
    {
        printf("out of memory.\n");
        return;
    }
    strcpy(addedNode->str, word);

    if (counter == 1) //if it is the first word, add it after the head
    {
        ptrNode temp = L->next;
        L->next = addedNode;
        addedNode->next = temp;
    }
    else // adding the other subsequent words after each other 
    {
        ptrNode prev = L; // to find the last recently added node (from the user) to insert after it
        for (int i=1; i<counter; i++) // example: if the added word is the fourth, it will be inserted after 3 previous words
            prev = prev->next;
        ptrNode temp = prev->next; // to not lose the first node from initial text, to insert before it
        prev->next = addedNode;
        addedNode-> next = temp;
    }
}

void insertMiddle(linkedList L, char word[], ptrNode prev) //to insert at the middle of the text (after prev word)
{
    if (L == NULL)
    {
        printf("List not found.\n");
        return;
    }

    //creating a new node with the word to insert it
    ptrNode addedNode = (ptrNode)malloc(sizeof(struct node));
    if (addedNode == NULL)
    {
        printf("Out of memory.\n");
        return;
    }

    strcpy(addedNode->str, word);

    ptrNode temp = prev->next; //to not lose the rest of the text
    prev->next = addedNode;
    addedNode->next = temp; //re-attaching to the rest of the list
}

ptrNode findWord(linkedList L, char word[]) //to find a word in the text and return its node
{
    ptrNode temp = L->next; 
    while (temp != NULL) 
        {
            if (strcmp(temp->str , word) == 0)
                    break; 
            temp = temp->next; //traversing untill it is found or the end of the list
        }
    
    return temp; //returns NULL if not found
}

void deleteString() 
{
    printf("Enter the string to delete. If it ends with a period '.' or any punctuation, please enter them as well :)\n\n");
    char line[500];
    gets(line);

    char* word = strtok(line," ");

    while (word != NULL)
    {
        int Index = findIndex(L, word); 
        if (Index == -2)
        {
            printf("Word not found.\n\n");
            return;
        }

        // creating stack node to push the word to undo stack
        ptrStackNode Snode = (ptrStackNode)malloc(sizeof(struct stackNode));
        if(Snode == NULL)
        {
            printf("Out of memory.\n");
            return;
        }

        Snode->operation = 1; //1 for deleting
        Snode->index = Index;
        strcpy(Snode->str, word);
        push(undoStack, Snode);

        ptrNode deletedNode = findWord(L, word);

        if (L->next == deletedNode) //if the deleted node is the first in the list
            L->next = deletedNode->next;
        else
        {
            ptrNode previousNode = findPrevious(L,deletedNode);
            previousNode->next = deletedNode->next;
        }
    
        free(deletedNode);

        word = strtok(NULL," ");
    }
    printf("String has been deleted, updated text is:\n\n");
    printLoadedText();
    
}

ptrNode findPrevious(linkedList L, ptrNode p) //to find the previuos node of a specific one
{
    if (L == NULL)
    {
        printf("List not found.\n");
        return NULL;
    }
    if (L->next == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }

    if (p == NULL)
    {
        printf("Node not found???!!!!!??.\n"); ///////////////////
        return NULL;
    }

    ptrNode temp = L;
    while (temp->next != NULL && temp->next != p) //traversing until it finds p as the next of temp (or until the next is NULL)
        temp = temp->next; 

    return temp;
}

void undo ()
{
    if (undoStack == NULL)  
    {   printf("Undo stack not found.\n");
        return;
    }
    if (undoStack->next == NULL)
    {
        printf("No more operations to undo.\n");
        return;
    }

    ptrStackNode topNode = top(undoStack); //we can only access top node
    if (topNode == NULL)
    {
        printf("Top node is NULL.\n");
        return;
    }
    pop(undoStack); //deleting from undo stack
    push(redoStack,topNode); //adding to redo stack

    if(topNode->operation == 0) // if it was an insert operation, when undo is done, delete the word
        deleteWithIndex(L, topNode->index);
    if (topNode->operation == 1) // if it was a delete operation, when undo is done, re add the node
        insertWithIndex(L,topNode->str,topNode->index);
    
    printLoadedText();
}

void deleteWithIndex (linkedList L, int Index)
{
    if (L==NULL)
    {
        printf("List not found.\n");
        return;
    }

    if (Index == -1)
    {
        ptrNode last = L;
        while(last->next != NULL) //finding the last node to delete since -1 means the node is the last in the list
            last = last->next;
        
        ptrNode prevNode = findPrevious(L,last);
        prevNode->next = NULL;
        free(last);
        return;
    }

    ptrNode temp = L->next;
    int index=0;
    while(temp != NULL)
    {
        if (index == Index)
            break;
        
        index = index + strlen(temp->str) + 1; //+1 for the space character between words.
        temp = temp->next;
    }

    if (L->next == temp) //if the deleted node is the first in the list
        L->next = temp->next;
        else
        {
            ptrNode previousNode = findPrevious(L,temp);
            previousNode->next = temp->next;
        }
    
        free(temp);
}

void insertWithIndex (linkedList L, char word[], int Index)
{
    if (L== NULL)
    {
        printf("List not found.\n");
        return;
    }

    //creating a new node to insert it in the list
    ptrNode newNode = (ptrNode)malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        printf("Out of memory.\n");
        return;
    }

    strcpy(newNode->str, word);

    //if the first word of the text was deleted, re-insert it after the head
    if (Index == 0)
    {
        newNode->next = L->next;
        L->next = newNode;
        return; 
    }
    
    // if the last word of the text was deleted, find the recent last node and re-insert after it
    if (Index == -1)
    {
        ptrNode last = L;
        while (last->next != NULL)
            last = last->next;
        last->next = newNode;
        newNode->next = NULL;
        return;
    }

    // if the deleted word was in the middle
    ptrNode temp = L->next;
    int index=0;
    while(temp->next != NULL)
    {
        if (index == Index)
            break;
        
        index = index + strlen(temp->str) + 1; // +1 for the space character between words -> to find the right insertion index
        temp = temp->next; //traversing through the linked lisr untill the index of the re-inserted word matches the index of the list words
    }

    //finding the previous node to re-insert after it
    ptrNode prevNode = findPrevious(L,temp);
    if (prevNode == NULL)
    {
        printf("prev not found.\n");
        return;
    }
    prevNode->next = newNode;
    newNode->next = temp;
}

void redo () 
{
    if (redoStack == NULL)  
    {   printf("Redo stack not found.\n");
        return;
    }
    if (redoStack->next == NULL)
    {
        printf("No operations left to redo.\n");
        return;
    }

    ptrStackNode topNode = top(redoStack); //the first node after the head
    if (topNode == NULL)
    {
        printf("Top node NULL."); 
        return;
    }

    pop(redoStack); //deleting from the undo stack
    push(undoStack,topNode); //adding to the redo stack

    if (topNode->operation == 0) // if it was insert operation, re-insert it again because undo deleted it
        insertWithIndex(L,topNode->str,topNode->index);
    if (topNode->operation == 1) // if it was delete operation, delete it again because undo inserted it
        deleteWithIndex(L, topNode->index);
    
    printLoadedText();

}

void printStacks () //prints the contents of the stacks without traversing
{
    //ctreating a temp stack to pop from original stack then print the popped element and then push back into original stack
    Stack tempStack = createStack();

    ptrStackNode topNodeS = top(undoStack); //we can only access top node
    if (topNodeS == NULL)
    {
        printf("Undo stack is empty.\n\n");
        return;
    }
    //printing the undo stack
    printf("Contents of undo stack:\n\n");
    while(topNodeS != NULL)
    {
        pop(undoStack); //popping the top node from undo stack
        printf("String: %s\tOperation: %d\tIndex: %d\n",topNodeS->str, topNodeS->operation, topNodeS->index); //printing top node's contents
        push(tempStack,topNodeS); //pushing top node to temp stack
        topNodeS = top(undoStack); //getting the top node again
    }

    //pushing temp stack elements back into undo stack to have the elements in the same order
    topNodeS = top(tempStack);
    while(topNodeS != NULL)
    {
        pop(tempStack);
        push(undoStack, topNodeS);
        topNodeS = top(tempStack);
    }

    printf("\n\n");
    printf("Contents of redo stack:\n\n");

    //printing the redo stack
    ptrStackNode topNodeR = top (redoStack);
    if (topNodeR == NULL)
    {
        printf("Redo stack is empty.\n\n");
        return;
    }

    while(topNodeR != NULL)
    {
        pop(redoStack);
        printf("String: %s\tOperation: %d\tIndex: %d\n",topNodeR->str, topNodeR->operation, topNodeR->index);
        push(tempStack, topNodeR);
        topNodeR = top(redoStack);
    }

    topNodeR = top(tempStack);
    while (topNodeR != NULL)
    {
        pop(tempStack);
        push(redoStack, topNodeR);
        topNodeR = top(tempStack);
    }
    printf("\n\n");
    deleteStack(tempStack);
    
}

void saveToFile () //saving to output file
{
    printf("Enter the name of the output file.\n\n");
    char name[50];
    gets(name);
    FILE* f = fopen(name,"w");

    if (f == NULL)
    {
        printf("Can't open output file %s",name);
        return;
    }

    if (L->next == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    //same as printing the text in the printLoadedText function
    ptrNode tempNode = L->next;
    while(tempNode != NULL)
    {
        fprintf(f,"%s",tempNode->str);
        fprintf(f," ");
        tempNode = tempNode->next;
    }

    fclose(f);
    printf("Text saved to output file.\n\n");
}

void deletelinkedList (linkedList L)
{
    if (L== NULL)
    {
        printf("List does not exist.\n");
        return;
    }
    ptrNode p = L->next;
    ptrNode temp;
    L->next = NULL;
    while (p != NULL)
    {
        temp = p->next;
        free(p); //deleting all the nodes
        p = temp;
    }
    
    free(L);
}

void deleteQueue (Queue Q)
{
    if (Q == NULL)
    {
        printf("Queue not found.\n");
        return;
    }

    ptrQueueNode front = Q->next;
    while (front != NULL)
    {
        ptrQueueNode temp = front->next;
        free(front);
        front = temp;
    }
    free(Q);
}