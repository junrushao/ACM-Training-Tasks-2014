
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Main {

	int t, a, b;
	final static BigInteger limit = BigInteger.TEN.pow(100);

	public boolean solve() {
		try {
			t = nextInt();
			a = nextInt();
			b = nextInt();
		}
		catch (RuntimeException e) {
			return false;
		}
		String expression = "(" + t + "^" + a + "-1)/(" + t + "^" + b + "-1) ";
		out.print(expression);
		if (t == 1) {
			out.println("is not an integer with less than 100 digits.");
			return true;
		}
		if (a < b) {
			out.println("is not an integer with less than 100 digits.");
			return true;
		}
		if (a == b) {
			out.println("1");
			return true;
		}
		// a > b
		if (a % b != 0) {
			out.println("is not an integer with less than 100 digits.");
			return true;
		}
		// a % b = 0
		{
			double res = Math.log10(t) * (double)(a - b);
			if (res > 101) {
				out.println("is not an integer with less than 100 digits.");
				return true;
			}
		}
		BigInteger T = BigInteger.ONE;
		BigInteger ans = BigInteger.ZERO;
		BigInteger q = BigInteger.valueOf(t).pow(b);
		for (int i = 0; i < a; i += b) {
			ans = ans.add(T);
			if (ans.compareTo(limit) > 0) {
				out.println("is not an integer with less than 100 digits.");
				return true;
			}
			T = T.multiply(q);
		}
		out.println(ans.toString());
		return true;
	}

	public void run() {
		tokenizer = null;
		reader = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);
		while ( solve() );
		out.close();
	}

	public static void main(String[] args) {
		new Main().run();
	}

	public StringTokenizer tokenizer;
	public BufferedReader reader;
	public PrintWriter out;

	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			}
			catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}

	public int nextInt() {
		return Integer.parseInt(next());
	}

	public BigInteger nextBigInteger() {
		return new BigInteger(next());
	}
}
