#include "fonction.h"

void verification_options_element(int* option_a, int* option_t, int* nb_element, int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'a' && argv[i][2] == '\0') {
            *option_a = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 't' && argv[i][2] == '\0') {
            *option_t = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'a' && argv[i][2] == 't' && argv[i][3] == '\0') {
            *option_a = 1;
            *option_t = 1;
        } else {
            struct stat info;
            if (stat(argv[i], &info) == 0) {
                (*nb_element)++;
            }
        }
    }
}

void fill_name_info_element(t_element* element, struct stat info, int argc, char** argv) {
    int index = 0;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &info) == 0) {
            element[index].name = argv[i];
            element[index].info = info;
            index++;
        }  
    }
}

int compare_element(t_element* a, t_element* b, int option_t) {
    //a fichier et b dossier
    if (S_ISDIR(a->info.st_mode) && S_ISDIR(b->info.st_mode) == 0) {
        swap_element(a, b);
    //a et b de même type
    } else if (S_ISDIR(a->info.st_mode) == S_ISDIR(b->info.st_mode)) {
        if (option_t) {
            compare_date(a, b);
        } else {
            compare_alphabet(a, b);
        }
    }
    return 0;
}

void compare_alphabet(t_element* a, t_element* b) {
    int i = 0;
    while( a->name[i] != '\0') {
        if (a->name[i] > b->name[i]) {
            swap_element(a, b);
            return;
        }
        if (b->name[i] == '\0') {
            swap_element(a, b);
            return;
        }
        i++;
    }
}

void compare_date(t_element* a, t_element* b) {
    if (a->info.st_mtim.tv_sec < b->info.st_mtim.tv_sec) {
        swap_element(a, b);
    } else if (a->info.st_mtim.tv_sec == b->info.st_mtim.tv_sec) {
        if (a->info.st_mtim.tv_nsec < b->info.st_mtim.tv_nsec) {
            swap_element(a, b);
        } else if (a->info.st_mtim.tv_nsec == b->info.st_mtim.tv_nsec) {
            compare_alphabet(a, b);
        }
    }
}

void swap_element(t_element* a, t_element* b) {
    t_element c = *a;
    *a = *b;
    *b = c;
}

void display_directory_or_file(char* name, struct stat info, int option_a, int option_t) {
    if (S_ISDIR(info.st_mode)) { //dossier
        int nb_element_in_directory = 0;
        DIR* directory_open = opendir(name);
        if (directory_open != NULL) {
            struct stat info;
            struct dirent* entry_directory_open = readdir(directory_open);
            while(entry_directory_open != NULL) {
                char* name_file = test_element_in_directory(name, entry_directory_open->d_name); 

                if (stat(name_file, &info) == 0 && (entry_directory_open->d_name[0] != '.' || option_a == 1)) {
                    nb_element_in_directory++;
                }
                free(name_file);
                entry_directory_open = readdir(directory_open);
            }

            closedir(directory_open);
            t_element* element_in_directory = malloc(sizeof(t_element) * nb_element_in_directory);

            directory_open = opendir(name);
            if (directory_open != NULL) {
                entry_directory_open = readdir(directory_open);
                int index = 0;
                while(entry_directory_open != NULL) {
                    char* name_file = test_element_in_directory(name, entry_directory_open->d_name);

                    if (stat(name_file, &info) == 0 && (entry_directory_open->d_name[0] != '.' || option_a == 1)) {
                        fill_name_directory(element_in_directory, index, entry_directory_open->d_name);
                        fill_info_directory(element_in_directory, index, element_in_directory[index].name, entry_directory_open->d_name);
                        index++;
                    }
                    free(name_file);
                    entry_directory_open = readdir(directory_open);
                }
                closedir(directory_open);

                for(int i = 0; i < nb_element_in_directory; i++) {
                    for (int j = i + 1; j < nb_element_in_directory; j++) {
                        compare_element(&element_in_directory[i], &element_in_directory[j], option_t);
                    }
                }
                for (int i = 0; i < nb_element_in_directory; i++) {
                    printf("%s\n", element_in_directory[i].name);
                    free(element_in_directory[i].name);
                }
            }
            free(element_in_directory);
        }
    } else { //fichier
        printf("%s\n", name);
    }
}

void fill_name_directory(t_element* element_in_directory, int index, char* d_name) {
    int count_d_name = count_string(d_name);
    element_in_directory[index].name = malloc(sizeof(char) * (count_d_name + 1));

    for (int i = 0; i < count_d_name; i++) {
        element_in_directory[index].name[i] = d_name[i];
    }
    element_in_directory[index].name[count_d_name] = '\0';
}

void fill_info_directory(t_element* element_in_directory, int index, char* name, char* d_name) {
    int count_name = count_string(name);
    int count_d_name = count_string(d_name);
    char* name_file = malloc(sizeof(char) * (count_name + count_d_name + 2));

    construct_name_file(count_name, count_d_name, name, d_name, name_file);
    
    struct stat info;
    stat(name_file, &info);
    element_in_directory[index].info = info;
    free(name_file);
}

void construct_name_file(int count_name, int count_d_name, char* name, char* d_name, char* name_file) {
    int index = 0;
    for (int i = 0; i < count_name; i++) {
        name_file[index] = name[i];
        index++;
    }
    name_file[index] = '/';
    index++;
    for (int i = 0; i < count_d_name; i++) {
        name_file[index] = d_name[i];
        index++;
    }
    name_file[index] = '\0';
}

int count_string(char* name) {
    int i = 0, count = 0;
    while (name[i] != '\0') {
        count++;
        i++;
    }
    return count;
}

char* test_element_in_directory(char* name, char* d_name) {
    int count_name = count_string(name);
    int count_d_name = count_string(d_name);
    char* name_file = malloc(sizeof(char) * (count_name + count_d_name + 2));
    construct_name_file(count_name, count_d_name, name, d_name, name_file);
    return name_file;
}