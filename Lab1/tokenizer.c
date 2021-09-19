#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is a whitespace character
   ('\t', ' ').
   Zero terminators are not printable (therefor false).
 */
bool delim_character (char c){
  if (c == '\t' || c ==' ')
    return true;
  else
    return false;
}

/* Return true (non-zero) if c is a non-whitespace character
   (not tab or space). Zero terminators are not printable
   (therefore false).
*/
bool non_delim_character(char c ){
  if (c == '\t' || c == ' ' || c == '\0')
    return false;
  else
    return true;
}

/* Returns a pointer to the first character of the next
   space-separated word.
*/
char *word_start(char* str){
  while(delim_character(*str))
    str++;
  return str;
}

/* Returns a pointer to the first space character of the zero
   terminated string.
*/
char *end_word(char* str){
  while(non_delim_character(*str))
    str++;
  return str;
}

/* counts the number of words or tokens*/
int count_tokens(char* str){
  int count = 0;
  while(*str != '\0'){
    if (delim_character(*str))
      count++;
    str++;
  }
  count++; // accounts for the terminator.
  return count;
}

/* Returns a freshly allocated zero-terminated vector of freshly 
   allocated space-seperated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){
  char *copy = (char*)malloc((len+1)*sizeof(char));
  for (int i = 0; i < len; i++)
    *(copy+i) = *(inStr+i);
  *(copy+len) = '\0';
  return copy;
}

char** tokenize(char* str){
  int count = count_tokens(str);
  char **arrayOfPointers = (char**)malloc((count+1)*sizeof(char*));
  char *end;
  char *start = word_start(str);
  for (int i = 0; i < count; i++){
    end = end_word(start);
    *(arrayOfPointers+i) = copy_str(start, (end-start));
    start = word_start(end);
  }
  *(arrayOfPointers+count) = NULL;
  return arrayOfPointers;
}

void print_all_tokens(char** tokens){
  for (int i = 0; *tokens != '\0'; i++){
    printf("Tokens[%d]: %s\n", i, *tokens);
    *tokens++;
  }
}

int main(){
  char input[100]; // User input can only be 100 chars long.
  char **pointerStorage;
  printf("Type 'x' to quit.\n");
  while(1){
    printf("Input: ");
    fgets(input, sizeof(input), stdin);
    if (*input=='x'){break;}
    pointerStorage = tokenize(input);
    print_all_tokens(pointerStorage);
    printf("\n");
  }
}


  
