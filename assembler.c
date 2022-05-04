//Sections of code borrowed from EECS 370 p1a

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
struct Label
{
    /* data */
    char name[MAXLINELENGTH];
    int address;
};
int CheckInJail(char jail[MAXLINELENGTH][MAXLINELENGTH],int length,char * label){
    for(int i =0;i<length;++i){
        if(!strcmp(label,jail[i])){
           return 1; 
        }
    }
    return 0;
}

int grabLabels(struct Label* labelptr,int currentline,FILE *inFilePtr,int *numLabels,char jail[MAXLINELENGTH][MAXLINELENGTH]){ 
    char line[MAXLINELENGTH];
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
	/* reached end of file */
        return(0);
    }
    if (strlen(line) == MAXLINELENGTH-1) {
        printf("error: line too long\n");
        exit(1);
    }
    char label[MAXLINELENGTH];
    char* ptr = line;
    if (sscanf(ptr, "%[^\t\n ]", label)) {
        //adds label to the array
        if(!CheckInJail(jail,*numLabels,label)){
            strcpy(labelptr->name,label);
            labelptr->address= currentline;
            strcpy(jail[*numLabels],label);
            *numLabels = *numLabels+1;
            //labelptr = labelptr+1;
        }
        // throw error
        else{
           printf("multipe definition of Label%s\n",label);
           exit(1);
        }
    }
    return 1;

}
int searchLabels(struct Label labels[],int numlabels,char* label){
    for(struct Label* ptr = labels;ptr<labels+numlabels;++ptr){
       if(strcmp(ptr->name,label)==0){
           return ptr->address;
        }
    }
    return -1;
}
int computeOffset(int PC,int address){
    return address-(PC);
}

int main(int argc,char *argv[]){

}
int
readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
    char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;

    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
	/* reached end of file */
        return(0);
    }

    /* check for line too long */
    if (strlen(line) == MAXLINELENGTH-1) {
	printf("error: line too long\n");
	exit(1);
    }

    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n ]", label)) {
	/* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }

    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
        opcode, arg0, arg1, arg2);
    return(1);
}

int
isNumber(char *string)
{
    /* return 1 if string is a number */
    int i;
    return( (sscanf(string, "%d", &i)) == 1);
}

