/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** clock
*/

#include "server.h"

bool get_elapsed_time(struct timeval *startTime)
{
    struct timeval currentTime;
    double elapsed = 0;

    gettimeofday(&currentTime, NULL);
    elapsed = (currentTime.tv_sec - startTime->tv_sec) * 1000.0;
    elapsed += (currentTime.tv_usec - startTime->tv_usec) / 1000.0;
    if (elapsed >= (TIMEOUT / 1000)) {
        gettimeofday(startTime, NULL);
        return true;
    } else {
        return false;
    }
}
