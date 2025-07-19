import serial
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets
import re

# Serial (modificar COMx conforme necessário)
ser = serial.Serial('COM4', 115200, timeout=0)

# Interface gráfica
app = QtWidgets.QApplication([])
win = pg.GraphicsLayoutWidget(show=True, title="Leitura CAN em Tempo Real")
win.resize(1000, 600)
plot = win.addPlot(title="Bytes CAN")
plot.setYRange(0, 255)

# Inicialização de curvas para os bytes
curvas = [None] * 8  # Inicializando a lista de curvas com None
dados = [[] for _ in range(8)]  # Para até 8 bytes de cada mensagem CAN
tempo = []
max_pontos = 200  # Número máximo de pontos no gráfico (evita sobrecarga)
contador = 0
frame_skip = 5  # Atualiza gráfico a cada 5 ciclos
frame_count = 0

# Regex para detectar dados CAN (padrão geral)
padrao = re.compile(r"ID:\s*([0-9A-Fa-f]+)\s*\|\s*Data:\s*([0-9A-Fa-f\s]+)")

# ID do CAN que você deseja filtrar
id_desejado = 0x280  # Substitua pelo ID que você deseja filtrar, por exemplo, 0x280

# Adicionando a legenda no gráfico
legend = plot.addLegend()  # Adiciona a legenda ao gráfico

# Lista de bytes a exibir (indices de 0 a 7, correspondendo a byte1 a byte8)
bytes_a_exibir = [1, 4,3 ,5 , 7]  # Exemplo: Exibir byte1, byte3, byte5 e byte7

# Função de atualização do gráfico
def update():
    global contador, frame_count
    try:
        linha = ser.readline().decode('utf-8', errors='ignore').strip()  # Lê a linha de dados serial
        if linha:
            print("Recebido:", linha)  # Para debug, imprime a linha recebida

        match = padrao.search(linha)  # Tenta encontrar a linha que corresponde ao padrão
        if match:
            # Captura o ID e os dados do CAN
            id_can = int(match.group(1), 16)  # Converte o ID para inteiro
            dados_str = match.group(2).split()
            if len(dados_str) == 8:  # Garantir que temos todos os 8 bytes
                valores = [int(b, 16) for b in dados_str]

                # Verifica se o ID da mensagem corresponde ao ID desejado
                if id_can == id_desejado:
                    # Adicionar dados a cada curva
                    for i in range(8):
                        dados[i].append(valores[i])
                        if len(dados[i]) > max_pontos:
                            dados[i] = dados[i][-max_pontos:]  # Limita os pontos para a quantidade máxima

                    tempo.append(contador)
                    if len(tempo) > max_pontos:
                        tempo[:] = tempo[-max_pontos:]

                    contador += 1

                    # Só atualiza o gráfico a cada 'frame_skip' ciclos
                    frame_count += 1
                    if frame_count >= frame_skip:
                        # Atualiza as curvas para os bytes selecionados
                        for i in bytes_a_exibir:
                            if curvas[i] is None:
                                # Cria a curva para o byte selecionado
                                curvas[i] = plot.plot(pen=pg.mkPen(color=pg.intColor(i), width=2), name=f"Byte {i+1}")
                            # Atualiza os dados da curva
                            curvas[i].setData(tempo, dados[i])

                        # Ajuste dinâmico da faixa Y para estabilizar
                        plot.setYRange(min(min(dados[i]) for i in bytes_a_exibir) - 10,
                                    max(max(dados[i]) for i in bytes_a_exibir) + 10)

                        frame_count = 0

    except Exception as e:
        print("Erro:", e)

# Timer para leitura em tempo real (atualização a cada 1ms)
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(1)

# Iniciar a aplicação gráfica
if __name__ == '__main__':
    QtWidgets.QApplication.instance().exec_()
