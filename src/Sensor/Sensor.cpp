/*
  >Sensor.cpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Implementação do construtor da classe Sensor base.
*/

// Inclusões
#include "Sensor.hpp"  // Incluir cabeçalho da classe

// Implementação do Construtor
Sensor::Sensor(int pinoEntrada, TipoPino tipoPino) {
  this->pinoEntrada = pinoEntrada;
  this->tipoPino = tipoPino;
  pinMode(this->pinoEntrada, INPUT);  // Configura o pino como entrada
}
