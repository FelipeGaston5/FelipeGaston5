#include <mcp_can.h>
#include <SPI.h>

#define CAN_CS_PIN 10  // Pino CS do MCP2515
#define MAX_IDS 1000  // Número máximo de IDs únicos a serem armazenados

MCP_CAN CAN(CAN_CS_PIN); // Cria uma instância do MCP2515

// Armazena os IDs já vistos
unsigned long seenIDs[MAX_IDS];
int idCount = 0;

void setup() {
  Serial.begin(115200);
  
  // Inicializa o MCP2515
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 inicializado com sucesso!");
  } else {
    Serial.println("Erro ao inicializar o MCP2515!");
    while (1);
  }

  CAN.setMode(MCP_NORMAL); // Modo de operação normal
  memset(seenIDs, 0, sizeof(seenIDs)); // Zera o array de IDs
  Serial.println("IDs únicos detectados:");
}

// Verifica se um ID já foi armazenado
bool isIDSeen(unsigned long id) {
  for (int i = 0; i < idCount; i++) {
    if (seenIDs[i] == id) return true;
  }
  return false;
}

void loop() {
  if (CAN.checkReceive() == CAN_MSGAVAIL) { // Se houver mensagens CAN
    long unsigned int canId;
    unsigned char len = 0;
    unsigned char buf[8];
    
    CAN.readMsgBuf(&canId, &len, buf); // Lê a mensagem
    
    // Se o ID não foi visto antes e há espaço no array
    if (!isIDSeen(canId) && (idCount < MAX_IDS)) {
      seenIDs[idCount] = canId; // Armazena o ID
      idCount++;
      
      // Exibe o ID no monitor serial
      Serial.print("ID: 0x");
      Serial.println(canId, HEX);
    }
  }
}