package java.ED;

public class Array {
    
    public static void main(String[] args) {
        int vet[]; //Declaração de Array

        vet = new int[10]; //Construção de Array

        vet[0] = 10; //Inserir Primeiro valor do Array
        System.out.println(vet[0]); //Mostrar primeiro valor

        for (int i = 0; i<vet.length; i++){
            System.out.println("Vet[" +i+ "] = " + vet[i]); //Percorrendo o Array pelo e vendo quantidades
        }

    }

}
