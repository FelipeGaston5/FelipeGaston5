package service;

import model.Transacao;
import model.Conta;

import java.util.ArrayList;
import java.util.List;

public class TransacaoService {
    private static final List<Transacao> transacoes = new ArrayList<>();

    public void registrarTransacao(String tipo, double valor, Conta conta) {
        Transacao t = new Transacao(tipo, valor, conta);
        transacoes.add(t);
    }

    public List<Transacao> listarPorConta(Conta conta) {
        List<Transacao> resultado = new ArrayList<>();
        for (Transacao t : transacoes) {
            if (t.getConta().equals(conta)) {
                resultado.add(t);
            }
        }
        return resultado;
    }
}
