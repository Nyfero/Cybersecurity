#include "../../inc/ft_otp.hpp"

int check_key(std::string file) {
    if (!std::filesystem::exists(file)) {
        std::cerr << "ft_opt: error: " << file << " doesn't exist" << std::endl;
        return 1;
    }
    // ouverture du fichier 
    // dechiffrage du fichier 
    // verification du contenu (hexa + lenght)
    //fermeture du fichier

    return 0;
}