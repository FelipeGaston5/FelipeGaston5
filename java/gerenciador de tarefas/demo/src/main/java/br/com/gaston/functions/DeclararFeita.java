package br.com.gaston.functions;

import br.com.gaston.models.Tarefa;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.*;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class DeclararFeita {
    private final String caminhoArquivo = "C:/Users/gasto/OneDrive/Área de Trabalho/projeto/Java/gerenciador de tarefas/demo/src/main/resources/Tarefas.json";
    private final Gson gson = new Gson();

    public void declararFeita() {
        try {
            List<Tarefa> tarefas = lerTarefasDoArquivo();

            if (tarefas.isEmpty()) {
                System.out.println("Não há tarefas para marcar como feitas.");
                return;
            }

            for (int i = 0; i < tarefas.size(); i++) {
                String status = tarefas.get(i).isFeita() ? "[FEITA]" : "[PENDENTE]";
                System.out.println(i + " - " + tarefas.get(i).getNome() + " " + status);
            }

            System.out.print("Digite o número da tarefa que deseja marcar como feita: ");
            Scanner scanner = new Scanner(System.in);
            int indice = scanner.nextInt();

            if (indice >= 0 && indice < tarefas.size()) {
                tarefas.get(indice).setFeita(true);
                salvarTarefasNoArquivo(tarefas);
                System.out.println("Tarefa marcada como feita.");
            } else {
                System.out.println("Índice inválido.");
            }

        } catch (IOException e) {
            System.out.println("Erro ao manipular o arquivo: " + e.getMessage());
        }
    }

    private List<Tarefa> lerTarefasDoArquivo() throws IOException {
        File file = new File(caminhoArquivo);
        if (!file.exists() || file.length() == 0)
            return new ArrayList<>();

        Reader reader = new FileReader(file);
        Type tarefaListType = new TypeToken<ArrayList<Tarefa>>() {
        }.getType();
        List<Tarefa> tarefas = gson.fromJson(reader, tarefaListType);
        reader.close();
        return tarefas != null ? tarefas : new ArrayList<>();
    }

    private void salvarTarefasNoArquivo(List<Tarefa> tarefas) throws IOException {
        Writer writer = new FileWriter(caminhoArquivo);
        gson.toJson(tarefas, writer);
        writer.flush();
        writer.close();
        new Escolha();
    }
    
}
