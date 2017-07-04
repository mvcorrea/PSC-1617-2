#include <stdio.h>
#include <string.h>


    int process(int argc, char* argv[], char* line){
        int out = 0;
        for(int i = 1; i < argc; i++){ // verify all occurencies
            char *ret = strstr(line, argv[i]);
            //printf("%s:\t %s\n", argv[i],ret);
            out |= ret == NULL ? 0 : 1;
        }
        return out;
    }

/*   
int main(int argc, char* argv[]){
    char *line = NULL;
    size_t len = 0;
    size_t read = 0;
    while (read != -1) { // each line
        puts("enter a line (^d to exit)");
        read = getline(&line, &len, stdin);
        // printf("line = %s", line);
        // printf("line length = %zu\n", read);
        // puts("");
        int out = process(argc, argv, line);
        if(out) printf("> %s", line);
        puts("");
    }
    return 0;
}
*/