# C-Users-arcarrizopa-Desktop-Posgrado-7_Repositorio_Github
Programación
Software de vigilancia
Plataforma embebida: EDU-CIAA-NXP

Aplicación:

La aplicación es sobre un control de vigilancia en una casa particular. El acceso al armado de seguridad es local, desde el panel de comando en el hogar y también remota, desde el centro de vigilancia.

Periféricos: 
UART, GPIO

Descripción de cada estado
Sus modos de armado de seguridad son:
1. Modo cierre total. En este modo el propietario activa la seguridad bajo el concepto de que en la casa no queda ningún familiar;
2. Modo cierre nocturno. En este modo el propietario y / o su familia activan la seguridad teniendo presente solo los sensores de acceso a la casa (puertas, ventanas,etc.).
3. Modo de prueba de sensores. En este modo se da la posibilidad al propietario de realizar test de confirmación de funcionamiento de los sensores de la casa.

Definir los módulos de software (archivos) que va  implementar para cada periférico.

- aplicacion_uart.h y aplicacion_uart.c. Módulos de implementación principal. 
- arm_cierre_noc.h y arm_cierre_noc.c. Módulos  de implementación de rutina para el Modo de seguridad en estado nocturno.
- arm_cierre_total.h y arm_cierre_total.c. Módulos de implementación de rutina para el Modo de seguridad con cierre total de la vivienda.
- arm_test.h y arm_test.c. Módulos de rutina encargados de las pruebas de sensores.
- menu.h y menu.c. Módulos de software para el menú del del panel de control y comunicación.

Prototipos de las principales funciones públicas y privadas de cada módulo definido .

- typedef enum {OPTION_AL1 = '1', OPTION_AL2 = '2', OPTION_AL3 = '3', OPTION_AL4 = '4',} menu_alarma;
- int menu_options(void);// función menú para la selección de las opciones según el modo que elija el usuario. Devuelve la opción seleccionada;
- void  arm_cierretotal(void); // función de control de disparo de sensores. Comunica en caso de disparo o si la el sistema de vigilancia es desactivado;
- void arm_cierrenoc(void); // función de control de disparo de sensores en modo nocturno, por lo que el sensor de movimiento (TEC2) no es tenido en cuenta. Comunica en caso de disparo o si la el sistema de vigilancia es desactivado;
- void arm_test(void); // función de verificación de los sensores. Confirma en caso de detectar activación de sensores.

