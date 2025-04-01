/*
  >SensorTemperatura.cpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Coletar a temperatura via sensor
  Componentes de Hardware usados no Protótipo:
    Sensor de Temperatura DS18B20
*/

// Inclusões
#include "SensorTemperatura.hpp"  // Incluir o cabeçalho da classe

// Implementando o construtor
SensorTemperatura::SensorTemperatura(int pinoEntrada)
  : Sensor(pinoEntrada, TipoPino::DIGITAL) {
  oneWire = OneWire(pinoEntrada);               // Inicializa a comunicação OneWire com o pino
  sensorDS18B20 = DallasTemperature(&oneWire);  // Associa o OneWire ao sensor DS18B20
  sensorDS18B20.begin();                        // Inicializa o sensor
  sensorDS18B20.setResolution(10);              // Alterando a precisão para 9 bits com menor tempo de resposta (9 a 12)
}

// Implementação da função para ler o valor de temperatura
float SensorTemperatura::lerValor() {
  sensorDS18B20.requestTemperatures();                   // Solicita a leitura da temperatura
  float temperatura = sensorDS18B20.getTempCByIndex(0);  // Obtém a temperatura em Celsius

  // Se a temperatura não for válida, retorna um valor de erro
  if (isnan(temperatura)) {
    return -999.0f;  // Retorna -999.0 em caso de falha
  }

  return temperatura;  // Retorna a temperatura com precisão de ponto flutuante
}
