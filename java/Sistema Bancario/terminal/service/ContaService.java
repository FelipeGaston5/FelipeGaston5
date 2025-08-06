package service;

import model.Conta;
import model.ContaCorrente;
import model.ContaPoupanca;
import model.Cliente;
import repository.ContaRepository;

public class ContaService {

    public Conta criarContaCorrente(Cliente cliente) {
        int numeroConta = ContaRepository.gerarNumeroConta();
        ContaCorrente conta = new ContaCorrente(numeroConta, cliente);
        ContaRepository.adicionar(conta);
        return conta;
    }

    public Conta criarContaPoupanca(Cliente cliente) {
        int numeroConta = ContaRepository.gerarNumeroConta();
        ContaPoupanca conta = new ContaPoupanca(numeroConta, cliente);
        ContaRepository.adicionar(conta);
        return conta;
    }

    public boolean depositar(int numeroConta, double valor) {
        Conta conta = ContaRepository.buscarPorNumero(numeroConta);
        if (conta == null || valor <= 0) {
            return false;
        }
        conta.depositar(valor);
        return true;
    }

    public Conta buscarPorNumero(int numero) {
        return ContaRepository.buscarPorNumero(numero);
    }
}
