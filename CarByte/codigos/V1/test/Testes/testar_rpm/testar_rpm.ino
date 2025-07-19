#include <SPI.h>
#include <mcp_can.h>

// Pino CS do MCP2515
const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);

// Variáveis de mensagem
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

void setup() {
  // Inicializa o Serial para visualização
  Serial.begin(115200);
  
  // Inicializa o barramento CAN
  while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ)) {
    Serial.println("Tentando iniciar o CAN...");
    delay(1000);
  }
  Serial.println("CAN inicializado com sucesso!");

  // Configura o CAN para modo normal
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  // Verifica se há dados disponíveis
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    // Lê a mensagem do CAN
    CAN.readMsgBuf(&rxId, &len, rxBuf);

    // Verifica se o ID da mensagem é 0x280 (é o ID que você está monitorando)
    if (rxId == 0x280 && len == 8) {
      decode280(rxBuf);
    }
  }
}

void decode280(unsigned char *data) {
  // Decodifica o byte 0 para saber o estado dos pedais
  byte pedalByte = data[0];
  bool embreagem = (pedalByte == 1);  // 1: embreagem pressionada
  bool acelerador = (pedalByte == 8); // 8: acelerador pressionado

  // Calcula o RPM (usando o byte 3)
  int rpmRaw = data[3];  // Agora o RPM está no byte 3
  float rpm = rpmRaw * 50.0; // Multiplica o valor do byte 3 por 50 para ajustar a escala (ajuste conforme necessário)

  // Posição do acelerador (byte 5) de 0 a 255
  byte posAcelerador = data[5]; 

  // Exibe os dados no Serial Monitor
  Serial.println("---------------");
  Serial.print("Pedais: ");
  Serial.print("Embreagem: "); Serial.print(embreagem ? "PISADA" : "solta");
  Serial.print(" | Acelerador: "); Serial.println(acelerador ? "PISADO" : "solto");

  Serial.print("RPM estimado: ");
  Serial.println(rpm);

  Serial.print("Posição do acelerador: ");
  Serial.print(map(posAcelerador, 0, 255, 0, 100)); 
  Serial.println(" %");

  // Exibe os bytes da mensagem
  Serial.print("Bytes: ");
  for (int i = 0; i < 8; i++) {
    if (data[i] < 16) Serial.print("0");
    Serial.print(data[i], HEX); 
    Serial.print(" ");
  }
  Serial.println();
}
