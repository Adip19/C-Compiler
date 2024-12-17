#include <stdio.h>
#ifndef FRONT_H
#define FRONT_H

struct phrase{ 
    char lineError[200]; 
    const char *labelName; 
    enum{ /*סוגי המשפטים שיש*/ 
        phrase_empty, /*empty sentence*/ 
        phrase_comment, /*note sentence*/ 
        phrase_directive,/*הנחיה*/ 
        phrase_inst, /*instruction sentence*/ 
        phrase_define  
    }phrase_type; 
    union{ 
        struct{ 
            char *label; 
            int number; 
        }define; 
        struct{ /*האופציות של משפט הנחיה*/ 
            enum{ 
                phrase_data, 
                phrase_string, 
                phrase_entry, 
                phrase_extern 
            }directive_type; 
            union{/*כל משפט הנחיה יכול לקבל לייבל/ מחרוזת/ הגדרת קבוע-שזהו הסטראקט*/ 
                char * label; 
                char * string;
                struct{ /*הסטראקט חייב לקבל שם קבוע(תווית) וערך*/ 
                    int number;
                    enum{ 
                        data_label, 
                        data_count /* number*/ 
                    }data_options; 
                }data[80]; /*limit*/ 
            }directive_options; 
        }directive; 
        struct{ /*group of instractions*/ 
            enum{ 
                type_mov, 
                type_cmp, 
                type_add, 
                type_sub, 
                type_lea,/*עד כאן מקבלים 2 אופרנדים*/ 
                type_not, 
                type_clr, 
                type_inc, 
                type_dec, 
                type_jmp, 
                type_bne, 
                type_red, 
                type_prn, 
                type_jsr, /*עד לכאן מקבלים אןפרנד אחד*/ 
                type_rst, 
                type_hlt /*בלי אופרנדים בכלל*/ 
            }inst_type;/* OPCODE*/ 
            struct{ /*שיטות מיעון*/ 
                enum{ 
                  phrase_immed, 
                  phrase_label, /*כי בתוך מיעון ישיר יש רק לייבל*/   
                  phrase_idx,/* לאינדקס יש 2 חלוקות כי יכול לקבל גם לייבל וגם קבוע*/ 
                  phrase_reg /*מיעון רק של רגיסטרים*/ 
                }operands_type; 
                union{ /*כל שיטת מיעון מקבל ערך אחר. מיידי-מספר או קבוע, ישיר-תווית, אינדקס קבוע-יכול לקבל לייבל או ערך רגיסטר-מקבל רק רגיסטר*/ 
                    int immed; /* number */
                    char * label; /* label/define */
                    int reg; 
                    struct{ 
                        char * label; 
                        union{ 
                            int number; 
                            char * label; 
                        }idx_options; 
                    }index; 
                }operand_options; 
            }operands[2]; /* לבדוק- לדעתנו זו כמות הפעולות */ 
        }inst; 
    }phrase_options; 
}; 

 
 

/*פונקציה דאנחנו נותנים לה שורה והיא מחזירה לנו מבנה של סטרקט */ 

int get_phrase_from_line(struct phrase *newphrase, char *line); 

 #endif
