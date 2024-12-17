#pragma once
#include "helpFunctions.h"

struct ext *extSearch(struct ext *externals, const int externals_size, const char *name){
    int i;
    for(i=0;i<externals_size;i++){
        if(strcmp(name,externals[i].externalName)==0)
            return & externals[i];
    }
    return NULL;

}

struct label *labelLookUp(struct label *label_table,const int label_table_size, const char * name){ 
    int i;
    for(i=0; i<label_table_size;i++){ 
        if(strcmp(label_table[i].labName,name)==0)
            return &label_table[i]; 
       
    } 
        return NULL;
}

int get_phrase_from_line(struct phrase *newphrase, char *line){
    int i = 0;
    int j = 0;
    char *word, labelSave[MAX_LABELS], numSave[81];
    int lab = 0; /* Label definition */
    int result;
    char *char_p;
    int defineNum;                    
    /* Variables for scan label */
    char *first_operand; /* A variable holding the label in the first operand/parameter. */
    char *second_operand; /* A variable holding the label in the second operand/parameter. */
    int first_result; /* A variable that holds the result of the source operand/parameter. */
    int result_second = 0; /* A variable that holds the result of the target operand/parameter. */
    int first_operand_address; /* A variable that holds the types of addressing methods possible in the source argument. */
    int second_operand_address; /* A variable that holds the types of addressable methods possible in the target argument. */
    word = (char*)malloc(sizeof(char)); 
    while (line[i] != '\0' && isspace(line[i])) { /* Skip spaces */
        i++;
    }
    while(!isspace(line[i]) != 0) /* Get the first word */
    {
	 if(line[i] == '.') {
	   break;
	}
        
        word = (char*)realloc(word, sizeof(char)*(j+1));
        word[j] = line[i]; /* Copying word char by char */
        i++;
        j++;
        word = (char*)realloc(word, j+1);
        word[j] = '\0';
    }		
    /* 3 - Define checker */
   printf("line is:  %s\n", line);
   printf("i is:  %d\n", i);
    if(line[i] == '.')
    {
	while(!isspace(line[i]) != 0) /* Get the first word */
       {       
		word = (char*)realloc(word, sizeof(char)*(j+1));
		word[j] = line[i]; /* Copying word char by char */
		i++;
		j++;
		word = (char*)realloc(word, j+1);
		word[j] = '\0';
        }	
        if(strncmp(word,".define", 7) == 0)  /* Define found */
        {
            if(strlen(word) > 7) /* There is no space immediately after define  */
            {
                free(word);
                printf( "There is no space immediately after define\n"); 
                return -1;
            }
            free(word);
            /* Get the next word after define */
            word = (char*)malloc(sizeof(char)*MAX_LABELS); /* Allocating space for a label with a length of 30 characters + a string termination character. */
            memset(word, '\0', MAX_LABELS); /* Insert string-terminators for convenience. */
            while(line[i] == ' ' || line[i] == '\t')
            {
                i++;
            }            
            j = 0;
            while(i < strlen(line) && !isspace(line[i]) != 0)  /* Gets the word from the line */
            {
                if(j == MAX_LABELS-1)
                {
                    free(word);
                    printf( "A label name cannot be longer than the length\n"); 
                    return -1; /* A label name cannot be longer than the length */
                }
                word[j] = line[i]; /* Copying char by char */
                i++;
                j++;
            }
            while(i < strlen(line)) /* Check line from this place */
            {
                while(isspace(line[i])) /* Skip space */
                {
                   i++;
                }
		printf("IM: |%s|",word);
			printf("numSave Start is: |%s| \n", numSave);		
                if(line[i] == '=') /* Check if there's an equal sign '=' */
                {
		    i++;
                    while(isspace(line[i]))
		      i++;	
		    
		    j=0;
			printf("numSave Start is: |%s| \n", numSave);		
                    while(isdigit(line[i])) /* Skip whitespace after '=' */
                    {
			printf("numSave in %d is: |%s| \n", i ,numSave);		
			numSave[j]=line[i];
			j++;
                        i++;
                    } 
			
			printf("numSave is: |%s| \n", numSave);		
			printf("line[i] i:%d line[i] is:%c \n",i,line[i]);
			defineNum = atoi(numSave);
			printf("define num is: %d\n", atoi(numSave));
                            free(word);
                            break; /* delete ?? Return 0 indicating success */
		printf("Done check =\n\n");
                }    
                else /* If no digit is found after '=', return an error */
                {
	   	    printf("Word is: %s",word);
                    free(word);
                    printf( "Error code for incorrect define format\n"); 
                    return -1; /* Error code for incorrect define format */
                }
                i++;
            }
            /* If defined right - go on*/
                    printf( "Now ADDEFINE\n"); 
            addDefine(newphrase, word, defineNum); /* Inserting the label name and value 2 as mdefine type and internal */
	    return 0;
        }
    }   
	 
    /* 5 - Is label? If not: 7 */
    /*if(line[i] == ':') Label checker*/
    char_p = strchr(line, ':');
    if(char_p)
    {
       	printf("Label found: %s\n",word);
        strcpy(labelSave, word);
        free(word);
        i++; /* Next char */
        lab = 1; /* 6 - The flag turn on */
        word = (char *)malloc(sizeof(char));
        while(line[i] == ' ' || line[i] == '\t')
        {
            i++;
        }
        j = 0;
        while(!isspace(line[i]) != 0) /* The word after the label */
        {
            word = (char *)realloc(word, sizeof(char)*(j+1));
            word[j] = line[i]; /* Inserting the character from the line into its place in the word. */
            i++;
            j++;
        }
        word = (char *)realloc(word, j+1);
        word[j] = '\0';

    }
    /*
    From this line of code, the function runs on the word read after the label or the first word received if not a label.
    "lab" is used as a flag for the function with whether or not a label appeared at the beginning of the line.
    */
    
    /* 7 - data/string? If not go to 10 */
    if(word[0] == '.') /* Data was found */
    {
printf(". FOUND*****\n");
        if(strncmp(word,".data", 5) == 0)
        { 
		printf("DATA FOUND*****\n");
            if(strlen(word) > 5) /* Wrong definition */
            {
                free(word);
                printf("There is no space immediately after the data directive sentence \n");
                return -1; /* There is no space immediately after the data directive sentence */
            }
            result = data_instruction(newphrase, line, i, labelSave, word); /* Checks numbers */
            if( result != -1)
            {
                addLabelData(newphrase, labelSave, word); /* Inserting the label name and word number into the Struct array. */
                return 0;
            }
            free(word);
            return -1;
        }
        
        if(strncmp(word,".string", 7) == 0) /* String was found */
        { 
	    printf("String FOUND*****\n");
            if(strlen(word) > 7) /* There is no space immediately after the directive sentence */
            {
                free(word);
                printf("There is no space immediately after the directive sentence\n");
                return -1;
            }

            lab = stringCase(newphrase, line, i);
			printf("lab is:|%d|\n",lab);
printf("word is:%s\n",word);
	while(line[i] == ' ' || line[i] == '\t' || line[i] == '"')
        {
            i++;
        }
        j = 0;
	while(!isspace(line[i]) != 0) /* The word after the label */
        {
            word = (char *)realloc(word, sizeof(char)*(j+1));
            word[j] = line[i]; /* Inserting the character from the line into its place in the word. */
            i++;
            j++;
        }
	j--;
	word[j] = '\0';
printf("word is:%s\n",word);
            if(lab != -1)
            {
                addLabelString(newphrase, labelSave, word); /* Inserting the label name and word number into the Struct array. */
                return 0;
            }
            free(word);
            return lab;
        }

	/* 10 - extren/entry? If no go to 12  לא נבדק!!!! */
        if(strncmp(word,".entry", 6) == 0) /* Entry was found */
        {
            if(strlen(word) > 6 ) /* There is no space immediately after the directive sentence. */
            {
                free(word);
                printf("There is no space immediately after the directive sentence.\n");
                return -1;
            }
            free(word);
            /* Get the next word after entry */
            word = (char*)malloc(sizeof(char)*MAX_LABELS); /* Allocating space for a label & a string termination character. */
            memset(word, '\0', MAX_LABELS); /* Insert string-terminators for convenience. */
            while(line[i] == ' ' || line[i] == '\t') /* Skips spaces */
            {
                i++;
            }            
            j = 0;
            while(i < strlen(line) && !isspace(line[i]) != 0) /* Gets the word */
            {
                if(j == MAX_LABELS-1)  /* Label name exceeded length characters. */
                {
                    free(word);
                    printf(" A label name cannot be longer than 31 characters.\n");
                    return -1; /* A label name cannot be longer than 31 characters. */
                }
                word[j] = line[i]; /* Copying char by char */
                i++;
                j++;
            }    
            while(i < strlen(line)) /* Checks line */
            {
                if(!isspace(line[i]) != 0)  /* Non-white character is found */
                {
                    free(word);
                    printf(" A label name cannot be longer than 31 characters.\n");
                    return -1; /* There is an invalid character at the end of the line. */
                }
                i++;
            }
            addLabelEntry(newphrase, labelSave, word); /* Inserting the label name and value 1 into the label array */
 	    return 0;

        }
         
        printf("before extern\n");
        if(strncmp(word,".extern", 7) == 0)  /* 11 - Extern found, If not extrnal go to 2 */
        {
		printf("IM EXTERN\n");
            if(strlen(word) > 7) /* There is no space immediately after the directive sentence */
            {
                free(word);
                printf("There is no space immediately after the extern directive sentence\n");
                return -1; /* There is no space immediately after the extern directive sentence */
            }
            free(word);
            /* Get the next word after extern */
            word = (char*)malloc(sizeof(char)*MAX_LABELS); /* Allocating space for a label with a length of 30 characters + a string termination character. */
            memset(word, '\0', MAX_LABELS); /* Insert string-terminators for convenience. */
            while(line[i] == ' ' || line[i] == '\t') /* Skips spaces */
            {
                i++;
            }            
            j = 0;
            while(i < strlen(line) && !isspace(line[i]) != 0) /* Gets the word */
            { 
                if(j == MAX_LABELS-1)
                {
                    free(word);
                    printf("A label name cannot be longer than 31 characters.\n");
                    return -1; /* A label name cannot be longer than 31 characters. */
                }
                word[j] = line[i]; /* Inserting the character from the line into its place in the word. */
                i++;
                j++;
            }
            while(i < strlen(line))  /* Checks line from this index */
            {
                if(!isspace(line[i]) != 0) /* Non-white character is found */
                {
                    free(word);
                    printf("There is an invalid character at the end of the line\n");
                    return -1; /* There is an invalid character at the end of the line */
                }
                word[j] = line[i]; /* Copying char by char */
                i++;
                j++;
            } 
            addLabelExtern(newphrase, labelSave, word); /* Inserting the label name and value 1 into the label array */
	    return 0; /* The line was successfully received */
        }
            /*free(word);*/
            
        
        /*free(word);*/
        printf("Command prompt not recognized\n");
        return -1; /* Command prompt not recognized */
    }
printf("Word is:%s\n",word);
    result = what_command(word); /* 13 - Check command type - another file */
    /*free(word);*/
    if(result == -1)
    {
        printf("The action word in the line is incorrect.\n");
        return -1; /* The action word in the line is incorrect. */
    }
	printf("*****RESTULT IS:%d*****\n",result);
    /* 14 - Operand analyzer */
    /* שיטות מיעון 2 אופרנדים*/
    if((result >= 0 && result <= 3) || result == 6) /* The commands: mov, cmp, add, lea */
    {
	printf("result in if 0-3:%d\n",result);
        first_operand = (char*)malloc(sizeof(char)*MAX_LABELS); /* Allocation of space for two possible lab. */
        memset(first_operand,'\0',MAX_LABELS); /* Insert string-terminators for convenience. איפוס */
        second_operand = (char*)malloc(sizeof(char)*MAX_LABELS);
        memset(second_operand,'\0',MAX_LABELS); /* Insert string-terminators for convenience. איפוס */
        if(result == 6) /* lea */
        { 
            first_operand_address = 1; /* lea can get 1,2 */
        }
        else /* mov, cmp, add or sub */
        {
                first_operand_address = 2; /* get 0,1,2,3 */
        }
	printf("before if\n");
            first_result = find_operand(newphrase, line, &i, &first_operand_address, 0); /* The function identifies the number/label/register. */
            			    printf("first result:%d\n",first_result);

                printf("after if...\n");
	    if(first_operand_address == -1) /* An error was detected in the line. */
            {
                /*free(first_operand);
                free(second_operand);*/
                printf("An error was detected in the line.\n");
                return -1;  /* Returns error */
            }
            /* Get the second operand - it can get  1, 3 */
            i++;
            if(result == 1) /* cmp can get 0,1,2,3 */
            { 
                second_operand_address = 5;
            } 
            else /* mov, add, sub, lea */ 
            {
                second_operand_address = 3; /* get 1,2,3*/
            }
            result_second = find_operand(newphrase, line, &i, &second_operand_address, 1); /* The function identifies the number/label/register. */
            if(second_operand_address == -1) /* An error was detected in the line. */
            { 
                /*free(first_operand);
                free(second_operand);*/
                printf("HERE An error was detected in the line.\n");
                return -1;
            }
            if(first_operand_address == -1) /* An error was detected in the line. */
            { 
                /*free(first_operand);
                free(second_operand);*/
                printf("An error was detected in the line.\n");
                return -1;
            } 
    
		printf("$$$$$$$$$Arrived to methods\n");
        printf("first_operand_address is:%d\n",first_operand_address);
        printf("second_operand_address is:%d\n",second_operand_address);


	/* שיטות מיעון */
           /* כש2 האופרנדים מסוג 3 -  האופציה היחידה והמיוחדת היא רגיסטרים */
            if(first_operand_address == 3 && second_operand_address == 3) /* If both operands found are registers.  */
            { 
		printf("IM in reg option\n");
                newphrase->phrase_options.inst.operands[0].operands_type = phrase_reg;
                newphrase->phrase_options.inst.operands[0].operand_options.reg = result_second;
                newphrase->phrase_options.inst.operands[1].operand_options.reg = first_result;
                /*free(first_operand);
                free(second_operand);*/
                return 0; /* The line was successfully encoded. */
            }
	 /* בדיקת שאר שיטות המיעון */
            /* אם האופרנד הראשון מותאם לשיטת מיעון הבאות*/
            switch (first_operand_address) /* Coding the word according to the method of addressing found. */
            {
                case phrase_immed: /* Immediate addressing method מספר או קבוע*/
		    printf("IM in immed option 1\n");
                    if(first_result != 0) /* אם מספר/אחרת מגדיר בפונקצית חיפוש */
                    {
                        
                        newphrase->phrase_options.inst.operands[0].operand_options.immed = first_result;
                        break;
                    }
                case phrase_label: /* Direct address metohd */
                    /*newphrase->phrase_options.inst.operands[0].operand_options.label = first_result;*/
                    break;
                case phrase_idx: /* אינדקס עם לייבל*/
                    if(first_result != 0) /* תווית */
                    {
                        
                       printf("NUMBER\n");
                        newphrase->phrase_options.inst.operands[1].operand_options.index.idx_options.number = first_result;
                        break;
                    }
		    printf("opeand[1] is:%d\n",newphrase->phrase_options.inst.operands[1].operand_options.index.idx_options.number);
	    }
                    /* תתקדם כמות לפי הסוגריים */
                    /* הדפס את הערך */
                    /* לתאם עם ענבר */
    

	    switch (second_operand_address) /* Coding the word according to the method of addressing found */
            {
                case phrase_immed: /* Immediate addressing method מספר או קבוע*/
		    printf("IM in immed option 2\n");
                    if(result_second == 2) /* לבדוק איך למצוא  - קבוע */
                    {
                        /*newphrase->phrase_options.inst.operands[1].operand_options.label = result_second;*/
                        break;
                    }
                    else /* מספר */
                    {
                        newphrase->phrase_options.inst.operands[1].operand_options.immed = result_second;
                        break;
                    }
                case phrase_label: /* Direct address metohd */
		    printf("IM in label option 2\n");
                    /*newphrase->phrase_options.inst.operands[1].operand_options.label = result_second;*/
                    break;
                case phrase_idx: /* אינדקס עם לייבל*/
		    printf("IM in idx option 2\n");
			printf("result_second is: %d\n",result_second);
                    if(result_second ==  2) /* תווית */
			{
                        /*newphrase->phrase_options.inst.operands[1].operand_options.index.idx_options.label = result_second;*/
			}
                    else /* מספר */
			{
                        newphrase->phrase_options.inst.operands[1].operand_options.index.idx_options.number = result_second;
			}
	                 
            }
            free(first_operand);
            free(second_operand);
            return 0; /* The line was successfully encoded. */
     } /* End of the instruction that accepts 2 operands. */
else if((result >= 4 && result <= 13) || result != 6) /* sub, not, clr, inc, dec, jmp, bne, red, prn, jsr*/
    {   
            first_result = (int)malloc(sizeof(char)*MAX_LABELS); /* Allocation of size 31 for an optional label. */
            /*memset(first_result,'\0',MAX_LABELS);  Insert string-terminators for convenience. */
            if(result == 4 || result == 5 || result == 7 || result == 8 || result == 11) /* not, clr, inc, dec - methods 1,2,3. */
            {
                first_operand_address = 3;
                first_result = find_operand(newphrase, line, &i, &first_operand_address, 0); /* The function identifies the label/register. */
                if(first_operand_address == -1) /* Error */
                {
                    /*free(first_result);*/
                    return -1; /* Returns the error number */
                }
            }
            
            if(result == 9 || result == 10 ||result == 13) /* jmp, bne, jsr - methods 1, 3 */
            {
                first_operand_address = 4;
                first_result = find_operand(newphrase, line, &i, &first_operand_address, 0); /* The function identifies the number/label/register. */
                if(first_operand_address == -1) /* Error */
                {
                    /*free(first_result);*/
                    return first_result;
                }
            }
            
            if(result == 12)  /*prn - methods 0,1,2,3. */
            {
                first_operand_address = 5;
                first_result = find_operand(newphrase, line, &i, &first_operand_address, 0); /* The function identifies the number/label/register. */
                if(first_operand_address == -1) /* Error */
                {
                    /*free(first_result);*/
                    printf("Error - operned was not defined \n");
                    return -1;
                }
            }
        switch (first_operand_address) /* Coding the word according to the method of addressing found. */
            {
                case phrase_immed: /* Immediate addressing method מספר או קבוע*/
                    if(first_result != 0) /* אם מספר ואם קבוע זה בפונקציית חיפוש */
                    {
                        newphrase->phrase_options.inst.operands[0].operand_options.immed = first_result;
                        break;
                    }
                case phrase_label: /* Direct address metohd */
                   /* newphrase->phrase_options.inst.operands[0].operand_options.label = first_operand;*/
                    break;
                case phrase_idx: /* אינדקס עם לייבל*/
                    if(result_second != 0) /* אם מספר */
                        newphrase->phrase_options.inst.operands[1].operand_options.index.idx_options.number = result_second;
                    /* תתקדם כמות לפי הסוגריים */
                    /* הדפס את הערך */
                    /* לתאם עם ענבר */
        
        /*free(first_result); */
        return 0; /* The line was successfully encoded. */        
    }
}
    if(result == 14 || result == 15) /* rts or hlt */
    {
	printf("im rts or hlt\n");
        while(i < strlen(line)) /* Checking the line */
        {
            if(!isspace(line[i]) != 0 && line[i] != '\0')  /* There is a char after the label */
            {
                printf("There is a char after the label\n");
                return -1;
            }
            i++;
        }
	newphrase->phrase_type= phrase_inst;
	strcpy(newphrase->phrase_options.inst.operands[0].operand_options.label,labelSave);
	newphrase->phrase_options.inst.operands[0].operands_type = phrase_label;
	newphrase->phrase_options.inst.inst_type = result;
	printf("phrase type is:%d",newphrase->phrase_type);
        return 0;
    }

    return 0;
}
 

/* Function to determine the command type */ 
int what_command(char *input_word) { 



    if(strcmp(input_word, "mov") == 0 )  

        return  0; 

    if(strcmp(input_word, "cmp") == 0 ) 

        return  1; 

    if(strcmp(input_word, "add") == 0 ) 

        return  2; 

    if(strcmp(input_word, "sub") == 0 ) 

        return  3; 

    if(strcmp(input_word, "lea") == 0 ) 

        return  6; 

    if(strcmp(input_word, "not") == 0 ) 

        return  4; 

    if(strcmp(input_word, "clr") == 0 ) 

        return 5; 

    if(strcmp(input_word, "inc") == 0 ) 

        return 7; 

    if(strcmp(input_word, "dec") == 0 ) 

        return 8; 

    if(strcmp(input_word, "jmp") == 0 ) 

        return 9;     

    if(strcmp(input_word, "bne") == 0 ) 

        return 10; 

    if(strcmp(input_word, "red") == 0 ) 

        return 11; 

    if(strcmp(input_word, "prn") == 0 ) 

        return 12; 

    if(strcmp(input_word, "jsr") == 0 ) 

        return 13;     

    if(strcmp(input_word, "rts") == 0 ) 

        return  14; 

    if(strcmp(input_word, "hlt") == 0 ) { 

        return 15; 

    }     

    return -1; /* If no suitable word is found. */ 

 } 

/* Converts a string to its binary representation and adds it to the temporary file with the extension .an */
int stringCase(struct phrase *newphrase, char *name, int index)
{
    int i  = index;
    int j=0;
    int length;
    char copyWord[1024];
    /* int num_count = 0;  Counts the number of code words-the letters entered into the array */
    struct myStruct *arr = NULL; /* An array that stores all the code words - the letters found */
    printf("name is:|%s|\n",name);
    if(name[i] != ' ') /* There is no space between the instruction for quotation marks */
    {
        printf("There is no space between the instruction for quotation marks\n");
        return -1;
    }
i++;
    printf("name is:|%c|\n",name[i]);
	printf("name is:|%s|\n",name);
    while(name[i] == ' ' || name[i] == '\t')  /* Skips spaces */
    {
        i++;
    }
    if(name[i] != '"' ) /* Incorrect opening of quotation marks */
    {
        printf("Incorrect opening of quotation marks\n");
        return -1;
    }
    i++;
    if(name[i] == '"') /* A data instruction that does not have a single letter  */
    {
        return 0;
    }

     while(name[i] != '"' && name[i] != '\0') /* Checking for ending quote */
     {
        
	
        if(j == MAX_LABELS-1)
        {
            /*free(name);*/
            printf("A label name cannot be longer than the length\n");
            return -1; /* A label name cannot be longer than the length */
        }
        copyWord[j] = name[i]; /* Copying char by char */
printf("i is:%d\n",i);
    printf("name is:|%c|,copyword is:|%c|\n",name[i],copyWord[j]);
        i++;
        j++;
    }
copyWord[j] = '\0';
    if(name[i] != '"') /* Incorrect closing quotation marks */
    {
        free(arr);
        printf("Incorrect closing quotation marks\n");
        return -1;
    }
    i++;
    while(name[i] == ' ' || name[i] == '\t')   /* Skips spaces */
    {
        i++;               
    }
    if(name[i] != '\0' && name[i] != ' ' && name[i] != '\t' && name[i] != '\n') /* Checks for end of line */
    {
            free(arr);
            printf("Incorrect closing quotation marks\n");
            return -1; /* The command line string is not properly terminated */
    }
printf("copy is:|%s|\n",copyWord);
    /* If String is correct copy to the data array in the struct */  
        length = strlen(copyWord);
        newphrase->phrase_options.directive.directive_options.string = (char *)malloc(length * sizeof(char));
        if (newphrase->phrase_options.directive.directive_options.string == NULL)
        {   
            fprintf(stderr, "Memory allocation failed\n"); 
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < length; j++) { 
            newphrase->phrase_options.directive.directive_options.data[j].number = (int)copyWord[j];
		printf("String[%d] is:|%d|\n",j,newphrase->phrase_options.directive.directive_options.data[j].number);
        } 

    
    return 0;
}

/* Checks the data instruction and add the numbers to the code word array */
int data_instruction(struct phrase *newphrase, char *str, int index, char * labelSave, char * word)
{
    int num; /* Value */
    int sign = 1; /* Plus/Minus */
    int i = 0; /* Index */
    int idxData = 0;
    char* p = (index+str); 
    int num_count = 0; /* Count number of codewords */
    struct label *array = NULL; /* An array that stores all the code words - the numbers found */
    char *wordData;
    while(*p != '\0')
    {  
        while (*p == ' ' || *p == '\t' || (*p == ',' && *(p+1) == ' ')) /* Skips before comma */
        {
            p++;
        } printf("p is:%s,char is\n",p);
		printf("p isalpha(*p):%d\n",isalpha(*p));
        if(*p == '\n' && num_count == 0)  /* There is no char  */
        {
            return 0;
        }
        if(*p == '\0')  /* Check if its the end of the string */
        {
            break;
        }
        /*if(isalpha(*p))*/
	else
        {
            int j = 0;
            wordData = (char*)malloc(sizeof(char)*MAX_LABELS); /* Allocating space for a label & a string termination character. */
            memset(wordData, '\0', MAX_LABELS); /* Insert string-terminators for convenience. */
            while (*p != ' ' && *p != '\n' && *p != '\0') /* Get the word until space or newline */
            {
                wordData[j++] = *p;
                p++;
            }
            wordData[j] = '\0';
	    printf("wordData is:|%s|",wordData);
            if(*p == '-')  /* Check for minus */
            {
                if(sign == -1) /* There was already a minus sign in that number */
                { 
                    free(array);
                    printf("Double minus sign.\n");
                    return -1; /* Double minus sign. */
                }
                sign = -1; /* Put the value -1 to indicate a negative number */
                p++;
            }
            else if( *p == '+')  /* Checks plus */
            {	
                if(*p == '+')
                { 
                    if(sign == -1) /* Checking whether a minus has already been marked. */
                    { 
                        free(array);
                        printf("Plus sign after minus.\n");
                        return -1; /* Plus sign after minus. */
                    }
                    p++;
                }
                else {
                    if(!isdigit(*p)) /* Checking whether the character is valid. */
                    { 
                        free(array);
                        printf("Invalid character in the data statement.\n");
                        return -1; /* Invalid character in the data statement. */
                    }
                }
            }
            
            /* Checks numbers */
            num = atoi(wordData);

            while(isdigit(*p)) /* Checks digits */
            { 
                num = num * 10 + (*p - '0'); /* Building the number */
                p++;
            }
		printf("build num is:%d\n",num);
            if(sign == 0 || (num == 0 && *(p-1) != '0')) /* Check number */
            {
                free(array);
                printf("****The number is invalid.\n");
                return -1; /* The number is invalid. */
            }     
            if(sign * num > 16383 || sign * num < -8192)
            {
                printf("The number out of range.\n");
                return -1; /* The number out of range. */
            }
            /* here */
            newphrase->phrase_options.directive.directive_options.data[idxData].number = num;
            idxData++;
            i++;
            

            /* Check for comma */
            while (*p == ' ' || *p == '\t') /* Skips spaces */
            {
                p++;
            }
            if(*p == ',')
            {
                p++;
                while(*p == ' ' || *p == '\t' ) /* Skips spaces */
                {
                    p++;
                }
                if (*p == ',') /* Found dobule comma */
                {
                    free(array);
                    printf("Consecutive commas in the data instruction.\n");
                    return -1; /* Consecutive commas in the data instruction. */
                }
                sign = 1;
            }
            
    }    
printf("Word is:%s\n",wordData);
    strcpy(word,wordData);	
} 
    free(array);    
    return 0;

}


/*The function sends the row and index to discover each operand in turn. It returns the name of the number or register or zero if it is a label*/
int find_operand(struct phrase *newphrase, char *line, int *index, int *address, int operandPlc)
{
    int i = *index;
    int j = 0;
    int checker = -1;
    char *labelOption;
	printf("line[%d] is - %c|\n",i,line[i]);  
    while(line[i] == ' ' || line[i] == '\t') /* Skips spaces */
    {
        i++;
    }
	printf("line[%d] is:%c|\n",i,line[i]);  
    switch(line[i]) /* Checking every line */
    {   
        case '#' : /* Immediate method check */ 
		printf("in Case #\n");
            i++;
            if(*address == 1 || *address == 3 || *address == 4) /* mov cmp add sub not clr leaX2 inc dec jmp bne red jsr */
            {
                *address = -1;
                printf("Immediate addressing method is not valid in this operation.\n");
                return -1; /* Immediate addressing method is not valid in this operation. */
            }
            checker = Address1_fixed_number(line, &i, address,operandPlc);
            	printf("HERE\n");
            if(*address == -1)  /* No correct addressing method was found */
            {
                *index = i;
                printf("No correct addressing method was found.\n");
                return -1; /* Returns the error number */
            }
            
            if(*address == 5) /* The second operand of the instruction word cmp */
            { 
                while(i < strlen(line)) /* Check all the line */
                { 
                    if(!isspace(line[i]) != 0)  /* If there is a character that is not a white character */
                    {
                        *address = -1;
                        printf("There is an invalid character at the end of the line.\n");
                        return -1; /* There is an invalid character at the end of the line */
                    }
                 i++;    
                }
            }

            newphrase->phrase_options.inst.operands[operandPlc].operands_type = phrase_immed;
            *address = 0;  /* For immediate method */
            *index = i;
            newphrase->phrase_options.inst.operands[operandPlc].operand_options.immed = checker;
            return 0; /* Returns the constant number. */
        case 'r': /* Register check - first operand */
	   printf("in Case r\n");
            i++;
		printf("line[%d] is:%c\n",i,line[i]);
            if(line[i] >= '0' && line[i] <= '7') /* the method will return -1 if it is not register */
            {
                checker = line[i] - 48;

		printf("checker is:%d\n",checker);
                i++;
                if(i+1 == strlen(line) ||line[i+1] == ' ' || line[i+1] == '\t' || line[i+1] == ',')
                {
                    if(*address == 1)  /* The first operand for the instruction lea */
                    {
                        *address = -1;
                        printf("Register addressing method is not valid in this operand.\n");
                        return -1; /* Register addressing method is not valid in this operand. */
                    } /* End lea */
                    while(i < strlen(line) && (line[i] == ' ' || line[i] == '\t'))
                    { 
                        i++;
                    }
                    if(*address == 2)  /* First operand of the instructions of the first type */
                    {
                        if(i == strlen(line))
                        {
                            *address = -1;
                            printf("Instructions of this type contain an additional openend, which is not found.\n");
                            return -1;  /* Instructions of this type contain an additional openend, which is not found */   
                        }
                        if(line[i] != ',')
                        {
                            *address = -1;
                            printf("Missing comma after first operand.\n");
                            return -1;  /* Missing comma after first operand */   
                        }
                        else
                        {
                            *index = i;
                           *address = 3; /*For direct regiester method*/
                            newphrase->phrase_options.inst.operands[operandPlc].operands_type = phrase_reg;
                            newphrase->phrase_options.inst.operands[operandPlc].operand_options.reg = checker;
                            return checker; /* Returning the number of the register*/
                        }
                    }
                    while(i < strlen(line) && (line[i] == ' ' || line[i] == '\t')) /* Skips spaces */
                    { 
                        i++;
                    }
                    if(line[i] == '\0' || line[i] =='\n' || i+1 == strlen(line)) /* Check if there is only space to the end */
                    {
                        newphrase->phrase_options.inst.operands[operandPlc].operands_type = phrase_label;
                        newphrase->phrase_options.inst.operands[operandPlc].operand_options.immed = checker;
                        return checker; /* Returning the number of the register*/
                    }
                    else
                    {
                        *address = -1;
                        if(line[i] == ',')
                        {
                            printf("Invalid comma\n");
                            return -1; /* Invalid comma */    
                        }
                        printf("There is an invalid character at the end of the line\n");
                        return -1; /* There is an invalid character at the end of the line */
                    }
                }
                else /* Probably label starting with r and number */
                {
                    i--;    
                }
                i--;
            } /* end start of register */
        default:
		printf("in Case defult\n");
            if(!isalpha(line[i]) != 0)
            {
                *address = -1; /* No correct addressing method was found */
                printf("No correct addressing method was found\n");
                return -1; /* it cont be a label - an recognize oprator*/
            }
            j = 0;
            labelOption = (char *)malloc(sizeof(char));
            while(i < strlen(line) && !isspace(line[i]) != 0)
            {
                if(line[i] == ',')
                {
                    if(*address != 1 )
                    {
                        *address = -1;
                        printf(" HERE Invalid comma\n");  
                        return -1; /* Invalid comma */
                    }
                    break;
                }
                if(line[i] == '[') /* Index define method */
                {
		        i++;		
	            printf("after [\n");
                    j = 0;
                    *address = 2;
                    if(*address == 2)
                    {
                        printf("in address 2\n");
                            *index = i;
                        while((!isspace(line[i]) != 0) && line[i] != ']') /* Get the first word */
                        {       
                            labelOption[j] = line[i]; /* Copying word char by char */
                            i++;
                            j++;
                        }	
                        newphrase->phrase_options.inst.operands[operandPlc].operands_type = phrase_idx;
                        labelOption[j] = '\0'; /* end of get the word */
					    printf("labelOptions is***:%s\n",labelOption);
                                   printf("IM before is number\n");
                        if(isNumber(labelOption))
			{
                            newphrase->phrase_options.inst.operands[operandPlc].operand_options.index.idx_options.number = atoi(labelOption);
			}
			else if(!isNumber(labelOption))
			{
                            newphrase->phrase_options.inst.operands[operandPlc].operand_options.index.label = labelOption;
			}
                                           
                        else 
                        {
                            newphrase->phrase_options.inst.operands[operandPlc].operand_options.index.idx_options.label = labelOption; 
                            /*  לבדוק שהעתיק */
                            free(labelOption);
                            /*free(checkerOpe);*/
                            return 0; 
                        } 
                    }
                    if(*address == 4) /* שיטות מיעון שלא מקבלות את אינדקס */
                    {
                        *address = -1;
                        free(labelOption);
                        printf("index method is illegal in this instruction.\n");  
                        return -1; /* Jump addressing method is illegal in this instruction. */
                    }    
                }
                labelOption = (char*)realloc(labelOption, sizeof(char)*(j+1));
                labelOption[j] = line[i]; /* Copy the word */
                                            		printf("HERE***:%c\n",line[i]);

                i++;
                j++;

            }
            j--;
            labelOption = (char*)realloc(labelOption, j+1);
		j++;
            labelOption[j] = '\0'; /* end of get the word */  
            printf("labeloption***:%s\n",labelOption);
              
        }
            *index = i; /* The value of the index in line */
            newphrase->phrase_options.inst.operands[operandPlc].operands_type = phrase_label ; /* Dirrect method */
            newphrase->phrase_options.inst.operands[operandPlc].operand_options.label = labelOption ; /* Dirrect method */
            free(labelOption);
            printf("labeloption:%s\n",labelOption);
            return 2;

}



/*A function that get a line, an index and a case type and checks if it is correct and if not returns minus 1*/
int Address1_fixed_number(char *line, int *index, int *address_case, int operandPlc)
{
    int i = *index;
    int cursor = 0; /* A marker intended to indicate different states in a line */ 
    int num = 0;
    char *p = (line+(*index));
        if(*address_case != 1 && *address_case != 4 && *address_case != 6)
        {
            *address_case = -1;
            printf("Invalid immediate addressing method in this action word.\n");
            return -1; /* Invalid immediate addressing method in this action word. */
        }
        cursor = 1;
        if(*p == '-' )
        {
            cursor = -1;
            p++;
            i++;
            }
        if(*p == '+')
        {
            if(cursor == -1) /* If there was already a minus */
            {
                *address_case = -1;
                printf("There is already a minus.\n");
                return -1; /*There is already a minus*/
            }
            p++;
            i++;
        }
        if(isdigit(*p) == 0) /* The character is not a number */
        {
            *address_case = -1;
            printf("Illegal char\n");
            return -1; /* Illegal char */
        }
        while(!isdigit(*p) == 0)  /* While digit - Build the number */
        {
            num = num * 10 + (*p - '0');
            p++;
            i++;
        }
        if( num*cursor > 4095 || num*cursor < -2047)
        {
            *address_case = -1;
            printf("The number out of range\n");
            return -1; /*The number out of range*/
        }
        if(*address_case == 4 || *address_case == 1)
        {
            while(*p == ' ' || *p =='\t') /* Skip spaces */
            {
                p++;
                i++;
            }
        }
        if(*p == '\0' || *p =='\n') /* Spaces to the end */
        {
            if(*address_case == 5) /* prn or cmp */
            {
                *address_case = -1;
                printf("the line end - missing data\n");
                return -1; /* the line end - missing data */ 
            }
            else
            {    
                *address_case = 2; /* mov cmp add sub*/
                *index = i;
                return(num*cursor);
            }
        }
        /* In case there is a character after the number or after the space promotion */
        if(*address_case != 1)  /* Check !!!!!  Only in methods where the operand is a source operand, there can be a character after the space */
        {
            *address_case = -1;
            printf("the line doesnt ends corectlly\n");
            return -1; /* the line doesnt ends corectlly */     
        }
         *address_case = 2;
         *index = i;
         return (num*cursor);
}

