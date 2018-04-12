#include "PCA9536.h"

PCA9536 ioex;
uint32_t port = 0;

void setup()
{
    ioex.setup();
}

void loop()
{
    ioex.output(port % 16);
    ++port;
    delay(1000);
}
