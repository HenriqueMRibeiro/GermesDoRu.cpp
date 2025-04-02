/*
  >AtuadorPWM.cpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Controlar potência de um atuador (pastilha peltier)
  Componentes de Hardware usados no Protótipo:
    Pastilha Peltier 12V
*/

// Inclusões
#include "AtuadorPWM.hpp"  // Incluir o cabeçalho

// Construtor
AtuadorPWM::AtuadorPWM(int pinoSaida, int frequencia, int resolucao) {
  this->pinoSaida = pinoSaida;
  this->frequencia = frequencia;
  this->resolucao = resolucao;

  pinMode(this->pinoSaida, OUTPUT);                                // Configura o pino como saída
  ledcAttach(this->pinoSaida, this->frequencia, this->resolucao);  // Atribuindo um PWM em um pino com uma dada frequencia e uma dada resolução
  this->dutyCycle = 0;                                             // Iniciando a potência como 0% de duty cycle.
}

// Definir potencia
void AtuadorPWM::definirPotencia(int potenciaPercentual) {
  potenciaPercentual = constrain(potenciaPercentual, 0, 100);                        // Limitando intervalos
  this->dutyCycle = map(potenciaPercentual, 0, 100, 0, (1 << this->resolucao) - 1);  // Mapeando de 0 a 100% em termos de saída analógica
  ledcWrite(this->pinoSaida, this->dutyCycle);                                       // Aplica o duty cycle (potência)
}
