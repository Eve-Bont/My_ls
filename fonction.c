#include "fonction.h"

void verification_options_operand(int* option_a, int* option_t, int* nb_operand, int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'a' && argv[i][2] == '\0') {
            *option_a = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '\0') {
            *option_t = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'a' && argv[i][2] == 't' && argv[i][3] == '\0') {
            *option_a = 1;
            *option_t = 1;
        } else {
            (*nb_operand)++;
        }
    }
}

int fill_info_element(t_element* element, struct stat info, int argc, char** argv) {
    int index = 0;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &info) == 0) {
            element[index].name = argv[i];
            element[index].info = info;
            index++;
        }  
    }
    return index;
}

void display_directory_or_file(char* name, int option_a, int option_t, struct stat info) {
    if (S_ISDIR(info.st_mode)) { //dossier
        DIR* directory_open = opendir(name);
        if (directory_open != NULL) {
            struct dirent* entry_directory_open = readdir(directory_open);
            while(entry_directory_open != NULL) {
                if (entry_directory_open->d_name[0] != '.' || option_a == 1) {
                    printf("%s\n", entry_directory_open->d_name);
                }
                entry_directory_open = readdir(directory_open);
            }
            closedir(directory_open);
        }
    } else { //fichier
        printf("%s\n", name);
    }
}

void sorting_element(t_element* element, int nb_operand_valid) {
    for(int i = 0; i < nb_operand_valid; i++) {
        for (int j = i + 1; j < nb_operand_valid; j++) {
            compare_element(&element[i], &element[j]);
        }
    }
}

int compare_element(t_element* a, t_element* b) {
    //a fichier et b dossier
    if (S_ISDIR(a->info.st_mode) && S_ISDIR(b->info.st_mode) == 0) {
        swap_element(a, b);
    } else if (S_ISDIR(a->info.st_mode) == S_ISDIR(b->info.st_mode)) {
        int i = 0;
        while( a->name[i] != '\0') {
            if (a->name[i] > b->name[i]) {
                swap_element(a, b);
                return 0;
            }
            if (b->name[i] == '\0') {
                swap_element(a, b);
                return 0;
            }
            i++;
        }
    }
    return 0;
}

void swap_element(t_element* a, t_element* b) {
    t_element c = *a;
    *a = *b;
    *b = c;
}