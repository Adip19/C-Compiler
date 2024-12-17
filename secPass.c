#include "secPass.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINARY_ARR_SIZE 200

/* Function to extract and encode the first word into the struct */
void encode_first_word(struct phrase *line_struct, const char *line) {
    char *first_word = NULL; /* Declare first_word locally here */
    int i = 0;
    /* Allocate memory for the word */
    first_word = (char *)malloc(strlen(line) );
	printf("IM firstWORD\n");
    if (first_word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    /* Copy characters from the line until a space or newline is encountered */
    while (line[i] != '\0' && line[i] != ' ' && line[i] != '\n') {
        first_word[i] = line[i];
        i++;
    }
    first_word[i] = '\0'; /* Null-terminate the string */

    /* Update the phrase type to phrase_string and set the first word */
    if (line_struct->phrase_type == phrase_directive) {
        line_struct->phrase_type = phrase_string;
        line_struct->phrase_options.directive.directive_type = phrase_string;
        strcpy(line_struct->phrase_options.directive.directive_options.string , first_word); /* Duplicate the string */
	}
printf("IN firstWord phrase type is:%d",line_struct->phrase_type);
    
/*
    free(first_word); Free the memory allocated for the first word */
}

int secPass(struct translation_unit *prog, const char* amFileName, FILE *amFile) {
    char line[81] = {0};
    /*short int binaryArr[MAX_BINARY_ARR_SIZE];   Binary array to store information */
    int errorFlag = 0;
    int lineC = 1;
    short int resetWord = 0;
    struct phrase *line_struct = calloc(1, sizeof(struct phrase));
    struct label *labelFind= NULL;
    struct ext *extFind,*extTemp;
    int i, j;
    struct ext *ext1 = (struct ext *)malloc(sizeof(struct ext));

    /* Check memory allocation */
    if (line_struct == NULL || ext1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    rewind(amFile);

    while (fgets(line, sizeof(line), amFile)) {
        printf("********* Processing line in second pass: %s\n", line);
        j = get_phrase_from_line(line_struct, line);
        if (errorFlag == -1)
		return -1;

        /* Extract and encode the first word only if the phrase type is phrase_inst */

        /*encode_first_word(line_struct, line);*/

	switch (line_struct->phrase_type) {
	    case phrase_empty:
		printf("Phrase type: empty\n");
		break;
	    case phrase_comment:
		printf("Phrase type: comment\n");
		break;
	    case phrase_directive:
		printf("Phrase type: directive\n");
		if(line_struct->phrase_options.directive.directive_type == phrase_string)
		{
			for(j=0 ; j<4 ; j++)
			{
				printf("num in {%d} string is:%c\n",j,line_struct->phrase_options.directive.directive_options.data[j].number);
				printf("**%d**\n",numToBinary(line_struct->phrase_options.directive.directive_options.data[j].number));
				prog->code_image[prog->IC] = numToBinary(line_struct->phrase_options.directive.directive_options.data[j].number);
				printf("IM num in []:%d\n",prog->code_image[prog->IC]);
				prog->IC++;
			}		

		}
		if(line_struct->phrase_options.directive.directive_options.data[0].number)
		{
			printf("IM num in struct:%d\n",line_struct->phrase_options.directive.directive_options.data[0].number);
		numToBinary(line_struct->phrase_options.directive.directive_options.data[0].number);
		
                prog->code_image[prog->IC] = line_struct->phrase_options.directive.directive_options.data[0].number;
               			printf("IM num in []:%d\n",prog->code_image[prog->IC]);
	        prog->IC++;

		}

		printf("Hiiii Im before the ext\n");

		printf("Hiiii Im  %d\n",line_struct->phrase_options.directive.directive_type);
	    if (line_struct->phrase_options.directive.directive_type == phrase_extern) {
		printf("Hiiii Im in the ext\n");
                if (!extFind) {
		printf("Hiiii Im in the ext1\n");
                    extFind = malloc(sizeof(struct ext) * (prog->extCount + 1));
		printf("Hiiii Im in the ext2\n");
                    if (!extFind) {
		printf("Hiiii Im in the ext3\n");
                        printf("No space\n");
                        errorFlag = 1;
                        return errorFlag;
                    }
                }
		printf("Hiiii Im in the ext4\n");
		extFind = malloc(sizeof(struct ext) * (prog->extCount + 1));
		printf("Hiiii Im in the ext4444444444444444\n");
printf("%s\n", line_struct->phrase_options.directive.directive_options.label);
                strcpy(extFind[prog->extCount].externalName, line_struct->phrase_options.directive.directive_options.label);
		printf("Hiiii Im in the ext5\n");
                extFind[prog->extCount].addresses[extFind[prog->extCount].address_count] = prog->IC + 100;
		printf("Hiiii Im in the ext6\n");
                extFind[prog->extCount].address_count = 1;
		printf("Hiiii Im in the ext7\n");
                prog->extCount++;
		printf("Hiiii Im in the ext8\n");
                extTemp = realloc(extFind, sizeof(struct ext) * (prog->extCount + 1));
		printf("Hiiii Im in the ext9\n");
                if (!extTemp) {
                    printf("No space\n");
                    errorFlag = 1;
                    return errorFlag;
                }
                extFind = extTemp;
            }
        
		break;
	    case phrase_inst:
	        printf("Hi Im in the phrase inst type %d\n", line_struct->phrase_options.inst.inst_type);
                resetWord = 0;
                numToBinary(line_struct->phrase_options.inst.inst_type);
                update_opcode(resetWord, (line_struct->phrase_options.inst.inst_type));
                source((line_struct->phrase_options.inst.operands[0].operand_options.immed));
                destination(resetWord, (line_struct->phrase_options.inst.operands[1].operand_options.immed));
                prog->code_image[prog->IC] = resetWord;
                prog->IC++;

            	if (line_struct->phrase_options.inst.operands[0].operands_type == phrase_reg && line_struct->phrase_options.inst.operands[1].operands_type == phrase_reg) {
                prog->code_image[prog->IC] = line_struct->phrase_options.inst.operands[0].operand_options.reg;
                prog->code_image[prog->IC] = line_struct->phrase_options.inst.operands[1].operand_options.reg;
                source(prog->code_image[prog->IC] = line_struct->phrase_options.inst.operands[0].operand_options.reg);
                destination((prog->code_image[prog->IC]), line_struct->phrase_options.inst.operands[1].operand_options.reg);
                prog->IC++;
            }
             else {
                for (i = 0; i < 2; i++) {
                    if (line_struct->phrase_options.inst.operands[i].operands_type == phrase_reg) {
                        prog->code_image[prog->IC] = line_struct->phrase_options.inst.operands[i].operand_options.reg;
                        prog->IC++;
                        }
                    else if (line_struct->phrase_options.inst.operands[i].operands_type == phrase_immed) {
                        writeBinary2_4(line_struct->phrase_options.inst.operands[i].operand_options.immed);
                        }
                    else if (line_struct->phrase_options.inst.operands[i].operands_type == phrase_idx) {
                            if (line_struct->phrase_options.inst.operands[i].operand_options.index.idx_options.label != NULL) {
                                labelFind = labelLookUp(prog->label_table, prog->labCount, line_struct->phrase_options.inst.operands[i].operand_options.index.idx_options.label);
                                prog->code_image[prog->IC] = labelFind->address << 2;
                                prog->IC++;
                            } else {
                                prog->code_image[prog->IC] = line_struct->phrase_options.inst.operands[i].operand_options.index.idx_options.number << 2;
                                prog->IC++;
                            }
                    }
                }
		printf("Instruction type: %d\n", line_struct->phrase_options.inst.inst_type);
		break;
	    case phrase_define:
		printf("Phrase type: define\n");
        for (i = 0; i < 2; i++) {
                     if (line_struct->phrase_options.inst.operands[i].operands_type == phrase_label || line_struct->phrase_options.inst.operands[i].operands_type == phrase_idx) {
                        printf("Hi Im in the phrase index define/label type\n");
                        if (line_struct->phrase_options.inst.operands[i].operands_type == phrase_label) {
                            labelFind = labelLookUp(prog->label_table, prog->labCount, line_struct->phrase_options.inst.operands[i].operand_options.label);
                            if (labelFind) {
                                writeBinary2_4(labelFind->number);
                                if (labelFind->labType != labExtern) {
                                    prog->code_image[prog->IC] = labelFind->address << 2;
                                }
                                if (labelFind->labType == labExtern) {
                                    prog->code_image[prog->IC] |= 1;
                                    extFind = extSearch(prog->externals, prog->extCount, labelFind->labName);
                                    if (extFind) {
                                        extFind->addresses[extFind->address_count] = prog->IC + 100;
                                        extFind->address_count++;
                                    } else {
                                        /* Allocate memory for the new external entry */
                                     strcpy(prog->externals[prog->extCount].externalName, labelFind->labName);
                                        if (prog->externals[prog->extCount].externalName == NULL) {
                                            fprintf(stderr, "Memory allocation failed\n");
                                            exit(EXIT_FAILURE);
                                        }
                                        prog->externals[prog->extCount].addresses[prog->externals[prog->extCount].address_count] = prog->IC + 100;
                                        prog->externals[prog->extCount].address_count++;
                                        prog->extCount++;
                                    }
                                } else {
                                    prog->code_image[prog->IC] |= 2;
                                    }
                                prog->IC++;
                            } /*else {
                                errorFlag = 1;
                                printf("**********error in line %d undefined label: %s\n", lineC, line_struct->phrase_options.inst.operands[i].operand_options.label);
                            }*/
                        }}}
		/*printf("Label: %s\n", line_struct->phrase_options.define.label);
		printf("Number: %d\n", line_struct->phrase_options.define.number);*/
		break;
        default:
		    printf("Unknown phrase type\n");
        }
            lineC++;
        }
    }
    free(ext1);
    free(line_struct);
    return errorFlag;
}


