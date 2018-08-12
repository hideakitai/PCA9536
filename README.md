# PCA9536

Arduino library for [PCA9536](http://www.ti.com/product/PCA9536/description) 4-Bit I2C and SMBus I/O Expander With Configuration Registers

## Usage

``` C++
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
```

## License

MIT
