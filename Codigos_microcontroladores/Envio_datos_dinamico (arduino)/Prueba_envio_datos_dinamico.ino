

#include "DHT.h"

#define DHTTYPE DHT11

const int sensorLDR = A1;
const int sensorHum = A2;
const int DHTPin = 4;

DHT dht(DHTPin, DHTTYPE);


//definir medias iniciales
float med_temp = 20;
float med_light = 50;
float med_hum = 50;
float med_hum_suelo = 50;
float media_total = (med_temp + med_light + med_hum + med_hum_suelo) / 4;


//definir alpha
float alpha = 0.1;

//definir delay default-minimo-maximo
float default_time = 30000;
float lower_time = 5000;     //Tiempo minimo para el intervalo
float upper_time = 150000;   //Tiempo máximo para el intervalo
float delay_time = default_time;



void setup()
{
  Serial.begin(9600);

  dht.begin();

}

void loop()
{


  int valueLDR = 0;
  float light = 0;
  float lightAcum = 0;


  //Obtener 10 datos de temperatura, para reducir el ruido

  for (byte i = 0; i < 10; i = i + 1) {
    valueLDR = analogRead(sensorLDR);
    light = map(valueLDR, 0, 1023, 0, 100);
    lightAcum = light + lightAcum;
  }

  light = lightAcum / 10.0;

  float temperatura = ((int) (dht.readTemperature() * 10)) / 10.0;
  float humedad = ((int) (dht.readHumidity() * 10)) / 10.0;
  int valueHumSuelo = analogRead(sensorHum);

  float humSuelo = map(valueHumSuelo, 260, 455, 100, 0);


  //Aqui se pueden enviar los datos al ESP


  // Ponderar suma de valores obtenidos (media actual)
  float media_actual = (temperatura + humedad + light + humSuelo) / 4;

  // Calcular la diferencia porcentual entre el promedio y la ultima medición
  float diff = calc_dif_porcentual(media_total, media_actual);


  

    //EJEMPLO ALGORITMO ADAPTATIVO, se ajusta segun la diferencia porcentual (delay_time)

    if(diff > 100 && delay_time>lower_time){
        delay_time = delay_time * 0.9;; //Reducir tiempo
    }
    else if(diff <= 100 && diff>10 && delay_time>lower_time){
        delay_time = delay_time - (10*diff); //Reducir tiempo
    }
    else if(diff <= 10 &&  delay_time < upper_time ){
        delay_time = delay_time + (10*diff); // Aumentar tiempo
    }
    else{
        // Mantiene la velocidad de actualización tal como está
        delay_time = delay_time;
}

  
  Serial.println("Temperatura: " + String(temperatura) + "°C");
  Serial.println("Luz: " + String(light));
  Serial.println("Humedad: " + String(humedad));
  Serial.println("HumedadSuelo: " + String(humSuelo));
 
  Serial.println("Diferencia porcentual: " + String(diff) + " Tiempo delay: " + String(delay_time) + " Promedio actual: " + String(media_total) +  " nuevo_promedio: " + String(media_actual));



  //Calcular el nuevo promedio (promedio_dinamico)
  med_temp =  promedio_dinamico(alpha, med_temp, temperatura);
  med_light = promedio_dinamico(alpha, med_light, light);
  med_hum = promedio_dinamico(alpha, med_hum, humedad);
  med_hum_suelo = promedio_dinamico(alpha, med_hum_suelo, humSuelo);
  media_total = (med_temp + med_light + med_hum + med_hum_suelo) / 4;


  delay(delay_time);  
}


// Función para calcular nueva media
float promedio_dinamico(float &alpha, float &val_medio, float &val_nuevo) {
  float nuevo_medio = (1 - alpha) * val_medio + alpha * val_nuevo;
  return nuevo_medio;
}


//Funcion para calcular diferencia porcentual
float calc_dif_porcentual(float &val_1, float &val_2) {
  float dif_porcentual = (abs(val_1 - val_2) / val_1) * 100;
  return dif_porcentual;
}
