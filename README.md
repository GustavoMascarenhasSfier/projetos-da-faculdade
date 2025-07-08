# 🚗 Sistema de Estacionamento Automatizado com Arduino

Este projeto consiste em um sistema de estacionamento inteligente desenvolvido com **Arduino**, que controla o acesso de veículos por meio de senha, sensores infravermelhos, servo motor e exibição em LCD. O sistema simula a entrada e saída de veículos, gerenciando o número de vagas disponíveis.

---

## 📦 Funcionalidades

- 🔐 **Acesso com senha** via teclado matricial (Keypad)
- 🚧 **Controle de cancela** com servo motor
- 📊 **Monitoramento de vagas disponíveis** em tempo real
- 👁️‍🗨️ **Detecção de entrada e saída** com sensores infravermelhos
- 📺 **Exibição de mensagens** em display LCD 16x2
- 📍 **Feedback visual e interativo** com mensagens durante todas as etapas

---

## 🧰 Componentes Utilizados

| Componente         | Quantidade |
|--------------------|------------|
| Arduino UNO        | 1          |
| Display LCD 16x2   | 1          |
| Teclado Matricial 4x4 | 1        |
| Servo Motor        | 1          |
| Sensor Infravermelho (IR) | 2      |
| Jumpers            | Diversos   |
| Protoboard         | 1          |
| Resistores (se necessário) | -    |

---

## ⚙️ Especificações do Sistema

- **Senha Padrão**: `1234`
- **Total de Vagas**: 4
- **Controle de acesso**: Entrada liberada apenas após senha correta
- **Atualização de vagas**:
  - Entrada reduz uma vaga
  - Saída aumenta uma vaga
- **Mensagens informativas** no LCD para cada ação

---

## 📂 Estrutura do Código

Arquivo principal: `estacionamento.cpp`

### Principais funções:

- `setup()` – Inicializa o LCD, sensores, servo motor e cancela
- `loop()` – Controla o fluxo principal entre entrada de senha e monitoramento de vagas
- `Open()` – Solicita e valida a senha via teclado
- `ServoOpen()` e `ServoClose()` – Abrem e fecham a cancela com o servo motor
- `checkParking()` – Lógica de entrada/saída de carros usando sensores IR
- `loading()` – Animação de carregamento no LCD
- `clearData()` – Limpa os dados inseridos no teclado

---

## 🔌 Ligações dos Componentes

- **Servo Motor**: Pino 2
- **Sensor IR Entrada (IR1)**: Pino 11
- **Sensor IR Saída (IR2)**: Pino 12
- **LCD (via portas analógicas)**: A0 a A5
- **Teclado Matricial**:
  - Linhas: Pinos 3 a 6
  - Colunas: Pinos 7 a 10

---

## 🚦 Fluxo de Funcionamento

1. **Inicialização**
   - LCD exibe mensagem de carregamento
2. **Autenticação**
   - Usuário insere senha no teclado
   - Senha correta → cancela abre
   - Senha incorreta → acesso negado
3. **Entrada**
   - Sensor IR detecta carro na entrada
   - Cancela abre, carro entra, vaga reduz
4. **Saída**
   - Sensor IR detecta carro na saída
   - Cancela abre, carro sai, vaga aumenta
5. **Atualização contínua**
   - LCD mostra vagas disponíveis

---

## 🧪 Sugestões de Expansão

- Integração com módulo RFID
- Registro de horários de entrada e saída com módulo RTC
- Envio de dados para servidor web ou app via Wi-Fi (ESP8266)
- Criação de interface gráfica em display touchscreen

---


## 📝 Licença

Este projeto é de uso educacional e pode ser adaptado livremente. Atribuição é apreciada. 😉
