/*   EJERICIO 2 DRIVER: VOID GPIO_INIT2026(VOID) PARA ESP32
		Ahora segmentar código.
		Archivos:
		gpio_2026.h = declaraciones o prototipos, definición de ctes.
		gpio_2026.c = implementacion de funciones
		 	 
		APLICACIÓN: BTN1= activa secuencia			SECUENCIA: R -> G -> B y se repite
					BTN2= detiene secuencia
*/



/* ═══════════════════════════════════════════════════════════
   DRIVER
   ═══════════════════════════════════════════════════════════ */

#include "gpio_2026.h"
#include "../gpio_2026.c"

/* ═══════════════════════════════════════════════════════════
   APLICACIÓN
   ═══════════════════════════════════════════════════════════ */

void app_main(void)
{
    gpio_init2026();
    bool running = false;
    uint8_t color = 0;

    while (true) {

        // BTN1 — inicia secuencia
        if (gpio_read(PIN_BIT18)) {
            running = true;
            vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_MS));
        }

        // BTN2 — detiene secuencia y apaga RGB
        if (gpio_read(PIN_BIT19)) {
            running = false;
            color = 0;               // reinicia color para próxima secuencia
            rgb_set(0, 0, 0);        // apaga todo
            printf("Boton2 presiondo\n");
            vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_MS));
        }

        // Secuencia R → G → B
        if (running) {
            switch (color) {
                case 0: rgb_set(1, 0, 0); printf("Rojo\n"); break;  // Rojo
                case 1: rgb_set(0, 1, 0);printf("verde\n"); break;  // Verde
                case 2: rgb_set(0, 0, 1);printf("azul\n"); break;  // Azul
            }

            color = (color + 1) % 3;  
            vTaskDelay(pdMS_TO_TICKS(COLOR_MS));
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
