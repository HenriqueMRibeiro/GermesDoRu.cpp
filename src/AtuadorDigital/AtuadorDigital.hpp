/*
  >AtuadorDigital.hpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Controlar potência de um atuador (motor, pastilha peltier)
  Componentes de Hardware usados no Protótipo:
    Motobomba 12V
*/

#ifndef ATUADORDIGITAL_HPP
#define ATUADORDIGITAL_HPP

// Inclusões
#include <Arduino.h>  // Biblioteca necessária do Arduino IDE

// Classe
class AtuadorDigital {
private:
  int pinoSaida;  // Pino de saída digital convencional
  bool status;    // Ligado ou desligado

public:
  // Construtor
  AtuadorDigital(int pinoSaida);

  // Definir potência
  void ligar();
  void desligar();
  bool verificarStatus();
};

#endif