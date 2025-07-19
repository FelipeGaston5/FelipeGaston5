import serial
import tkinter as tk
from tkinter import ttk

# Configuração da porta serial (ajuste para a porta correta)
arduino_port = "COM4"  # Altere para o número da porta serial do seu Arduino
baud_rate = 115200     # A mesma taxa de transmissão configurada no Arduino

# Função para ler os dados da porta serial
def read_serial_data(ser, text_area):
    while True:
        try:
            # Lê os dados da porta serial
            data = ser.readline().decode('utf-8').strip()  # Lê e decodifica os dados
            if data:
                # Atualiza a interface gráfica com as novas mensagens
                text_area.insert(tk.END, f"{data}\n")
                text_area.yview(tk.END)  # Faz o scroll automático para o final
        except Exception as e:
            print(f"Erro na leitura da serial: {e}")
            break

# Função para criar a interface gráfica
def create_gui():
    # Criação da janela principal
    root = tk.Tk()
    root.title("Monitor CAN")
    root.geometry("700x500")  # Tamanho da janela

    # Estilo da janela
    style = ttk.Style()
    style.theme_use("clam")

    # Label de título
    title_label = ttk.Label(root, text="Monitor CAN", font=("Helvetica", 18, "bold"))
    title_label.pack(pady=10)

    # Área de texto para exibir as mensagens
    text_area = tk.Text(root, width=80, height=20, font=("Courier", 12), wrap="word", bg="#ECF0F1", fg="#34495E", padx=10, pady=10)
    text_area.pack(padx=20, pady=10)

    # Criando a porta serial
    ser = serial.Serial(arduino_port, baud_rate)
    print(f"Conectado à porta {arduino_port} com baud rate {baud_rate}")

    # Botão para sair
    exit_button = ttk.Button(root, text="Sair", command=root.quit)
    exit_button.pack(pady=20)

    # Iniciar a leitura dos dados em uma thread separada
    root.after(100, read_serial_data, ser, text_area)

    # Iniciar a interface gráfica
    root.mainloop()

# Executar a aplicação
create_gui()
