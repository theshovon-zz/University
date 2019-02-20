//
// EECS2031 team.c
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: <Shovon Saha>
// Student Info: <215246473>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//**********************************************************************
// Linked List Definitions 
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
struct Player {
	char * family_name;
	char * first_name;
	char position;
	int value;
	struct Player * next;	
};

//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//

struct Player * create_player(char * family_name, char * first_name, char position, int value);
struct Player * insert_player(struct Player * head, struct Player *player);
int to_number(char number[]);
bool has_duplicate(struct Player * head, char family_name[]);
struct Player * delete_player(struct Player * head, char family_name[]);
void search_family_name(struct Player * head, char family_name[]);
void search_less_equal_value(struct Player * head, int value);
void print_team(struct Player * head);
void print_player( struct Player *player);
struct Player * quit(struct Player * head);




//**********************************************************************
// Support Function Declarations
//

void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly 
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main (void)
{ 
    const char bannerString[]
        = "Personal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head.
    struct Player *head = NULL;
 
    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);
    
    //char * response;
	char response;
    char input[MAX_LENGTH+1];
    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
	
	/*if(sizeof(response)!=1){
	printf("Wrong choice");
	continue;
	}*/
        response = toupper(input[0]);
	
        if (response == 'I')
        {
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).

            char family_name[MAX_LENGTH+1];
            char first_name[MAX_LENGTH+1];
            char position;
            int value;
            char c;
            bool validity_of_position=false;
            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
            printf("family name: ");
            safegets(family_name,MAX_LENGTH+1);
            printf("first name: ");
            safegets(first_name,MAX_LENGTH+1);
            printf("position: ");
            position = toupper(getchar());
            //assign validity of position
            while((c=getchar())!='\n'){
                validity_of_position=true;
            }
		char v[MAX_LENGTH+1];
            	printf("value: ");
            	safegets(v,MAX_LENGTH+1);
            	value = to_number(v);
            //check validity of position
            if(validity_of_position){
                printf("Invalid Position. Positions are 'G', 'D', 'M', or 'S'.\n" );
                continue;
            }
            //check value
            if(value < 0){
                printf("The value should be a positive number");
                continue;
            }
            //check for duplicate family name
            if(has_duplicate(head, family_name)){
                familyNameDuplicate(family_name);
                continue;
            }
            //create a player node
             struct Player * new_player = create_player(family_name, first_name, position, value);
            //insert the new player into the list
            head = insert_player(head, new_player);

        }
        else if (response == 'D')
        {
            // Delete a player 
            char family_name[MAX_LENGTH+1];
            printf("\nEnter family name for entry to delete: ");
            safegets(family_name,MAX_LENGTH+1);
            head = delete_player(head, family_name);

        }
        else if (response == 'S')
        {
            // Search for a player by family name.
            char family_name[MAX_LENGTH+1];
            printf("\nEnter family name to search for: ");
            safegets(family_name,MAX_LENGTH+1);
            search_family_name(head, family_name);
        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal to value.
            char v[MAX_LENGTH+1];
            int value;
            printf("\nEnter value: ");
            safegets(v,MAX_LENGTH+1);
            value = to_number(v);
            if(value < 0){
                printf("The value should be a positive number");
                continue;
            }
            search_less_equal_value(head, value);

        }
        else if (response == 'P')
        {
            // Print the team.
            print_team(head);
        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else 
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');
  
    // Delete the whole linked list that hold the team.
    head = quit(head);

    // Print the linked list to confirm deletion.
    print_team(head);

    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name 
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);
	
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.
//----------------------------------------------------------------------------------------

struct Player * create_player(char * family_name, char * first_name, char position, int value){
    struct Player * new_player = malloc(sizeof(struct Player));
    if(new_player == NULL)
    {
        printf("Error: malloc failed in creating the player at create_player.\n");
        exit(EXIT_FAILURE);
    }
    (*new_player).family_name = (char*) malloc(strlen(family_name)*sizeof(char));
    if((*new_player).family_name == NULL)
    {
        printf("Error: malloc failed in adding family name at create_player.\n");
        exit(EXIT_FAILURE);
    }
    strcpy((*new_player).family_name,family_name);
    (*new_player).first_name = (char*) malloc(strlen(first_name)*sizeof(char));
    if((*new_player).first_name == NULL)
    {
        printf("Error: malloc failed in adding first name at create_player.\n");
        exit(EXIT_FAILURE);
    }
    strcpy((*new_player).first_name,first_name);
    (*new_player).position = position;
    (*new_player).value = value;
    (*new_player).next = NULL;
    return new_player;
}
//----------------------------------------------------------------------------------------
struct Player * insert_player(struct Player * head, struct Player *player){
    char position = (*player).position;
    if(!(position == 'G' || position == 'D' || position == 'M' || position =='S')){
        free((*player).family_name);
        free((*player).first_name);
        free(player);
        printf("Invalid Position. Positions should be 'G', 'D', 'M', or 'S'\n" );
        return head;
    }
    if(head == NULL){
	head = player;
	return head;
    }


    switch(position) {
        
        case 'G' :
            //insert new player to the front
            if((*head).position != 'G'){
                (*player).next = head;
                head = player;
            }
		else{
                struct Player * pointer = head;
                //add to the end of G's
                while((*pointer).next != NULL && (*(*pointer).next).position == 'G'){
	            pointer = (*pointer).next;
                }
                (*player).next = (*pointer).next;
                (*pointer).next = player;
            }
            break;
        
        case 'D' :
            //insert player infront of M or S
            if((*head).position == 'M' || (*head).position == 'S'){
                (*player).next = head;
                head = player;
            }
		else{
                struct Player * pointer = head;
                //add to the end of D's
                while((*pointer).next != NULL && (*(*pointer).next).position != 'M' &&( *(*pointer).next).position != 'S'){
	            pointer = (*pointer).next;
                }
                (*player).next = (*pointer).next;
                (*pointer).next = player;
            }
            break;
       
        case 'M' :
            //insert player infront of S
            if((*head).position == 'S'){
                (*player).next = head;
                head = player;
            }
		else{
                struct Player * pointer = head;
		//insert to the end of M's 
                while((*pointer).next != NULL && (*(*pointer).next).position != 'S'){
	            pointer = (*pointer).next;
                }
                (*player).next = (*pointer).next;
                (*pointer).next = player;
            }
            break;

        case 'S' :
        	//insert player at the end 
            {
                struct Player * pointer = head;
                while((*pointer).next != NULL){
	            pointer = (*pointer).next;
                }
                (*pointer).next = player;
            }
            break;
   }
    return head;
}
//----------------------------------------------------------------------------------------
bool has_duplicate(struct Player * head, char family_name[]){
    struct Player * pointer = head;
    while(pointer != NULL){
        if(strcmp((*pointer).family_name,family_name)==0){
            return true;
        }
        pointer = (*pointer).next;
    }
    return false;
}
//----------------------------------------------------------------------------------------
int to_number(char number[])
{
	bool is_num = true;
	int i ;
	int index = 0;
	while(number[index] != '\0' && index < MAX_LENGTH){
		if(number[index] < '0' || number[index] > '9'){
		is_num = false;
		}
		index++;
	}
	return is_num ? i=atoi(number) : -1;
	
}
//----------------------------------------------------------------------------------------
struct Player * delete_player(struct Player * head, char family_name[]){
    //check if family name exists in the list
    if(head == NULL){
        familyNameNotFound(family_name);
        return head;
    }
    
    struct Player * prev = NULL;
    struct Player * current = head;
    //searching list for family name
    while(current != NULL){
        if(strcmp((*current).family_name,family_name)==0){
            break;
        }
        prev = current;
        current = (*current).next;
    }
    if(current == NULL){
        familyNameNotFound(family_name);
        return head; 
    }

    if(prev == NULL){
        head=(*head).next;    
        familyNameDeleted((*current).family_name);
    } else {
        (*prev).next = (*current).next;  
        familyNameDeleted((*current).family_name);
    }
    (*current).next = NULL;
    free(current);
    current = head;
    prev = head;
    return head;            
}
//----------------------------------------------------------------------------------------
void search_family_name(struct Player * head, char family_name[]){
    //check for duplicates
    if(has_duplicate(head, family_name)){
        familyNameFound(family_name);
        struct Player * pointer = head;
        while(pointer != NULL){
            if(strcmp((*pointer).family_name,family_name) == 0){
                break;
            }
            pointer = (*pointer).next;
        }
        print_player(pointer);
    } 
	else {
     
        familyNameNotFound(family_name);
    }
}
//----------------------------------------------------------------------------------------
void search_less_equal_value(struct Player * head, int value){
    bool player_exists = false;
    struct Player * pointer = head;
    while(pointer != NULL){
        if((*pointer).value <= value){
            print_player(pointer);
            player_exists = true;
        }
        pointer = (*pointer).next;
    }
    if(!player_exists){
	printNoPlayersWithLowerValue(value);
	}
}

//----------------------------------------------------------------------------------------
void print_team(struct Player * head){
    if(head == NULL){
        printTeamEmpty();
    } 
	else {
        printTeamTitle();
        struct Player * pointer = head;
        while(pointer != NULL){
            print_player(pointer);
            pointer = (*pointer).next;
        }
    }
}
//----------------------------------------------------------------------------------------
void print_player(struct Player *player){
	printf("\n");
    	printf("%s\n",(*player).family_name);	
    	printf("%s\n",(*player).first_name);
    	printf("%c\n",(*player).position);
    	printf("%d\n",(*player).value);
}
//----------------------------------------------------------------------------------------
struct Player * quit(struct Player * head){
    struct Player * deloc;
    while(head != NULL){
       deloc = head;
        head = (*head).next;
        (*deloc).next = NULL;
        free(deloc);
    }
   deloc = head;
    return head;
}


