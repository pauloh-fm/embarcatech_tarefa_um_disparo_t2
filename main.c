#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "botao.h"
#include <stdio.h>

// Definindo os pinos GPIO
#define LED_BLUE_PIN 11
#define LED_RED_PIN 12
#define LED_GREEN_PIN 13
#define DELAY_MS 3000  // Tempo de atraso (3 segundos)

// Variáveis de controle
bool temporizador_executando = false;  // Controla se o temporizador está em execução
int estado_leds = 0;                   // Estado atual dos LEDs

// Protótipo da função de callback do temporizador
int64_t leds_callback(alarm_id_t id, void *user_data);

// Inicializa os LEDs
void init_leds(void) {
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Desliga todos os LEDs inicialmente
    gpio_put(LED_BLUE_PIN, 0);
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);
}

// Atualiza o estado dos LEDs de acordo com a sequência
void atualizar_leds() {
    // Desliga todos os LEDs antes de alterar o estado
    gpio_put(LED_BLUE_PIN, 0);
    gpio_put(LED_RED_PIN, 0);
    gpio_put(LED_GREEN_PIN, 0);

    // Liga os LEDs com base no estado atual
    switch (estado_leds) {
        case 0:
            gpio_put(LED_BLUE_PIN, 1);
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);
            estado_leds = 1;
            break;
        case 1:
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);
            estado_leds = 2;
            break;
        case 2:
            gpio_put(LED_GREEN_PIN, 1);
            estado_leds = 3;
            break;
        case 3:
            temporizador_executando = false;  // Finaliza o temporizador
            estado_leds = 0;
            printf("Sequência concluída.\n");
            return;
    }

    // Inicia o temporizador para o próximo callback
    add_alarm_in_ms(DELAY_MS, leds_callback, NULL, false);
}

// Callback do temporizador
int64_t leds_callback(alarm_id_t id, void *user_data) {
    atualizar_leds();
    return 0;
}

int main() {
    stdio_init_all();  // Inicializa a UART para saída serial
    init_leds();       // Inicializa os LEDs
    init_botoes(botao_a);  // Inicializa o botão

    printf("Sistema iniciado. Aperte o botão para iniciar a sequência.\n");

    while (true) {
        // Verifica se o botão foi pressionado e o temporizador não está em execução
        if (!temporizador_executando && button_debounce(botao_a)) {
            printf("Botão pressionado! Iniciando sequência de LEDs.\n");

            // Liga todos os LEDs e inicia o temporizador
            gpio_put(LED_BLUE_PIN, 1);
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);

            // Define o estado inicial e inicia o temporizador
            estado_leds = 1;
            temporizador_executando = true;

            // Inicia o temporizador para o primeiro callback
            add_alarm_in_ms(DELAY_MS, leds_callback, NULL, false);
        }

        // Aguarda um pequeno delay para não sobrecarregar o loop
        sleep_ms(10);
    }

    return 0;
}
