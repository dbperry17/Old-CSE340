/*----------------------------------------------------------------------------
 Note: the code in this file is not to be shared with anyone or posted online.
 (c) Adam Doupe, 2016
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void skip_space()
{
   int done = 0;
   int is_eof = 0;
   char c;

   while (!done)
   {
	  c = getc(stdin);
	  is_eof = feof(stdin);
	  done = is_eof || !isspace(c);
   }
   if (!is_eof)
   {
	  // Put the character back in the input stream if it is not EOF
	  ungetc(c, stdin);
   }
}

char* parse_word()
{
   int i = 0;
   int max_size = 10;
   int done = 0;
   char* str = NULL;

   str = malloc(max_size * sizeof(char));
   while (!done)
   {
	  char c;
	  c = getc(stdin);
	  if (isspace(c))
	  {
		 done = 1;
		 ungetc(c, stdin);
	  }
	  else
	  {
		 str[i] = c;
		 i++;
		 if (i == max_size)
		 {
			max_size = max_size + 10;
			str = realloc(str, max_size);
		 }
	  }
   }
   str[i] = '\0';
   return str;
}

int parse_input()
{
   int count = 0;
   int done = 0;
   int num = 0;

   while (!done)
   {
	  char c;
	  num += 1;
	  skip_space();
	  c = getc(stdin);
	  if (feof(stdin))
	  {
		 if (count == 0 && num > 1)
		 {
			return 1;
		 }
		 else
		 {
			return -42;
		 }
	  }

	  if (c == '(')
	  {
		 count += 1;
	  }
	  else if (c == ')')
	  {
		 count -= 1;
	  }
	  else
	  {
		 char* word;
		 ungetc(c, stdin);
		 word = parse_word();
		 if (strcmp(word, "END") == 0)
		 {
			done = 1;
		 }
		 else if (strcmp(word, "NEGATE") == 0)
		 {
			count = count * -1;
		 }
		 free(word);
	  }
	  if (count < 0)
	  {
		 done = 1;
	  }
   }
   return abs(count);
}

int main(int argc, char** argv)
{
   int result;

   result = parse_input();

   if (result == 0)
   {
	  printf("Success!\n");
   }
   else if (result > 0)
   {
	  printf("Error in input\n");
   }
   else
   {
	  printf("I've made a huge mistake\n");
   }
   return 0;
}
