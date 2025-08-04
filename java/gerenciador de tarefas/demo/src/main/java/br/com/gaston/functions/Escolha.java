package br.com.gaston.functions;

import java.util.Scanner;

public class Escolha {

    Scanner ler = new Scanner(System.in);

    public Escolha() {
        System.out.println("O que deseja fazer?");
        System.out.println("--------------------");
        System.out.println("1 - Cadastrar tarefa");
        System.out.println("2 - Listar tarefas");
        System.out.println("3 - Excluir tarefa");
        System.out.println("4 - Declarar feita");
        System.out.println("5 - Sair");
        System.out.println("--------------------");
        System.out.print("Digite a opção desejada: ");
        int opcao = ler.nextInt();
        ler.nextLine();

        switch (opcao) {
            case 1:
                Cadastrar cadastrar = new Cadastrar();
                cadastrar.cadastrarTarefa();
                break;
            case 2:
                Listar listar = new Listar();
                listar.listarTarefas();
                break;
            case 3:
                Excluir excluir = new Excluir();
                excluir.excluirTarefa();
                break;
            case 4:
                DeclararFeita declararFeita = new DeclararFeita();
                declararFeita.declararFeita();
                break;
            case 5:
                System.out.println("Saindo do programa...");
                break;
            default:
                System.out.println("Opção inválida!");
        }
    }
}
