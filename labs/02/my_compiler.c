#include <stdio.h>
#include <stdlib.h>

struct sNode 
{ 
   char data;
   int line;
   struct sNode *next; 
}; 

void push(struct sNode** top, int new);

int pop(struct sNode** top);

int isBalanced(char* file_name);

int main(int argc, char **argv){
    char* file_name;
    char ch;
    FILE *fp;

    file_name = argv[1];

    isBalanced(file_name);

    return 0; 
    
}

void push(struct sNode** top, int new){
    struct sNode* nNode = (struct sNode*) malloc(sizeof(struct sNode));

    if (nNode == NULL){
        printf("Stack overflow n");
        getchar();
        exit(0);
    }

    nNode->data = new;
    nNode->next = (*top);

    (*top) = nNode;
}

int pop(struct sNode** node){
    char res;
    struct sNode *top;

    if (*node == NULL){
        printf("Stack overflow n"); 
        getchar(); 
        exit(0);
    }
    else{
        top = *node;
        res = top->data;
        *node = top->next;
        free(top);
        return res;
    }
}

int isBalanced(char* file_name){

    struct sNode *stack = NULL;
    struct sNode *lines = NULL;
    FILE* fp;
    char ch;
    fp = fopen(file_name, "rb");
    int line = 1;

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while((ch = fgetc(fp)) != EOF){

        if (ch == '/'){
            if ((ch = fgetc(fp)) == '/'){
                while(ch = fgetc(fp) != '\n'){
                    continue;
                }
                line++;
            }
        }
        

        if (ch == '\''){
            while((ch = fgetc(fp)) != '\''){
                if(ch == EOF){
                    printf("There is a missing \' : error in line %d\n",line);
                    return 0;
                }
                continue;
            }
        }

        if (ch == '\"'){
            while((ch = fgetc(fp)) != '\"'){
                if(ch == EOF){
                    printf("There is a missing \" : error in line %d\n",line);
                    return 0;
                    
                }
                continue;
            }
        }

        if (ch == '{' || ch == '(' || ch == '['){
            push(&stack, ch);
            push(&lines, line);
        }

        if (ch == '}'){
            if (stack == NULL){
                printf("There is a missing { : error in line %d\n",line); 
                return 0;
            }
            else if(pop(&stack) != '{'){
                pop(&lines);
                printf("There is a missing { : error in line %d\n",line); 
                return 0;
            }
            

        } else if (ch == ']'){
            if (stack == NULL){
                printf("There is a missing [ : error in line %d\n",line); 
                return 0;
            }
            else if(pop(&stack) != '['){
                pop(&lines);
                printf("There is a missing [ : error in line %d\n",line); 
                return 0;
            }
            

        } else if (ch == ')'){
            if (stack == NULL){
                printf("There is a missing ( : error in line %d\n",line); 
                return 0;
            }
            else if(pop(&stack) != '('){
                pop(&lines);
                printf("There is a missing ( : error in line %d\n",line); 
                return 0;
            }

            
        }

        if (ch == '\n'){
            line++;
        }
        
    }

    fclose(fp);
    
    if (stack == NULL){
        printf("There are no errors\n");
        return 1;
    }
    else{
        char c;
        int error_line;
        while(stack!=NULL){
            c = pop(&stack);
            error_line = pop(&lines);
            if (c == '('){
                printf("There is a missing ): error in line %d\n",error_line); 
            } else if (c == '{'){
                printf("There is a missing }: error in line %d\n",error_line); 
            } else {
                printf("There is a missing ]: error in line %d\n",error_line); 
            }
        }
        return 0;
    }

}