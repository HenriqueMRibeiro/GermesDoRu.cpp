/*
  >AtuadorDigital.cpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Controlar potência de um atuador (motor, pastilha peltier)
  Componentes de Hardware usados no Protótipo:
    Motobomba 12V
*/

// Inclusões
#include "AtuadorDigital.hpp"  // Cabeçalho da classe

// Construtor
AtuadorDigital::AtuadorDigital(int pinoSaida) {
  pinMode(this->pinoSaida, OUTPUT);
  this->pinoSaida = pinoSaida;
  this->status = false;
}

void AtuadorDigital::ligar() {
  this->status = true;
  digitalWrite(this->pinoSaida, HIGH);
}

void AtuadorDigital::desligar() {
  this->status = false;
  digitalWrite(this->pinoSaida, LOW);
}

bool AtuadorDigital::verificarStatus() {
  return this->status;
}