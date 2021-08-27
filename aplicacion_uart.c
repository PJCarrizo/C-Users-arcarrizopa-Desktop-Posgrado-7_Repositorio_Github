/*=============================================================================
 * Author: Pablo Jesús Carrizo
 * Date: 2021/08/20
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "aplicacion_uart.h"
#include "sapi.h"     // <= sAPI header
#include "menu.h"
#include "arm_cierre_total.h"
#include "arm_cierre_noc.h"
#include "arm_test.h"
/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/
//extern uint8_t modo_alarma_actual = 0;
//static uint8_t modo_alarma2 = 0;
//static uint8_t modo_alarma3 = 0;
typedef enum{
    MODO_ALARMA_1 = 1,
	MODO_ALARMA_2 = 2,
	MODO_ALARMA_3 = 3,
} modo_alarma;

modo_alarma modo_alarma_actual = 0;
/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   // ------------- INICIALIZACIONES -------------
	/* Variable de Retardo no bloqueante */
	delay_t delay;

	/* Inicializar Retardo no bloqueante con tiempo en milisegundos (500ms = 0,5s) */
	delayConfig( &delay, 50 );

   // ----- Declaraciòn de variable local -----------------------------------
   //modo_alarma modo_alarma_actual;

   // ----- Repeat for ever -------------------------
   // FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET.
   while( true ) {

	  modo_alarma_actual = menu_options();


	  while (!gpioRead( TEC1 ) || !gpioRead( TEC2 ) || !gpioRead( TEC3 ) || !gpioRead( TEC4 )){
	  			delayRead( &delay );
	  }

	  //delayRead( &delay );


	  switch (modo_alarma_actual) {
	  	  case MODO_ALARMA_1:

	  		  arm_cierretotal();
	  		  while (!gpioRead( TEC1 ) || !gpioRead( TEC2 ) || !gpioRead( TEC3 ) || !gpioRead( TEC4 )){
	  		  			delayRead( &delay );
	  		  }

	  		  break;
	  	  case MODO_ALARMA_2:

	  		  arm_cierrenoc();
	  		  while (!gpioRead( TEC1 ) || !gpioRead( TEC2 ) || !gpioRead( TEC3 ) || !gpioRead( TEC4 )){
	  		  			delayRead( &delay );
	  		  }

	  		  break;
	  	  case MODO_ALARMA_3:
	  		  arm_test();
	  		  while (!gpioRead( TEC1 ) || !gpioRead( TEC2 ) || !gpioRead( TEC3 ) || !gpioRead( TEC4 )){
	  		  			delayRead( &delay );
	  		  }

	  		  break;
	  }
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
