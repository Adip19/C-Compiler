#include "firstPass.h"
int firstPass(struct translation_unit * prog, const char* amFileName, FILE *amFile) { 
    char line[81] = {0};
    /*int IC = 100, DC= 0; */
    /* 1 - Reset*/
    int errorFlag = 0;  
    int lineC=1; 
    struct phrase *line_struct =  calloc(1,sizeof(struct phrase));
    /*line_struct = {0};*/
    while(fgets(line,sizeof(line),amFile)){ /* 2- Read the line - if end go to 16 */
        get_phrase_from_line(line_struct, line);   /* מחזיר את העץ שבנינו*/
        if((line_struct->lineError[0]) != '\0') { /* בודק שגיאת תחביר */
            printf("%s:%d: syntax error: %s", amFileName,lineC,line_struct->lineError); 
            lineC++;  
            errorFlag = 1; 
            continue; /* Drop out of loop*/ 
        }
	else if(line_struct->phrase_type == phrase_empty){
            lineC++; 
            /*free(line_struct);
            free(labelFind);
            free(line);
            continue;*/
        }
    	printf("%s\n",line);
	 
    }
    return errorFlag;  
} 




    

