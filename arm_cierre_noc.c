/*
 * arm_cierre_noc.c
 *
 *  Created on: 26 ago. 2021
 *      Author: Pablo Jesús Carrizo
 */
/*==================[inclusions]=============================================*/

#include "sapi.h"     // <= sAPI header
#include "arm_cierre_noc.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
//static uint8_t modo_alarma_select = 0;
//static uint8_t modo_alarma2 = 0;
//static uint8_t modo_alarma3 = 0;
/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

typedef enum{
    OPTION_AL1 = '1',
    OPTION_AL2 = '2',
    OPTION_AL3 = '3',
	OPTION_AL4 = '4',
} menu_alarma;

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DEL LLAMADO DESDE aplicacion_uart
int arm_cierrenoc(void){

    // ------------- INICIALIZACIONES -------------
	/* Variable de Retardo no bloqueante */
	delay_t delay;

	/* Inicializar Retardo no bloqueante con tiempo en milisegundos (500ms = 0,5s) */
	delayConfig( &delay, 50 );

	// Inicializar UART_USB a 115200 baudios
	uartConfig( UART_USB, 115200 );

	uint8_t input2 = 0;
	uint8_t input3 = 0;
	menu_alarma dato_alarma = 0;
    static char zona [3];
    uint8_t valor = FALSE;
    uint8_t led = 0;

    while (1){
    	valor = FALSE;
    	dato_alarma = 0;
    	delayRead( &delay );
		//uartWriteString( UART_USB, "-----PRUEBA\r\n" ); //
		while (valor == FALSE){
			delayRead( &delay );
			uartReadByte( UART_USB, &input2 );	// se toma dato desde la PC
			input3 = input2;
			//uartWriteString( UART_USB, "-----BUCLE DE DETECCION DE DISPARO DE ZONAS------\r\n" ); //
			if (!gpioRead( TEC1 )){
				do{
					delayRead( &delay );
				}while (!gpioRead( TEC1 ));

				dato_alarma = '1';
				valor = TRUE;
			}

			if (!gpioRead( TEC2) ){
				do{
					delayRead( &delay );
				}while (!gpioRead( TEC2 ));
				delayConfig( &delay, 1000 );
				//dato_alarma = '2';
				gpioWrite( LED3, ON );
				delayRead( &delay );
				gpioWrite( LED3, OFF );
				delayConfig( &delay, 50 );
			}
				//valor = TRUE;

			if (!gpioRead( TEC3 )){
				do{
					delayRead( &delay );
				}while (!gpioRead( TEC3 ));

				dato_alarma = '3';
				valor = TRUE;
			}
			if ( !gpioRead( TEC4 ) ){// || input3
				do{
					delayRead( &delay );
				}while (!gpioRead( TEC4 ));
				uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------\r\n" ); //
				uartWriteString( UART_USB, "                           ALARMA DESACTIVADA DESDE PANEL DEL HOGAR \r\n" ); // Envia mensaje al ACUDA  sobre la zona involucrada
				uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------\r\n" ); //
				gpioWrite( LED3, OFF );
				gpioWrite( LED2, OFF );
				gpioWrite( LED1, OFF );
				gpioWrite( LEDB, OFF );

				return 0;
			}
			if ( input3 ){
				delayRead( &delay );
				uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------------------------------------------\r\n" ); //
				uartWriteString( UART_USB, "                        ALARMA DESACTIVADA DESDE EL CENTRO DE VIGILANCIA\r\n" ); // Envia mensaje al ACUDA  sobre la zona involucrada
				uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------------------------------------------\r\n" ); //
				gpioWrite( LED3, OFF );
				gpioWrite( LED2, OFF );
				gpioWrite( LED1, OFF );
				gpioWrite( LEDB, OFF );

				return 0;
			}


			/*
			if ( !gpioRead( TEC4 ) || input3 ){
				delayRead( &delay );

				uartWriteString( UART_USB, "---------------------------------\r\n" ); //
				uartWriteString( UART_USB, "*****!!ALARMA DESACTIVADA!!*****\r\n" ); // Envia mensaje al ACUDA  sobre la zona involucrada
				uartWriteString( UART_USB, "---------------------------------\r\n" ); //
				return 0;
			}
*/
		}
		switch (dato_alarma) {
			case OPTION_AL1:
				input3 = 0;
				valor = FALSE;
				uartWriteString( UART_USB, "                           DISPARO ALARMA, PROPIETARIO: PJC  \r\n" ); // Envia mensaje al ACUDA
				uartWriteString( UART_USB, "\r\n" ); //
				gpioWrite( LED3, ON );
				uartWriteString( UART_USB, "                               ZONA 1: VENTANA HABITACIÓN     \r\n" ); // Envia mensaje al ACUDA sobre la zona involucrada
		while ( valor == FALSE ){
					if (!gpioRead( TEC4 ) || input3 != 0)
						valor = TRUE;
					delayRead( &delay );
					uartReadByte( UART_USB, &input2 );	// se toma dato desde la PC
					input3 = input2;
				}
				if (input3 != 0){
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------------------------------------------\r\n" ); //
					uartWriteString( UART_USB, "                        ALARMA DESACTIVADA DESDE EL CENTRO DE VIGILANCIA\r\n" ); // Envia mensaje al ACUDA  sobre la zona involucrada
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------------------------------------------\r\n" ); //
					gpioWrite( LED3, OFF );
					gpioWrite( LED2, OFF );
					gpioWrite( LED1, OFF );
					gpioWrite( LEDB, OFF );
					return 0;
				}
				else{
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------\r\n" ); //
					uartWriteString( UART_USB, "                           ALARMA DESACTIVADA DESDE PANEL DEL HOGAR \r\n" ); // Envia mensaje al ACUDA  sobre la zona involucrada
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------\r\n" ); //
					gpioWrite( LED3, OFF );
					gpioWrite( LED2, OFF );
					gpioWrite( LED1, OFF );
					gpioWrite( LEDB, OFF );
					return 0;

				}

			break;
			case OPTION_AL3:
				input3 = 0;
				valor = FALSE;
				uartWriteString( UART_USB, "\r\n" ); // Envia primera linea
				uartWriteString( UART_USB, "                       __________________________________________________\r\n" ); //
				uartWriteString( UART_USB, "                         *****  DISPARO ALARMA, PROPIETARIO: PJC  *****\r\n" ); // Envia mensaje al ACUDA
				uartWriteString( UART_USB, "\r\n" ); //
				gpioWrite( LED3, ON );
				uartWriteString( UART_USB, "                         *****       ZONA 3: PUERTA PRINCIPAL   *****\r\n" ); // Envia mensaje al ACUDA sobre la zona involucrada
				uartWriteString( UART_USB, "                       _________________________________________________\r\n" ); //
				while ( valor == FALSE ){
					if (!gpioRead( TEC4 ) || input3 != 0)
						valor = TRUE;
					delayRead( &delay );
					uartReadByte( UART_USB, &input2 );	// se toma dato desde la PC
					input3 = input2;
				}
				if (input3 != 0){
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------------------------------------------\r\n" ); //
					uartWriteString( UART_USB, "                        ALARMA DESACTIVADA DESDE EL CENTRO DE VIGILANCIA\r\n" ); // Envia mensaje al ACUDA  sobre la zona involucrada
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------------------------------------------\r\n" ); //
					gpioWrite( LED3, OFF );
					gpioWrite( LED2, OFF );
					gpioWrite( LED1, OFF );
					gpioWrite( LEDB, OFF );
					return 0;
				}
				else{
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------\r\n" ); //
					uartWriteString( UART_USB, "                           ALARMA DESACTIVADA DESDE PANEL DEL HOGAR \r\n" ); // Envia mensaje al ACUDA  sobre la zona involucrada
					uartWriteString( UART_USB, "                -------------------------------------------------------------------------------------------\r\n" ); //
					gpioWrite( LED3, OFF );
					gpioWrite( LED2, OFF );
					gpioWrite( LED1, OFF );
					gpioWrite( LEDB, OFF );
					return 0;

				}
			break;

		}

    }

    return 0;
 }

 /*==================[end of file]============================================*/




