#ifndef functions_c
#define functions_c

void delay(int milliSeconds)
{
    clock_t start_time = clock();
    while(clock()<start_time + milliSeconds)
        ;
}

#endif // functions_h
