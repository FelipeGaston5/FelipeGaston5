package controller;

import model.Cliente;
import model.ContaCorrente;
import model.ContaPoupanca;
import model.Conta;
import repository.ClienteRepository;
import repository.ContaRepository;

import java.util.Scanner;

public class ContaController {
    private final Scanner scanner;

    public ContaController(Scanner scanner) {
        this.scanner = scanner;
    }

    public void criarContaCorrente() {
        System.out.println("=== Criar Conta Corrente ===");
        System.out.print("CPF do Cliente: ");
        String cpf = scanner.nextLine();

        Cliente cliente = ClienteRepository.buscarPorCpf(cpf);
        if (cliente == null) {
            System.out.println("Cliente não encontrado!");
            return;
        }

        int numeroConta = ContaRepository.gerarNumeroConta();
        ContaCorrente conta = new ContaCorrente(numeroConta, cliente);
        ContaRepository.adicionar(conta);

        System.out.println("Conta corrente criada com número: " + numeroConta);
    }

    public void criarContaPoupanca() {
        System.out.println("=== Criar Conta Poupança ===");
        System.out.print("CPF do Cliente: ");
        String cpf = scanner.nextLine();

        Cliente cliente = ClienteRepository.buscarPorCpf(cpf);
        if (cliente == null) {
            System.out.println("Cliente não encontrado!");
            return;
        }

        int numeroConta = ContaRepository.gerarNumeroConta();
        ContaPoupanca conta = new ContaPoupanca(numeroConta, cliente);
        ContaRepository.adicionar(conta);

        System.out.println("Conta poupança criada com número: " + numeroConta);
    }

    public void depositar() {
        System.out.println("=== Depósito ===");
        System.out.print("Número da conta: ");
        int numero = scanner.nextInt();
        scanner.nextLine(); // limpar buffer

        Conta conta = ContaRepository.buscarPorNumero(numero);
        if (conta == null) {
            System.out.println("Conta não encontrada!");
            return;
        }

        System.out.print("Valor do depósito: ");
        double valor = scanner.nextDouble();
        scanner.nextLine();

        if (valor <= 0) {
            System.out.println("Valor inválido!");
            return;
        }

        conta.depositar(valor);
        System.out.println("Depósito realizado com sucesso! Saldo atual: R$ " + conta.getSaldo());
    }

    public void imprimirExtrato() {
        System.out.println("=== Extrato ===");
        System.out.print("Número da conta: ");
        int numero = scanner.nextInt();
        scanner.nextLine();

        Conta conta = ContaRepository.buscarPorNumero(numero);
        if (conta == null) {
            System.out.println("Conta não encontrada!");
            return;
        }

        conta.imprimirExtrato();
    }
}
