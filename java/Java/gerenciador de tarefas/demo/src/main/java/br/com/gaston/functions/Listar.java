package br.com.gaston.functions;

import br.com.gaston.models.Tarefa;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Type;
import java.util.List;

public class Listar {
    private final String caminhoArquivo = "C:/Users/gasto/OneDrive/Área de Trabalho/projeto/Java/gerenciador de tarefas/demo/src/main/resources/Tarefas.json";

    public Listar() {
        System.out.println("=====================================");
        System.out.println("Listando todas as tarefas cadastradas:");
        System.out.println("=====================================");
    }

    public void listarTarefas() {
        try {
            Gson gson = new Gson();
            FileReader leitor = new FileReader(caminhoArquivo);

            Type tarefaListType = new TypeToken<List<Tarefa>>() {
            }.getType();
            List<Tarefa> tarefas = gson.fromJson(leitor, tarefaListType);
            leitor.close();

            if (tarefas == null || tarefas.isEmpty()) {
                System.out.println("Nenhuma tarefa encontrada.");
                System.out.println("======================================");
                new Escolha();
                return;
            }

            for (int i = 0; i < tarefas.size(); i++) {
                Tarefa t = tarefas.get(i);
                System.out.println("Tarefa " + (i + 1) + ":");
                System.out.println("Nome: " + t.getNome());
                System.out.println("Descrição: " + t.getDescricao());
                System.out.println("Data: " + t.getData());
                System.out.println("Hora: " + t.getHora());
                System.out.println("Prioridade: " + t.getPrioridade());
                System.out.println("Feita: " + (t.isFeita() ? "Sim" : "Não"));
                System.out.println("-------------------------------------");
            }

        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo JSON: " + e.getMessage());
        }

        new Escolha();
    }
}
