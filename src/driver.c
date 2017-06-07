#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEME_OVERLOAD   9001

const char MAGIC_NUMS[4] = {0x50, 0x4B, 0x03, 0x04};
const char* OUT_NAME = "encoded.docx";
const char* OUT_2 = "decoded.out";

void circumvent(FILE* fin) {
    
    FILE* fout = fopen(OUT_NAME, "wb");
    if(fout == NULL) {
        printf("Unable to open file, exiting.\n");
        exit(MEME_OVERLOAD);
    }
    fwrite(MAGIC_NUMS, 1, 4, fout);
    int toRead = 100;
    unsigned char buf[toRead];
    while(!feof(fin)) {
        fread(buf, sizeof(char), sizeof(buf), fin);
        fwrite(buf, sizeof(char), sizeof(buf), fout);
    }
    fclose(fout);
}

void restore(FILE* fin) {

    FILE* fout = fopen(OUT_2, "wb");
    if(fout == NULL) {
        printf("Unable to open file, exiting.\n");
        exit(MEME_OVERLOAD);
    }    
    fseek(fin, 4, SEEK_SET);
    int toRead = 100;
    unsigned char buf[toRead];
    while(!feof(fin)) {
        fread(buf, sizeof(char), sizeof(buf), fin);
        fwrite(buf, sizeof(char), sizeof(buf), fout);
    }
    fclose(fout);
}

void printUsage() {
    printf("Usage: ./executable -e|d filename\n");
    exit(MEME_OVERLOAD);
}

int main(int argc, char** argv) {
    // Check failure conditions
    if(argc != 3) { // Needs -d/e and filename
        printUsage();
    }
    if(strlen(argv[1]) != 2) {
        printUsage();
    }
    char option = argv[1][1];
    
    // Open the file to work on.
    FILE* fin = fopen(argv[2], "rb");
    // Guarantee it succeeds.
    if(fin == NULL) {
        printf("Unable to open file, exiting.\n");
        exit(MEME_OVERLOAD);
    }
    if(option == 'e') {
        circumvent(fin);
    } else if(option == 'd') {
        restore(fin);
    } else {
        printUsage();
    }
    fclose(fin);
    return 0;
}

