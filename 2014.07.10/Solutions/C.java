import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    static int N = 28;
    static int M = 14;
    static int[] PRIMES = {2, 3, 5, 7, 11, 13};

    static String[] ANSWERS = {"",
        "1",
        "2",
        "6",
        "12",
        "72",
        "72",
        "864",
        "1728",
        "13824",
        "22032",
        "555264",
        "476928",
        "17625600",
        "29599488",
        "321115392",
        "805146624",
        "46097049600",
        "36481536000",
        "2754120268800",
        "3661604352000",
        "83905105305600",
        "192859121664000",
        "20092043520000000",
        "15074060547686400",
        "1342354557616128000",
        "3016995034075545600",
        "143424493149899980800",
        "268367392739686809600"};

    public void run() {
        //int maskCount = 0;
        //int[] masks = new int[M];
        //int[] count = new int[M];
        //for (int i = 1; i <= N; ++ i) {
        //    int mask = 0;
        //    for (int j = 0; j < PRIMES.length; ++ j) {
        //        if (i % PRIMES[j] == 0) {
        //            mask |= 1 << j;
        //        }
        //    }
        //    int index = 0;
        //    while (index < maskCount && masks[index] != mask) {
        //        index ++;
        //    }
        //    if (index == maskCount) {
        //        masks[maskCount] = mask;
        //        count[maskCount ++] = 1;
        //    }
        //    count[index] ++;
        //}
        //int[] base = new int[M + 1];
        //base[0] = 1;
        //for (int i = 0; i < M; ++ i) {
        //    base[i + 1] = base[i] * count[i];
        //}
        //BigInteger[][] ways = new BigInteger[base[M]][M];
        //Arrays.fill(ways[0], BigInteger.ZERO);
        //ways[0][0] = BigInteger.ONE;
        //for (int mask = 1; mask < base[M]; ++ mask) {
        //    for (int i = 0; i < M; ++ i) {
        //        BigInteger result = BigInteger.ZERO;
        //        BigInteger remainder = BigInteger.valueOf(mask / base[i] % count[i]);
        //        if (remainder.signum() > 0) {
        //            int newMask = mask - base[i];
        //            for (int j = 0; j < M; ++ j) {
        //                if (newMask == 0 || (masks[i] & masks[j]) == 0) {
        //                    result = result.add(ways[newMask][j].multiply(remainder));
        //                }
        //            }
        //        }
        //        ways[mask][i] = result;
        //    }
        //}
        //for (int n = 1, now = 0; n <= N; ++ n) {
        //    int mask = 0;
        //    for (int j = 0; j < PRIMES.length; ++ j) {
        //        if (n % PRIMES[j] == 0) {
        //            mask |= 1 << j;
        //        }
        //    }
        //    int index = 0;
        //    while (index < maskCount && masks[index] != mask) {
        //        index ++;
        //    }
        //    now += base[index];
        //    BigInteger result = BigInteger.ZERO;
        //    for (int i = 0; i < M; ++ i) {
        //        result = result.add(ways[now][i]);
        //    }
        //    System.err.println(String.format("\"%d\", ", result));
        //}
        try {
            int tests = reader.nextInt();
            while (tests > 0) {
                tests --;
                int n = reader.nextInt();
                int m = reader.nextInt();
                writer.println(new BigInteger(ANSWERS[n]).mod(BigInteger.valueOf(m)));
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