public abstract class figura{
    private int x,y;

    public figura(int xi, int yi){
        x = xi;
        y = yi;
    }

    public int getX(){
        return x;
    }

    public int setX(){
        return this.x = x;
    }

    public int getY(){
        return y;
    }

    public int setY(){
        return this.y = y;
    }

    public abstract void desenhar();
}