package br.com.gaston.functions;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import br.com.gaston.models.Tarefa;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;

public class Cadastrar {
    Scanner ler;
    private String nome;
    private String descricao;
    private String data;
    private String hora;
    private int prioridade;

    private void salvarTarefa(Tarefa novaTarefa) {
    Gson gson = new Gson();
    List<Tarefa> tarefas = new ArrayList<>();
    File file = new File("C:/Users/gasto/OneDrive/Área de Trabalho/projeto/Java/gerenciador de tarefas/demo/src/main/resources/Tarefas.json");


    if (file.exists()) {
        try (Reader reader = new FileReader(file)) {
            java.lang.reflect.Type tarefaListType = new TypeToken<List<Tarefa>>() {}.getType();
            tarefas = gson.fromJson(reader, tarefaListType);
        } catch (IOException e) {
            System.out.println("Erro ao ler o JSON: " + e.getMessage());
        }
    }

    tarefas.add(novaTarefa);

    try (Writer writer = new FileWriter(file)) {
        gson.toJson(tarefas, writer);
    } catch (IOException e) {
        System.out.println("Erro ao salvar a tarefa: " + e.getMessage());
    }
    }

    public Cadastrar() {
        this.ler = new Scanner(System.in);
        System.out.println("Você escolheu cadastrar uma tarefa.");
        System.out.println("=====================================");
    }

    public void cadastrarTarefa() {
        System.out.print("Digite o nome da tarefa: ");
        this.nome = this.ler.nextLine();
        System.out.print("Digite a descrição da tarefa: ");
        this.descricao = this.ler.nextLine();
        System.out.print("Digite a data (dd/mm/aaaa): ");
        this.data = this.ler.nextLine();
        System.out.print("Digite a hora (hh:mm): ");
        this.hora = this.ler.nextLine();
        System.out.print("Digite a prioridade (1-5): ");
        this.prioridade = this.ler.nextInt();
        System.out.println("=====================================");
        System.out.println("Tarefa cadastrada com os seguintes dados:");
        System.out.println("Nome: " + this.nome);
        System.out.println("Descrição: " + this.descricao);
        System.out.println("Data: " + this.data);
        System.out.println("Hora: " + this.hora);
        System.out.println("Prioridade: " + this.prioridade);
        System.out.println("=====================================");
        System.out.println("Deseja Salvar a tarefa? (s/n)");
        String var2 = this.ler.next();
        boolean var1;
        if (var2.equalsIgnoreCase("s")) {
            var1 = true;
        } else {
            if (!var2.equalsIgnoreCase("n")) {
                System.out.println("Opção inválida. Por favor, digite 's' para sim ou 'n' para não.");
                this.cadastrarTarefa();
                return;
            }

            var1 = false;
        }

        if (var1) {
            System.out.println("Tarefa salva com sucesso!");
        }

    Tarefa tarefa = new Tarefa(this.nome, this.descricao, this.data, this.hora, this.prioridade, false);
    salvarTarefa(tarefa);
    System.out.println("Tarefa cadastrada e salva com sucesso!");
    new Escolha();  
    }
    

}
