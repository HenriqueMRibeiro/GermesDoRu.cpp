/*
  >Sensor.hpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Classe base para criação de subclasses de sensores.
*/

#ifndef SENSOR_HPP
#define SENSOR_HPP

// Inclusões
#include <Arduino.h>  // Biblioteca necessária do Arduino IDE

// Enum para definir o tipo do pino
enum class TipoPino {
  DIGITAL,
  ANALOGICO
};

// Definição da classe Sensor (Classe Base)
class Sensor {
protected:
  int pinoEntrada;    // Pino do Sensor
  TipoPino tipoPino;  // Tipo do pino

public:
  // Construtor
  Sensor(int pinoEntrada, TipoPino tipoPino);

  // Método virtual puro (cada sensor implementará sua própria leitura)
  virtual float lerValor() = 0;
};

#endif
