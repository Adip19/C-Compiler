#include "preAssem.c"
#include "firstPass.c"
#include "secPass.c"
#include "backend.c"

int main(int argc, char **argv) {
    int i;
    char *amFileName;
    FILE *amFile;
    struct translation_unit program;
    for (i = 1; i < argc; i++) {
        amFileName = preasm(argv[i]);
        memset(&program,0,sizeof(struct translation_unit));
        if (amFileName) {
            amFile = fopen(amFileName, "r");
            if (amFile) {
                if (!firstPass(&program, amFileName, amFile)) {
                    rewind(amFile);
                    if (!secPass(&program, amFileName, amFile)) {
			printf("codeImage is:%d\n",program.code_image[0]);
                        print_ob_file(argv[i], &program);
			printf("HERE After OB\n");
                        /*if (program.entryCount >= 1)  Fixed member access
                            print_ent_file(argv[i], &program);*/
                        if (program.extCount >= 1) /* Fixed member access*/
                            print_ext_file(argv[i], &program);
                    }
                }
                fclose(amFile);
            }
            free(amFileName);
        }
    }

    return 0;
}

