package model;

public class ContaCorrente extends Conta {
    public ContaCorrente(int numero, Cliente cliente) {
        super(numero, cliente);
    }

    @Override
    public void imprimirExtrato() {
        System.out.println("Conta Corrente: " + numero + ", Saldo: R$" + saldo);
    }
}
