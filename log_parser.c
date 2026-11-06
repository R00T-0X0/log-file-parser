
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *logFile;
    char line[512];
    const char *keyword;

    unsigned long lineNumber = 0;
    unsigned long alertCount = 0;

    if (argc != 3)
    {
        printf("Usage: %s <logfile> <keyword>\n", argv[0]);
        return 1;
    }

    keyword = argv[2];

    if (keyword[0] == '\0')
    {
        printf("Error: Search keyword cannot be empty.\n");
        return 1;
    }

    logFile = fopen(argv[1], "r");

    if (logFile == NULL)
    {
        printf("Error: Unable to open the log file.\n");
        return 1;
    }

    printf("\nLog File Analysis\n");
    printf("Searching for: %s\n", keyword);
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), logFile) != NULL)
    {
        lineNumber++;

        if (strstr(line, keyword) != NULL)
        {
            alertCount++;

            printf("[ALERT] Line %lu: %s", lineNumber, line);

            if (strchr(line, '\n') == NULL)
                printf("\n");
        }
    }

    if (ferror(logFile))
    {
        printf("\nError: An error occurred while reading the file.\n");
        fclose(logFile);
        return 1;
    }

    printf("----------------------------------------\n");
    printf("Analysis Summary\n");
    printf("File: %s\n", argv[1]);
    printf("Keyword: %s\n", keyword);
    printf("Total Alerts: %lu\n", alertCount);
    printf("----------------------------------------\n");

    fclose(logFile);

    return 0;
}
