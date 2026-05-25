#ifndef GPIO_2026_H
#define GPIO_2026_H

#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/* ── Registros GPIO ─────────────────────────────────────────── */
#define GPIO_ENABLE     (*(volatile uint32_t*)0x3FF44020)
#define GPIO_OUT        (*(volatile uint32_t*)0x3FF44004)
#define GPIO_OUT_W1TS   (*(volatile uint32_t*)0x3FF44008)
#define GPIO_OUT_W1TC   (*(volatile uint32_t*)0x3FF4400C)
#define GPIO_IN         (*(volatile uint32_t*)0x3FF4403C)

/* ── Registros IO_MUX ───────────────────────────────────────── */
#define IO_MUX_GPIO18_REG (*(volatile uint32_t*)0x3FF49070) // BTN1
#define IO_MUX_GPIO19_REG (*(volatile uint32_t*)0x3FF49074) // BTN2
#define IO_MUX_GPIO12_REG (*(volatile uint32_t*)0x3FF49034) // R
#define IO_MUX_GPIO13_REG (*(volatile uint32_t*)0x3FF49038) // G
#define IO_MUX_GPIO14_REG (*(volatile uint32_t*)0x3FF49030) // B

/* ── Bits de configuración IO_MUX ──────────────────────────── */
#define FUN_IE      (1 << 9)   // Input enable
#define PULL_WPD    (1 << 7)   // Pull-down enable
#define PULL_WPU    (1 << 8)   // Pull-up enable

/* ── Máscaras de pines ──────────────────────────────────────── */
#define PIN_BIT18   (1 << 18)  // BTN1
#define PIN_BIT19   (1 << 19)  // BTN2
#define PIN_BIT12   (1 << 12)  // RGB - Verde
#define PIN_BIT13   (1 << 13)  // RGB - Rojo
#define PIN_BIT14   (1 << 14)  // RGB - Azul

/* ───────── RGB ────────────── */
#define RGB_ALL     (PIN_BIT12 | PIN_BIT13 | PIN_BIT14)

#define DEBOUNCE_MS  50
#define COLOR_MS    1000

/* ───────── Prototipos ─────────────────────────────────────────────── */
void gpio_init2026(void);
void gpio_config_in(volatile uint32_t *pin, uint32_t bit, uint32_t pull_mode);
void gpio_config_out(volatile uint32_t *pin, uint32_t bit);
bool gpio_read(uint32_t pin_bit);
void gpio_write(uint32_t pin_bit, int on_off);
void rgb_set(int r, int g, int b);   // simplifica la secuencia

#endif