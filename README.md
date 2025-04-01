# GermesDoRU.cpp  
**Cidades e Casas do Futuro – Controle Inteligente de Temperatura Urbana e Residencial**

## Autores

- José Henrique M Ribeiro  
- Natanael da S Medeiros  
- João Vitor D Paulo  
- Isaque Felipe C dos Santos  
- Bruno Dourado M Botelho

## Sobre o Projeto

Este projeto foi desenvolvido para a disciplina **Técnicas de Programação - 2024.2** da **Universidade Federal de Campina Grande (UFCG)**, no curso de Engenharia Elétrica. A solução proposta integra duas plataformas principais:

- **SIRUI (Sistema Integrado de Resfriamento Urbano Inteligente):** Plataforma responsável por monitorar e intervir em áreas urbanas, mitigando o fenômeno das ilhas de calor por meio de sensores IoT e atuadores (irrigação, nebulização, aplicação de materiais reflexivos, entre outros).
- **RISRU (Rede Integrada de Sensores Residenciais e Urbanos):** Rede de sensores que coleta dados ambientais em tempo real, permitindo a climatização inteligente de ambientes residenciais.

O projeto demonstra, através de um protótipo em escala reduzida, a viabilidade da integração de tecnologias IoT, automação e soluções sustentáveis para melhorar o conforto térmico e a eficiência energética tanto em ambientes urbanos quanto residenciais.

## Motivação

Com o crescimento acelerado das cidades e o consequente aumento das temperaturas urbanas, a implementação de soluções inteligentes para o controle térmico tornou-se essencial para melhorar a qualidade de vida, reduzir o consumo energético e promover a sustentabilidade. O GermesDoRU.cpp propõe uma abordagem inovadora para enfrentar esses desafios, integrando tecnologias de automação e IoT em um sistema coeso e escalável.

## Funcionalidades

- **Monitoramento em tempo real:** Coleta de dados ambientais (temperatura, umidade, radiação solar, etc.) por meio de sensores distribuídos.
- **Controle automatizado:** Acionamento de sistemas de resfriamento (irrigação automatizada, nebulização, pastilha Peltier) e dispositivos como janelas inteligentes.
- **Interface de comunicação:** Conexão via Bluetooth que permite o monitoramento e o controle remoto do sistema.
- **Integração urbana e residencial:** Solução adaptável tanto para intervenções em áreas urbanas críticas quanto para ambientes residenciais.

## Tecnologias Utilizadas

- **Hardware:** Arduino, ESP32, sensores IoT (DS18B20, FC-28, entre outros), atuadores (servo motor, pastilha Peltier, bomba d’água).
- **Software:** C/C++ para programação dos microcontroladores, integração com plataformas open source para monitoramento e análise.
- **Comunicação:** Protocolos de comunicação sem fio (Wi-Fi, Bluetooth).
