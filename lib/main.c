#include <stdio.h>
#include "LTP_message.h"

int main(void)
{
    struct LTPSample sample;
    printf("Hi!");
    int size = sizeof(sample);
    printf("%d",size);
    return 1;
}
