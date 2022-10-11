# PdM_sescriba
Repositorio con Practicas de Programacion de Microprocesadors
Autor: Escribá Pedro Santiago

------------------------------------------------------------------------
Práctica 1
Objetivo:
Familiarizarse con el entorno de trabajo STM32CubeIDE + NUCLE-F429ZI + firmware. 

Punto 1:
Implementar un programa que genere una secuencia periódica con los leds de la placa NUCLEO-F429ZI.

La secuencia debe seguir el orden: LED1, LED2, LED3, LED1,... etc.
Cada led debe permanecer encendido 200 ms. y 200 ms apagado.  No debe encenderse más de un led simultáneamente.

Punto 2:
Utilizar el pulsador azul (USER_BUTTON) para controlar cómo se recorre la secuencia de leds.  Cada vez que se presiona el pulsador se debe alternar el orden de la secuencia entre:
LED1, LED2, LED3, LED1,... etc.
LED1, LED3, LED2, LED1,... etc.

Algunas preguntas para pensar el ejercicio:

¿Cómo responde el programa a las pulsaciones, hay falsos positivos o pulsaciones no detectadas? ¿Se implementa alguna técnica de antirrebote de las pulsaciones?
¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar un led? ¿Qué diferencia hay entre estas alternativas?
¿Se puede cambiar el sentido de la secuencia en cualquier momento  de la ejecución?
¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido de cada led fuera sensiblemente más grande, 1 segundo por ejemplo? ¿Y si fuera  sensiblemente más chico, 50 ms por ejemplo?

------------------------------------------------------------------------
Práctica 2
Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes. 
Punto 1
Implementar las funciones auxiliares necesarias para usar retardos no bloqueantes en un archivo fuente main.c con su correspondiente archivo de cabecera main.h.
En main.h se deben ubicar los prototipos de las siguientes funciones y las declaraciones
typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t;	  // Qué biblioteca se debe incluir para que esto compile?
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

En main.c se deben ubicar la implementación de todas las funciones:
Consideraciones para la implementación:
delayInit debe cargar el valor de duración del retardo en la estructura, en el campo correspondiente. No debe iniciar el conteo del retardo. Debe inicializar el flag running en 'false'.
delayRead debe verificar el estado del flag running.
false, tomar marca de tiempo y cambiar running a ‘true’ 
true, hacer la cuenta para saber si el tiempo del retardo se cumplió o no:

‘marca de tiempo actual - marca de tiempo inicial es mayor o igual a duración del retardo’,

 y devolver un valor booleano que indique si el tiempo se cumplió o no.
delayWrite debe permitir cambiar el tiempo de duración de un delay existente

NOTA: para obtener una marca de tiempo se puede usar la función HAL_GetTick() que devuelve un valor que se incrementa cada 1 ms y que se puede usar como base de tiempo.

Punto 2
Implementar un programa que utilice retardos no bloqueantes y  haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de la siguiente manera:
LED1: 100 ms. 
LED2: 500 ms.
LED3: 1000 ms.

Para pensar luego de resolver el ejercicio:
¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o estos están hardcodeados?
¿Qué bibliotecas estándar se debieron agregar a API_delay.h para que el código compile? Si las funcionalidades de una API propia crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.
¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?

------------------------------------------------------------------------
Práctica 3
Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2.
Punto 1
Crear un nuevo proyecto como copia del proyecto realizado para la práctica 2.
Crear una carpeta API dentro de la carpeta Drivers en la estructura de directorios del nuevo proyecto. Crear dentro de la carpeta API, subcapetas /src y /inc.

Encapsular las funciones necesarias para usar retardos no bloqueantes en un archivo fuente API_delay.c con su correspondiente archivo de cabecera API_delay.h, y ubicar estos archivos en la carpeta API creada.
En API_delay.h se deben ubicar los prototipos de las funciones y declaraciones
typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t;	  // Qué biblioteca se debe incluir para que esto compile?
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

En API_delay.c se deben ubicar la implementación de todas las funciones.
nota: cuando se agregar carpetas a un proyecto de eclipse se deben incluir en el include path para que se incluya su contenido en la compilación.  Se debe hacer clic derecho sobre la carpeta con los archivos de encabezamiento y seleccionar la opción add/remove include path.

Punto 2
Implementar un programa que utilice retardos no bloqueantes y haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de acuerdo a una secuencia predeterminada como en la práctica 1.
Cada led debe permanecer encendido 200 ms.  No debe encenderse más de un led simultáneamente en ningún momento.

Para pensar luego de resolver el ejercicio:
¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o estos están hardcodeados? ¿Hay números “mágicos”?
¿Qué bibliotecas estándar se debieron agregar a API_delay.h para que el código compile? Si las funcionalidades de una API propia crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.
¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?

------------------------------------------------------------------------
Práctica 4
Objetivo:
Implementar un MEF para trabajar con anti-rebotes por software. 
Punto 1
Crear un nuevo proyecto como copia del proyecto realizado para la práctica 3.

Implementar una MEF anti-rebote que permita leer el estado del pulsador de la placa NUCLEO-F429ZI y generar acciones o eventos ante un flanco descendente o ascendente, de acuerdo al siguiente diagrama:



El estado inicial de la MEF debe ser BUTTON_UP.

Implementar dentro de main.c, las funciones:

void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed();			// debe togglear el LED1
void buttonReleased();		// debe togglear el LED3

El tiempo de anti-rebote debe ser de 40 ms con un retardo no bloqueante como los implementados en la práctica 3.

La función debounceFSM_update() debe llamarse periódicamente.


typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t
Punto 2
Crear un nuevo proyecto como copia del proyecto con la implementación del punto 1 de la práctica 4.

Implementar un módulo de software en un archivos fuente API_debounce.c con su correspondiente archivo de cabecera API_debounce.h y ubicarlos en el proyecto dentro de  las carpetas /drivers/API/src y /drivers/API/inc, respectivamente.
En API_debounce.h se deben ubicar los prototipos de las funciones públicas y las declaraciones:
void debounceFSM_init();
void debounceFSM_update();

/* La función readKey debe leer una variable interna del módulo y devolver true o false si la tecla fue presionada.  Si devuelve true, debe resetear (poner en false) el estado de la variable.*/
bool_t readKey();

En API_debounce.c se deben ubicar las declaraciones privadas, los prototipos de las funciones privadas y la implementación de todas las funciones del módulo, privadas y públicas:

La declaración de debounceState_t debe ser privada en el archivo .c y la variable de estado de tipo debounceState_t debe ser global privada (con static).

Declarar una variable tipo bool_t global privada que se ponga en true cuando ocurre un flanco descendente y se ponga en false cuando se llame a la función readKey();

Implementar un programa que cambie la frecuencia de toggleo del LED2 entre 100 ms y 500 ms cada vez que se presione la tecla.  El programa debe usar las funciones anti-rebote del módulo API_debounce y los retardos no bloqueantes del módulo API_delay.

Para pensar luego de resolver el ejercicio:
¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?
¿Se nota una mejora en la detección de las pulsaciones respecto a la práctica 0?
------------------------------------------------------------------------
Proyecto final: MEF y driver para módulo inercial MPU9250

Definición del trabajo: 
- Programa capaz de leer y escribir los registros de un módulo MPU9250 (Unidad de Medición Inercial) 
- Uso de comunicación I2C. 
- Tomar los valores de salida de un giroscopio, un acelerómetro y un sensor de temperatura para un instante dado. 
- Entregados al usuario mediante comunicación UART e impresos en pantalla. 
- Uso de una MEF (Máquina de Estados Finitos), 
    - Encargada de leer los registros cada 1 segundo
    - Imprimirlos por pantalla 
    - Realizar otras actividades sin afectar el flujo del programa (Sin bloqueo).
    
Periféricos utilizados:
- UART
- I2C
- Timer

Modularización: 
- Core
	- src (.c)
		- APP → SM
		- MAIN
	- inc (.h)
		- APP → SM
		- MAIN
- Driver
	- DEV
		- src (.c)→ Timer, UART, MPU9250, Port (I2C)
		- inc (.h)→ Timer, UART, MPU9250, Port (I2C)
MEF:
![Screenshot 2022-10-11 192627](https://user-images.githubusercontent.com/55771346/195209780-94d37d66-3aa2-4440-b6a5-72177b0659dd.png)


