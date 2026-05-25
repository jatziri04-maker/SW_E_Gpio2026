#include <stdio.h>
#include "gpio_2026.h"

/* ── Macro MCU_SEL = función 2 (GPIO) en bits [14:12] ──────── */
#define MCU_SEL_GPIO(pin_reg) \
    do {                      \
        (pin_reg) &= ~(7 << 12); \
        (pin_reg) |=  (2 << 12); \
    } while(0)
    
    
    void gpio_init2026(void)
{
    // PULL_WPU porque los botones son activos en bajo
    gpio_config_in(&IO_MUX_GPIO18_REG, PIN_BIT18, PULL_WPU);
    gpio_config_in(&IO_MUX_GPIO19_REG, PIN_BIT19, PULL_WPU);

    gpio_config_out(&IO_MUX_GPIO12_REG, PIN_BIT12);
    gpio_config_out(&IO_MUX_GPIO13_REG, PIN_BIT13);
    gpio_config_out(&IO_MUX_GPIO14_REG, PIN_BIT14);
}

void gpio_config_in(volatile uint32_t *pin, uint32_t bit, uint32_t pull_mode)
{
    *pin |= FUN_IE;             // Habilitar input
    GPIO_ENABLE &= ~bit;        // Deshabilitar como salida

    MCU_SEL_GPIO(*pin);         // Funcion 2 = GPIO

    // Aplicar modo de pull
    if (pull_mode == PULL_WPD) {
        *pin |=  PULL_WPD;
        *pin &= ~PULL_WPU;
    } else if (pull_mode == PULL_WPU) {
        *pin |=  PULL_WPU;
        *pin &= ~PULL_WPD;
    }
}

void gpio_config_out(volatile uint32_t *pin, uint32_t bit)
{
    *pin &= ~FUN_IE;
    MCU_SEL_GPIO(*pin);
    GPIO_ENABLE |= bit;
    GPIO_OUT_W1TS = bit;  // iniciar en 1 = LEDs apagados (ánodo común)
}

bool gpio_read(uint32_t pin_bit)
{
    return ((GPIO_IN & pin_bit) == 0);  // invertido
}

void gpio_write(uint32_t pin_bit, int on_off)
{
    bool es_rgb = (pin_bit & RGB_ALL) != 0;

    if (on_off) {
        // Encender
        if (es_rgb) GPIO_OUT_W1TC = pin_bit;  // ánodo comun: 0 = enciende 
        else        GPIO_OUT_W1TS = pin_bit;
    } else {
        // Apagar
        if (es_rgb) GPIO_OUT_W1TS = pin_bit;  // ánodo comun: 1 = apaga 
        else        GPIO_OUT_W1TC = pin_bit;
    }
}

// Enciende el color indicado y apaga los demás en una sola función
void rgb_set(int r, int g, int b)
{
    gpio_write(PIN_BIT13, r);
    gpio_write(PIN_BIT12, g);
    gpio_write(PIN_BIT14, b);
}

