#include <stdio.h>
#define BUFFER_MAX_LENGTH 30

int _isspace(int c) {       // returns 0 if char is not "empty"
  if (c == ' ') return 1;   // space
  if (c == '\n') return 2;  // newline
  if (c == '\t') return 3;  // tab
  return 0;
}

char *leftTrim(char *str) {
  while (_isspace(*str)) str++;
  return str;
}

char *rightTrim(char *str) {
  char *right = str + strlen(str) - 1;  // pointer to the array end
  while (_isspace(*right)) --right;
  *(right + 1) = '\0';
  return str;
}



char *strtrim(char *str) { return leftTrim(rightTrim(str)); }

// int main(int argc, char* argv[]) {

//     char bufferOrig[BUFFER_MAX_LENGTH] ={0};

//     printf("strtrim: reads line from stdin removing pre/pos spaces\n");
//     int cnt = 0;
//     while(fgets(bufferOrig, BUFFER_MAX_LENGTH , stdin)){ // break with ^D
//         if(strlen(bufferOrig) == 1) return 0; // exit with empty\n
//         int cntBefore = 0, cntAfter = 0;
//         for(int i = 0; bufferOrig[i] != '\0'; i++) cntBefore++;
//         char *res = strtrim(bufferOrig);
//         for(int i = 0; res[i] != '\0'; i++) cntAfter++;
//         printf("%03d: %d - [%s] - %d\n", cnt++, cntBefore, res, cntAfter);
//     }
//     return 0;
// }