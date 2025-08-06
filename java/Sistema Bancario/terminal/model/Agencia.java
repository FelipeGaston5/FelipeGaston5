package model;

public class Agencia {
    private int numero;
    private String nome;
    private Endereco endereco;

    public Agencia(int numero, String nome, Endereco endereco) {
        this.numero = numero;
        this.nome = nome;
        this.endereco = endereco;
    }

    public int getNumero() {
        return numero;
    }

    public String getNome() {
        return nome;
    }

    public Endereco getEndereco() {
        return endereco;
    }
}
