package repository;

import model.Conta;

import java.util.ArrayList;
import java.util.List;

public class ContaRepository {
    private static final List<Conta> contas = new ArrayList<>();
    private static int contadorNumeroConta = 1001;

    public static void adicionar(Conta conta) {
        contas.add(conta);
    }

    public static Conta buscarPorNumero(int numero) {
        for (Conta c : contas) {
            if (c.getNumero() == numero) {
                return c;
            }
        }
        return null;
    }

    public static int gerarNumeroConta() {
        return contadorNumeroConta++;
    }

    public static List<Conta> listarTodas() {
        return new ArrayList<>(contas);
    }
}
