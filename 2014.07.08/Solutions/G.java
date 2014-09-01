import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Main {

	final static BigInteger ZERO = BigInteger.ZERO;
	final static BigInteger ONE = BigInteger.ONE;
	final static BigInteger TWO = BigInteger.valueOf(2);
	final static BigInteger TEN = BigInteger.TEN;

	BigInteger H, l, h;
	int T;

	public void run() throws Exception {
		T = nextInt();
		for (int tt = 1; tt <= T; ++tt) {
			H = nextBigInteger();
			l = nextBigInteger();
			h = BigInteger.valueOf(nextInt());
			BigInteger now = ONE.add(H.multiply(H).add(l.multiply(l)).divide(h.multiply(H)));
			BigInteger Sr = ONE;
			for (int i = 1; i <= 500; ++i)
				Sr = Sr.add(now.divide(Sr)).shiftRight(1);
			while(Sr.multiply(Sr).compareTo(now) < 0) Sr = Sr.add(ONE);
			while(Sr.multiply(Sr).compareTo(now) > 0) Sr = Sr.subtract(ONE);
			
			writer.println(Sr.add(ONE).shiftRight(1).toString());
		}
		reader.close();
		writer.close();
	}

	BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
	PrintWriter writer = new PrintWriter(System.out);
	StringTokenizer tokenizer = null;

	String next() throws Exception {
		for (; tokenizer == null || !tokenizer.hasMoreTokens();) {
			tokenizer = new StringTokenizer(reader.readLine());
		}
		return tokenizer.nextToken();
	}

	int nextInt() throws Exception {
		return Integer.parseInt(next());
	}

	BigInteger nextBigInteger() throws Exception {
		return new BigInteger(next());
	}

	public static void main(String args[]) throws Exception {
		(new Main()).run();
	}
}
