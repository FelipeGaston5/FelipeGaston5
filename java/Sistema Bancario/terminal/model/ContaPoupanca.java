package model;

public class ContaPoupanca extends Conta {
    private double taxaJuros = 0.01; // 1% ao mês

    public ContaPoupanca(int numero, Cliente cliente) {
        super(numero, cliente);
    }

    public void aplicarRendimento() {
        saldo += saldo * taxaJuros;
    }

    @Override
    public void imprimirExtrato() {
        System.out.println("Conta Poupança: " + numero + ", Saldo: R$" + saldo);
    }
}
