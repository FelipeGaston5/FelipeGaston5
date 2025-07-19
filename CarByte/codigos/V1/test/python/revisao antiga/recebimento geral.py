import serial
import csv
from datetime import datetime

# CONFIGURAÇÃO DA SERIAL (ajuste conforme sua porta)
porta_serial = 'COM4'  # Altere conforme necessário
baudrate = 115200

# Função para interpretar os dados do ID
def interpretar_id(id_hex, data_bytes):
    info = f"[ID: {id_hex}] "

    if id_hex == '0x280':
        try:
            rpm_raw = int(data_bytes[1], 16) << 8 | int(data_bytes[2], 16)
            rpm = rpm_raw / 4.0
            info += f"RPM aproximado: {rpm:.1f} | "
            pos_acel = int(data_bytes[5], 16)
            info += f"Pedal: {round(pos_acel / 255 * 100)}% | "
        except:
            info += "Erro ao decodificar 0x280"
    else:
        info += "Dados brutos: " + " ".join(data_bytes)

    return info

# Função para receber dados da porta serial e gravar no CSV
def receber_dados_serial():
    try:
        # ABRE CONEXÃO SERIAL
        ser = serial.Serial(porta_serial, baudrate, timeout=1)
        print(f"[INFO] Conectado à {porta_serial}")
        
        with open('log_can_data.csv', mode='a', newline='') as arquivo_csv:
            writer = csv.writer(arquivo_csv)
            writer.writerow(['timestamp', 'id', 'bytes'])  # Cabeçalhos (caso o arquivo seja novo)
            
            print("[INFO] Aguardando dados na porta serial...")
            
            while True:
                linha = ser.readline().decode('utf-8').strip()
                
                # Verifica se a linha começa com "ID:" (indicando que é um dado CAN)
                if linha.startswith("ID:"):
                    partes = linha.split(" | ")
                    id_part = partes[0].split(":")[1].strip()
                    bytes_part = partes[1].split(":")[1].strip()
                    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')

                    # Grava os dados no CSV
                    writer.writerow([timestamp, id_part, bytes_part])

                    # Interpreta os dados
                    data_bytes = bytes_part.split()
                    interpretado = interpretar_id(id_part, data_bytes)
                    print(f"[{timestamp}] {interpretado}")

    except KeyboardInterrupt:
        print("\n[INFO] Encerrado pelo usuário.")
    except FileNotFoundError:
        print("[ERROR] Erro ao carregar o arquivo CSV: O arquivo não foi encontrado.")
    except Exception as e:
        print(f"[ERROR] Erro ao receber dados: {e}")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()  # Garante que a porta serial seja fechada corretamente

if __name__ == "__main__":
    receber_dados_serial()
