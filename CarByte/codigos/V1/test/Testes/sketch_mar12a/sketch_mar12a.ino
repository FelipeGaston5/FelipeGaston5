#include <SPI.h>
#include <mcp_can.h>

// Configurar os pinos
const int SPI_CS_PIN = 10;
MCP_CAN can(SPI_CS_PIN);

// Variáveis CAN
unsigned int RPM = 0;
byte cargaMotor = 0;
int velocidade = 0;
byte nivel_Comb = 0;
unsigned long odometro = 0;
float AVG = 0.0;
char direcao = '-';

// Tanque
const float Tanque = 50.0;
float LitrosNoTanque = 0.0;
float autonomiaEstimada = 0.0;

// Trip A
float KmInicioTripA = 0;
float KmAtualTripA = 0;
float ConsumoTripA = 0;
float ConsumoMedioTripA = 0;

// Trip B
float KmInicioTripB = 0;
float KmAtualTripB = 0;
float ConsumoTripB = 0;
float ConsumoMedioTripB = 0;

// Geral
float consumoTotalDesdeInicio = 0;
float consumoMedioGeral = 0;

// =================== FUNÇÕES ===================

void avg(){
  if (velocidade > 1){
    AVG = velocidade / (cargaMotor / 10.0 + 1);
  } else {
    AVG = 0;
  }
}

void atualizarTripA(){
  KmAtualTripA = odometro - KmInicioTripA;
  ConsumoTripA += AVG / 3600.0;
  if (KmAtualTripA > 0){
    ConsumoMedioTripA = ConsumoTripA / KmAtualTripA;
  }
}

void atualizarTripB(){
  KmAtualTripB = odometro - KmInicioTripB;
  ConsumoTripB += AVG / 3600.0;
  if (KmAtualTripB > 0){
    ConsumoMedioTripB = ConsumoTripB / KmAtualTripB;
  }
}

void ConsumoGeral(){
  float kmRodado = odometro;
  consumoTotalDesdeInicio += AVG / 3600.0;
  if (kmRodado > 0){
    consumoMedioGeral = consumoTotalDesdeInicio / kmRodado;
  }
}

void Autonomia(){
  LitrosNoTanque = (nivel_Comb / 255.0) * Tanque;
  if (consumoMedioGeral > 0){
    autonomiaEstimada = LitrosNoTanque / consumoMedioGeral;
  } else {
    autonomiaEstimada = 0;
  }
}

// ===================  SETUP  ===================

void setup() {
  Serial.begin(115200);
  if (can.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN iniciado");
  } else {
    Serial.println("Erro ao iniciar CAN");
    while (1);
  }
  can.setMode(MCP_NORMAL);
}

void loop() {
  if (CAN_MSGAVAIL == can.checkReceive()) {
    long unsigned int rxId;
    byte len = 0;
    byte buf[8];

    can.readMsgBuf(&rxId, &len, buf);

    switch (rxId) {
      case 0x280: // RPM e carga
        RPM = buf[3] * 100;
        cargaMotor = buf[7];
        break;

      case 0x320: // Velocidade e combustível
        velocidade = ((buf[4] << 8) | buf[3]) / 100.0;
        nivel_Comb = buf[2];
        break;

      case 0x520: // Odômetro
        odometro = (buf[7] << 16) | (buf[6] << 8) | buf[5];  // Valor real do odômetro recebido
        break;
    }

    // Atualizar todos os cálculos
    avg();
    atualizarTripA();
    atualizarTripB();
    ConsumoGeral();
    Autonomia();

    // Serial Print
    Serial.print("RPM: "); Serial.print(RPM);
    Serial.print(" | Carga: "); Serial.print(cargaMotor);
    Serial.print(" | Vel: "); Serial.print(velocidade); Serial.print(" km/h");
    Serial.print(" | Comb: "); Serial.print(nivel_Comb);
    Serial.print(" | Odo: "); Serial.print(odometro);  // Exibindo o valor real do odômetro
    Serial.print(" | AVG: "); Serial.print(AVG);
    Serial.print(" | Autonomia: "); Serial.println(autonomiaEstimada);

    // Dados das trips
    Serial.print("Trip A - Km: "); Serial.print(KmAtualTripA);
    Serial.print(" | Consumo: "); Serial.print(ConsumoMedioTripA); Serial.println(" l/km");

    Serial.print("Trip B - Km: "); Serial.print(KmAtualTripB);
    Serial.print(" | Consumo: "); Serial.print(ConsumoMedioTripB); Serial.println(" l/km");

    // Consumo geral
    Serial.print("Consumo Geral: "); Serial.print(consumoMedioGeral); Serial.println(" l/km");
  }
}
