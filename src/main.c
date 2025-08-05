#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "ms5637.h"

// Configurações I2C
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5
#define SSD1306_ADDR 0x3C

// Estrutura do display
ssd1306_t display;

/**
 * @brief Desenha um painel de dados no display
 * @param temp Temperatura em °C
 * @param press Pressão em mbar
 * @param alt Altitude em metros
 */
void draw_sensor_panel(ssd1306_t *disp, float temp, float press, float alt) {
    char buffer[16];
    
    // Limpa o display
    ssd1306_clear(disp);
    
    // Cabeçalho
    ssd1306_draw_string(disp, 30, 0, "MS5637 SENSOR");
    ssd1306_fill_rect(disp, 0, 10, 128, 1, true);
    
    // Temperatura
    ssd1306_draw_string(disp, 10, 15, "Temperatura:");
    snprintf(buffer, sizeof(buffer), "%.2f C", temp);
    ssd1306_draw_string(disp, 80, 15, buffer);
    
    // Pressão
    ssd1306_draw_string(disp, 10, 27, "Pressao:");
    snprintf(buffer, sizeof(buffer), "%.2f hPa", press);
    ssd1306_draw_string(disp, 80, 27, buffer);
    
    // Altitude
    ssd1306_draw_string(disp, 10, 39, "Altitude:");
    snprintf(buffer, sizeof(buffer), "%.2f m", alt);
    ssd1306_draw_string(disp, 80, 39, buffer);
    
    // Rodapé
    ssd1306_fill_rect(disp, 0, 50, 128, 1, true);
    ssd1306_draw_string(disp, 20, 55, "Pico W - I2C");
    
    // Atualiza o display
    ssd1306_display(disp);
}

/**
 * @brief Calcula a altitude relativa
 * @param pressure Pressão atual
 * @param baseline Pressão de referência
 * @return Altitude em metros
 */
float calculate_altitude(float pressure, float baseline) {
    return 44330.0f * (1.0f - powf(pressure / baseline, 1.0f / 5.255f));
}

int main() {
    stdio_init_all();
    
    // Inicializa I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    
    // Inicializa display
    ssd1306_init(&display, I2C_PORT, SSD1306_ADDR);
    ssd1306_clear(&display);
    ssd1306_draw_string(&display, 20, 20, "Inicializando...");
    ssd1306_display(&display);
    
    // Inicializa sensor
    ms5637_init();
    
    // Captura pressão de referência
    float baseline = 0;
    float temp, press;
    while(baseline == 0) {
        if(ms5637_read_temperature_pressure(&temp, &press) == MS5637_STATUS_OK) {
            baseline = press;
        }
        sleep_ms(500);
    }
    
    // Loop principal
    while(true) {
        if(ms5637_read_temperature_pressure(&temp, &press) == MS5637_STATUS_OK) {
            float altitude = calculate_altitude(press, baseline);
            
            // Atualiza display
            draw_sensor_panel(&display, temp, press, altitude);
            
            // Log serial (opcional)
            printf("Temp: %.2f°C | Pressão: %.2fhPa | Alt: %.2fm\n", 
                  temp, press, altitude);
        } else {
            // Mensagem de erro no display
            ssd1306_clear(&display);
            ssd1306_draw_string(&display, 10, 20, "Erro de leitura!");
            ssd1306_draw_string(&display, 10, 35, "Verifique sensor");
            ssd1306_display(&display);
        }
        
        sleep_ms(1000); // Atualiza a cada 1 segundo
    }
}