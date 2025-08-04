package br.com.gaston.models;

import com.google.gson.annotations.SerializedName;

public class Tarefa {
    private String nome;
    private String descricao;
    private String data;
    private String hora;
    private int prioridade;
    @SerializedName("concluida")
    private boolean feita;

    public Tarefa(String var1, String var2, String var3, String var4, int var5, boolean var6) {
        this.nome = var1;
        this.descricao = var2;
        this.data = var3;
        this.hora = var4;
        this.prioridade = var5;
        this.feita = var6;
    }

    public String getNome() {
        return this.nome;
    }

    public String getDescricao() {
        return this.descricao;
    }

    public String getData() {
        return this.data;
    }

    public String getHora() {
        return this.hora;
    }

    public int getPrioridade() {
        return this.prioridade;
    }

    public boolean isFeita() {
        return this.feita;
    }

    public void setNome(String var1) {
        this.nome = var1;
    }

    public void setDescricao(String var2) {
        this.descricao = var2;
    }

    public void setData(String var3) {
        this.data = var3;
    }

    public void setHora(String var4) {
        this.hora = var4;
    }

    public void setPrioridade(int var5) {
        this.prioridade = var5;
    }

    public void setFeita(boolean var6) {
        this.feita = var6;
    }
}
