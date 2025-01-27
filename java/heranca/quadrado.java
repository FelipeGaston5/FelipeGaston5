public class quadrado extends figura{

    private int lado;

    public int getLado(int lado){
        return lado;
    }

    public void setLado(int lado){
        this.lado = lado;
    }

    public quadrado(int x, int y, int lado){
        super(x,y);

        this.lado = lado;
    }

    public void desenhar(){

        System.out.println("<<<---> Quadrado <--->>>");
        System.out.println("X: " + getX());
        System.out.println("Y: " + getY());
        System.out.println("Lado: " + lado);
    }

}