package model;

public class CartaoDebito {
    private String numero;
    private String validade;
    private Conta conta;

    public CartaoDebito(String numero, String validade, Conta conta) {
        this.numero = numero;
        this.validade = validade;
        this.conta = conta;
    }

    public String getNumero() {
        return numero;
    }

    public String getValidade() {
        return validade;
    }

    public Conta getConta() {
        return conta;
    }
}
