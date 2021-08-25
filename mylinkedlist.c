/*
 * File: mylinkedlist.c
 * YOUR NAME ... 
 * YOU NEED TO IMPLEMENT THE FUNCTIONS  here
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
#include "mylinkedlist.h"
 
/*
 * Function: NewStudentCell
 * Usage: student_cell_T *element;
 *        element = NewStudentCell(int id, double gpa, char *name);
 * --------------------------
 * This function allocates space for a student cell and intilize its fileds
 */
student_cell_T *NewStudentCell(int id, double gpa, char *name)
{
   student_cell_T *element;
  
   element = (student_cell_T *) malloc( sizeof(student_cell_T) );
   if( !element){
     fprintf(stderr,"NewStudentCell cannot allocate memory\n");
     return NULL;
   }
   element->id = id;
   element->gpa = gpa;
   element->name = name;

  return element;
}


/*
 * Function: NewLinkedList
 * Usage: linked_list_T *list;
 *        list = NewLinkedList();
 * --------------------------
 * This function allocates and returns an empty linked list.
 */
linked_list_T *NewLinkedList(void)
{
   linked_list_T *list;
  
   list = (linked_list_T *) malloc( sizeof(linked_list_T) );
   if( !list){
     fprintf(stderr, "NewLinkedList cannot allocate memory\n");
     return NULL;
   }

   list->head = NULL;
   list->tail = NULL;

  return list;
}

//DONE
/*
 * Function: FreeLinkedList
 * Usage: FreeLinkedList(list);
 * ------------------------
 * This function frees the storage associated with list.
 */
void FreeLinkedList(linked_list_T *list)
{
  student_cell_T * toRemove; //create pointer to element we will remove
  student_cell_T * pointer = list->head; //create pointer to element we will remove

  if(list->head == NULL){ //if list is empty then do nothing 
  }else{
    while(pointer != NULL){ //iterate through entire list
      toRemove = Delist(list);//remove element and set it to pointer
      pointer = pointer->next;
      free(toRemove->name);
      free(toRemove);
    }
  }
  toRemove = NULL;
  free(list); //free the list
}


//DONE AND TESTED
/*
 * Function: Enlist
 * Usage: Enlist(list, element);
 * -------------------------------
 * This function adds a student cell pointed by element to the end of the list.
 */
void Enlist(linked_list_T *list, student_cell_T *element)
{

  if(list->head == NULL){ //if there is nothing in the list
    list->head = element; //make the head the element
    list->tail = element; //make the tail the element
    list->tail->next = NULL; //set the tail next to be NULL
  }else{
    list->tail->next = element;  //set the tails next to be element
    list->tail=element; //then set the tail to = to element 
    list->tail->next=NULL; //initialize the tails next to be null 
  }
}


//DONE AND TESTED 
/*
 * Function: Delist
 * Usage: element = Delist(list);
 * --------------------------------
 * This function removes the student cell at the head of the list
 * and returns its address to the caller (client).  If the list is empty, Delist
 * prints an Error with an appropriate message and returns NULL.
 */
student_cell_T *Delist(linked_list_T *list)
{
  if(LinkedListIsEmpty(list) == 0){
    printf("ERROR: List is empty\n");
    return(NULL);
  }else{
    student_cell_T *pointer = list->head; //set a temp pointer to the head of the list

    list->head = list->head->next; //mark the next element as the head
    return pointer; //return the address 
  }
}



//DONE AND TESTED 
/*
 * Functions: LinkedListIsEmpty, LinkedListIsFull
 * Usage: if (LinkedListIsEmpty(list)) . . .
 *        if (LinkedListIsFull(list)) . . .
 * -------------------------------------
 * These functions test whether the list is empty or full.
 */
int LinkedListIsEmpty(linked_list_T *list)
{
  int boolean = 0; //0 is true anything else is false 
  if(list->head == NULL){ //if list is null then return 0 true it is empty
    return boolean;
  }else{  //if the list is not null then it means there are things in the list so return 1 for false
    boolean = 1;
    return boolean;
  }
}




//DONE AND TESTED
/*
 * Function: LinkedListLength
 * Usage: n = LinkedListLength(list);
 * ------------------------------
 * This function returns the number of elements in the list.
 */
int LinkedListLength(linked_list_T  *list)
{
  int count = 0; //initialize variable we will use for counter

  student_cell_T * pointer = list->head; //create pointer to head

  while(pointer != NULL){ //while pointer is not null
    count++; //increment count by one
    pointer = pointer->next; //set the pointer to the pointers next 
  }

  return count; //return number of elements in the list
}

//DONE AND TESTED
/*
 * Function: GetLinkedListElement
 * Usage: element = GetLinkedListElement(list, index);
 * -----------------------------------------------
 * This function returns the element at the specified index in the
 * list, where the head of the list is defined as index 0. For
 * example, calling GetLinkedListElement(list, 0) returns the initial
 * element from the list without removing it.  If the caller tries
 * to select an element that is out of range, GetLinkedListElement prints
 * Error and returns NULL.  Note: This function is not a fundamental list operation
 * and is instead provided mainly to facilitate debugging.
 */
student_cell_T *GetLinkedListElement(linked_list_T *list, int index)
{
  int max = LinkedListLength(list);

  if(index > max){  //if index is bigger than the max (length of the current list) print error and return null
    printf("Error: Index out of bounds\n");
    return(NULL);
  }

  student_cell_T * pointer = list->head; //create pointer to head
  student_cell_T * element = (student_cell_T *) malloc( sizeof(student_cell_T) );

  for(int i = 0; i!=index-1;i++){
    pointer = pointer->next;
  }
  element->id = pointer->id;
  element->name = pointer->name;
  element->gpa = pointer->gpa;

  return element;
}



/* OTHER FUNCTIONS YOU WOULD NEED....
 * EXPORT THEM HERE, BUT IMPLMENT THEM in mylinkedlist.c 
 */



/*
 * Function: GetAllElements
 * Usage: GetAllElements(list);
 * -----------------------------------------------
 * This function prints out all the elements that are in the list. For
 * example, calling GetAllElements(list) prints out all the elements
 * without removing any elements in the list.  If the caller tries
 * to print out the elements in an empty list. GetAllElements prints
 * Error.
 */
void GetAllElements(linked_list_T *list){

  student_cell_T * pointer = list->head; //create pointer to head of list

  printf("\nPrinting all students...\n");
  if(LinkedListIsEmpty(list) == 0){ //if list head is null
  printf("ERROR: List is empty there is nothing to print\n"); //print text
  }else{
    while(pointer != NULL){ //iterate through entire list
      printf("Student : %s, ID : %d, GPA : %.2f \n", pointer->name, pointer->id, pointer->gpa); //print student information
      pointer = pointer->next; //set pointer to be the next element
    }
  }
}



/*
 * Function: PrintMinMeanMax
 * Usage: PrintMinMeanMax(list);
 * -----------------------------------------------
 * This function prints out the Minimum GPA, Mean GPA, and the Max GPA
 * that are in the list. For example, calling PrintMinMeanMax(list) 
 * prints out min, mean, and max of the list without removing any 
 * elements in the list.  If the caller tries to print the min, mean, max
 * of an empty list. PrintMinMeanMax prints Error.
 */
void PrintMinMeanMax(linked_list_T *list){
  
  student_cell_T * pointer = list->head; //create pointer to head of list

  if(LinkedListIsEmpty(list) == 0){ //if head is null  (list is empty)
  printf("ERROR: List is empty there is no min, mean, or max to print\n"); //print text
  }else{

    int length = LinkedListLength(list); //get list length and store into variable length
    double max = pointer->gpa; //set max to the first current gpa
    double min = pointer->gpa; //set min to the first current gpa
    double mean = 0; //set mean to 0 


    while(pointer != NULL){ //iterate through entire list
      if(max < pointer->gpa){ //if max is smaller than the gpa being pointed to
        max = pointer->gpa; //set new max to current pointers gpa
      }
      if(min> pointer->gpa){//if min is bigger than the gpa being pointed to
        min = pointer->gpa; //set new mean to current pointers gpa
      }
      mean += pointer->gpa; //add gpa to mean
      pointer = pointer->next; //set pointer to be the next element
    }
  mean = mean / length; //get mean by sum/size
  printf("Min GPA : %.2f , Mean GPA : %.2f , Max GPA : %.2f \n", min, mean, max); //print out info
  
  }
}


/*
 * Function: RemoveMaxGPA
 * Usage: RemoveMaxGPA(list);
 * -----------------------------------------------
 * This function prints out the element that has the highest GPA in 
 * the list. For example, calling RemoveMaxGPA(list) prints out the 
 * student with the highest GPA and prints their information. If the 
 * caller tries to print out the elements in an empty list. 
 * RemoveMaxGPA prints Error.
 */
void RemoveMaxGPA(linked_list_T *list){

  student_cell_T * current = list->head;
  student_cell_T * previous = current;
  student_cell_T * maxStu = current;
  
  //find max gpa in list
  while(current->next != NULL){
    if(maxStu->gpa < current->gpa){
      maxStu = current;
    }
    current = current->next;
  }

  current = list->head; //reset the current to point to first element

  printf("Student %s, with ID %d and GPA of %.2lf has the highest GPA.\n", maxStu->name, maxStu->id, maxStu->gpa);

  //find element in list and remove
  while(current != maxStu){
    previous = current;
    current = current->next;
  } 

  //exit while loop hwen current == maxStu
  previous->next = current->next;
  free(current->name);
  free(current);
  printf("Student has been removed\n");

}
