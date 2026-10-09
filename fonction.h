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

int verification_options_element(int* option_a, int* option_t, int* nb_element, int argc, char** argv);
int element_invalid(char* element);
void fill_name_info_element(t_element* element, int argc, char** argv);
int compare_element(t_element* a, t_element* b, int option_t, int inside_directory);
void compare_alphabet(t_element* a, t_element* b);
void compare_date(t_element* a, t_element* b);
void swap_element(t_element* a, t_element* b);
int display_directory_or_file(char* name, struct stat info, int option_a, int option_t);
void fill_name_directory(t_element* element_in_directory, int index, char* d_name);
void fill_info_directory(t_element* element_in_directory, int index, char* name, char* d_name);
void construct_name_file(int count_name, int count_d_name, char* name, char* d_name, char* name_file);
int count_string(char* name);
char* test_element_in_directory(char* name, char* d_name);