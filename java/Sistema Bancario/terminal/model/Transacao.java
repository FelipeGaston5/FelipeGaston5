package model;

import java.time.LocalDateTime;

public class Transacao {
    private String tipo; // "Saque", "Depósito", "Transferência"
    private double valor;
    private LocalDateTime dataHora;
    private Conta conta;

    public Transacao(String tipo, double valor, Conta conta) {
        this.tipo = tipo;
        this.valor = valor;
        this.conta = conta;
        this.dataHora = LocalDateTime.now();
    }

    public String getTipo() {
        return tipo;
    }

    public double getValor() {
        return valor;
    }

    public LocalDateTime getDataHora() {
        return dataHora;
    }

    public Conta getConta() {
        return conta;
    }
}
