package model;

public class Usuario {
    private String login;
    private String senha;
    private Cliente cliente;

    public Usuario(String login, String senha, Cliente cliente) {
        this.login = login;
        this.senha = senha;
        this.cliente = cliente;
    }

    public String getLogin() {
        return login;
    }

    public String getSenha() {
        return senha;
    }

    public Cliente getCliente() {
        return cliente;
    }

    public boolean autenticar(String login, String senha) {
        return this.login.equals(login) && this.senha.equals(senha);
    }
}
