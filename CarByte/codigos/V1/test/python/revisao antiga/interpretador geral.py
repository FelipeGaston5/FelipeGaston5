import pandas as pd

# Função para carregar e contar as ocorrências de bytes na ID 0xD0
def contar_ocorrencias_bytes(caminho):
    try:
        # Carregar o CSV
        df = pd.read_csv(caminho)
        print("[INFO] CSV carregado com sucesso.")

        # Exibe as primeiras linhas para verificar o conteúdo
        print("\n[INFO] Primeiras linhas do CSV:")
        print(df.head())

        # Filtra os dados pela ID D0
        df_d0 = df[df['id'].str.lower() == 'd0']
        df_d0['bytes'] = df_d0['bytes'].str.strip()

        # Remove múltiplos espaços e divide os bytes corretamente
        df_d0['bytes'] = df_d0['bytes'].apply(lambda x: ' '.join(x.split()))

        # Exibe os dados filtrados pela ID D0
        print("\n[INFO] Dados filtrados pela ID D0:")
        print(df_d0.head())

        # Filtra apenas as linhas que têm exatamente 6 bytes (separados por espaço)
        df_d0 = df_d0[df_d0['bytes'].str.count(' ') == 5]

        # Exibe as linhas filtradas com 6 bytes
        print("\n[INFO] Dados com exatamente 6 bytes:")
        print(df_d0.head())

        # Extrai os bytes e os separa em colunas
        for i in range(6):
            df_d0[f'byte_{i}'] = df_d0['bytes'].apply(lambda x: x.split()[i] if len(x.split()) == 6 else None)

        # Contar as ocorrências de cada byte em cada coluna de byte
        contagens = {}
        for i in range(6):
            byte_col = f'byte_{i}'
            contagens[byte_col] = df_d0[byte_col].value_counts()

        # Exibir os resultados
        print("\n[INFO] Ocorrências de cada byte na ID 0xD0:")
        for i in range(6):
            byte_col = f'byte_{i}'
            print(f"\n{byte_col}:")
            print(contagens[byte_col])

        # Convertendo os valores hexadecimais de byte_0 e byte_1 para inteiros
        df_d0['byte_0_int'] = df_d0['byte_0'].apply(lambda x: int(x, 16) if pd.notna(x) else None)
        df_d0['byte_1_int'] = df_d0['byte_1'].apply(lambda x: int(x, 16) if pd.notna(x) else None)

        # Calculando a correlação entre os bytes 0 e 1
        correlacao = df_d0[['byte_0_int', 'byte_1_int']].corr()
        
        # Exibe a correlação entre byte_0 e byte_1
        print("\n[INFO] Correlação entre byte_0 e byte_1:")
        print(correlacao)

    except Exception as e:
        print(f"[ERRO] Falha ao processar o CSV: {e}")

# Função principal
def main():
    caminho_csv = "farois.csv"  # Caminho correto do seu CSV
    contar_ocorrencias_bytes(caminho_csv)

if __name__ == "__main__":
    main()
