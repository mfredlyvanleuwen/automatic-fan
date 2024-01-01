#include <DHT.h>
#include <Ultrasonic.h>
#include <ESP8266WiFi.h>

#define DHTPIN D11    // Pin yang digunakan untuk menghubungkan DHT22
#define DHTTYPE DHT22   // Tipe sensor DHT22
#define echoPin D3
#define trigPin D7
#define relayPin D4 


DHT dht(DHTPIN, DHTTYPE);

Ultrasonic ultrasonic(D7, D3);   // Pin trigger dan echo untuk HCSR04

void setup() {
  // Inisialisasi serial untuk debugging
  Serial.begin(9600);
  dht.begin();

  // Inisialisasi pin relay

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Baca nilai suhu dan kelembaban dari DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Baca nilai jarak dari HCSR04
  float distance = ultrasonic.read();

  //jarak
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Cek apakah jarak kurang dari 10 cm, jika ya maka aktifkan relay
  
//  if (distance < 100) {
//    digitalWrite(relayPin, LOW);
//  } else {
//   digitalWrite(relayPin, HIGH);
//  }

  if (t > 28.50){
    if(distance<=100){
    digitalWrite(relayPin, LOW); // relay aktif
  } else { // selain itu maka
  digitalWrite(relayPin, HIGH); // relay mati
  }
  }else{
    digitalWrite(relayPin, HIGH);
  }
  
  // Cetak nilai suhu, kelembaban, dan jarak ke serial monitor
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print(" derajat Celcius, Kelembaban: ");
  Serial.print(h);
  Serial.print(" Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Tunggu selama 1 detik sebelum membaca nilai sensor kembali
  delay(2000);
}
