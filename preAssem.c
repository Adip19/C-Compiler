
#include "preAssem.h"
#define AFTER_SPACE(s) while (*s && isspace(*s)) s++ 
#define WHITESPACES " \t\n\f\r\v" 
#define strcatWithMalloc(s1,s2) strcat(strcpy(malloc(strlen(s1)+strlen(s2)+1),s1),s2)

struct Macro *searchMacro(struct Macro *macro_table, const int tableSize, const char *name) { 
    int i; 
    for (i = 0; i < tableSize; i++) { 
        if (strcmp(macro_table[i].mName, name) == 0) {
            return &macro_table[i]; }
    } 
    return NULL; 
} 

int macro_line(char *s, struct Macro **mcr, struct Macro *m_table, int *m_table_size, int *flag) { 
    char *c1, *c2 = '\0'; 
    struct Macro *f;
    AFTER_SPACE(s);
    c1 = strstr(s, "endmcr"); /* endmacro*/
    if (c1) {
	flag = 0;
        *mcr = NULL; 
        return 0; 
    } 
    c1 = strstr(s, "mcr");
    if (c1) { /* def macro */
	if (*mcr == NULL) {
	    *mcr = malloc(sizeof(struct Macro));
	    if (*mcr == NULL) {
		fprintf(stderr, "Error: Unable to allocate memory for struct Macro\n");
		return -1;
	    }
	    (*mcr)->lineC = *m_table_size;
        c1 += 3; /* Updated the position of the pointer */
        AFTER_SPACE(c1);
	c2 = malloc(strlen(c1) + 1); /* Cheking!! */
	if (c2 == NULL) {
    		printf("Error: Memory allocation for c2 failed\n");
		return -1;
	}
	strcpy(c2, c1);
        if (c2) /* Not null */
	{
            c2[strlen(c2)+1] = '\0'; 
	}
	if(*c2 == '\0') {
	   return 2;
	}
	*flag = 1;
	m_table[(*m_table_size)].lineC = ((*mcr)->lineC);
	*mcr = &m_table[*m_table_size];
	strcpy((*mcr)->lines[(*mcr)->lineC], c1); /* Puts the macro */
        strcpy(m_table[*m_table_size].mName, c1); /* Puts in the macro table */
	/*((*mcr)->lineC)++;*/
	}
        return 1; /* הגדרה */
    }
	c2 = s;
    /*c2 = strpbrk(s,WHITESPACES);*/
    if (c2 && (*flag == 0)) { /* !=0 */
        c1 = c2;
        AFTER_SPACE(c2);
        if (*c2 != '\0') /* end of line */
	{
	  *mcr = NULL;
          return 3;
	} 
        *c1 = '\0'; 
    } 
    f = searchMacro(m_table, *m_table_size, s); 
    if (f) { /* != NULL macro found - put the data */
        (*mcr) = f; /* get its place */
        return 2; 
    }
    return 3; 
} 

char *preasm(char *bname) {
    char line[MAX_LINE_LEN] = {0}; 
    struct Macro macro_table[MAX_MCR]; 
    int macro_count = 0; 
    FILE *as_file; 
    FILE *am_file; 
    struct Macro *macro = malloc(sizeof(struct Macro)); /*Allocate memory for the macro*/
    char *amFileName = NULL; /* Initialize to NULL*/
    char *asFileName = NULL; /* Initialize to NULL*/
    int line_co = 1; 
    int g = 0;
    int flag = 0;
    if (macro == NULL) {
    /* Handle allocation failure */
    return NULL;
}
    /*(macro)->lineC = 0;*/

    asFileName = strcatWithMalloc(bname, ".as"); 
    amFileName = strcatWithMalloc(bname, ".am"); 
    am_file = fopen(amFileName, "w"); 
    as_file = fopen(asFileName, "r"); 

    if (!as_file || !am_file) { 
        if (asFileName) free(asFileName); /* Free the allocated memory if exists*/
        if (amFileName) free(amFileName); /* Free the allocated memory if exists*/
        return NULL; 
    }

    while (fgets(line, MAX_LINE_LEN, as_file) != NULL) { 
        switch (macro_line(line, &macro, macro_table, &macro_count, &flag)) { 
            case 0: /* end of macro def*/ 
                macro = NULL;
                break; 
            case 1: /* macro def*/
                break; 
            case 2: /* Inside */
			(macro_table->lineC) = (macro->lineC);
                for ( ; g <= (macro_table->lineC); g++) {
                    fputs(macro_table->lines[g], am_file);
                } 
		g--;
                macro = NULL; 
                break; 
            case 3:/* Any other line */ 
		if(flag == 0)
		    macro = NULL;
                if (macro !=  NULL) {
		    strcpy(macro->mName,macro->lines[macro->lineC]);
                    strcpy(macro->lines[macro->lineC], line); 
                    (macro->lineC)++; /* Fixed the unicode character issue*/
		    macro_count++; /*???*/
                /* if here */} 
             	else {
                    fputs(line, am_file); 
 	     	}
                break; 
        } 
        line_co++; 
    } 
    fclose(am_file); 
    fclose(as_file); 
    return amFileName; 
}


int main6(int argc, char *argv[])
{
    char *outputFile = preasm(argv[1]);
    if (outputFile) {
        free(outputFile); /* Free the allocated memory for the filename*/
    } else {
        printf("Error: Unable to process input file.\n");
    }
    return 0;
}
