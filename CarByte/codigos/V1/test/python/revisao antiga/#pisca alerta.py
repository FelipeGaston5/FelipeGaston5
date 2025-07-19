import serial
import time

# Configuração da porta serial
PORTA_SERIAL = 'COM4'  # Altere para a porta do seu Arduino
BAUD_RATE = 115200     # A mesma taxa de transmissão configurada no Arduino

# Define o padrão de início e fim do ciclo do pisca alerta
PATRON_INICIO = "51"
PATRON_FIM = "41"

# Abre a porta serial
ser = serial.Serial(PORTA_SERIAL, BAUD_RATE, timeout=1)

# Função para verificar o ciclo completo de pisca alerta
def verificar_pisca_alerta(ciclo_bytes):
    # Verifica se o ciclo de bytes começa com 51 e termina com 41
    print("Analisando ciclo:", ciclo_bytes)  # Adicionado para depuração
    if ciclo_bytes[0] == PATRON_INICIO and ciclo_bytes[-1] == PATRON_FIM:
        return True  # Ciclo de pisca alerta identificado
    return False  # Caso não seja o ciclo de pisca alerta

# Função para ler e analisar os dados da porta serial
def ler_serial():
    tempo_inicial = time.time()
    ciclo_bytes = []
    contador = 0
    
    while True:
        dados = ser.readline().decode('utf-8').strip()
        
        if dados:
            # Divide os dados recebidos para formar os ciclos de bytes
            ciclo_bytes.append(dados.split()[0])  # Armazena apenas o byte 0 de cada mensagem
            
            # Verifica se é um ciclo completo
            if len(ciclo_bytes) >= 2:  # Pelo menos 2 bytes para comparar o ciclo
                if verificar_pisca_alerta(ciclo_bytes):
                    print("Pisca alerta ACESO")
                else:
                    print("Pisca alerta APAGADO")
                
                # Reinicia o ciclo de contagem
                ciclo_bytes = []
            
            # Controle de tempo: verifica se passou 0.5s
            tempo_atual = time.time()
            intervalo = tempo_atual - tempo_inicial
            
            if intervalo >= 0.5:  # Se passou 0.5 segundos
                print(f"Ciclo de 0.5s detectado. Total de ciclos: {contador}")
                contador = 0  # Resetando o contador
                tempo_inicial = tempo_atual  # Resetando o tempo

            contador += 1  # Incrementa o contador de ciclos

            # Espera antes de ler o próximo dado
            time.sleep(0.1)

# Chama a função para começar a ler os dados da serial
ler_serial()
