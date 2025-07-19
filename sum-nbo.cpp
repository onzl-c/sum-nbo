#include <iostream>
#include <stdint.h>
#include <cstdio>
#include <cstdlib>
#include <arpa/inet.h>

using namespace std;

uint32_t file_to_host(const char* filename) {
    FILE* pfile = fopen(filename, "rb");

    if (pfile == NULL) {
        fprintf(stderr, "[Error] cannot open file: '%s'\n", filename);
        return 1;
    }

    uint32_t network_buffer;
    size_t read_c = fread(&network_buffer, sizeof(uint32_t), 1, pfile);
    if (read_c != 1) {
        fprintf(stderr, "[Error]: file size is smaller than 4bytes: '%s'\n", filename);
        fclose(pfile);
        return 1;
    }

    fclose(pfile);

    return ntohl(network_buffer);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "[Error]: number of files isn't 3");
        return 1;
    }

    uint32_t n1 = file_to_host(argv[1]);
    uint32_t n2 = file_to_host(argv[2]);
    uint32_t n3 = file_to_host(argv[3]);

    uint32_t sum = n1 + n2 + n3;

    printf("%d(0x%08x) + %d(0x%08x) + %d(0x%08x)= %d(0x%08x)", n1, n1, n2, n2, n3, n3, sum, sum);

    return 0;
}
