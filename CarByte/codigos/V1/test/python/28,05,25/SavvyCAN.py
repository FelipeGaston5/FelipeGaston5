import serial
import can 
import time

serial_port = 'COM3'
baud_rate = 115200

can_interface = 'can0'

def setup_serial(line):
    parts = line.strip().split()
    if len(parts) < 2:
        return None

    try:
        can_id = int(parts[0], 16)
        data = bytes(int(b, 16) for b in parts[1:])
        return can.Mensage(arbitration_id = can_id, data = data, is_extended_id = False)
    except:
        return None
    
def main():
    ser = serial.Serial(serial_port, baud_rate, timesout = 1)
    
    bus = can.interface.Bus(channel = can_interface, bustype = 'socketcan')
    
    print(f"Lendo dados da serial {serial_port} e enviando para {can_interface}...")
    
    while True:
        line = ser.readline().decode('utf-8').strip()
        if not line:
            continue
        
        mensage = setup_serial(line)
        if mensage:
            try:
                bus.send(mensage)
                print(f"Enviado: {mensage}")
            except can.CanError:
                print("Erro ao enviar mensagem CAN.")

if __name__ == "__main__":
    main()
        