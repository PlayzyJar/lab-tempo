// Para testar diferentes exemplos copie o código abaixo (ou exemplo desejado) para o arquivo main.c
// e execute o projeto. Cada exemplo deve ser testado separadamente.

// OBS1: Certifique-se de que o diretório src/ms5637_02ba03 esteja incluído no caminho 
// e que o arquivo CMakeLists.txt esteja configurado corretamente para incluir o ms5637.c 
// OBS2: Mantenha os arquivos de biblioteca: ms5637.h e ms5637.c na pasta src/ms5637_02ba03/ para melhor modularização e funcionamento.
// O código abaixo é um exemplo de como usar a biblioteca MS5637 para ler temperatura e pressão atmosférica
// e calcular a variação de altura baseada na pressão atmosférica.

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "src/ms5637_02ba03/ms5637.h"


// Função para calcular a altitude baseada na pressão atmosférica ao nível do mar P0(1013.25 mbar) considerando a média global
// Fórmula: h = 44330 * (1 - (P / P0)^(1/5.255))
// onde P0 é a pressão ao nível do mar (nesse exemplo pode ser calibrada para o meu local manualmente)    
float calc_altitude(float pressure, float sea_level_pressure) {
    return 44330.0f * (1.0f - powf(pressure / sea_level_pressure, 1.0f / 5.255f));
}

int main() {
    stdio_init_all();
    ms5637_init();

    const float sea_level_pressure = 1013.25f; // mbar (pode ser calibrado para o local)

    while (true) {
        float temperature, pressure;
        if (ms5637_read_temperature_pressure(&temperature, &pressure) == MS5637_STATUS_OK) {
            float altitude = calc_altitude(pressure, sea_level_pressure);
            printf("Altura estimada: %.2f m | Pressão: %.2f mbar | Temp: %.2f °C\n",
                   altitude, pressure, temperature);
        } else {
            printf("Erro de leitura do sensor\n");
        }
        sleep_ms(1000);
    }
}
