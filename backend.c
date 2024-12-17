#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Function to convert an integer to a binary string */
void intToBinaryString(int num, char *binaryStr) {
    int i;
    for (i = 13; i >= 0; i--) {
        binaryStr[i] = (num & 1) ? '1' : '0';
        num >>= 1;
    }
    binaryStr[14] = '\0';
}

/* Function to encode binary numbers to symbols */
char* numToEncodedString(const char *binary) {
    char *encoded_symbols = (char *)malloc(8 * sizeof(char)); 
    int i;
    for (i = 0; i < 14; i += 2) {
        if (binary[i] == '0' && binary[i + 1] == '0') {
            encoded_symbols[i / 2] = '*'; 
        } else if (binary[i] == '0' && binary[i + 1] == '1') {
            encoded_symbols[i / 2] = '#'; 
        } else if (binary[i] == '1' && binary[i + 1] == '0') {
            encoded_symbols[i / 2] = '%'; 
        } else if (binary[i] == '1' && binary[i + 1] == '1') {
            encoded_symbols[i / 2] = '!'; 
        }
    }
    encoded_symbols[7] = '\0'; 
    return encoded_symbols;
}

/* Function to print object file */
void print_ob_file(const char *bname, const struct translation_unit* prog) {
    char *obFileName;
    FILE *obFile;
    int i;
    char binary[15];
    char *encoded_symbols;

    obFileName = (char *)malloc((strlen(bname) + 4) * sizeof(char));
    sprintf(obFileName, "%s.ob", bname);
    obFile = fopen(obFileName, "w");

    if (obFile) {
        for (i = 0; i < prog->IC; i++) {
            intToBinaryString(prog->code_image[i], binary);
            encoded_symbols = numToEncodedString(binary);
            fprintf(obFile, "%s\n", encoded_symbols);
            free(encoded_symbols);
        }
        for (i = 0; i < prog->DC; i++) {
            intToBinaryString(prog->data_image[i], binary);
            encoded_symbols = numToEncodedString(binary);
            fprintf(obFile, "%s\n", encoded_symbols);
            free(encoded_symbols);
        }
        fclose(obFile);
    }
    free(obFileName);
}

/* Function to print external file */
void print_ext_file(const char *bname, const struct translation_unit* prog) {
    int i, j;
    char *extFileName;
    FILE *extFile;

    if (bname == NULL || prog == NULL) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return;
    }

    extFileName = (char *)malloc((strlen(bname) + 5) * sizeof(char));
    if (extFileName == NULL) {
        perror("Failed to allocate memory for external file name");
        return;
    }

    sprintf(extFileName, "%s.ext", bname);
    printf("Debug: External file name: %s\n", extFileName);

    extFile = fopen(extFileName, "w");
    if (extFile == NULL) {
        perror("Failed to open external file");
        free(extFileName);
        return;
    }

    printf("Debug: extCount: %d\n", prog->extCount);
    for (i = 0; i < prog->extCount; i++) {
        printf("Debug: External name: %s, Address count: %d\n", prog->externals[i].externalName, prog->externals[i].address_count);
        for (j = 0; j < prog->externals[i].address_count; j++) {
            printf("Debug: Writing address: %d\n", prog->externals[i].addresses[j]);
            fprintf(extFile, "%s\t%d\n", prog->externals[i].externalName, prog->externals[i].addresses[j]);
        }
    }
    fclose(extFile);
    free(extFileName);

    printf("Debug: External file created successfully.\n");
}


