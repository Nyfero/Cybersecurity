#include "../../inc/ft_otp.hpp"

int encrypt(std::string file) {
    char c;
    int key = 3;

    std::fstream fin, fout;
 
    fin.open(file, std::fstream::in);
    fout.open("ft_otp.key", std::fstream::out);
 
    int i = 0;
    int temp;
    while (fin.get(c)) {
        if (i % 2 == 0) {
            temp = (c + key + i);
        }
        else {
            temp = (c + key + (i * 2));
        }
        i++;
 
        fout.put((char)temp);
    }
 
    fin.close();
    fout.close();
    return 0;
}
