import java.util.Scanner;

public class Main {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Bem vindo a Enigma!");
        System.out.print("Você deseja codificar ou decodifocar? (c/d): ");
        String escolha = scanner.nextLine().trim().toUpperCase();

        System.out.print("Digite o texto: ");
        String texto = scanner.nextLine();

        if (escolha.equals("c") || escolha.equals("C")){
            Codificador.resetRotores();
            String codificado = Codificador.codificar(texto);
            System.out.println("Texto codificado: " + codificado);
        } else if (escolha.equals("d") ||  escolha.equals("D")){
            Decodificador.resetRotores();
            String decodificado = Decodificador.decodificador(texto);
            System.out.println("Texto decodificado: " + decodificado);
        } else {
            System.out.println("Opção inválida. Por favor, escolha 'c' ou 'd'.");
        }
        scanner.close();
    }
}
