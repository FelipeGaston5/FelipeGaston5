#include <SPI.h>
#include <mcp_can.h>

#define CAN_CS_PIN 10 // Pino CS do MCP2515 (ajuste se necessário)

MCP_CAN CAN(CAN_CS_PIN); // Criação do objeto MCP_CAN

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Inicializando MCP2515...");

  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 inicializado com sucesso!");
  } else {
    Serial.println("Erro ao inicializar o MCP2515. Verifique a conexão e o cristal.");
    while (1);
  }

  CAN.setMode(MCP_NORMAL); // Coloca o MCP2515 em modo normal
  Serial.println("Modo NORMAL definido. Pronto para receber mensagens CAN.");
}

void loop() {
  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    long unsigned int canId;
    unsigned char len = 0;
    unsigned char buf[8];

    CAN.readMsgBuf(&canId, &len, buf); // Lê a mensagem

    Serial.print("ID: 0x");
    Serial.print(canId, HEX);
    Serial.print(" | Len: ");
    Serial.print(len);
    Serial.print(" | Data: ");

    for (int i = 0; i < len; i++) {
      if (buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }

    Serial.println();
  }
}
