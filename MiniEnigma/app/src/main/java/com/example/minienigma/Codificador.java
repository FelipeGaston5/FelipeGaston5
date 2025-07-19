package com.example.minienigma;

public class Codificador {
    static int[] rotores = { 3, 1, 4 };

    public static void setRotores(int r1, int r2, int r3) {
        rotores = new int[]{r1, r2, r3};
    }


    public static String codificar(String texto) {
        StringBuilder resultado = new StringBuilder();

        for (int i = 0; i < texto.length(); i++) {
            char c = texto.charAt(i);

            if (Character.isLetter(c)) {
                boolean isUpper = Character.isUpperCase(c);
                c = Character.toLowerCase(c);

                int deslocamento = (rotores[0] + rotores[1] + rotores[2]) % 26;
                char codificado = (char) ('a' + (c - 'a' + deslocamento) % 26);

                resultado.append(isUpper ? Character.toUpperCase(codificado) : codificado);

                avancaRotores();

            } else {
                resultado.append(c);
            }
        }

        return resultado.toString();
    }

    private static void avancaRotores() {
        rotores[0]++;
        if (rotores[0] >= 26) {
            rotores[0] = 0;
            rotores[1]++;
            if (rotores[1] >= 26) {
                rotores[1] = 0;
                rotores[2]++;
                if (rotores[2] >= 26) {
                    rotores[2] = 0;
                }
            }
        }
    }

    public static void resetRotores() {
        rotores = new int[]{ 3, 1, 4 };
    }
}
