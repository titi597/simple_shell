#include "shell.h"

int main(int ac, char **argv)
{

    size_t n = 0;
    ssize_t nchars_read;
    char *prompt = "(ts_shell) $ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    const char *delim = "\n";
    int num_tokens = 0;
    char *token;
    int i;

    (void)ac;
   
    while (1) {
        printf("%s", prompt);

        nchars_read = getline(&lineptr, &n, stdin);

        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL){
            perror("t_sh: memory alloction error");
            return (-1);
        }

        /* copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);


        if (nchars_read == -1) {
            printf("Exiting shell...\n");
            return (-1);
        }

        if (lineptr[0] != '\0' && lineptr[0] != '\n') {
            printf("%s", lineptr);
            /* Process the user input here (e.g., parse and execute commands). */
        }

        
         /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */

        token = strtok(lineptr, delim);

        while (token != NULL){
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++){
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        execmd(argv);


        /* free up allocated memory */
        free(lineptr);
        lineptr = NULL;
        free(lineptr_copy);
        free(argv);
        
    }

    return (0);
}