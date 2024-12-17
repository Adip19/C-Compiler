#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpFunctions.h"
#include "front.c"
#define MAX_LABELS 1024
#ifndef LABEL_H
#define LABEL_H

struct label{
    char *labName; /* Name */
    int number; /* Value OR defined at : 0-direct, 1-immediate, 2-internal, 3-opernad, 4-external  */
    int address; /* IC/DC       Place: 0-data, 1-code, 2-mydefine */
    int labDefine; /* 0 - Regular, 1 - Define*/
    enum{
        labCode,
        labEntryCode,
        labData,
        labEntryData,
        labEntry,
        labExtern
    }labType; /* labEntryCode, labEntryData , labCode, labData; 1-internal, 2-external The line number that showed up in */
};

int label_existence(struct label *label_table, char *label);

int get_inst_value(char *mnemonic);

void addDefine(struct phrase *phrases, char *word, int number);

void addLabelData(struct phrase *phrases, char *labelSave, char *word);

void addLabelString(struct phrase *phrases, char *labelSave, char *word);/* לטפל במערך נתונים */

void addLabelEntry(struct phrase *phrases, char *labelSave, char *word);


#endif /* LABEL_H  */
