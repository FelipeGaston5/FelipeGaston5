package model;

public class CartaoCredito {
    private String numero;
    private String validade;
    private double limite;
    private Cliente titular;

    public CartaoCredito(String numero, String validade, double limite, Cliente titular) {
        this.numero = numero;
        this.validade = validade;
        this.limite = limite;
        this.titular = titular;
    }

    public String getNumero() {
        return numero;
    }

    public String getValidade() {
        return validade;
    }

    public double getLimite() {
        return limite;
    }

    public Cliente getTitular() {
        return titular;
    }
}
