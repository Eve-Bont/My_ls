#include "fonction.h"

int main(int argc, char** argv) {
    int option_a = 0, option_t = 0, nb_element = 0;
    verification_options_operand(&option_a, &option_t, &nb_element, argc, argv);
    
    t_element* element = malloc(sizeof(t_element) * nb_element);

    struct stat info;
    int nb_element_valid = fill_info_element(element, info, argc, argv);

    return 0;
}