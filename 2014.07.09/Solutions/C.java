import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    void run() throws Exception {
        BigInteger[] val = new BigInteger[10];
        Arrays.fill(val, BigInteger.ONE);
        String s;
        for (;;) {
            if ((s = reader.readLine()) == null) break;
            if ((int)s.length() == 0) break;
            char op = s.charAt(1);
            int x = (int)(s.charAt(0) - 'A'), y;
            if (op == '+') {
                y = (int)(s.charAt(3) - 'A');
                val[x] = val[x].add(val[y]);
            } else if (op == '*') {
                y = (int)(s.charAt(3) - 'A');
                val[x] = val[x].multiply(val[y]);
            } else {
                y = (int)(s.charAt(2) - 'A');
                val[x] = val[y];
            }
        }
        for (int i = 0; i < 10; ++i) writer.println(val[i]);
        reader.close();
        writer.close();
    }

    public static void main(String[] args) throws Exception {
        (new Main()).run();
    }

    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter writer = new PrintWriter(System.out);
    StringTokenizer tokenizer = null;

    String next() throws Exception {
        for (; tokenizer == null || !tokenizer.hasMoreTokens(); ) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

    int nextInt() throws Exception {
        return Integer.parseInt(next());
    }
}
