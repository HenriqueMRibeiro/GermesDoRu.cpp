/*
  >SensorTemperatura.hpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Classe para coletar a temperatura via sensor DS18B20.
  Componentes de Hardware usados no Protótipo:
    - Sensor de Temperatura DS18B20
*/

#ifndef SENSORTEMPERATURA_HPP
#define SENSORTEMPERATURA_HPP

// Inclusões
#include <Arduino.h>            // Biblioteca necessária do Arduino IDE
#include <OneWire.h>            // Biblioteca para comunicação OneWire
#include <DallasTemperature.h>  // Biblioteca para controle do sensor DS18B20
#include "Sensor.hpp"           // Classe base Sensor

// Classe SensorTemperatura
class SensorTemperatura : public Sensor {
private:
  OneWire oneWire;                  // Instância de comunicação OneWire
  DallasTemperature sensorDS18B20;  // Instância do sensor de temperatura

public:
  // Construtor
  SensorTemperatura(int pinoEntrada);

  // Sobrescreve a função para ler a temperatura
  float lerValor() override;
};

#endif