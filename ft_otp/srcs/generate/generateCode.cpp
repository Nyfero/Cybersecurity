#include "../../inc/ft_otp.hpp"

int generate_code(std::string file) {
    if (check_key(file))
        return 1;

    // Load the key from a source
    const std::string &key = decrypt(file);

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