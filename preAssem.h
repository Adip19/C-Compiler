#pragma once
#include <string.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <ctype.h>
/* 
   pre_asem: pre-processes an assembly file, handling macro commands and creating a new file without macro commands. 
*/

/* Constants/Macros */

#define as_file_ext ".as"
#define am_file_ext ".am"
#define MAX_MCR_LEN 31 
#define MAX_MCR 100 
#define MACRO "mcr"
#define ENDMACRO "endmcr"
#define MAX_LINE_LEN 81

/* Struct Definition */

struct Macro {
    char mName[MAX_MCR_LEN + 1]; 
    char lines[MAX_MCR][MAX_MCR_LEN]; 
    int lineC; 
};

/* Function Prototypes */

/*
   searchMacro: Searches for a macro by name in an array of Macro instances.
   Parameters:
   - macro_table: Pointer to the array of Macro instances to search.
   - tableSize: Integer representing the size of the macro_table array.
   - name: Pointer to the string containing the name of the macro to search for.
   Return Value:
   - Pointer to the found Macro instance if found, otherwise NULL.
*/
struct Macro *searchMacro(struct Macro *macro_table, const int tableSize, const char *name);

/*
   macro_line: Parses a line of input to identify macro definitions and other lines.
   Parameters:
   - s: Pointer to the input string.
   - mcr: Pointer to a pointer to the current Macro instance.
   - m_table: Array of Macro instances.
   - m_table_size: Pointer to an integer representing the size of the m_table array.
   Return Value:
   - 0: End of macro definition.
   - 1: Macro definition encountered.
   - 2: Macro line encountered.
   - 3: Any other line.
*/
int macro_line(char *s, struct Macro **mcr, struct Macro *m_table, int *m_table_size, int *flag);

/*
   preasm: Processes assembly files and generates macro files.
   Parameters:
   - bname: Pointer to the base filename (without extension).
   Return Value:
   - Pointer to the generated macro file name, or NULL if an error occurred.
*/
char *preasm(char *bname);
