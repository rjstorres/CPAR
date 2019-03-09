import java.util.Scanner;
public class MatrixProduct1 {

    public static void OnMult(int n_a, int n_b)
    {

        double temp;
        int i, j, k;
        int c_lin = n_a;
        int c_col = n_b;

        //Create arrays
        double a[] = new double[n_a*n_a];
        double b[] = new double[n_b*n_b];
        double c[] = new double[c_lin*c_col];

        //Initialize array a
        for(i=0; i<n_a*n_a; i++)
            a[i] = (double)1.0;

        //Initialize array b
        for(i=0; i<n_b*n_b; i++)
            b[i] = (double)(i+1);

        long start= System.currentTimeMillis();
        //Matrix Multiplication
        for(i=0; i<n_a; i++)
            for( j=0; j<n_b; j++) {
                temp = 0;
                for( k=0; k<n_a; k++)
                    temp += a[i*n_a+k] * b[k*n_b+j];
                c[i*n_a+j]=temp;
            }
        long end= System.currentTimeMillis();
        //Print Result Matrix
        System.out.println("Result matrix:");
        for(i=0; i< Math.min(c_lin*c_col, 10); i++)
            System.out.print(c[i] + " ");
        System.out.println();

        System.out.println("\nTime MULT: %l");
        System.out.println(end-start);

    }

    public static void OnMultLine(int n_a, int n_b){
        int i, j, k;
        int c_lin = n_a;
        int c_col = n_b;

        //Create arrays
        double a[] = new double[n_a*n_a];
        double b[] = new double[n_b*n_b];
        double c[] = new double[c_lin*c_col];

        //Initialize array a
        for(i=0; i<n_a*n_a; i++)
            a[i] = (double)1.0;

        //Initialize array b
        for(i=0; i<n_b*n_b; i++)
            b[i] = (double)(i+1);

        //Initialize array c
        for(i=0; i<c_lin*c_col; i++)
            c[i] = (double)0.0;

        //Matrix multiplication
        for(i=0; i<n_a; i++)
            for( k=0; k<n_b; k++)
                for( j=0; j<n_b; j++)
                    c[i*n_a+j] += a[i*n_a+k] * b[k*n_b+j];

        //Print Result Matrix
        System.out.println("Result matrix:");
        for(i=0; i< Math.min(c_lin*c_col, 10); i++)
            System.out.print(c[i] + " ");
        System.out.println();
    }

    public static void main (String [] args) throws java.lang.InterruptedException
    {
        int op=1;
        do {
            System.out.println("\n1. Multiplication");
            System.out.println("\n2. Line Multiplication");
            System.out.println("Selection?: ");

            Scanner in = new Scanner(System.in);
            op = in.nextInt();

            if (op == 0)
                break;

            System.out.println("Dimensions: lins cols ?");

            int lin, col;
            lin= in.nextInt();
            col= in.nextInt();


            long start= System.currentTimeMillis();

            switch (op){
                case 1:
                    OnMult(lin, col);
                    break;
                case 2:
                    OnMultLine(lin, col);
                    break;
            }

            long end= System.currentTimeMillis();
            System.out.println("\nTime: %l");
            System.out.println(end-start);



        }while (op != 0);

    }
}
