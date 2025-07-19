# analizes das luzes externas

import pandas as pd

# Função para verificar eventos de faróis e setas
def verificar_farol_setas(caminho):
    try:
        df = pd.read_csv(caminho)
        df['timestamp'] = pd.to_datetime(df['timestamp'])
        
        # Filtra os dados pela ID 0xD0 (faróis/setas)
        df_d0 = df[df['id'].str.lower() == 'd0']
        df_d0['bytes'] = df_d0['bytes'].str.strip()
        
        # Remove múltiplos espaços e divide os bytes corretamente
        df_d0['bytes'] = df_d0['bytes'].apply(lambda x: ' '.join(x.split()))

        # Extração dos bytes
        for i in range(6):  # Já sabemos que os dados são compostos por 6 bytes
            df_d0[f'byte_{i}'] = df_d0['bytes'].apply(lambda x: x.split()[i] if len(x.split()) == 6 else None)
        
        # Agora, identificamos os momentos em que byte_0 ou byte_1 alteram
        farol_seta_ativado = df_d0[(df_d0['byte_0'].notna()) & (df_d0['byte_1'].notna())]
        
        # Exibe os eventos de alteração
        print(f"[INFO] Momentos em que os faróis ou setas foram acionados:")
        print(farol_seta_ativado[['timestamp', 'byte_0', 'byte_1']])

    except Exception as e:
        print(f"[ERRO] Falha ao processar o CSV: {e}")

# Função principal
def main():
    caminho_csv = "farois.csv"  # Caminho correto do seu CSV
    verificar_farol_setas(caminho_csv)

if __name__ == "__main__":
    main()
