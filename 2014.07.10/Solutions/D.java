import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    static int COUNT = 100;

    public void run() {
        try {
            int tests = reader.nextInt();
            while (tests > 0) {
                tests --;
                int n = reader.nextInt();
                int all = (n + 1) * n / 2;
                long[][][] ways = new long[n + 2][all + 1][2];
                ways[0][0][0] = 1;
                for (int i = 0; i <= n; ++ i) {
                    for (int j = 0; j <= all; ++ j) {
                        for (int parity = 0; parity < 2; ++ parity) {
                            if (ways[i][j][parity] > 0) {
                                for (int ii = i; ii <= n; ++ ii) {
                                    int length = ii - i;
                                    ways[ii + 1][j + (length + 1) * length / 2][parity ^ 1] += ways[i][j][parity];
                                }
                            }
                        }
                    }
                }
                BigDecimal result = BigDecimal.ONE;
                for (int j = 0; j < all; ++ j) {
                    for (int parity = 0; parity < 2; ++ parity) {
                        BigDecimal p = BigDecimal.valueOf(j).divide(BigDecimal.valueOf(all), COUNT, BigDecimal.ROUND_HALF_EVEN);
                        BigDecimal r = p.divide(BigDecimal.ONE.subtract(p), COUNT, BigDecimal.ROUND_HALF_EVEN).multiply(BigDecimal.valueOf(ways[n + 1][j][parity]));
                        if (parity == 0) {
                            result = result.add(r);
                        } else {
                            result = result.subtract(r);
                        }
                    }
                }
                result = result.setScale(15, BigDecimal.ROUND_HALF_EVEN);
                writer.println(result.toPlainString());
            }
        } catch (IOException ex) {
        }
        writer.close();
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