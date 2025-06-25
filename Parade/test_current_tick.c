#include "settings_parade.h"

int pi;

void start_time()
{
    int startTime = get_current_tick(pi) % 1000000;
    int time;
    while (1)
    {
        time = get_current_tick(pi);
        if (time % 1000000 > startTime)
        {
            printf("%d\n", time);
            break;
        }
    }
}

int main()
{
    pi = pigpio_start(NULL, NULL);
    for (int i = 0; i < 10; i++)
    {
        start_time();
        sleep(1);
    }
    return 0;
}