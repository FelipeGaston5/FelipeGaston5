#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN iniciado");
  } else {
    Serial.println("Erro ao iniciar CAN");
    while (1);
  }
  CAN.setMode(MCP_NORMAL);

  // Enviar requisição UDS para ler DTCs ativos:
  byte dtcRequest[] = {0x03, 0x19, 0x00, 0x00, 0, 0, 0, 0};
  CAN.sendMsgBuf(0x7E0, 0, 8, dtcRequest);
  Serial.println("Solicitando DTCs ativos...");
}

void loop() {
  unsigned long rxId;
  byte len;
  byte buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    CAN.readMsgBuf(&rxId, &len, buf);

    // Filtrar somente ID 0x550
    if (rxId == 0x7EF && rxId == 0x7E8) {
      Serial.print("Resposta ID 0x7EF: ");
      for (int i = 0; i < len; i++) {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      // Se quiser interpretar a resposta do serviço 0x19 (DTCs), mantenha esse código:
      if (len >= 3 && buf[1] == 0x59 && buf[2] == 0x02) {
        Serial.println("DTCs encontrados:");

        int dtcCount = (len - 3) / 2;
        if (dtcCount == 0) {
          Serial.println("Nenhum DTC ativo.");
        }
        for (int i = 0; i < dtcCount; i++) {
          int dtcHigh = buf[3 + i * 2];
          int dtcLow = buf[4 + i * 2];
          char dtcCode[6] = {0};

          char firstChar;
          switch ((dtcHigh & 0xC0) >> 6) {
            case 0: firstChar = 'P'; break;
            case 1: firstChar = 'C'; break;
            case 2: firstChar = 'B'; break;
            case 3: firstChar = 'U'; break;
          }
          dtcCode[0] = firstChar;
          dtcCode[1] = '0' + ((dtcHigh & 0x30) >> 4);
          dtcCode[2] = '0' + (dtcHigh & 0x0F);
          dtcCode[3] = '0' + ((dtcLow & 0xF0) >> 4);
          dtcCode[4] = '0' + (dtcLow & 0x0F);

          Serial.print("DTC: ");
          Serial.println(dtcCode);
        }
      }
    }
  }
}
