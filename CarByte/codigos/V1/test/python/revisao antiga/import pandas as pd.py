import pandas as pd
import matplotlib.pyplot as plt

# Carregar o arquivo CSV
df = pd.read_csv("C:\\Users\\gasto\\Desktop\\CarByte\\Documentação e anotações\\dados\\1.8km.csv")

# Função para extrair todos os bytes
def extrair_bytes(bytes_str):
    return [int(byte, 16) for byte in bytes_str.split()]

# Aplicar a função para extrair todos os bytes
df['bytes_extrados'] = df['bytes'].apply(extrair_bytes)

# Estabelecendo a temperatura do painel (90°C)
temperatura_painel = 90

# Função para mapear e comparar cada byte com a temperatura
def comparar_bytes_com_temperatura(bytes_lista):
    resultados = {}
    for i, byte in enumerate(bytes_lista):
        # Vamos assumir que a temperatura pode ser proporcional ao valor do byte.
        # Ajuste a fórmula conforme necessário, dependendo da sua calibração.
        if byte * (105 / 10) == temperatura_painel:
            resultados[f'byte_{i}'] = byte
    return resultados

# Aplicar a função para comparar os bytes com a temperatura
df['comparacao_temperatura'] = df['bytes_extrados'].apply(comparar_bytes_com_temperatura)

# Gráfico para visualizar a comparação de bytes com a temperatura
plt.figure(figsize=(10,6))

# Plotando os valores de cada byte extraído ao longo do tempo
for i in range(len(df['bytes_extrados'][0])):  # Assumindo que todos os registros possuem a mesma quantidade de bytes
    plt.plot(df['timestamp'], [bytes_lista[i] for bytes_lista in df['bytes_extrados']], label=f'Byte {i}', linestyle='-', marker='o')

# Adicionando a linha de temperatura do painel (90°C) para comparação
plt.axhline(y=temperatura_painel, color='r', linestyle='--', label="Temperatura (90°C)")

# Ajustes no gráfico
plt.xlabel('Timestamp')
plt.ylabel('Valor dos Bytes')
plt.title('Comparação de Bytes com a Temperatura de 90°C')
plt.xticks(rotation=45)
plt.legend(loc='best')
plt.tight_layout()

# Salvar o gráfico em um arquivo
plt.savefig("C:\\Users\\gasto\\Desktop\\CarByte\\Documentação e anotações\\dados\\grafico_comparacao_temperatura.png")

# Exibir mensagem informando que o gráfico foi salvo
print("Gráfico salvo com sucesso em: C:\\Users\\gasto\\Desktop\\CarByte\\Documentação e anotações\\dados\\grafico_comparacao_temperatura.png")
