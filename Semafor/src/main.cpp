#include <Arduino.h>

void ledON (void * pvParameters);
void ledOFF(void * pvParameters);
int LED =2; 

SemaphoreHandle_t semafor;

void setup(){

    Serial.begin(112500);
    pinMode(LED, OUTPUT);
    semafor= xSemaphoreCreateMutex();
    
    xTaskCreate(ledON,"LED ON",10000,NULL,1,NULL);
    
    xTaskCreate(ledOFF,"LED OFF",10000,NULL,1,NULL);

}

void loop(){}

void ledON (void * pvParameters){
    for(;;){
        xSemaphoreTake(semafor, portMAX_DELAY);
        Serial.println("Ejecutando tarea: LED ON");
        digitalWrite(LED, HIGH);
        delay(3000);
        xSemaphoreGive(semafor);
    }
}

void ledOFF (void * pvParameters){
    for(;;){
        xSemaphoreTake(semafor, portMAX_DELAY);
        Serial.println("Ejecutando tarea: LED OFF");
        digitalWrite(LED, LOW);
        delay(1500);
        xSemaphoreGive(semafor);
    }
}
