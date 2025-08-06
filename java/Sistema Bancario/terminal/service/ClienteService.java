package service;

import model.Cliente;
import repository.ClienteRepository;

public class ClienteService {

    public boolean cadastrarCliente(Cliente cliente) {
        if (ClienteRepository.buscarPorCpf(cliente.getCpf()) != null) {
            return false; // Cliente já existe
        }
        ClienteRepository.adicionar(cliente);
        return true;
    }

    public Cliente buscarPorCpf(String cpf) {
        return ClienteRepository.buscarPorCpf(cpf);
    }
}
