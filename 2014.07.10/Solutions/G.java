import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public void run() {
        try {
            int t = reader.nextInt();
            while (t > 0) {
                t --;
                int n = reader.nextInt();
                writer.println(solve(n));
            }
        } catch (IOException ex) {
        }
        writer.close();
    }

    long solve(int n) {
        if (n % 2 == 0) {
            if (n % 4 == 0) {
                return ((long)n * n >> 2) - 1;
            } else {
                int middle = n / 2;
                long maximum = middle;
                for (int i = 0; i <= 2 && i <= middle; ++ i) {
                    maximum = Math.max(maximum, lcm(middle - i, middle + i));
                }
                return maximum;
            }
        } else {
            return (long)(n >> 1) * (n + 1 >> 1);
        }
    }

    long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    long lcm(long a, long b) {
        return a / gcd(a, b) * b;
    }

    Main() {
        reader = new InputReader(System.in);
        writer = new PrintWriter(System.out);
    }

    public static void main(String[] args) {
        new Main().run();
    }

    private static void debug(Object...os) {
        System.err.println(Arrays.deepToString(os));
    }

    private InputReader reader;
    private PrintWriter writer;
}

class InputReader {
    InputReader(InputStream in) {
        reader    = new BufferedReader(new InputStreamReader(in));
        tokenizer = new StringTokenizer("");
    }

    private String next() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            String line = reader.readLine();
            if (line == null) {
                throw new IOException();
            }
            tokenizer = new StringTokenizer(line);
        }
        return tokenizer.nextToken();
    }

    public Integer nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    private BufferedReader  reader;
    private StringTokenizer tokenizer;
}