
#include "label.h"

int what_command(char *input_word);

/* The function gets a label name and checks if it's existence */ 
int label_existence(struct label *label_table,char *label) 
{ 
    int i; 
    if(strlen(label) > MAX_LABELS) 
    {  
        return -1;     
    } 
    if(what_command(label) != -1) /* A label name cannot be an instruction name. */ 
    { 
        return -1;  /* לא הצלחנו לטפל עדיין - לבדוק */
    } 
    if(!isalpha(label_table[0].labName) != 0) /* A label name cannot start with a non-letter character */   
    { 
        return -1; 
    } 
     

    for(i = 1; i < sizeof(label_table); i++) /* Cheack whether there are not number/letter */ 

    {  

        if(!isalnum(label_table[i].labName) != 0) /* A label name cannot contain characters other than letters or numbers */ 

        { 

            return -1;    

        } 

    } 

    if(strlen(label_table[i].labName) == 2 && label_table[i].labName[0] == 'r' && label_table[i].labName[1] <= 7 && label_table[i].labName[1] >= 0) /* A label name cannot be a register name */ 

    { 

        return -1;  

    } 

    if(label_table[i].labType > 1) /* A label name cannot be the name of a directive statement */ 

    {  

        return -1;  

    }   

    return 0; 

} 



void addDefine(struct phrase *newphrases, char *word, int number) {
        printf("word in addDefine: %s\n",word);
newphrases->phrase_options.define.label = malloc(strlen(word)+1);
newphrases->phrase_type = 4; /* Set the type of the phrase to define */
        strcpy((newphrases->phrase_options.define.label), word); /* Copy the label name */
        printf("label in addDefine: %s\n",newphrases->phrase_options.define.label);
newphrases->phrase_options.define.number = number; /* Copy the number */
        newphrases->phrase_options.directive.directive_type = phrase_data; /* Set directive type to data */
        newphrases->phrase_options.directive.directive_options.data[0].data_options = data_label; /* Set data option for the first data */
        newphrases->phrase_options.directive.directive_options.data[1].data_options = data_count; /* Set data option for the second data */

printf("number in addDefine: %d\n",newphrases->phrase_options.define.number);
}




void addLabelData(struct phrase *newphrases, char *labelSave, char *word) {
        newphrases->phrase_type = 2; /* Set the type of the phrase to dirctive */
        newphrases->phrase_options.directive.directive_type = phrase_data; /* Set directive type to data */
        newphrases->phrase_options.directive.directive_options.label = labelSave; /* Set data name */
        newphrases->phrase_options.directive.directive_options.string = word; /* Set data string */
printf("label in addLabelData -  word: %s\n",newphrases->phrase_options.directive.directive_options.string);
printf("label in addLabelData -  label: %s\n",newphrases->phrase_options.directive.directive_options.label);

    }

void addLabelString(struct phrase *newphrases, char *labelSave, char *word) { /* לטפל במערך נתונים */
        newphrases->phrase_type = 2; /* Set the type of the phrase to directive */
        newphrases->phrase_options.directive.directive_type = phrase_string; /* Set directive type to data */
        newphrases->phrase_options.directive.directive_options.label = malloc(strlen(labelSave)+1); /* Set data name */
	strcpy((newphrases->phrase_options.directive.directive_options.label), labelSave); /* Copy the label name */
printf("label in addString -  label: %s\n",newphrases->phrase_options.directive.directive_options.label);
        newphrases->phrase_options.directive.directive_options.string = word; /* Set data string */
printf("word is:%s\n",word);
printf("label in addString -  word: %s\n",newphrases->phrase_options.directive.directive_options.string);


    }

void addLabelEntry(struct phrase *newphrases, char *labelSave, char *word) {
        newphrases->phrase_type = 2; /* Set the type of the phrase to directive */
        newphrases->phrase_options.directive.directive_type = phrase_entry; /* Set directive type to data */
        newphrases->phrase_options.directive.directive_options.label = word; /* Set data string */

    }

void addLabelExtern(struct phrase *newphrases, char *labelSave, char *word) {
        newphrases->phrase_type = 2; /* Set the type of the phrase to directive */
        newphrases->phrase_options.directive.directive_type = phrase_extern; /* Set directive type to data */
        newphrases->phrase_options.directive.directive_options.label = word; /* Set data string */

    }
