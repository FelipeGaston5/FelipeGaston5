package repository;

import model.Cliente;

import java.util.ArrayList;
import java.util.List;

public class ClienteRepository {
    private static final List<Cliente> clientes = new ArrayList<>();

    public static void adicionar(Cliente cliente) {
        clientes.add(cliente);
    }

    public static Cliente buscarPorCpf(String cpf) {
        for (Cliente c : clientes) {
            if (c.getCpf().equals(cpf)) {
                return c;
            }
        }
        return null;
    }

    public static List<Cliente> listarTodos() {
        return new ArrayList<>(clientes); // Retorna cópia da lista
    }
}
