import serial
import time
import csv
from datetime import datetime
import subprocess  # Módulo para executar outro script

# CONFIGURAÇÃO DA SERIAL (ajuste conforme sua porta)
porta_serial = 'COM4'  # Altere conforme necessário
baudrate = 115200

# ABRE CONEXÃO
ser = serial.Serial(porta_serial, baudrate, timeout=1)
print(f"[INFO] Conectado à {porta_serial}")

# CRIA O CSV PARA O ID 0xD0
with open('log_can_data_d0.csv', mode='w', newline='') as arquivo_csv_d0:
    writer_d0 = csv.writer(arquivo_csv_d0)
    writer_d0.writerow(['timestamp', 'id', 'bytes'])  # Cabeçalhos

    try:
        while True:
            linha = ser.readline().decode('utf-8').strip()
            if linha.startswith("ID:"):
                partes = linha.split(" | ")
                id_part = partes[0].split(":")[1].strip()
                bytes_part = partes[1].split(":")[1].strip()
                timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')

                if id_part.lower() == '0xd0':  # Filtra apenas os dados com ID 0xD0
                    print(f"[{timestamp}] ID {id_part} => {bytes_part}")
                    writer_d0.writerow([timestamp, id_part, bytes_part])
    except KeyboardInterrupt:
        print("\n[INFO] Encerrado pelo usuário.")
    finally:
        ser.close()  # Garante que a porta seja fechada corretamente

# Chama o script 'recebimento.py' para interpretar os dados
print("[INFO] Iniciando o script de interpretação de dados.")
subprocess.run(['python', '../python/recebimento.py'])  # Executa 'recebimento.py' automaticamente
