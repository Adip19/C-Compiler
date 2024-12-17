
#include "numbers.h"
void update_opcode(short int bits, short int opcode) { 
    opcode = opcode << 6; /* shift the num value to the left to occupy the 6-9 bits */ 
    }

/* Sets the value to the 2-3 bits */ 
void destination(short int bits, int num) 
{ 
    short int dest;
    if(num >= 0 && num <= 3) { /* make sure num is in the range of 0-3 */ 
        dest = num << 2; 
        bits = bits | dest; /* clear the 2-3 bits and set the value */ 
    } 
} 
void source(short int num) 
{ 
    num = num << 4; /* shift the num value to the left to occupy the 4-5 bits */ 
    } 

short int numToBinary(short int num) {
    short int binary = 0; /* Initialize binary representation */
    int i;

    /* Handle negative numbers using two's complement representation */
    if (num < 0) {
        num = (1 << 14) + num; /* Add 2^14 to the negative number to get the two's complement */
    }

    /* Make sure only the least significant 14 bits are set */
    num = num & 0x3FFF;

    /* Convert number to binary representation */
    for (i = 0; i < 14; i++) {
        if (num & (1 << i)) {
            binary |= (1 << i); /* Set the i-th bit in binary */
        }
    }

    return binary;
}

void ARE(short int *bits, short int num) 
{ 
    if (num >= 0 && num <= 2) { /* make sure num is in the range of 0-2 */ 
        *bits &= 0xFFFC; /* clear the first two bits */
        *bits |= num; /* set the value of num in the first two bits */
    } 
} 

/*Returns the two's complement of the given unsigned integer.*/ 
short int twoComplement(short int num) 
{ 
    return ~num + 1; 
} 
void writeBinary2_4(short int num) 
{ 
    int shiftedNum = (num & 0x7) << 2; /* Ensure only the least significant 3 bits are kept and shift to occupy bits 2-4 */ 
    num &= ~(0x1C); /* Clear bits 2-4 */ 
    num |= shiftedNum; /* Set bits 2-4 to the binary representation of num */ 
} 

short int writeBinary5_7(short int num) 
{ 
    int shiftedNum = (num & 0x7) << 5; /* Ensure only the least significant 3 bits are kept and shift to occupy bits 5-7 */ 
    return shiftedNum; /* Return the value to be assigned */
} 

/* Modify string_to_ascii to return short int */

short int string_to_ascii(const char *str) {
    int i;
    char ch;
    while (*str) {
        ch = *str;
        printf("%c: ", ch);
        for (i = 7; i >= 0; i--) {
            printf("%d", (ch >> i) & 1);
        }
        printf(" /* ASCII code for '%c' */\n", ch);
        str++;
    }
    return (short int)ch;
}


bool isNegative(int num) { 

    return num < 0; 

} 

int isNumber(const char *str) {
    int i;
    if (str == NULL || *str == '\0') {
        return 0;  /* Empty string is not a number */
    }

    /* Check each character in the string */
    for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '+') {
            return 0;  /* Non-digit characters found */
        }
    }

    return 1;  /* All characters are digits */
}
