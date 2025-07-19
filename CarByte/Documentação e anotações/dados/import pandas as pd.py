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

# Função para plotar os bytes selecionados
def plotar_bytes(selecionados):
    # Plotando o gráfico
    plt.figure(figsize=(12, 8))

    # Plotar apenas os bytes selecionados no gráfico
    for col in selecionados:
        if col in byte_columns:
            plt.plot(df['timestamp'], df[col], label=f'Byte {col[-1]}')
        else:
            print(f"Byte {col[-1]} não encontrado. Verifique a lista de bytes.")

    # Adicionar título e rótulos
    plt.title('Variação dos Bytes ao Longo do Tempo')
    plt.xlabel('Tempo')
    plt.ylabel('Valor dos Bytes')

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
bytes_a_exibir = [ 'byte4', 'byte1', 'byte3', 'byte7', 'byte5']  # Exemplo de bytes para exibir
plotar_bytes(bytes_a_exibir)
