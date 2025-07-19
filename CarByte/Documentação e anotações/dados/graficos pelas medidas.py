import pandas as pd
import matplotlib.pyplot as plt

# Caminho do arquivo CSV
csv_path = "C:\\Users\\gasto\\Desktop\\CarByte\\Documentação e anotações\\dados\\log_can_data.csv"

# Carregar o CSV
df = pd.read_csv(csv_path)

# Função para extrair todos os bytes como inteiros
def extrair_bytes(bytes_str):
    try:
        # Dividimos a string 'bytes' em uma lista e convertemos cada valor hexadecimal em inteiro
        bytes_lista = bytes_str.split()
        bytes_inteiros = [int(b, 16) for b in bytes_lista]  # Convertendo de hex para inteiro
        return bytes_inteiros
    except Exception as e:
        print(f"Erro ao extrair os bytes: {e}")
        return None

# Aplicar a função para extrair os bytes
df['bytes_list'] = df['bytes'].apply(extrair_bytes)

# Criar colunas para cada byte
byte_columns = ['byte' + str(i) for i in range(8)]
for i, col in enumerate(byte_columns):
    df[col] = df['bytes_list'].apply(lambda x: x[i] if x is not None else None)

# Verificar os primeiros dados
print(df[['timestamp'] + byte_columns].head())

# Converter o 'timestamp' para datetime para facilitar o gráfico
df['timestamp'] = pd.to_datetime(df['timestamp'])

# Função para mapear os bytes para bar
def mapear_para_bar(byte_val, max_val=5):
    if byte_val is not None:
        return (byte_val / 255) * max_val  # Convertendo para o intervalo de 0 a max_val bar
    return None

# Função para mapear o byte 3 para RPM (0 a 8000 RPM)
def mapear_para_rpm(byte_val):
    if byte_val is not None:
        return (byte_val / 255) * 8000  # Convertendo para a escala de RPM (supondo 8000 RPM como máximo)
    return None

# Função para mapear o byte 7 para MAP (Pressão Absoluta)
def mapear_para_map(byte_val):
    if byte_val is not None:
        return (byte_val / 255) * 200  # Convertendo para a escala de MAP em kPa (supondo 200 kPa como máximo)
    return None

# Função para mapear o byte 5 para Pedal do Acelerador
def mapear_para_pedal(byte_val):
    if byte_val is not None:
        return (byte_val / 255) * 100  # Convertendo para a escala de Pedal do Acelerador (0 a 100%)
    return None

# Aplicar as conversões para os bytes 1, 4, 3, 7 e 5
df['byte1_bar'] = df['byte1'].apply(mapear_para_bar, max_val=5)  # Ajustar o máximo conforme o contexto
df['byte4_bar'] = df['byte4'].apply(mapear_para_bar, max_val=5)  # Ajustar o máximo conforme o contexto
df['byte3_rpm'] = df['byte3'].apply(mapear_para_rpm)  # Ajuste para RPM entre 0 e 8000
df['byte7_map'] = df['byte7'].apply(mapear_para_map)
df['byte5_pedal'] = df['byte5'].apply(mapear_para_pedal)

# Função para plotar os bytes selecionados
def plotar_bytes(selecionados):
    # Plotando o gráfico
    plt.figure(figsize=(12, 8))

    # Plotar apenas os bytes selecionados no gráfico
    for col in selecionados:
        if col in df.columns:
            plt.plot(df['timestamp'], df[col], label=f'{col}')
        else:
            print(f"Byte {col} não encontrado. Verifique a lista de bytes.")

    # Adicionar título e rótulos
    plt.title('Variação dos Bytes ao Longo do Tempo')
    plt.xlabel('Tempo')
    plt.ylabel('Valor')

    # Adicionar rotação para os rótulos do eixo x
    plt.xticks(rotation=45)

    # Melhorar o layout
    plt.tight_layout()

    # Exibir a legenda
    plt.legend()

    # Mostrar o gráfico
    plt.show()

# Exemplo de como escolher quais bytes exibir
# A lista abaixo pode ser ajustada conforme os bytes que você deseja visualizar
bytes_a_exibir = ['byte1_bar', 'byte4_bar', 'byte3_rpm', 'byte7_map', 'byte5_pedal']  # Bytes para exibir
plotar_bytes(bytes_a_exibir)
