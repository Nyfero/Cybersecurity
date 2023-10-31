#include "../../inc/ft_otp.hpp"

int generate_code(std::string file) {
    if (check_key(file))
        return 1;


// Generate a random key and initialization vector (IV)
    unsigned char tmp[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    std::cout << "tmp: " << tmp << std::endl;
    std::cout << "iv: " << iv << std::endl;
    if (RAND_bytes(tmp, EVP_MAX_KEY_LENGTH) != 1 || RAND_bytes(iv, EVP_MAX_IV_LENGTH) != 1) {
        std::cerr << "Failed to generate key and IV." << std::endl;
        return 1;
    }
    if (decryptFile(file.c_str(), "ft_otp.key", tmp, iv)) {
        std::cerr << "Failed to decrypt" << std::endl;
        return 1;
    }

    // Load the key from a source
    const std::string &key = file;

    // Calculate the counter if not provided (time-based, 30-second intervals)
    size_t counter = static_cast<unsigned long long>(std::time(nullptr) / 30);

    // Calculate the HMAC-SHA1 hash of the key and counter
    unsigned char hmac_hash[SHA_DIGEST_LENGTH];
    HMAC(EVP_sha1(), key.c_str(), key.length(), reinterpret_cast<const unsigned char*>(&counter), sizeof(counter), hmac_hash, nullptr);

    // Extract the HOTP code from the hash
    int offset = hmac_hash[SHA_DIGEST_LENGTH - 1] & 0x0F;
    int hotp = ((hmac_hash[offset] & 0x7F) << 24 |
                (hmac_hash[offset + 1] & 0xFF) << 16 |
                (hmac_hash[offset + 2] & 0xFF) << 8 |
                (hmac_hash[offset + 3] & 0xFF)) % 1000000;

    // Format the HOTP as a 6-digit string with leading zeros if needed
    std::ostringstream hotpStr;
    hotpStr << std::setw(6) << std::setfill('0') << hotp;
    std::cout << hotpStr.str() << std::endl;

    return 0;
}