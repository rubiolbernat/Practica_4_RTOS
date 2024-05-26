# PRACTICA 4 :  RTOS
**Alumne: Bernat Rubiol**

L'objectiu de la pràctica és comprendre el funcionament d'un sistema operatiu en temps
Real.

Per a això realitzarem una pràctica on generarem diverses tasques i veurem com
sexecuten dividint el temps dús de la cpu.



## Exercici Pràctic 1


1. Descebre la sortida pel port sèrie


 this is ESP32 task
 this is another task


La sortida pel port sèrie intercala aquests dos missatges que es repeteixen contínuament, ja que les dues funcions s'executen en paral·lel.


2. Explicar el funcionament
En aquesta pràctica, podem veure el funcionament de dues tasques executant-se alhora a les dues CPUs (Central Processing Unit) de l'ESP32.

La funció **void setup()**


      void setup() {

      Serial.begin(112500);
      /* we create a new task here */
      xTaskCreate( anotherTask,"another Task", 10000,NULL,1,NULL); 
      }


Primer configurem la comunicació serial per enviar i rebre dades a través del port sèrie a una velocitat de 112.500 bauds.

Fem servir la funció **xTaskCreate()** per crear una nova tasca anomenada 'anotherTask'. Això ens permet executar codi en paral·lel amb la tasca principal. A aquesta funció us assignem una mida de 10000 bytes per emmagatzemar les seves variables i dades.

Cada tasca que creem pot tenir una prioritat assingnada. Les prioritats van de 0 a 24, com més baix sigui el nombre, més prioritat li donem. En aquest cas, assignem una prioritat d'1 a la tasca **anotherTask**. Si hi ha múltiples tasques executant-se alhora, la tasca amb la prioritat més alta serà la primera a executar-se. Si hi hagués dues tasques amb el mateix grau de prioritat, el temps de CPU es repartiria.


La funció **loop()** és el bucle principal del programa. Aquest és el que treu pel port sèrie el missatge:


 this is ESP32 task


Tot seguit espera 1 segon abans de repetir el procés (el temps d'espera el podem modificar amb el delay()).

La funció **anotherTask()** : declara una tasca


    void anotherTask( void * parameter )
    {
    /* loop forever */
    for(;;)
    {
    Serial.println("this is another Task");
    delay(1000);
    }
    /* delete a task when finish,
    this will never happen because this is infinity loop */
    vTaskDelete( NULL );
    }


és un bucle infinit que s'executa en paral·lel amb la funció **loop()**. Aquesta ens imprimeix pel port sèrie:


 this is another task


i espera un temps (modificable al 'delay()') de x segons abans de repetir el procés.
La funció **vTaskDelete(NULL)** en aquest context és inabastable i no té cap efecte pràctic ja que està dins un bucle infinit.
De tota manera, la funció és utilitzada en sistemes basats en FreeRTOS (un sistema operatiu en temps real) per eliminar una tasca quan ja no és necessària o quan ha completat la tasca. Quan es passa 'NULL', indica que voleu eliminar la tasca actual que esteu trucant a 'vTaskDelete()'.



## CONCLUSIÓ

En aquesta pràctica hem pogut veure com el mateix microcontrolador pot córrer múltiples tasques simultàniament, amb operacions independents en paral·lel.