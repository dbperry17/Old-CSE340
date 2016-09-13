#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;


extern "C"
{
  #include "lexer.h"
}

struct tokenStruct
{
    char current_token[MAX_TOKEN_LENGTH];   // token string
    int token_length;                       // token length
    token_type t_type;                      // token type
    int line;                               // current line number
    tokenStruct *next;                      // next token in LL
};

int totalLines = 0;


struct tokenStruct* addNodes()
{
    struct tokenStruct* head = NULL;
    struct tokenStruct* cur = new tokenStruct;
    struct tokenStruct* prev = NULL;
    int done = 0;

    while (!done)
    {
        cur->t_type = getToken();
        
        if (head == NULL)
	    {
	        head = cur;
	    }
	    else if (prev == NULL)
	    {
	        head->next = cur; //Because if the previous item doesn't exist,
	                          //then "head" must be the only item
	        prev = cur;
	    }
	    else
	    {
	       prev->next = cur;
	       prev = cur;
	    }
	    
	    if (cur->t_type == END_OF_FILE)
	    {
            done = 1;
	    }
	    else
	        totalLines++;
	    
	    //testing
	    cout << cur->t_type << endl;
    }
    
    cout << "Test: Head token type = " << head->t_type << endl;
    return head;
}

struct tokenStruct* reverseList(tokenStruct* head)



string tokenString(char* token)
{
    string myString(token);
    return myString;
}


void print_entries(struct tokenStruct* head)
{
    string typeNames[27] = 
    {
        "", //CHANGE BACK TO EMPTY STRING
        "IF",
        "WHILE",
        "DO",
        "THEN",
        "PRINT",
        "+",
        "-",
        "/",
        "*",
        "=",
        ":",
        ",",
        ";",
        "[",
        "]",
        "(",
        ")",
        "<>",
        ">",
        "<",
        "<=",
        ">=",
        ".",
        "NUM",
        "ID",
        "ERROR"
    };

    struct tokenStruct* cur;
    cur = head;
   
   
    //change output when done
    for(int i = 0; i < totalLines; i--)
    {   
        cout << "Current Token: " << tokenString(cur->current_token) 
             << "\nToken Length: " << cur->token_length
             << "\nToken Type: " << typeNames[cur->t_type]
             << "\nLine number: " << cur->line << "\n" << endl;
             
        cur = cur->next;
    }
}

int main()
{
    tokenStruct* head = addNodes();
    print_entries(head);
    
    delete head; //do linked list delete later
    return 0;
}

