#taxa de transmissão

import pandas as pd

# Função para calcular a taxa de transmissão
def calcular_taxa_transmissao(caminho_csv):
    try:
        # Carregar o CSV
        df = pd.read_csv(caminho_csv)

        # Converter a coluna 'timestamp' para o formato datetime
        df['timestamp'] = pd.to_datetime(df['timestamp'])
        
        # Obter o timestamp da primeira e última linha
        tempo_inicio = df['timestamp'].iloc[0]
        tempo_fim = df['timestamp'].iloc[-1]

        # Calcular o intervalo total de tempo
        intervalo_total = (tempo_fim - tempo_inicio).total_seconds()

        # Calcular o número total de linhas (mensagens)
        total_linhas = len(df)

        # Calcular a taxa de transmissão (mensagens por segundo)
        taxa_transmissao = total_linhas / intervalo_total

        print(f"[INFO] Intervalo total de tempo: {intervalo_total} segundos")
        print(f"[INFO] Número total de mensagens: {total_linhas}")
        print(f"[INFO] Taxa de Transmissão: {taxa_transmissao:.2f} mensagens por segundo")

    except Exception as e:
        print(f"[ERRO] Falha ao calcular a taxa de transmissão: {e}")

# Caminho do seu arquivo CSV
caminho_csv = 'pisca alerta.csv'

# Chamar a função
calcular_taxa_transmissao(caminho_csv)
