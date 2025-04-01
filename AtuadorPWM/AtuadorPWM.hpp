/*
  >AtuadorPWM.hpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Controlar potência de um atuador (motor, pastilha peltier)
  Componentes de Hardware usados no Protótipo:
    Motobomba 12V
*/

#ifndef ATUADORPWM_HPP
#define ATUADORPWM_HPP

// Inclusões
#include <Arduino.h>  // Biblioteca necessária do Arduino IDE

// Classe
class AtuadorPWM {
private:
  int pinoSaida;   // Pino de saída para PWM
  int frequencia;  // Frequência do PWM
  int resolucao;   // Resolução do PWM (8 bits = 0-255, 10 bits = 0-1023, etc.)
  int dutyCycle;   // Potência (duty cycle) do PWM
  int canal;

public:
  // Construtor
  AtuadorPWM(int pinoSaida, int frequencia, int resolucao = 8);

  // Definir potência
  void definirPotencia(int potenciaPercentual);
};

#endif
