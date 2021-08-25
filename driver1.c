/*
 * File: driver1.c
 * YOUR NAME ... YOU NEED TO IMPLEMENT THE main() + additional functions if needed
 *
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylinkedlist.h"

/*
 * First one (say driver1.c) gets three command-line arguments: x y z.  
 * It then asks user to enter x many integers, y many doubles, and z many lines. 
 * Prompt for each input at a time. 
 *
 * Everytime the program prints back the entered data on the stdout 
 *      while printing error messages on stderr (if any). 
 *
 * It also keeps track of the largest integer, largest double, and the longest string. 
 * At the end, your program (driver1.c) prints the largest integer, the largest double, 
 * and the longest line (longest string that were entered.) 
 */

/* 
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline '\n' character that terminates
 * the input is not stored as part of the string.
 */
char *ReadLine(void);



 
int main(int argc, char *arvg[])
{
  // YOU NEED TO IMPLEMENT THIS driver1.c USING FUNCTIONS FROM mylinkedlist.h
  // But before that, implement your ReadLine() function, and test it as shown below. 
  // IF NEEDED, YOU CAN ALSO IMLEMENT YOUR OWN FUNCTIONS HERE

  char *name, *temp;
  int choice, id, length, index, condition = 0;
  double gpa;
  
  linked_list_T *list = NewLinkedList();
  student_cell_T *element;

//testing readline function
/*   printf("Enter student's name  : ");
  name = ReadLine();
  printf("Name is %s \n\n", name);
  free(name); */


  while(condition!=8){ //while choice is not exit

    printf("\n1-Create a new student cell with given id, gpa, name info\n");
    printf("2-Remove the first student from linked list and print info\n");
    printf("3-Print number of students in list\n");
    printf("4-Print student at certain index\n");
    printf("5-Print our all students in linked list\n");
    printf("6-Print min, average, max gpa in list\n");
    printf("7-remove the student with highest gpa and print their information\n");
    printf("8-Exit\n");
    printf("\nEnter your choice : ");
    temp = ReadLine(); 
    choice = atoi(temp);
    free(temp);

    //scanf("%d", &choice);

    switch(choice){

      case 1: //create new studnet cell with given id, gpa, name and uses enlist method

        printf("Enter student's name  : ");
        name = ReadLine();

        // Uhhhh let me see or see if it does the problem
        //while(getchar() != '\n'); //get rid of excess \n in buffer

        printf("Enter students ID  : ");
        temp = ReadLine(); //??
        id = atoi(temp); //turn into int
        free(temp);

        //yes integer -> turn int to 
        //scanf("%d", &id);
        printf("Enter students GPA : ");
        temp = ReadLine();
        gpa = atof(temp); //
        free(temp); 
        //scanf("%lf", &gpa);
        
        element = NewStudentCell(id, gpa, name); //create new student cell with given information

        Enlist(list, element);  //enlist student into list, added to the end of the linked list
        printf("Student Enlisted\n"); //print out results
        
        //free(name); need to keep name 

        break;
      
      case 2: //remove (delist) the first student form linked list and print his/her id, gpa, name info

        element = Delist(list); //delist student and put info into element
        if(element == NULL){
          printf("Nothing in list.\n");
        }else{
        printf("Removed student from list, Name : %s, ID : %d, GPA : %.2f \n", //print out info of student
        element->name, element->id, element->gpa);
        }
        free(element->name);
        free(element);
        
        break;
      
      case 3: //Print number of students from list SHOULD BE GOOD
        length = LinkedListLength(list); //get length of list
        printf("The current list has %d students. (Length of List).\n", length); //print out length of list
        break;
      
      case 4: //print number of student at certain index
        printf("Which index would you like to retrieve information from? (Enter number) "); //print text
        temp = ReadLine();
        index = atoi(temp); //
        free(temp);

        student_cell_T *element = GetLinkedListElement(list, index); //get element at certain index

        if(element == NULL){
          printf("Please choose an index that exists.\n");
        }else{
          printf("\nStudent at index %d Name is %s, ID : %d, GPA : %.2f\n", index, element->name, element->id, //print info out
            element->gpa);
        }
        break;
      
      case 5: //print every student in the linked list
        GetAllElements(list); 
        break;
      
      case 6: //Print the min, average, max gpa in the linked list
        PrintMinMeanMax(list);
        break;
      
      case 7://Remove the student with highest gpa and print their information
        RemoveMaxGPA(list);
        break;
      
      case 8: //Exit
        printf("Goodbye\n");
        condition = 8;
        FreeLinkedList(list);
        break;

      default:
        printf("Please select options 1-8.\n");
    }//end switch

  //while(getchar() != '\n');
  }//end while loop

  return 0;
}

/* 
 * IMPLEMENTATION of ReadLine();
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline '\n' character that terminates
 * the input is not stored as part of the string.
 *
 * In contrast to standard I/O functions (e.g., scanf with "%s", fgets) 
 * that can read strings into a given static size buffer, ReadLine function 
 * should read the given input line of characters terminated by a newline 
 * character ('\n') into a dynamically allocated and resized buffer based on 
 * the length of the given input line. 
 *
 * When implementing this function you can use standard I/O functions. 
 * We just want you to make sure you allocate enough space for the entered data. 
 * So don't simply allocate 100 or 1000 bytes every time. 
 * If the given input has 5 characters, you need to allocate space for 6 characters.
 *
 * Hint: initially dynamically allocate an array of char with size 10. 
 * Then, read data into that array character by charecter (e.g, you can use getchar()). 
 * If you see '\n' char before reading 10th character, you are done. And you know the 
 * exact length of the input string. So, accordingly allocate enough space and copy the 
 * data into new char array, insert '\0' instead of '\n' and free the original array. 
 * Then return the new string. However, if you DO NOT see '\n' char after 10th character, 
 * then you need larger space. Accordingly, resize your original array and double its size 
 * and continue reading data character by character as in the first step... 
 * Hope you got the idea! 
 *
 * Also please check for possible errors (e.g., no memory etc.) and appropriately handle 
 * them. For example, if malloc returns NULL, free partially allocated space and return 
 * NULL from this function. The program calling this function may take other actions, 
 * e.g., stop the program!
 */


/* char *ReadLine(){
  char *buff = malloc(100);
  scanf("%s", buff);
  return buff;
} */



char *ReadLine()
{

  int variable = 10; //initialize new size

  char *buff = malloc(variable + 1); //allocated size 10 of memeory for char array +1 is for null character
  char *buff2;
  int c; //create a variable c an intialize - to read in char -------- getchar() returns int
  int i = 0;  //create a variable to use as counter

  if(buff == NULL){   //check if malloc returns null
        return(NULL); // if there is any error! 
  }

  while(((c = getchar()) != '\n') && (c != EOF)){ //while c is not equal to the newline character //set c to the new character
    if(i>=variable){ //if counter i is smaller or equal to the buff size (max and has not hit '\n') then allocate more memory for it
      variable *= 2; 
      buff = realloc(buff, variable+1); //resize array (more memory)
      if(buff == NULL){
        return(NULL); // if there is any error! 
      }
    }
    buff[i] = c; //set c into character array (for string)
    i++;  //incremement the counter 
  }
  buff[i] = '\0'; //set '\n' to '\0'
  
  buff2 = malloc(i+1); //realloc array with right  //check 
  if(buff2 == NULL){   //check if malloc returns null
        return(NULL); // if there is any error! 
  }

  strcpy(buff2, buff); //copy buff into buff2

  free(buff); //free buff

  return buff2; //return readline (string) 

 
  
}


