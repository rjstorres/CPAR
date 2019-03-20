import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class MatrixProduct1 {

    private static final int NUBMBER_OF_RUNS = 10;

    public static Long OnMult(int n_a, int n_b) {

        double temp;
        int i, j, k;
        int c_lin = n_a;
        int c_col = n_b;

        // Create arrays
        double a[] = new double[n_a * n_a];
        double b[] = new double[n_b * n_b];
        double c[] = new double[c_lin * c_col];

        // Initialize array a
        for (i = 0; i < n_a * n_a; i++)
            a[i] = (double) 1.0;

        // Initialize array b
        for (i = 0; i < n_b * n_b; i++)
            b[i] = (double) (i + 1);

        long start = System.nanoTime();
        // Matrix Multiplication
        for (i = 0; i < n_a; i++)
            for (j = 0; j < n_b; j++) {
                temp = 0;
                for (k = 0; k < n_a; k++)
                    temp += a[i * n_a + k] * b[k * n_b + j];
                c[i * n_a + j] = temp;
            }
        long end = System.nanoTime();

        return TimeUnit.NANOSECONDS.toMillis(end - start);

    }

    public static Long OnMultLine(int n_a, int n_b) {
        int i, j, k;
        int c_lin = n_a;
        int c_col = n_b;

        // Create arrays
        double a[] = new double[n_a * n_a];
        double b[] = new double[n_b * n_b];
        double c[] = new double[c_lin * c_col];

        // Initialize array a
        for (i = 0; i < n_a * n_a; i++)
            a[i] = (double) 1.0;

        // Initialize array b
        for (i = 0; i < n_b * n_b; i++)
            b[i] = (double) (i + 1);

        // Initialize array c
        for (i = 0; i < c_lin * c_col; i++)
            c[i] = (double) 0.0;

        long start = System.nanoTime();
        // Matrix multiplication
        for (i = 0; i < n_a; i++)
            for (k = 0; k < n_b; k++)
                for (j = 0; j < n_b; j++)
                    c[i * n_a + j] += a[i * n_a + k] * b[k * n_b + j];

        long end = System.nanoTime();

        return TimeUnit.NANOSECONDS.toMillis(end - start);
    }

    public static Long OnMultBlock(int n_a, int n_b, int blockSize) {
        int i, j, k;
        int c_lin = n_a;
        int c_col = n_b;

        // Create arrays
        double a[] = new double[n_a * n_a];
        double b[] = new double[n_b * n_b];
        double c[] = new double[c_lin * c_col];

        // Initialize array a
        for (i = 0; i < n_a * n_a; i++)
            a[i] = (double) 1.0;

        // Initialize array b
        for (i = 0; i < n_b * n_b; i++)
            b[i] = (double) (i + 1);

        // Initialize array c
        for (i = 0; i < c_lin * c_col; i++)
            c[i] = (double) 0.0;

        int nBlocks = n_a / blockSize;
        int iBase, jBase, kBase;
        long start = System.nanoTime();

        // ALGORITHM
        for (i = 0; i < nBlocks; i++) { // iterate blocks vertically
            iBase = i * blockSize;
            for (j = 0; j < nBlocks; j++) { // iterate blocks horizontally
                jBase = j * blockSize;
                for (k = 0; k < nBlocks; k++) {
                    kBase = k * blockSize;
                    for (int w = 0; w < blockSize; w++) {
                        for (int q = 0; q < blockSize; q++) {
                            for (int e = 0; e < blockSize; e++) {
                                c[(iBase + w) * n_a + kBase + e] += a[(iBase + w) * n_a + (jBase + q)]
                                        * b[(jBase + q) * n_b + kBase + e];
                            }
                        }
                    }
                }
            }
        }

        long end = System.nanoTime();



        return TimeUnit.NANOSECONDS.toMillis(end - start);
    }

    public static void main(String[] args) throws java.lang.InterruptedException, IOException {

        //console();
         benchmark();
    }

    public static void console() {
        int op = 1;
        Scanner in = new Scanner(System.in);
        do {
            System.out.println("\n1. Multiplication");
            System.out.println("\n2. Line Multiplication");
            System.out.println("Selection?: ");

            op = in.nextInt();

            if (op == 0)
                break;

            System.out.println("Dimensions: lins cols ?");

            int lin, col;
            lin = in.nextInt();
            col = in.nextInt();

            long start = System.nanoTime();

            switch (op) {
            case 1:
                OnMult(lin, col);
                break;
            case 2:
                OnMultLine(lin, col);
                break;
            case 3:
                OnMultBlock(lin, col, 128);
                break;
            }

            long end = System.nanoTime();
            System.out.println("\nTime: %l");
            System.out.println(end - start);
            System.gc();
        } while (op != 0);

        in.close();

    }

    public static void benchmark() throws IOException {
        FileWriter writer = new FileWriter("Benchmark.csv");

        writer.append("Algorithm, Run Number, Matrix size, Time, Blocksize,\n");
        System.out.println("Algorithm, Run Number, Matrix size, Time, Blocksize,\n");

       


        for (Integer j = 10000; j <= 10000; j += 2000)
            for (Integer i = 0; i < NUBMBER_OF_RUNS; i++) {
                Double time = OnMultLine(j, j) / 1000.0;
                writer.append("2," + i.toString() + "," + j.toString() + "," + time.toString() + ",\n");
                System.out.println("2," + i.toString() + "," + j.toString() + "," + time.toString() + ",\n");
            }

        for (Integer j = 4000; j <= 10000; j += 2000)
            for (Integer blocksize = 128; blocksize <= 512; blocksize += 64)
                for (Integer i = 0; i < NUBMBER_OF_RUNS; i++) { 
                    Double time = OnMultBlock(j, j, blocksize) / 1000.0;
                    writer.append("3," + i.toString() + "," + j.toString() + "," + time.toString() + "," + blocksize.toString() + ",\n");
                    System.out.println("3," + i.toString() + "," + j.toString() + "," + time.toString() + "," + blocksize.toString() + ",\n");
                }

        writer.flush();
        writer.close();
    }
}