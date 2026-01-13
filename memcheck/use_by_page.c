#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>
#endif

#define PAGE_SIZE 4096
#define SIZE_MIB 1024
#define PAUSE_MIB 128

#if defined(_WIN32)
size_t get_rss_kb(void) {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / 1024;
}
#else
size_t get_rss_kb(void) {
    FILE* f = NULL;
	f = fopen("/proc/self/status", "r");
	if (f == NULL) {
		printf("Call to getMemory FAILED; "
			   "linux file proc/self/status not found!\n");
		return 1;
	}

    char buffer[1024] = "";
    size_t rss = 0;

    while (fscanf(f, " %1023s", buffer) == 1) {
		if (strcmp(buffer, "VmRSS:") == 0) {
			fscanf(f, " %lu", &rss);
		}
	}
    fclose(f);
    return rss;
}
#endif

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <r|w>\n", argv[0]);
        return 1;
    }

    char mode = argv[1][0];
    if (mode != 'r' && mode != 'w') {
        printf("'r' or 'w' mode only\n");
        return 1;
    }
    size_t total_bytes = SIZE_MIB * 1024UL * 1024UL;

    printf("Mode %c\n", mode);
    printf("Allocating %d MiB\n", SIZE_MIB);

    unsigned char *buf = malloc(total_bytes);
    if (!buf) {
        perror("malloc");
        return 1;
    }

    size_t pause_bytes = PAUSE_MIB * 1024UL * 1024UL;

    for (size_t offset = 0; offset < total_bytes; offset += PAGE_SIZE) {

        if (mode == 'r') {
            volatile unsigned char v = buf[offset];
            (void)v;
        } else {
            buf[offset] = 255;
        }

        if (offset > 0 && offset % pause_bytes == 0) {
            printf(
                "Touched %ld MiB, RSS = %ld kB\n",
                offset / 1024 / 1024,
                get_rss_kb()
            );
            printf("Press enter to continue\n");
            getchar();
        }
    }

    printf("Final RSS = %ld kB\n", get_rss_kb());
    free(buf);
    return 0;
}
