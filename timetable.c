#include <stdio.h>
#include <time.h>

typedef struct {
    const char *name;
    int offset; // Offset from UTC in hours
} TimeZone;

void print_table_row(struct tm utc_time, TimeZone *time_zones, int num_zones) {
    printf("%02d:%02d %s\t", utc_time.tm_hour % 12 == 0 ? 12 : utc_time.tm_hour % 12,
           utc_time.tm_min, utc_time.tm_hour < 12 ? "AM" : "PM");

    for (int i = 0; i < num_zones; i++) {
        struct tm local_time = utc_time;
        local_time.tm_hour += time_zones[i].offset;
        mktime(&local_time); // Normalize the time struct

        printf("%02d:%02d %s\t", local_time.tm_hour % 12 == 0 ? 12 : local_time.tm_hour % 12,
               local_time.tm_min, local_time.tm_hour < 12 ? "AM" : "PM");
    }
    printf("\n");
}

int main() {
    TimeZone time_zones[] = {
        {"California", -8},
        {"Dallas, Texas", -6},
        {"New York", -5},
        {"Europe / CET", 1},
        {"India", 5 + 30 / 60} // India is UTC +5:30
    };
    int num_zones = sizeof(time_zones) / sizeof(time_zones[0]);

    // Print the header
    printf("UTC\t\t");
    for (int i = 0; i < num_zones; i++) {
        printf("%s\t", time_zones[i].name);
    }
    printf("\n");

    // Initialize the starting time (12:00 AM UTC)
    struct tm utc_time = {0};
    utc_time.tm_year = 2023 - 1900; // Year since 1900
    utc_time.tm_mon = 0;            // January
    utc_time.tm_mday = 1;           // 1st
    utc_time.tm_hour = 0;
    utc_time.tm_min = 0;

    // Print rows for every 30 minutes until 12:00 PM UTC
    for (int i = 0; i <= 24; i++) {
        print_table_row(utc_time, time_zones, num_zones);
        utc_time.tm_min += 30;
        mktime(&utc_time); // Normalize the time struct
    }

    return 0;
}