#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 80
#define MAX_LINES 100
#define MAX_WORDS 1000

struct word_count {
  char token[40];
        int freq;
};


int main ( int argc, char *argv[]) {

/* some common variables */
  int i=0, j = 0, line_count = 0, word_counts = 0, new_word_count = 0;
  char filename[MAX_LEN], line[MAX_LEN], *result;
  struct word_count tokens[MAX_LINES];
  FILE *fi, *fo;    // pointers for file input and output
  const char *outputfile = "result.txt";   // output file name
  const char delimiters[] = " .,;:!-\n\t\r"; // delimiters used to split words of a string


  // Get the filename.
  if (argc == 2) {
    // Get the filename from the command-line argument.
    strcpy(filename, argv[1]);
	
  } else {
    // Get the filename from the keyboard.
    printf("Enter the file name: ");
    fflush(stdout);
    scanf(" %s", filename);
    while (getchar() != '\n')
      ;
  }

/* code to get input file name from command line argument for for from input. */

// open input put file for reading  
  fi = fopen(filename, "r");


  if (fi == NULL){
    perror(filename);
    exit(EXIT_FAILURE);
  }  else {
	// Process the file line by line.
     while (fgets(line, MAX_LEN, fi) != NULL) {
    
       line_count ++;   // increate line count
        //fputs ( line, stdout );   // print the read line to screen
       
        //for each charator A-Z in line, convert it to lower case
	for(int i = 0; line[i]; i++){
	  line[i] = tolower(line[i]);
	}
        result = strtok(line, delimiters);  // get the pointer pointing to the first word token
        while(result != NULL) {
	  word_counts ++;		// increae word count
	  for (int a =0; a < j; a++){
	    if(strcmp(tokens[a].token,result)==0){ //check if word exists in array
	      //printf("result is %s and is the same as %s\n", result,tokens[a].token);
	      tokens[a].freq +=1;
	      i = 1; //set flag
	      break;
	    }
	  }
	  if (i != 1){ //if flag wasnt set, add word to array
	    strcpy(tokens[j].token, result);
	    tokens[j].freq = 1;
	  //printf("new value %s\n",tokens[j].token);
	  }
	  i = 0; //reset flag
	  j++;
	
	result = strtok(NULL, delimiters);  // get the next token
	}
      }
  }
  
	fclose ( fi );
    // print result to screen and file, in format "%-20s  %-3d\n"
	FILE *f = fopen("result.txt", "w");
	fprintf(f,"line count: %d\nword count: %d\nFrequency:\n",line_count, word_counts);
	printf("line count: %d\nword count: %d\nFrequency:\n",line_count, word_counts);
      for (int q = 0; q < j; q++){
	if(strcmp( tokens[q].token,"")!=0){
	  fprintf(f,"%-20s %-3d\n", tokens[q].token,tokens[q].freq);
	  printf("%-20s %-3d\n", tokens[q].token,tokens[q].freq);
	}
      }
      fclose(f);
      return 0;
}
