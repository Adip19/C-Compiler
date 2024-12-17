#pragma once
#ifndef HELPFUNCTION_H
#define HELPFUNCTION_H
 #include <stdio.h>
 #include <ctype.h> 
#include <stdlib.h> 
#include <string.h> 
#include "front.c" /* Include the header file where enum inst_type is defined*/ 
#include "label.c"
 #include "numbers.c"
#define LINE_MAX_LEN 81 
#define MAX_MEM_SIZE 1024 
#define MAX_LABELS 1024 
#define AFTER_SPACE(s) while (*s && isspace(*s)) s++ 
#define WHITESPACES " \t\n\f\r\v" 


struct ext { 

    char externalName[20]; 

    int addresses[MAX_LABELS]; 

    int address_count; 

}; 

 
 

struct translation_unit { 

    int code_image[MAX_MEM_SIZE]; 

    int IC; 

    int data_image[MAX_MEM_SIZE]; 

    int DC; 

    struct label label_table[MAX_LABELS]; 

    int labCount; 

    struct ext externals[MAX_LABELS]; 

    int extCount; 

    struct label *entries[MAX_LABELS]; 

    int entryCount; 

    int entryExist; 

}; 

 
 

struct ext *extSearch(struct ext *externals, const int externals_size, const char *name); 
 
int what_command(char *input_word);

int data_instruction(struct phrase *phrase, char *str, int index, char * labelSave, char * word);

int stringCase(struct phrase *phrase, char *name, int index);


int find_operand(struct phrase *newphrase, char *line, int *index, int *address, int operandPlc);

int Address1_fixed_number(char *line, int *index, int *address_case, int operandPlc);

int get_phrase_from_line(struct phrase *newphrase, char *line);

#endif /* HELPFUNCTION_H */

 
 

 
