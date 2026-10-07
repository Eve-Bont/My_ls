#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

typedef struct element_info {
    char* name;
    struct stat info;
} t_element;

void verification_options_operand(int* option_a, int* option_t, int* nb_operand, int argc, char** argv);
int fill_info_element(t_element* element, struct stat info, int argc, char** argv);
void display_directory_or_file(char* name, int option_a, int option_t, struct stat info);
void sorting_element(t_element* element, int nb_operand_valid);
int compare_element(t_element* a, t_element* b);
void swap_element(t_element* a, t_element* b);