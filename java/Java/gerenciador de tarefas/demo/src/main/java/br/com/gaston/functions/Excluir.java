package br.com.gaston.functions;

import br.com.gaston.models.Tarefa;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.*;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Excluir {
    private final String caminhoArquivo = "C:/Users/gasto/OneDrive/Área de Trabalho/projeto/Java/gerenciador de tarefas/demo/src/main/resources/Tarefas.json";
    private final Gson gson = new Gson();

    public void excluirTarefa() {
        try {
            List<Tarefa> tarefas = carregarTarefas();

            if (tarefas.isEmpty()) {
                System.out.println("Nenhuma tarefa cadastrada.");
                return;
            }

            for (int i = 0; i < tarefas.size(); i++) {
                System.out.println(i + "-" + tarefas.get(i).getNome());
            }

            System.out.print("Digite o número da tarefa que deseja excluir: ");
            Scanner ler = new Scanner(System.in);
            int indice = ler.nextInt();
            if (indice >= 0 && indice < tarefas.size()) {
                Tarefa removida = tarefas.remove(indice);
                salvarTarefasNoArquivo(tarefas);
                System.out.println("Tarefa \"" + removida.getNome() + "\" excluída com sucesso.");
            } else {
                System.out.println("Índice inválido.");
            }

        } catch (IOException e) {
            System.out.println("Erro ao acessar o arquivo de tarefas: " + e.getMessage());
        }
    }
    
    private List<Tarefa> carregarTarefas() throws IOException {
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
