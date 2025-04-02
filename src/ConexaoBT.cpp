/*
  >ConexaoBT.cpp
  Autores: GermesDoRu.cpp
  Data: 28/03/2025
  Descrição: Gerar uma conexão Bluetooth, bem como receber e enviar dados.
  Componentes de Hardware usados no Protótipo:
    Módulo Bluetooth integrado da ESP32
    Smartphone com Bluetooth
  Software de conexão usado no Protótipo:
    Arduino Bluetooth Controller, Giristudio, PlayStore
*/

// Inclusões
#include "ConexaoBT.hpp"  // Incluir o cabeçalho da classe

// Implementando o construtor
ConexaoBT::ConexaoBT(const String& nomeDispositivo) {
  this->nomeDispositivo = nomeDispositivo;  // Atribuindo o nome
  this->conectado = false;                  // Inicializar como desconectado
}

// Implementando a conexão Bluetooth
bool ConexaoBT::iniciarConexao() {
  this->conectado = this->SerialBT.begin(this->nomeDispositivo);  // Inicia a comunicação Bluetooth e salva o status
  return this->conectado;                                         // Retorna a flag indicando sucesso ou falha
}

// Verificando a conexão de um cliente Bluetooth
bool ConexaoBT::verificarConexao() {
  return this->SerialBT.hasClient();  // Retorna true se houver um cliente Bluetooth conectado
}

// Enviar dados via Bluetooth
void ConexaoBT::enviarDados(const String& dadosEnviar) {
  if (this->conectado && this->verificarConexao()) {  // Verifica se está conectado e se há cliente Bluetooth conectado
    this->SerialBT.println(dadosEnviar);              // Envia os dados
  }
}

// Receber dados via Bluetooth
String ConexaoBT::receberDados() {
  if (!this->conectado) {
    return "";  // Retorna string vazia se o Bluetooth não estiver conectado
  }
  if (this->SerialBT.available()) {      // Verifica se há dados disponíveis para leitura
    return this->SerialBT.readString();  // Lê e retorna os dados recebidos
  }
  return "";  // Retorna string vazia se não houver dados
}