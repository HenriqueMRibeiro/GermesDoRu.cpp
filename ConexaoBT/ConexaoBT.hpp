/*
  >ConexaoBT.hpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Gerar uma conexão Bluetooth, bem como receber e enviar dados.
  Componentes de Hardware usados no Protótipo:
    Módulo Bluetooth integrado da ESP32
    Smartphone com Bluetooth
  Software de conexão usado no Protótipo:
    Arduino Bluetooth Controller, Giristudio, PlayStore
*/

#ifndef CONEXAOBT_HPP
#define CONEXAOBT_HPP

// Inclusões
#include <Arduino.h>          // Biblioteca necessária do Arduino IDE
#include <BluetoothSerial.h>  // Biblioteca de conexões Bluetooth

// Classe ConexaoBT
class ConexaoBT {
private:
  BluetoothSerial SerialBT;  // Criando serial de conexão Bluetooth
  String nomeDispositivo;    // Nome do dispositivo Bluetooth gerado pela ESP32
  bool conectado;            // Flag para verificar se o Bluetooth foi inicializado

public:
  // Construtor
  ConexaoBT(const String& nomeDispositivo = "ESP32_Bluetooth_Padrão");

  // Inicializar a conexão
  bool iniciarConexao();

  // Verificar se há algum dispositivo conectado
  bool verificarConexao();

  // Envia dados via Bluetooth
  void enviarDados(const String& dadosEnviar);

  // Recebe dados via Bluetooth
  String receberDados();
};

#endif
