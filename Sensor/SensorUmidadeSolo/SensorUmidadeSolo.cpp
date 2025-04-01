/*
  >SensorUmidadeSolo.hpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Classe para coletar a umidade do solo via sensor FC-28.
  Componentes de Hardware usados no Protótipo:
    - Sensor de Umidade do Solo (FC-28)
*/

// Inclusões
#include "SensorUmidadeSolo.hpp"  // Inclui o cabeçalho da classe

// Construtor (passa o pino e define como analógico)
SensorUmidadeSolo::SensorUmidadeSolo(int pinoEntrada)
  : Sensor(pinoEntrada, TipoPino::ANALOGICO) {
}

// Implementação da leitura do sensor
float SensorUmidadeSolo::lerValor() {
  int leituraBruta = analogRead(this->pinoEntrada);  // Lê o valor do sensor (0 a 4095) ESP32 tem maior resolução do ADC

  // Mapeando para inversão: valor baixo corresponde a umidade baixa (solo não úmido)
  float umidade = map(leituraBruta, 4095, 0, 0, 100);

  // Retorna o valor da umidade
  return umidade;
}
