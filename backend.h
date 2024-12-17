#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpFunctions.c"

/**
 * @brief Convert an integer to a binary string.
 *
 * This function converts a given integer to a binary string representation.
 * The resulting binary string is stored in the provided character array.
 *
 * @param num The integer to be converted to binary.
 * @param binaryStr A character array to store the resulting binary string.
 */
void intToBinaryString(int num, char *binaryStr);

/**
 * @brief Encode binary numbers to symbols.
 *
 * This function encodes a binary string into a string of symbols.
 * Each pair of binary digits is mapped to a specific symbol:
 * - "00" -> '*'
 * - "01" -> '#'
 * - "10" -> '%'
 * - "11" -> '!'
 *
 * @param binary The binary string to be encoded.
 * @return A dynamically allocated string containing the encoded symbols.
 */
char* numToEncodedString(const char *binary);

/**
 * @brief Print the object file.
 *
 * This function creates an object file with the specified base name and writes
 * the encoded binary instructions from the translation unit into the file.
 *
 * @param bname The base name for the output file.
 * @param program A pointer to the translation unit containing the program data.
 */
void print_ob_file(const char *bname, const struct translation_unit* program);

/**
 * @brief Print the external references file.
 *
 * This function creates an external references file with the specified base name
 * and writes the external references from the translation unit into the file.
 *
 * @param bname The base name for the output file.
 * @param program A pointer to the translation unit containing the external references.
 */
void print_ext_file(const char *bname, const struct translation_unit* program);

#endif /* BACKEND_H */
