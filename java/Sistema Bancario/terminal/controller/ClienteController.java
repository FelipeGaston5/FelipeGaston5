package controller;

import model.Cliente;
import repository.ClienteRepository;

import java.util.Scanner;

public class ClienteController {
    private final Scanner scanner;

    public ClienteController(Scanner scanner) {
        this.scanner = scanner;
    }

    public void cadastrarCliente() {
        System.out.println("=== Cadastro de Cliente ===");
        System.out.print("Nome: ");
        String nome = scanner.nextLine();
        System.out.print("CPF: ");
        String cpf = scanner.nextLine();

        if (ClienteRepository.buscarPorCpf(cpf) != null) {
            System.out.println("Cliente com este CPF já cadastrado!");
            return;
        }

        Cliente cliente = new Cliente(nome, cpf);
        ClienteRepository.adicionar(cliente);
        System.out.println("Cliente cadastrado com sucesso!");
    }

    public void listarClientes() {
        System.out.println("=== Lista de Clientes ===");
        for (Cliente c : ClienteRepository.listarTodos()) {
            System.out.println("- " + c.getNome() + " (CPF: " + c.getCpf() + ")");
        }
    }
}
