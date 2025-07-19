#include <SPI.h>
#include <mcp_can.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

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
float odometroInicial = 0;
float consumoTotalDesdeInicio = 0;
float consumoMedioGeral = 0;

// =================== FUNÇÕES ===================

void avg(){
  if (velocidade > 1){
    AVG = velocidade / (cargaMotor / 10.0 + 1);
  }else{
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
  float kmRodado = odometro - odometroInicial;
  consumoTotalDesdeInicio += AVG/3600.0;
  if (kmRodado > 0){
    consumoMedioGeral = consumoTotalDesdeInicio / kmRodado;
  }
}

void Autonomia(){
  LitrosNoTanque = (nivel_Comb / 255.0) * Tanque;
  if (consumoMedioGeral > 0){
    autonomiaEstimada = LitrosNoTanque / consumoMedioGeral;
  }else{
    autonomiaEstimada = 0;
  }
}


// ===================  SETUP  ===================
void setup() {
  lcd.init();
  lcd.backlight();

  Serial.begin(115200);
  if (can.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN iniciado");
    lcd.print("CAN iniciado!");
    delay(3000);
    lcd.noDisplay();
  } else {
    Serial.println("Erro ao iniciar CAN");
    lcd.print("Erro ao iniciar CAN");
    delay(3000);
    lcd.noDisplay();
    while (1);
  }
  can.setMode(MCP_NORMAL);
  odometroInicial = odometro;

  lcd.clear();
  lcd.display();
}

void loop() {
  if (CAN_MSGAVAIL == can.checkReceive()) {
      lcd.clear();
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
        odometro = (buf[7] << 16) | (buf[6] << 8) | buf[5];
        break;

      delay(300);
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
    Serial.print(" | Odo: "); Serial.print(odometro);
    Serial.print(" | AVG: "); Serial.print(AVG);
    Serial.print(" | Autonomia: "); Serial.println(autonomiaEstimada);

    //LCD print
     // Linha 0
  lcd.setCursor(0, 0);
  lcd.print("RPM: "); lcd.print(RPM);
  lcd.setCursor(12, 0);
  lcd.print("Carga:"); lcd.print(cargaMotor); lcd.print("%");

  // Linha 1
  lcd.setCursor(0, 1);
  lcd.print("Vel: "); lcd.print(velocidade); lcd.print("km/h");
  lcd.setCursor(12, 1);
  lcd.print("Comb:"); lcd.print(nivel_Comb); lcd.print("%");

  // Linha 2
  lcd.setCursor(0, 2);
  lcd.print("Odo: "); lcd.print(odometro); lcd.print("km");
  lcd.setCursor(12, 2);
  lcd.print("AVG: "); lcd.print(AVG, 1); // 1 casa decimal

  // Linha 3
  lcd.setCursor(0, 3);
  lcd.print("Autonomia: "); lcd.print(autonomiaEstimada); lcd.print("km");

  lcd.display();
  
  }
}
