#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef void (*track_fn)(void);

typedef struct {
    track_fn maintenance;
    track_fn tracks[4];
    track_fn encore;
} album_t;

static int encore_unlocked = 0;

static void setup(void) {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

static void intro_theme(void) {
    puts("♪ Track 0 — Opening Theme");
    puts("Bright brass, fast tempo, perfect for the opening scene.");
}

static void rehearsal(void) {
    puts("♪ Track 1 — Rehearsal Room");
    puts("Metronome clicks echo through an empty music room.");
}

static void rooftop(void) {
    puts("♪ Track 2 — Rooftop at Dusk");
    puts("A quiet melody drifts over the city lights.");
}

static void ending_theme(void) {
    puts("♪ Track 3 — Ending Theme");
    puts("The credits roll. The player insists the album is over.");
}

static void maintenance_mode(void) {
    puts("♪ ??? — Archive Calibration");
    puts("A hidden catalog entry has been restored.");
    puts("The player now reports five tracks.");
    encore_unlocked = 1;
}

static void secret_encore(void) {
    char flag[128] = {0};
    FILE *fp = fopen("/flag.txt", "r");

    if (!fp) {
        puts("[!] Master recording unavailable.");
        return;
    }

    if (!fgets(flag, sizeof(flag), fp)) {
        fclose(fp);
        puts("[!] The master recording is unreadable.");
        return;
    }
    fclose(fp);

    flag[strcspn(flag, "\r\n")] = '\0';

    puts("♪ Track 4 — Encore");
    puts("This track was never printed on the album case.");
    printf("%s\n", flag);
}

static album_t album = {
    .maintenance = maintenance_mode,
    .tracks = {
        intro_theme,
        rehearsal,
        rooftop,
        ending_theme,
    },
    .encore = secret_encore,
};

_Static_assert(offsetof(album_t, tracks) == sizeof(track_fn), "album layout changed unexpectedly");

static void print_catalog(void) {
    puts("\n=== Hoshizora Live Archive ===");
    puts("Public catalog:");
    puts("  0. Opening Theme");
    puts("  1. Rehearsal Room");
    puts("  2. Rooftop at Dusk");
    puts("  3. Ending Theme");
    if (encore_unlocked) {
        puts("  4. Encore");
    }
}

static int read_track_id(unsigned long *out) {
    char buf[32];
    char *end = NULL;

    printf("Track ID (0-255): ");
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 0;
    }

    errno = 0;
    unsigned long value = strtoul(buf, &end, 10);

    if (errno != 0 || end == buf) {
        puts("Invalid track id.");
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        end++;
    }

    if (*end != '\0' || value > 255) {
        puts("Track IDs must be between 0 and 255.");
        return 0;
    }

    *out = value;
    return 1;
}

static int play_track(void) {
    unsigned long raw_id;

    if (!read_track_id(&raw_id)) {
        return 0;
    }

    int8_t track_id = (int8_t)raw_id;

    if ((!encore_unlocked && track_id > 3) ||
        (encore_unlocked && track_id > 4)) {
        puts("That track is not listed.");
        return 1;
    }

    printf("Loading track %d...\n", track_id);

    album.tracks[track_id]();
    return 1;
}

static void banner(void) {
    puts("====================================");
    puts("      HOSHIZORA LIVE ARCHIVE");
    puts("        Digital Album Player");
    puts("====================================");
    puts("The case lists four tracks.");
    puts("Staff say the encore was never released.");
}

int main(void) {
    setup();
    banner();
    while (1) {
        print_catalog();
        if (!play_track()) {
            break;
        }
    }
    return 0;
}
