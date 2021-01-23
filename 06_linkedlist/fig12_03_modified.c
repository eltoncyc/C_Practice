#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// self-referential structure                       
struct listNode {                                      
   char data; // each listNode contains a character 
   struct listNode *nextPtr; // pointer to next node
}; 

typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode *ListNodePtr; // synonym for ListNode*

// prototypes
void insert(ListNodePtr *sPtr, char value);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr, unsigned int id);
void instructions(void);
void merge(ListNodePtr* list1Ptr, ListNodePtr *List2Ptr);

int main(void)
{ 
   ListNodePtr startPtr1 = NULL; // initially there are no nodes for list 1
   ListNodePtr startPtr2 = NULL; // initially there are no nodes for list 2 
   char item; // char entered by user

   instructions(); // display the menu
   unsigned int choice; // user's choice

   // loop while user does not choose 3

   int timeToExit = 0;  // false to begin with
   do{
	  printf("%s", "? ");
	  scanf("%u", &choice);

      switch (choice) { 
         case 1:
            printf("%s", "Enter a character: ");
            scanf("\n%c", &item);
            insert(&startPtr1, item); // insert item in list
            printList(startPtr1, 1);
            break;

         case 2: // delete an element
            // if list is not empty
            if (!isEmpty(startPtr1)) { 
               printf("%s", "Enter character to be deleted: ");
               scanf("\n%c", &item);

               // if character is found, remove it
               if (delete(&startPtr1, item)) { // remove item
                  printf("%c deleted.\n", item);
                  printList(startPtr1, 1);
               } 
               else {
                  printf("%c not found.\n\n", item);
               } 
            } 
            else {
               puts("List 1 is empty.\n");
            } 

            break;

         case 3:
             printf("%s", "Enter a character: ");
             scanf("\n%c", &item);
             insert(&startPtr2, item); // insert item in list
             printList(startPtr2, 2);
             break;

         case 4:
             if (!isEmpty(startPtr2)) {
                 printf("%s", "Enter character to be deleted: ");
                 scanf("\n%c", &item);

                 // if character is found, remove it
                 if (delete(&startPtr2, item)) { // remove item
                     printf("%c deleted.\n", item);
                     printList(startPtr2, 2);
                 }
                 else {
                     printf("%c not found.\n\n", item);
                 }
             }
             else {
                 puts("List 2 is empty.\n");
             }

             break;

         case 5:
             // replaced the original code here 
             //     with the hint for assign6 posted on d2l       
             puts("\nBefore merge, the 2 lists are: \n");
             printList(startPtr1, 1);
             printList(startPtr2, 2);

             merge(&startPtr1, &startPtr2);

             puts("\nAfter merge, the 2 lists are: \n");
             printList(startPtr1, 1);
             printList(startPtr2, 2);

             break;

		 case 6:
			 timeToExit = 1; // now set to true
			 break;

         default:
            puts("Invalid choice.\n");
            instructions();
            break;
      } // end switch

   } while (!timeToExit);

   puts("End of run.");

   // Time to go home
   _getch();
} 

// display program instructions to user
void instructions(void)
{ 
   puts("Enter your choice:\n"
      "   1 to insert an element into the list 1.\n"
      "   2 to delete an element from the list 1.\n"
       "   3 to insert an element into the list 2.\n"
       "   4 to delete an element from the list 2.\n"
       "   5 merge list 2 into list 1.\n"
      "   6 to end.");
} 

// insert a new value into the list in sorted order
void insert(ListNodePtr *sPtr, char value)
{ 
   ListNodePtr newPtr = malloc(sizeof(ListNode)); // create node

   if (newPtr != NULL) { // is space available
      newPtr->data = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node

      ListNodePtr previousPtr = NULL;
      ListNodePtr currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while (currentPtr != NULL && value > currentPtr->data) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      }                                          

      // insert new node at beginning of list
      if (previousPtr == NULL) { 
         newPtr->nextPtr = *sPtr;
         *sPtr = newPtr;
      } 
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
      } 
   } 
   else {
      printf("%c not inserted. No memory available.\n", value);
   } 
} 

// delete a list element
char delete(ListNodePtr *sPtr, char value)
{ 
   // delete first node if a match is found
   // we need to treat deleting the first node as a special case
   if (value == (*sPtr)->data) { 
      ListNodePtr tempPtr = *sPtr; // hold onto node being removed
      *sPtr = (*sPtr)->nextPtr; // de-thread the node
      free(tempPtr); // free the de-threaded node
      return value;
   } 

   // normal case of potentially deleting node, but not first node
   else { 
      ListNodePtr previousPtr = *sPtr;
      ListNodePtr currentPtr = (*sPtr)->nextPtr;

      // loop to find the correct location in the list
      while (currentPtr != NULL && currentPtr->data != value) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } 

      // delete node at currentPtr
      if (currentPtr != NULL) { 
         ListNodePtr tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         free(tempPtr);
         return value;
      } 

	  else // data item not found so return NULL
	  { 
		  return '\0';
	  }
   } 

} 

// return 1 if the list is empty, 0 otherwise
int isEmpty(ListNodePtr sPtr)
{ 
   return sPtr == NULL;
} 

// print the list
void printList(ListNodePtr currentPtr, unsigned int listId)
{ 
   // if list is empty
   if (isEmpty(currentPtr)) {
      //puts("List is empty.\n");
      printf("List %d is empty.\n\n", listId);
   } 
   else { 
      //puts("The list is:");
      printf("List %d is:\n", listId);
      // while not the end of the list
      while (currentPtr != NULL) { 
         printf("%c --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;   
      } 

      puts("NULL\n\n");
   } 
} 

// merge list 2 into list 1
void merge(ListNodePtr *list1Ptr, ListNodePtr *list2Ptr)
{

    ListNodePtr previousList1Ptr = NULL;
    ListNodePtr currentList1Ptr = *list1Ptr;
    ListNodePtr currentList2Ptr = *list2Ptr;
    ListNodePtr nextList2Ptr;

    // move each node in list 2 to list 1 until list 2 has no node 
    while (currentList2Ptr != NULL)
    {   
        // save next pointer of the current node in list 2
        nextList2Ptr = currentList2Ptr->nextPtr;

        // loop to find the correct location in list 1
        while (currentList1Ptr != NULL && currentList2Ptr->data > currentList1Ptr->data) {
            previousList1Ptr = currentList1Ptr;
            currentList1Ptr = currentList1Ptr->nextPtr;
        }

        // move the current node in list 2 to the beginning of list 1
        if (previousList1Ptr == NULL) {
            currentList2Ptr->nextPtr = *list1Ptr;
            *list1Ptr = currentList2Ptr;
        }
        else { // move the current node in list 2 between previousList1Ptr and currentList1Ptr
            currentList2Ptr->nextPtr = currentList1Ptr;
            previousList1Ptr->nextPtr = currentList2Ptr;
        }
        // update the current nodes: 
        //  current node in list 2 should be the nextList2Ptr; 
        //  current node in list 1 should be the first node in list 1
        currentList2Ptr = nextList2Ptr;
        currentList1Ptr = *list1Ptr;
    }
    //finalize the list 2. it should be the last node (NULL) after the while loop
    *list2Ptr = currentList2Ptr;

}



/**************************************************************************
 * (C) Copyright 1992-2015 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
