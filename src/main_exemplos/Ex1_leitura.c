/*  Para testar diferentes exemplos:
Pode proceder de duas formas

Primeira:
Descomente a linha correspondentes ao exemplo que deseja testar no arquivo CMakeLists.txt em:
add_executable(MS5637_02BA03_BIBLIO
    src/ms5637_02ba03/ms5637.c
    # src/main.c
    src/main_exemplos/Ex1_leitura.c (neste exemplo em si descomentei a linha correspondente)
    # src/main_exemplos/Ex2_barometro.c
    # src/main_exemplos/Ex3_varBarometrica.c
    # src/main_exemplos/Ex4_ajustepressao.c
)

Segunda:
1 - Selecione o exemplo desejado
2 - Copie o código abaixo (ou exemplo desejado) para o arquivo main.c
3 - Execute o projeto. Cada exemplo deve ser testado separadamente. 


 OBS1: Certifique-se de que o arquivo CMakeLists.txt esteja configurado corretamente para incluir o ms5637.c
 e que o diretório src/ms5637_02ba03 esteja incluído no caminho
 OBS2: Mantenha os arquivos de biblioteca: ms5637.h e ms5637.c na pasta src/ms5637_02ba03/ para melhor funcionamento e modularização.

 O código abaixo é o exemplo de como usar a biblioteca MS5637 para ler temperatura e pressão atmosférica
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "src/ms5637_02ba03/ms5637.h"

int main() {
    stdio_init_all();
    ms5637_init();

    //Teste básico inicial - Leitura contínua de temperatura e pressão atmosférica em mbar

    while (true) {
        float temp, press;
        if (ms5637_read_temperature_pressure(&temp, &press) == MS5637_STATUS_OK) {
            printf("Temp: %.2f C | Pressão: %.2f mbar\n", temp, press);
        } else {
            printf("Erro na leitura do MS5637\n");
        }
        sleep_ms(1000);
    }
}
