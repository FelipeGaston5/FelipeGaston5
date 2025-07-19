import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

# Carrega e filtra os dados da ID 0x280
def carregar_dados(caminho):
    try:
        df = pd.read_csv(caminho)
        print("[INFO] CSV carregado com sucesso.")
        df = df[df['id'].str.lower() == '0x280']  # Filtra apenas ID 0x280
        df['bytes'] = df['bytes'].str.strip()
        df = df[df['bytes'].str.count(' ') == 7]  # Garante que haja 8 bytes

        for i in range(8):
            df[f'byte_{i}'] = df['bytes'].apply(lambda x: int(x.split()[i], 16))

        return df
    except Exception as e:
        print(f"[ERRO] Falha ao processar o CSV: {e}")
        return None

# Aplica análise estatística para sugerir padrões
def analisar_variancia(df):
    print("\n[INFO] Análise de variação dos bytes:")
    for i in range(8):
        col = f'byte_{i}'
        variancia = df[col].var()
        print(f" - {col}: variância = {variancia:.2f}")
    print("Valores altos de variância indicam dados contínuos (como RPM). Valores baixos sugerem estados (ligado/desligado).")

# Detecta bytes que possuem correlação forte entre si (ou com o tempo)
def analisar_correlacoes(df):
    print("\n[INFO] Correlações entre bytes:")
    corr = df[[f'byte_{i}' for i in range(8)]].corr()
    print(corr)

    plt.figure(figsize=(8, 6))
    plt.title("Correlação entre os bytes da ID 0x280")
    plt.imshow(corr, cmap='coolwarm', interpolation='none')
    plt.colorbar(label='Correlação')
    plt.xticks(range(8), [f'B{i}' for i in range(8)])
    plt.yticks(range(8), [f'B{i}' for i in range(8)])
    plt.show()

# Reduz dimensionalidade e mostra padrões
def aplicar_pca(df):
    X = df[[f'byte_{i}' for i in range(8)]]
    X_scaled = StandardScaler().fit_transform(X)

    pca = PCA(n_components=2)
    componentes = pca.fit_transform(X_scaled)

    plt.figure(figsize=(8, 6))
    plt.scatter(componentes[:, 0], componentes[:, 1], alpha=0.5)
    plt.xlabel("Componente Principal 1")
    plt.ylabel("Componente Principal 2")
    plt.title("Análise PCA dos Bytes da ID 0x280")
    plt.grid()
    plt.show()

    print(f"[INFO] Variância explicada pelos dois primeiros componentes: {pca.explained_variance_ratio_.sum():.2%}")

# Função principal
def main():
    caminho_csv = "C:\\Users\\gasto\\Desktop\\CarByte\\Documentação e anotações\\dados\\1.8km.csv"
    df = carregar_dados(caminho_csv)

    if df is not None and not df.empty:
        analisar_variancia(df)
        analisar_correlacoes(df)
        aplicar_pca(df)
    else:
        print("[ERRO] Nenhum dado encontrado para análise.")

if __name__ == "__main__":
    main()
