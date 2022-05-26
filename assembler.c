#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINELENGTH 1000

struct Label
{
    /* data */
    char name[MAXLINELENGTH];
    int address;
};
int isNumber(char *string){
    /* return 1 if string is a number */
    int i;
    return( (sscanf(string, "%d", &i)) == 1);
}
int CheckInJail(char jail[MAXLINELENGTH][10],int length,char * label){
    for(int i =0;i<length;++i){
        if(!strcmp(label,jail[i])){
           return 1; 
        }
    }
    return 0;
}

int findLabels(FILE *fileptr,struct Label* lptr,char jail[MAXLINELENGTH][10],int *numLabels){
    char buf[10];
    int lineNum =0; 
    while(fgets(buf,10,fileptr)){
        if(buf[0]=='.'){
            if(CheckInJail(jail,*numLabels,buf)){
                strcpy(lptr->name,buf);
                lptr->address = lineNum;
                strcpy(jail[*numLabels],buf);
                *numLabels++;
            }
            else{
                printf("Multiple definitions of label %s\n",buf);
                exit(1);
            }
        }
        ++lineNum;
    }
    return 1;
}

int parse(char *arg0,char *arg1,char *arg2, FILE *filePtr){
    return 1;
}

int main(int argc,char *argv[]){
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    inFileString = argv[1];
    outFileString = argv[2];
    if(argc != 3){
        printf("%s error usage: <assembly_code_file> <machine_code_file>\n",argv[0]);
        exit(1);
    }
    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL) {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }
    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL) {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }
    //Check for Labels
    struct Label labels[MAXLINELENGTH];
    struct Label* labelptr = labels;
    char jail[1000][10];

    return 0;

}