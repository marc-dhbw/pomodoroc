#include "timer.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

char* getCurrentTime() {
    time_t now = time(0);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; // Remove the newline character
    return time_str;
}

void startTimer(double minutes) {
    // Convert minutes to milliseconds
    unsigned long total_milliseconds = minutes * 60 * 1000;
    // Get the initial start time
    unsigned long start_time = GetTickCount64();

    // Loop until total_milliseconds is reduced to 0
    while (total_milliseconds > 0) {
        // Get the current tick count
        unsigned long current_time = GetTickCount64();

        // Calculate elapsed time since the last iteration
        unsigned long elapsed_time = current_time - start_time;

        // Update start_time for the next iteration
        start_time = current_time;

        // Decrease the total_milliseconds by the elapsed time
        total_milliseconds = (total_milliseconds > elapsed_time)
            ? total_milliseconds - elapsed_time
            : 0;

        // Calculate minutes and seconds left
        unsigned long mins_left = total_milliseconds / (60 * 1000);
        unsigned long secs_left = (total_milliseconds % (60 * 1000)) / 1000;
        // Print remaining time
        printf("\rTime remaining: %02lu:%02lu", mins_left, secs_left);
        fflush(stdout);
        // Sleep for 1 second
        // Check if there's time left to sleep
        if (total_milliseconds > 100) {
            Sleep(100);  // Sleep for 100 milliseconds to reduce CPU usage
        } else {
            // Sleep only for the remaining time if less than 100 milliseconds
            Sleep(total_milliseconds);
        }
    }
}
