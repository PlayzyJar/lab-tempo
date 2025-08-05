#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "src/ms5637_02ba03/ms5637.h"

// Fórmula inversa para ajuste da pressão ao nível do mar baseado em altitude conhecida
// P0 = P / (1 - (h / 44330))^5.255
// onde P é a pressão medida, h é a altitude conhecida e P0 é a pressão ao nível do mar 

float pressure_sea_level(float pressure, float altitude_m) {
    return pressure / powf(1.0f - (altitude_m / 44330.0f), 5.255f);
}

int main() {
    stdio_init_all();
    ms5637_init();

    const float known_altitude = 555.0f; // em metros (exemplo: Campina Grande, PB)

    while (true) {
        float temperature, pressure;
        if (ms5637_read_temperature_pressure(&temperature, &pressure) == MS5637_STATUS_OK) {
            float sea_level = pressure_sea_level(pressure, known_altitude);
            printf("Pressão ao nível do mar: %.2f mbar | Atual: %.2f mbar | Temp: %.2f °C\n",
                   sea_level, pressure, temperature);
        } else {
            printf("Falha ao ler sensor\n");
        }
        sleep_ms(1000);
    }
}
