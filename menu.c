/*
 * menu.c
 *
 *  Created on: 20 ago. 2021
 *      Author: Pablo Jesús Carrizo
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"     // <= sAPI header
#include "menu.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
static uint8_t modo_alarma_select = 0;
//static uint8_t modo_alarma2 = 0;
//static uint8_t modo_alarma3 = 0;
/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

typedef enum{
    OPTION_1 = '1',
    OPTION_2 = '2',
    OPTION_3 = '3',
} menu_state;

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DEL LLAMADO DESDE aplicacion_uart
int menu_options(void){

    // ------------- INICIALIZACIONES -------------
	/* Variable de Retardo no bloqueante */
	delay_t delay;

	/* Inicializar Retardo no bloqueante con tiempo en milisegundos (500ms = 0,5s) */
	delayConfig( &delay, 50 );

	// Inicializar UART_USB a 115200 baudios
	uartConfig( UART_USB, 115200 );

	uint8_t input1;
	uint8_t dato = 0;
    menu_state state;
    uint8_t modo_alarma_actual = 0;

    //printf("Please provide integer in range [1-4]: ");
    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia primera linea
    uartWriteString( UART_USB, "             *******    MENU PRINCIPAL DE PANEL DE ALARMA     *****\r\n" ); // Envia primera linea
    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia primera linea
    uartWriteString( UART_USB, "                         ARMADO SEGURIDAD CIERRE TOTAL________1\r\n" ); // Envia opción 1
    uartWriteString( UART_USB, "                         ARMADO SEGURIDAD NOCHE_______________2\r\n" ); // Envia opción 2
    uartWriteString( UART_USB, "                         PRUEBA DE ZONAS________________________3\r\n" ); // Envia opción 3

    while (dato == 0){

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    	/////////////////// RUTINA PARA LA SELECCION DE LAS OPCIONES DE ARMADO MEDIANTE UART //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    	uartReadByte( UART_USB, &input1 );	// se toma dato desde la PC
    	state = input1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    	/////////////////// RUTINA PARA LA SELECCION DE LAS OPCIONES DE ARMADO MEDIANTE TECLADO //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    	if ( !gpioRead( TEC1 ) ){			// Se tiene en cuenta si se selecciono desde teclado
    		do{
    			delayRead( &delay );
    		}while (!gpioRead( TEC1 ));
    		state = '1'; //OPTION_1
        }
        if ( !gpioRead( TEC2 ) ){
    		do{
    			delayRead( &delay );
    		}while (!gpioRead( TEC2 ));
        	state = '2'; //OPTION_2
        }
        if ( !gpioRead( TEC3 ) ){
    		do{
    			delayRead( &delay );
    		}while (!gpioRead( TEC3 ));
        	state = '3'; //OPTION_3
        }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       	/////////////////// RUTINA PARA MOSTRAR LAS OPCIONES DE ARMADO MEDIANTE MONITOR Y LED //////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		switch (state) {
			case OPTION_1:
				uartWriteString( UART_USB, "\r\n" ); // Envia primera linea
			    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia primera linea
				uartWriteString( UART_USB, "             *****   MODO DE VIGILANCIA CIERRE TOTAL     *****\r\n" ); // Envia mensaje al Centro de Vigilancia
				uartWriteString( UART_USB, "                       USTED SALIÓ DEL MENU OPCIONES\r\n" );
				uartWriteString( UART_USB, "                       CIRCUITO DE VIGILANCIA ARMADO\r\n" );
			    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia linea
				//modo_alarma_select = 1;
			    /* Enciendo el led azul y apago el resto*/
			    gpioWrite( LED1, OFF );
			    gpioWrite( LED2, OFF );
			    gpioWrite( LED3, OFF );
			    gpioWrite( LEDB, ON );
				dato = 1;
				/*delayRead( &delay );
				uartWriteByte(   UART_USB, 27    );   // ESC command
				uartWriteString( UART_USB, "[2J" );   // Clear screen command
				uartWriteByte(   UART_USB, 27    );   // ESC command
				uartWriteString( UART_USB, "[H"  );   // Cursor to home command
				delayRead( &delay ); // Pequeño delay para que permita mostrar nuevos mensajes
				uartWriteString( UART_USB, "************************************\r\n" ); //
				uartWriteString( UART_USB, "*****SE SELECCIONO CIERRE TOTAL*****\r\n" ); // Envia mensaje al propietario
				uartWriteString( UART_USB, "************************************\r\n" ); //
				*/
				modo_alarma_actual = 1;
				return 1 ;
				break;
			case OPTION_2:
			    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia primera linea
				uartWriteString( UART_USB, "                       - MODO DE VIGILANCIA CIERRE NOCTURNO -\r\n" ); // Envia mensaje al Centro de Vigilancia
				uartWriteString( UART_USB, "                          USTED SALIÓ DEL MENU OPCIONES\r\n" );
				uartWriteString( UART_USB, "                     CIRCUITO DE VIGILANCIA ARMADO EN MODO NOCTURNO\r\n" );
			    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia linea
				modo_alarma_select = 2;
				/* Enciendo el led 1 y apago el resto*/
			    gpioWrite( LED1, ON );
			    gpioWrite( LED2, OFF );
			    gpioWrite( LED3, OFF );
			    gpioWrite( LEDB, OFF );
				dato = 2;
				return 2;
				break;
			case OPTION_3:
			    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia primera linea
				uartWriteString( UART_USB, "                          - MODO DE TEST DE SENSORES -\r\n" ); // Envia mensaje al Centro de Vigilancia
				uartWriteString( UART_USB, "                          USTED SALIÓ DEL MENU OPCIONES\r\n" );
				uartWriteString( UART_USB, "                     CIRCUITO DE VIGILANCIA ARMADO EN MODO TEST SENSORES\r\n" );
			    uartWriteString( UART_USB, "          ****************************************************************************\r\n" ); // Envia linea
				modo_alarma_select = 3;
				/* Enciendo el led 2 y apago el resto*/
			    gpioWrite( LED1, OFF );
			    gpioWrite( LED2, ON );
			    gpioWrite( LED3, OFF );
			    gpioWrite( LEDB, OFF );
				dato = 3;
				return 3;
				break;
			//default:
				//uartWriteString( UART_USB, "__ALARMA 4__\r\n" ); // Envia primera linea
				//uartWriteByte( UART_USB, state ); // Envia '1'
				//uartWriteByte( UART_USB, input1 ); // Envia '1'
				//input1 = 0;
				//break;
		}
    }

    return 0;
 }

 /*==================[end of file]============================================*/

