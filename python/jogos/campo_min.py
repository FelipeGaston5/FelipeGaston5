import random
import tkinter as tk
from tkinter import messagebox

def iniciar_jogo():
    global tamanho, numero_bombas, tabuleiro, botoes, janela, bombas_marcadas
    try:
        tamanho = int(entrada_tamanho.get())
        numero_bombas = int(entrada_bombas.get())
        
        if tamanho < 5 or tamanho > 20:
            messagebox.showerror("Erro", "Tamanho deve ser entre 5 e 20")
            return
        if numero_bombas >= tamanho * tamanho:
            messagebox.showerror("Erro", "Muitas bombas para o tamanho do tabuleiro")
            return
            
        menu.destroy()
        
        janela = tk.Tk()
        janela.title('Campo Minado')
        
        tabuleiro = criar_tabuleiro(tamanho, numero_bombas)
        botoes = [[None for _ in range(tamanho)] for _ in range(tamanho)]
        bombas_marcadas = set()
        
        # Centraliza a janela na tela
        janela.update_idletasks()
        screen_width = janela.winfo_screenwidth()
        screen_height = janela.winfo_screenheight()
        
        exibir_tabuleiro()
        
        # Ajusta o tamanho da janela após criar os botões
        window_width = janela.winfo_width()
        window_height = janela.winfo_height()
        x = (screen_width - window_width) // 2
        y = (screen_height - window_height) // 2
        janela.geometry(f"+{x}+{y}")
        
        janela.resizable(False, False)
        janela.mainloop()
    except ValueError:
        messagebox.showerror("Erro", "Por favor, insira números válidos")

def criar_tabuleiro(tamanho, num_bombas):
    tabuleiro = [['0' for _ in range(tamanho)]for _ in range(tamanho)]

    bombas_colocadas = 0

    while bombas_colocadas < num_bombas:
        linha = random.randint(0, tamanho - 1)
        coluna = random.randint(0, tamanho - 1)

        if tabuleiro[linha][coluna] != 'B':
            tabuleiro[linha][coluna] = 'B'
            bombas_colocadas += 1
    
    for linha in range(tamanho):
        for coluna in range(tamanho):
            if tabuleiro[linha][coluna] != 'B':
                tabuleiro[linha][coluna] = str(calcular_bombas_adjacentes(tabuleiro, linha, coluna))

    return tabuleiro

def calcular_bombas_adjacentes(tabuleiro, linha, coluna):
    tamanho = len(tabuleiro)
    bombas = 0
    for i in range(-1, 2):
        for j in range(-1, 2):
            nova_linha, nova_coluna = linha + i, coluna + j
            if 0 <= nova_linha < tamanho and 0 <= nova_coluna < tamanho:
                if tabuleiro[nova_linha][nova_coluna] == 'B':
                    bombas += 1
    return bombas

def marcar_celula(event, linha, coluna):
    if botoes[linha][coluna]['state'] == 'normal':
        if botoes[linha][coluna]['text'] == '':
            botoes[linha][coluna].config(text='🚩')
            if tabuleiro[linha][coluna] == 'B':
                bombas_marcadas.add((linha, coluna))
                if len(bombas_marcadas) == numero_bombas:
                    todas_bombas_corretas = True
                    for l in range(tamanho):
                        for c in range(tamanho):
                            if botoes[l][c]['text'] == '🚩' and tabuleiro[l][c] != 'B':
                                todas_bombas_corretas = False
                                break
                    if todas_bombas_corretas:
                        messagebox.showinfo("Parabéns!", "Você venceu o jogo marcando todas as bombas!")
                        janela.quit()
        elif botoes[linha][coluna]['text'] == '🚩':
            botoes[linha][coluna].config(text='')
            if (linha, coluna) in bombas_marcadas:
                bombas_marcadas.remove((linha, coluna))

def verificar_vitoria():
    celulas_fechadas = 0
    for linha in range(tamanho):
        for coluna in range(tamanho):
            if botoes[linha][coluna]['state'] == 'normal' and tabuleiro[linha][coluna] != 'B':
                celulas_fechadas += 1
    return celulas_fechadas == 0

def revelar_celula(linha, coluna):
    if tabuleiro[linha][coluna] == 'B':
        messagebox.showinfo("Game Over","Você perdeu! Pisou em uma bomba.")
        janela.quit()
    else:
        botoes[linha][coluna].config(text=tabuleiro[linha][coluna], state="disabled", relief=tk.SUNKEN)
        if tabuleiro[linha][coluna] == '0':
            for i in range(-1, 2):
                for j in range(-1, 2):
                    nova_linha, nova_coluna = linha + i, coluna + j
                    if 0 <= nova_linha < tamanho and 0 <= nova_coluna < tamanho:
                        if botoes[nova_linha][nova_coluna]['state'] == 'normal':
                            botoes[nova_linha][nova_coluna].config(text=tabuleiro[nova_linha][nova_coluna], state='disabled', relief=tk.SUNKEN)
        if verificar_vitoria():
            messagebox.showinfo("Parabéns!", "Você venceu o jogo!")
            janela.quit()

def exibir_tabuleiro():
    frame = tk.Frame(janela)
    frame.pack(padx=10, pady=10)
    
    for linha in range(tamanho):
        for coluna in range(tamanho):
            botao = tk.Button(frame, width=2, height=1, command=lambda linha=linha, coluna=coluna: revelar_celula(linha, coluna))
            botao.bind('<Button-3>', lambda event, l=linha, c=coluna: marcar_celula(event, l, c))
            botao.grid(row=linha, column=coluna, padx=1, pady=1)
            botoes[linha][coluna] = botao

menu = tk.Tk()
menu.title('Campo Minado - Menu')
menu.geometry("300x250")

tk.Label(menu, text="Campo Minado", font=("Arial", 16, "bold")).pack(pady=15)

tk.Label(menu, text="Tamanho do tabuleiro (5-20):", font=("Arial", 10)).pack(pady=5)
entrada_tamanho = tk.Entry(menu, width=20)
entrada_tamanho.insert(0, "10")
entrada_tamanho.pack(pady=5)

tk.Label(menu, text="Número de bombas:", font=("Arial", 10)).pack(pady=5)
entrada_bombas = tk.Entry(menu, width=20)
entrada_bombas.insert(0, "10")
entrada_bombas.pack(pady=5)

tk.Button(menu, text="Iniciar Jogo", command=iniciar_jogo, width=15, height=2).pack(pady=20)

menu.mainloop()