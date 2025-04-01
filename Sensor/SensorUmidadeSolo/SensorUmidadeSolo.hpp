/*
  >SensorUmidadeSolo.hpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Classe para coletar a umidade do solo via sensor FC-28.
  Componentes de Hardware usados no Protótipo:
    - Sensor de Umidade do Solo (FC-28)
*/

#ifndef SENSORUMIDADESOLO_HPP
#define SENSORUMIDADESOLO_HPP

// Inclusões
#include <Arduino.h>   // Biblioteca necessária do Arduino IDE
#include "Sensor.hpp"  // Classe base Sensor

// Classe SensorUmidadeSolo
class SensorUmidadeSolo : public Sensor {
public:
  // Construtor
  SensorUmidadeSolo(int pinoEntrada);

  // Sobrescreve a função para ler a umidade do solo
  float lerValor() override;
};

#endif
