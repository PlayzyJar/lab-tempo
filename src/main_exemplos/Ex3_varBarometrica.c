#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "src/ms5637_02ba03/ms5637.h"

// Função para calcular a variação de altura baseada na pressão atmosférica capturada inicialmente ao ligar a placa
// Fórmula: h = 44330 * (1 - (P / P0)^(1/5.255))
// onde P0 é a pressão ao nível do mar (pode ser calibrada para o  local)
// P é a pressão medida e h é a variação de altura em metros       

float calc_altitude(float pressure, float baseline) {
    return 44330.0f * (1.0f - powf(pressure / baseline, 1.0f / 5.255f));
}

int main() {
    stdio_init_all();
    ms5637_init();

    // Pressão de referência (baseline) é capturada ao ligar o dispositivo
    // Isso permite calcular a variação de altura(altura relativa) em relação a essa pressão atmosférica
    // Essa pressão de referência pode ser ajustada manualmente se necessário

    float baseline_pressure = 0;
    float temperature, pressure;

    // Captura pressão de referência ao ligar
    while (baseline_pressure == 0) {
        if (ms5637_read_temperature_pressure(&temperature, &pressure) == MS5637_STATUS_OK) {
            baseline_pressure = pressure;
            printf("Pressão de referência capturada: %.2f mbar\n", baseline_pressure);
        } else {
            printf("Erro de leitura do sensor\n");
        } 
        sleep_ms(500);
    }

    while (true) {
        if (ms5637_read_temperature_pressure(&temperature, &pressure) == MS5637_STATUS_OK) {
            float delta = calc_altitude(pressure, baseline_pressure);
            printf("Altura relativa: %.2f m | Pressão: %.2f mbar| Temp: %.2f °C\n", delta, pressure, temperature);
        } else {
            printf("Erro ao ler sensor\n");
        }
        sleep_ms(500);
    }
}
