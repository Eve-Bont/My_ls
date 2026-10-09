#include "fonction.h"

int main(int argc, char** argv) {

    int option_a = 0, option_t = 0, nb_element = 0;
    int erreur = verification_options_element(&option_a, &option_t, &nb_element, argc, argv);

    if ((argc == 1 || nb_element == 0) && erreur == 0) {
        struct stat info;
        if (stat(".", &info) == 0) {
            display_directory_or_file(".", info, option_a, option_t);
        }
        return 0;
    }

    t_element* element = malloc(sizeof(t_element) * nb_element);
    if (element == NULL) {
        return 1;
    }

    fill_name_info_element(element, argc, argv);

    for(int i = 0; i < nb_element; i++) {
        for (int j = i + 1; j < nb_element; j++) {
            compare_element(&element[i], &element[j], option_t, 0);
        }
    }

    for (int i = 0; i < nb_element; i++) {
        int answer = display_directory_or_file(element[i].name, element[i].info, option_a, option_t);
        if (answer != 0) {
            return 1;
        }
    }

    free(element);
    if (erreur != 0) {
        return 1;
    }
    return 0;
}