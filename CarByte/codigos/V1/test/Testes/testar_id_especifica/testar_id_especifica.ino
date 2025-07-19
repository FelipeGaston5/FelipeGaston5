#include <mcp_can.h>
#include <SPI.h>


#define CAN_CS_PIN 10 // Pino CS do MCP2515

MCP_CAN CAN(CAN_CS_PIN); // Cria uma instância do MCP2515

// Variáveis globais
unsigned long targetID =  0x320; // ID que você quer filtrar (altere conforme necessário)

void setup() {
  Serial.begin(115200); // Inicia a comunicação serial

  // Inicializa o MCP2515
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 inicializado com sucesso!");
  } else {
    Serial.println("Erro ao inicializar o MCP2515!");
    while (1);
  }

  CAN.setMode(MCP_NORMAL); // Configura o modo de operação

  Serial.print("Monitorando mensagens CAN com ID: 0x");
  Serial.println(targetID, HEX);
}

void loop() {
  // Verifica se há mensagens CAN disponíveis
  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    long unsigned int canId; // ID da mensagem CAN
    unsigned char len = 0;   // Tamanho dos dados
    unsigned char buf[8];    // Buffer para os dados

    // Lê a mensagem CAN
    CAN.readMsgBuf(&canId, &len, buf);

    // Verifica se o ID da mensagem é o que você quer filtrar
    if (canId == targetID) {
      // Exibe o ID e os dados no monitor serial
      Serial.print("ID: 0x");
      Serial.print(canId, HEX);
      Serial.print(" | Dados: ");

      for (int i = 0; i < len; i++) {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
}