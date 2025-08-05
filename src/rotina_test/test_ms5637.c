
/* Rotina de testes básica e estruturada para a biblioteca do sensor MS5637-02BA03. 
O objetivo é verificar:

- Comunicação I2C correta com o sensor

- Leitura válida dos coeficientes da PROM

- Validação do CRC

- Leitura confiável de pressão e temperatura

- Detecção de erro de conexão

Essa rotina pode ser usada tanto em desenvolvimento quanto em validação de hardware e firmware. 

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "src/ms5637_02ba03/ms5637.h"

// Teste 1: Verifica comunicação e reset

bool test_reset() {
    if (ms5637_reset() == MS5637_STATUS_OK) {
        printf("[TESTE 1] Reset OK\n\n");
        return true;
    } else {
        printf("[TESTE 1] ERRO: Reset falhou\n\n");
        return false;
    }
}

// Teste 2: Verifica leitura da PROM e CRC
bool test_prom_crc() {
    ms5637_reset();
    sleep_ms(20);
    ms5637_status_t status = ms5637_read_temperature_pressure(NULL, NULL); // Força leitura que inclui prom

    if (status == MS5637_STATUS_CRC_ERROR) {
        printf("[TESTE 2] ERRO: Falha no CRC da PROM\n\n");
        return false;
    } else if (status == MS5637_STATUS_OK) {
        printf("[TESTE 2] Leitura PROM e CRC OK\n\n");
        return true;
    } else {
        printf("[TESTE 2] ERRO: Leitura da PROM falhou\n\n");
        return false;
    }
}

// Teste 3: Leitura contínua de pressão e temperatura
bool test_leitura_valida() {
    float temp, press;
    if (ms5637_read_temperature_pressure(&temp, &press) == MS5637_STATUS_OK) {
        printf("[TESTE 3] Temp: %.2f °C | Press: %.2f mbar\n", temp, press);
        return (temp > -50 && temp < 85 && press > 300 && press < 1200); // Faixas esperadas
    } else {
        printf("[TESTE 3] ERRO: Falha ao ler temp/press\n\n");
        return false;
    }
}


int main() {
    stdio_init_all();
    sleep_ms(7000); // Aguarda terminal USB

    printf("\n======== INÍCIO DOS TESTES MS5637 ========\n\n");

    ms5637_init();

    bool result1 = test_reset();
    bool result2 = test_prom_crc();
    bool result3 = test_leitura_valida();

    printf("\n======== RESULTADO FINAL ========\n\n");
    printf("Reset ......................: %s\n\n", result1 ? "OK" : "FALHOU");
    printf("PROM + CRC ................: %s\n\n", result2 ? "OK" : "FALHOU");
    printf("Leitura Temp/Press ........: %s\n\n", result3 ? "OK" : "FALHOU");

    if (result1 && result2 && result3) {
        printf("Ok. Todos os testes passaram.\n\n");
    } else {
        printf("Erro. Algum teste falhou. Verifique conexões ou sensor.\n\n");
    }

    while (true) sleep_ms(1000);
}
