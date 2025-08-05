# Lab-Tempo 🌡️

Projeto para Raspberry Pi Pico W que monitora condições atmosféricas usando:

- Sensor MS5637 (pressão/temperatura)
- Display OLED SSD1306 (128x64)

## Funcionalidades

- Medição precisa de temperatura e pressão
- Cálculo de altitude relativa
- Exibição em tempo real no display OLED
- Saída serial para monitoramento

## Conexões

| Componente   | Pino Pico |
|--------------|----------|
| SSD1306 SDA  | GP4      |
| SSD1306 SCL  | GP5      |
| MS5637 SDA   | GP4      |
| MS5637 SCL   | GP5      |

## Como usar

1. Conectar componentes
2. Compilar com CMake
3. Gravar no Pico
4. Dados aparecem no display

> Projeto em desenvolvimento - versão 0.1