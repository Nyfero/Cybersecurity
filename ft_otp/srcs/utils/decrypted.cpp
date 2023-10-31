#include "../../inc/ft_otp.hpp"

int decryptFile(const char* inputFile, const char* outputFile, const unsigned char* key, const unsigned char* iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        return 1;
    }

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        return 1;
    }

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Failed to open files." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    unsigned char inbuf[1024 + EVP_MAX_BLOCK_LENGTH], outbuf[1024];
    int bytesRead, outLength;

    while (true) {
        inFile.read(reinterpret_cast<char*>(inbuf), sizeof(inbuf));
        bytesRead = inFile.gcount(); // Get the number of bytes read in the last read operation

        if (bytesRead == 0) {
            // End of file or an error occurred
            break;
        }

        if (!EVP_DecryptUpdate(ctx, outbuf, &outLength, inbuf, bytesRead)) {
            std::cerr << "Failed to decrypt data." << std::endl;
            EVP_CIPHER_CTX_free(ctx);
            return 1;
        }

        outFile.write(reinterpret_cast<char*>(outbuf), outLength);
    }


    if (!EVP_DecryptFinal_ex(ctx, outbuf, &outLength)) {
        return 1;
    }

    outFile.write(reinterpret_cast<char*>(outbuf), outLength);

    inFile.close();
    outFile.close();

    EVP_CIPHER_CTX_free(ctx);
    return 0;
}

// int main() {
//     const char* inputFile = "encrypted_output.dat";
//     const char* outputFile = "decrypted_output.txt";

//     // Replace with the key and IV used for encryption
//     unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];

//     // ... Load key and IV here (e.g., from a secure source) ...

//     if (decryptFile(inputFile, outputFile, key, iv) != 0) {
//         std::cerr << "Decryption failed." << std::endl;
//         return 1;
//     }

//     std::cout << "File decrypted successfully." << std::endl;

//     return 0;
// }
