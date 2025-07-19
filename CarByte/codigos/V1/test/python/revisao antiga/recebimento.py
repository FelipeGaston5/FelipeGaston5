import csv
from datetime import datetime

# Função para interpretar os dados do CSV
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

# Função para ler o arquivo CSV
def ler_csv():
    try:
        with open('log_can_data.csv', mode='r') as arquivo_csv:
            reader = csv.reader(arquivo_csv)
            next(reader)  # Pula o cabeçalho
            for row in reader:
                timestamp, id_part, bytes_part = row
                data_bytes = bytes_part.split()
                interpretado = interpretar_id(id_part, data_bytes)
                print(f"[{timestamp}] {interpretado}")
    except FileNotFoundError:
        print("[ERROR] Erro ao carregar o arquivo CSV: O arquivo não foi encontrado.")
    except Exception as e:
        print(f"[ERROR] Erro ao ler o arquivo CSV: {e}")

if __name__ == "__main__":
    ler_csv()
