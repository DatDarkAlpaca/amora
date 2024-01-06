#include "file.h"
#include <stdio.h>
#include <stdlib.h>

static bool detect_bom(const FILE* const file)
{
    unsigned char buffer[3];
    fread(buffer + 0, sizeof(unsigned char), 3, file);

    fseek(file, 0L, SEEK_SET);
    return buffer[0] == 0xEF && buffer[1] == 0xBB && buffer[2] == 0xBF;
}

file_results read_file(const char* filepath)
{
    file_results results;
    results.contents = "";
    results.valid = false;

    // Open file:
    FILE* file = NULL;
    file = fopen(filepath, "r");
    
    if (!file)
        return results;

    // Get file size:
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);

    fseek(file, 0L, SEEK_SET);

    // Detect BOM:
    if (detect_bom(file))
        fseek(file, 3L, SEEK_SET);

    // Read file:
    char* fileBuffer = (char*)calloc(fileSize, sizeof(char));
    if (!fileBuffer)
        return results;

    size_t getsResult = fread(fileBuffer, sizeof(char), sizeof(char) * fileSize, file);
    if (!getsResult)
        return results;

    results.contents = fileBuffer;
    results.valid = true;

    return results;
}

void close_file(file_results result)
{
    free(result.contents);

    result.contents = NULL;
    result.valid = false;
}
