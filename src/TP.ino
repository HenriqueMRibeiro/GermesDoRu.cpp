/*
  >TP.ino
  Técnicas de Programação 2024.2
  Autores (GermesDoRu.cpp):
    José Henrique Mota Ribeiro
    Natanael da Silva Medeiros
    João Vitor Dias Paulo
    Isaque Felipe Carneiro dos Santos
    Bruno Dourado Miranda Botelho
  Data: 01/04/2025
  Descrição:
    Este código implementa um sistema de controle inteligente para automação de uma residência ou cidade, 
    utilizando um microcontrolador ESP32. O sistema é capaz de monitorar a temperatura e a umidade do solo, 
    controlando dispositivos como uma bomba d'água, uma pastilha Peltier (para controle de temperatura), 
    e um servo motor (para abrir e fechar uma janela). A comunicação entre o ESP32 e um dispositivo móvel é feita via Bluetooth, 
    permitindo o controle remoto dos dispositivos.
  Funcionalidade:
    - O sistema lê continuamente a temperatura de um sensor DS18B20 e a umidade do solo através de um sensor FC-28.
    - Com base nesses dados, o sistema aciona a bomba d'água quando a umidade do solo estiver abaixo de um valor predefinido (50%).
    - A pastilha Peltier é controlada para ajustar a temperatura para um valor desejado (definido via Bluetooth), com a potência ajustada conforme a diferença entre a temperatura real e a desejada.
    - Um servo motor controla a abertura ou fechamento de uma janela, conforme comandos recebidos via Bluetooth.
    - O sistema utiliza Bluetooth para comunicação e controle remoto dos dispositivos, com reconexão automática caso a conexão seja perdida.
  Elementos de Hardware:
    - ESP32: Microcontrolador utilizado para o controle e comunicação Bluetooth.
    - Sensor DS18B20: Sensor de temperatura utilizado para medir a temperatura ambiente.
    - Sensor FC-28: Sensor de umidade do solo, utilizado para medir a umidade em terrenos ou vasos.
    - Atuador PWM (Peltier): Pastilha Peltier controlada via PWM para ajustar a temperatura ambiente.
    - Atuador Digital (Bomba): Bomba d'água controlada via pino digital, acionada quando a umidade do solo estiver baixa.
    - Servo Motor: Servo motor utilizado para controlar a abertura e fechamento de uma janela inteligente.
    - Circuito Controlador:
      2xIRL520N
      2xResistor 10k
      1xResistor 4k7
      Dissipador de calor
  Elementos de Software:
    - Arduino IDE: Ambiente de desenvolvimento utilizado para programar o ESP32.
    - Arduino Bluetooth Controller: ambiente de comunicação terminal e switch entre ESP32-Usuário. App disponível na PlayStore.
  Repositório: https://github.com/HenriqueMRibeiro/GermesDoRu.cpp
*/

// Inclusões
#include <Arduino.h>              // Biblioteca Fundamental do Arduino IDE
#include <ESP32Servo.h>           // Biblioteca de controle de Servo
#include "ConexaoBT.hpp"          // Classe de conexão bluetooth
#include "SensorTemperatura.hpp"  // Classe do sensor DS18B20
#include "SensorUmidadeSolo.hpp"  // Classe do sensor FC-28
#include "AtuadorPWM.hpp"         // Classe do atuador PWM - Peltier
#include "AtuadorDigital.hpp"     // Classe do atuador digital convencional - Bomba

// Definições
#define SENSOR_TEMP_PIN 4          // Pino do sensor DS18B20
#define SENSOR_UMIDADE_PIN 34      // Pino analógico do sensor FC-28
#define ATUADOR_BOMBA_PIN 17       // Pino de controle do gate do IRL520N relacionado a bomba dágua
#define ATUADOR_PELTIER_PIN 5      // Pino de controle do gate do IRL520N relacionado a pastilha peltier
#define SERVO_JANELA_PIN 16        // Pino de controle do servo da janela inteligente
#define ATUADOR_PELTIER_FREQ 1000  // Frequência do PWM de chaveamento do IRL520N relacionado a pastilha peltier

// Objetos
ConexaoBT conexaoBT("GermesDoRu.cpp");
SensorTemperatura sensorTemperatura(SENSOR_TEMP_PIN);
SensorUmidadeSolo sensorUmidadeSolo(SENSOR_UMIDADE_PIN);
AtuadorPWM pastilhaPeltier(ATUADOR_PELTIER_PIN, ATUADOR_PELTIER_FREQ);
AtuadorDigital bombaDagua(ATUADOR_BOMBA_PIN);
Servo servoJanela;

// Variáveis de controle
int temperaturaDesejada = 25;   // Temperatura inicial (25°C)
int umidadeSoloLimiar = 50;     // Umidade relativa mínima para controle (50%)
float ultimaTemperatura = 0;    // Variável para suavização de temperatura
unsigned long lastMillis = 0;   // Variável para controle de temporização com millis()
unsigned long intervalo = 100;  // Intervalo de 100ms para a verificação do loop
unsigned long tempoUltimaConexao = 0;
unsigned long intervaloConexao = 5000;  // Intervalo de 5 segundos para reconectar ao Bluetooth

void setup() {
  Serial.begin(115200);                  // Iniciar a comunicação Serial a 115k200 de baudRate
  servoJanela.attach(SERVO_JANELA_PIN);  // Atribuindo o servo ao seu pino
  servoJanela.write(0);                  // Iniciando o sistema em 0°
  delay(100);                            // Delay de segurança

  // Iniciando a conexão bluetooth
  if (!conexaoBT.iniciarConexao()) {
    Serial.println("Erro ao iniciar a comunicação Bluetooth.");
  } else {
    Serial.println("Conexão Bluetooth iniciada com sucesso.");
  }
  delay(1000);  // Delay de segurança
}

void loop() {
  // Verificação da conexão Bluetooth
  if (millis() - tempoUltimaConexao > intervaloConexao) {
    tempoUltimaConexao = millis();
    if (!conexaoBT.verificarConexao()) {
      Serial.println("Desconectado. Tentando reconectar...");
      conexaoBT.iniciarConexao();
    }
  }

  // Processamento do comando recebido via Bluetooth
  String comando = conexaoBT.receberDados();
  if (comando != "") {
    processarComando(comando);  // Chama uma função para processar os comandos
  }

  // Leitura da umidade do solo
  float umidadeSolo = sensorUmidadeSolo.lerValor();  // Lê a umidade do solo
  // Se a umidade do solo for inferior a 50%, aciona a bomba d'água
  if (umidadeSolo < 50 && umidadeSolo >= 0) {
    bombaDagua.ligar();  // Liga a bomba
    Serial.println("Bomba acionada devido à umidade baixa.");
    conexaoBT.enviarDados("Bomba acionada devido à umidade baixa.");
  }

  // Lógica de controle da pastilha Peltier
  float temperaturaAtual = sensorTemperatura.lerValor();           // Lê a temperatura atual do sensor
  float erroTemperatura = temperaturaDesejada - temperaturaAtual;  // Diferença entre a temperatura desejada e a atual

  // Suavização da temperatura para evitar flutuações rápidas
  float mediaTemperatura = (temperaturaAtual * 0.1) + (ultimaTemperatura * 0.9);
  ultimaTemperatura = mediaTemperatura;

  // Mapeia a diferença de 0-10°C para 0-100% de potência
  int potencia = map(abs(erroTemperatura), 0, 10, 0, 100);  // Mapeia a diferença de 0-10°C para 0-100%

  // Se a diferença for muito pequena (menos de 0,5°C), desliga a pastilha
  if (abs(erroTemperatura) < 0.5) {
    potencia = 0;  // Desliga a pastilha Peltier quando a temperatura está próxima da desejada
  }

  pastilhaPeltier.definirPotencia(potencia);  // Define a potência da pastilha Peltier
  Serial.print("Temperatura Atual: ");
  conexaoBT.enviarDados("Temperatura Atual: ");
  Serial.print(temperaturaAtual);
  conexaoBT.enviarDados(String(temperaturaAtual));
  Serial.print("°C - Potência Peltier: ");
  conexaoBT.enviarDados("°C - Potência Peltier: ");
  Serial.print(potencia);
  conexaoBT.enviarDados(String(potencia));
  Serial.println("%");

  delay(50);  // Pequeno delay para garantir tempo de resposta
}

void processarComando(String comando) {
  if (comando == "ON1") {
    bombaDagua.ligar();  // Ativa a bomba
    Serial.println("Bomba ligada!");
    conexaoBT.enviarDados("Bomba ligada!");
  } else if (comando == "OFF1") {
    bombaDagua.desligar();  // Desativa a bomba
    Serial.println("Bomba desligada!");
    conexaoBT.enviarDados("Bomba desligada!");
  } else if (comando == "ON2") {
    servoJanela.write(90);  // Abre a janela (90 graus)
    conexaoBT.enviarDados("Janela aberta.");
    Serial.println("Janela aberta.");
  } else if (comando == "OFF2") {
    servoJanela.write(0);  // Fecha a janela (0 graus)
    conexaoBT.enviarDados("Janela fechada.");
    Serial.println("Janela fechada.");
  } else if (comando.startsWith("TEMP")) {
    temperaturaDesejada = comando.substring(4).toInt();  // Extrai temperatura desejada
    conexaoBT.enviarDados("Temperatura configurada.");
    Serial.print("Temperatura desejada: ");
    Serial.println(temperaturaDesejada);
  }
}
