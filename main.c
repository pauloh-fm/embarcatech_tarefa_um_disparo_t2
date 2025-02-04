#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "botao.h"
#include <stdio.h>

// Definindo os pinos GPIO
#define LED_BLUE_PIN 11
#define LED_RED_PIN 12
#define LED_GREEN_PIN 13

// Definindo o tempo de atraso  (3 segundos)
#define DELAY_MS 3000

// Variáveis de controle
bool executando_temporizador = false;  // Controla se o temporizador está em execução
int state = 0;                  // Estado atual dos LEDs

// Função de callback para alterar o estado dos LEDs
int64_t leds_callback(alarm_id_t id, void *user_data);

int main() {
    // Inicializa a UART para saída serial
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Inicializa o botão
    init_botoes(botao_a);

    printf("Sistema iniciado. Aguarde o pressionamento do botão.\n");

    while (true) {
        // Verifica se o botão foi pressionado
        if (gpio_get(botao_a) && !executando_temporizador) {
            printf("Botão pressionado! Iniciando temporização.\n");

            // Liga todos os LEDs e inicia o temporizador
            gpio_put(LED_BLUE_PIN, 1);
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);

            // Define o estado inicial e inicia o temporizador
            state = 1;
            executando_temporizador = true;

            // Inicia o temporizador para o primeiro callback
            add_alarm_in_ms(DELAY_MS, leds_callback, NULL, false);
        }

        // Aguarda um pequeno delay para não sobrecarregar o loop
        sleep_ms(10);
    }

    return 0;
}
