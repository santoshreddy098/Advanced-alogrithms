#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>

const unsigned int SHA256_K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

unsigned int rotateRight(unsigned int value, unsigned int bits) {
    return (value >> bits) | (value << (32 - bits));
}

std::vector<unsigned char> applyPadding(const std::string& input) {
    std::vector<unsigned char> padded(input.begin(), input.end());
    size_t originalLength = input.size() * 8;
    
    padded.push_back(0x80);
    while ((padded.size() * 8) % 512 != 448) {
        padded.push_back(0x00);
    }
    
    for (int i = 7; i >= 0; --i) {
        padded.push_back((originalLength >> (i * 8)) & 0xff);
    }
    return padded;
}

void processSHA256Block(const std::vector<unsigned char>& block, unsigned int hash[8]) {
    unsigned int w[64];
    for (int i = 0; i < 16; ++i) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
    }

    for (int i = 16; i < 64; ++i) {
        unsigned int s0 = rotateRight(w[i - 15], 7) ^ rotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3);
        unsigned int s1 = rotateRight(w[i - 2], 17) ^ rotateRight(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    unsigned int a, b, c, d, e, f, g, h;
    a = hash[0]; b = hash[1]; c = hash[2]; d = hash[3];
    e = hash[4]; f = hash[5]; g = hash[6]; h = hash[7];

    for (int i = 0; i < 64; ++i) {
        unsigned int S1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
        unsigned int ch = (e & f) ^ (~e & g);
        unsigned int temp1 = h + S1 + ch + SHA256_K[i] + w[i];
        unsigned int S0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
        unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
        unsigned int temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    hash[0] += a; hash[1] += b; hash[2] += c; hash[3] += d;
    hash[4] += e; hash[5] += f; hash[6] += g; hash[7] += h;
}

std::string computeSHA256(const std::string& input) {
    unsigned int hash[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    
    std::vector<unsigned char> paddedInput = applyPadding(input);
    for (size_t i = 0; i < paddedInput.size(); i += 64) {
        std::vector<unsigned char> block(paddedInput.begin() + i, paddedInput.begin() + i + 64);
        processSHA256Block(block, hash);
    }
    
    std::stringstream result;
    for (int i = 0; i < 8; ++i) {
        result << std::hex << std::setw(8) << std::setfill('0') << hash[i];
    }
    return result.str();
}

int main() {
    std::ifstream file("mark.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();
    
    std::string hash = computeSHA256(text);
    std::cout << "SHA-256 Hash: " << hash << std::endl;
    
    return 0;
}
