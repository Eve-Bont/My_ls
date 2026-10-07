#include "fonction.h"

int main(int argc, char** argv) {
    struct stat info;
    t_element* element;

    int option_a = 0, option_t = 0, nb_operand = 0;
    verification_options_operand(&option_a, &option_t, &nb_operand, argc, argv);
    
    element = malloc(sizeof(t_element) * nb_operand);
    int nb_operand_valid = fill_info_element(element, info, argc, argv);

    if (nb_operand_valid == 0) {
        if (stat(".", &info) == 0) {
            display_directory_or_file(".", option_a, info);
        } else {
            return -1;
        }
    }

    sorting_element(element, nb_operand_valid);

    for (int i = 0; i < nb_operand_valid; i++) {
        display_directory_or_file(element[i].name, option_a, option_t, element[i].info);
    }

    

    //tests
    for(int i = 0; i < nb_operand_valid; i++) {
        printf("%s\n", element[i].name);
    }
    free(element);
    return 0;
}