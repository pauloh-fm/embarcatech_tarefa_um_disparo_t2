#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "botao.h"

// Constante para o pino do botão A
const uint botao_a = 5;

// Função para inicializar o botão
void init_botoes(uint botao_pin) {
    gpio_init(botao_pin);
    gpio_set_dir(botao_pin, GPIO_IN);    // Configura o pino como entrada
    gpio_pull_down(botao_pin);           // Habilita o pull-down interno
}

// Função para verificar se o botão foi pressionado (com debounce)
bool button_debounce(uint botao_pin) {
    static uint32_t last_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Verifica se o botão foi pressionado (nível alto em pull-down)
    if (gpio_get(botao_pin)) {
        if (current_time - last_time > 200) {  // Delay de debounce de 200ms
            last_time = current_time;
            return true;
        }
    }

    return false;
}

