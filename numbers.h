#pragma once
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#ifndef NUMBERS_H
#define NUMBERS_H

/**
 * Updates the opcode value by shifting the bits to occupy the 4-5 bits.
 *
 * @param bits The original bits value.
 * @param opcode The opcode value to be shifted.
 */
void update_opcode(short int bits, short int opcode);

/**
 * Sets the value to the 2-3 bits.
 *
 * @param bits The original bits value.
 * @param num The number to set in the 2-3 bits.
 */
void destination(short int bits, int num);

/**
 * Sets the value to the 4-5 bits.
 *
 * @param bits The original bits value.
 * @param num The number to set in the 4-5 bits.
 */
void source(short int num);

/**
 * Converts a number to binary representation and stores it in bits (least significant 14 bits).
 *
 * @param bits Pointer to the bits value.
 * @param num The number to convert to binary.
 */
short int numToBinary(short int num);

/**
 * Sets the Absolute/Relocatable/External (ARE) bits based on the given num value.
 * @param num The value to set in the first two bits (0-2).
 */
void ARE(short int *bits,short int num);

/**
 * Finds the index of a command in the command table.
 *
 * @param command_table Array of command strings.
 * @param commWord The command word to search for.
 * @return The index of the command in the table, or -1 if not found.
 */

/*int opcodeIndex(const char *command_table[], char *commWord);*/

/**
 * Returns the two's complement of the given unsigned integer.
 *
 * @param num The unsigned integer.
 * @return The two's complement of the number.
 */
short int twoComplement(short int num);

/**
 * Writes the binary representation of a number to bits occupying bits 2-4.
 *
 * @param bits Pointer to the bits value.
 * @param num The number to write in binary.
 */
void writeBinary2_4(short int num);

/**
 * Writes the binary representation of a number to bits occupying bits 5-7.
 *
 * @param bits Pointer to the bits value.
 * @param num The number to write in binary.
 */
short int writeBinary5_7(short int num);


short int string_to_ascii(const char *str);

bool isNegative(int num);

int isNumber(const char *str);

#endif /* NUMBERS_H*/
