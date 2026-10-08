#include "fonction.h"

int main(int argc, char** argv) {
    int option_a = 0, option_t = 0, nb_element = 0;
    verification_options_element(&option_a, &option_t, &nb_element, argc, argv);
    
    t_element* element = malloc(sizeof(t_element) * nb_element);

    struct stat info;
    fill_name_info_element(element, info, argc, argv);

    for(int i = 0; i < nb_element; i++) {
        for (int j = i + 1; j < nb_element; j++) {
            compare_element(&element[i], &element[j], option_t);
        }
    }

    for (int i = 0; i < nb_element_valid; i++) {
        display_directory_or_file(element[i].name, element[i].info, option_a, option_t);
    }


    free(element);
    return 0;
}