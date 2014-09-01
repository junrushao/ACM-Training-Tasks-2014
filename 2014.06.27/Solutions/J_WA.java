import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Main {
	BigInteger ZERO = BigInteger.ZERO;
	BigInteger ONE = BigInteger.ONE;

	long Gcd(long a, long b) {
		long c;
		for ( ; ; ) {
			c = a % b;
			if (c == 0) break;
			a = b;
			b = c;
		}
		return b;
	}
	
	BigInteger floorDivide(BigInteger a, BigInteger b) {
		BigInteger res[] = a.divideAndRemainder(b);
		if (res[1].compareTo(ZERO) < 0)
			return res[0].subtract(ONE);
		return res[0];
	}
	
	BigInteger ceilDivide(BigInteger a, BigInteger b) {
		BigInteger res[] = a.divideAndRemainder(b);
		if (res[1].compareTo(ZERO) > 0)
			return res[0].add(ONE);
		return res[0];
	}

	BigInteger[] ExGcd(long a, long b) {
		if (b == 1)
			return new BigInteger[]{ZERO, ONE};
		BigInteger[] res = ExGcd(b, a % b);
		BigInteger x = res[0], y = res[1];
		return new BigInteger[]{ y.negate(), x.negate().subtract(BigInteger.valueOf(a / b).multiply(y)) };
		// -y, -x - [a / b] * y
	}
	
	long N1, F1, D1, N2, F2, D2;
	
	BigInteger[] doExGcd(long a, long b, long v) {
		BigInteger res[] = null;
		
		if (v == 0) res = new BigInteger[]{ZERO, ZERO};
		else {
			long gcd = Gcd(a, b);
			a /= gcd;
			b /= gcd;
			if (v % gcd != 0)
				return null;
			v /= gcd;
			res = ExGcd(a, b);
		}
		res[0] = res[0].multiply(BigInteger.valueOf(v));
		res[1] = res[1].multiply(BigInteger.valueOf(v));
		
		BigInteger x0 = res[0], y0 = res[1];
		BigInteger l1 = ceilDivide(x0.negate(), BigInteger.valueOf(b));
		BigInteger r1 = floorDivide(BigInteger.valueOf(N1).subtract(x0), BigInteger.valueOf(b));
		BigInteger l2 = ceilDivide(y0.negate(), BigInteger.valueOf(a));
		BigInteger r2 = floorDivide(BigInteger.valueOf(N2).subtract(y0), BigInteger.valueOf(a));
		BigInteger maxLeft = l1.min(l2);
		BigInteger minRight = r1.min(r2);
//		System.err.println("[L, R] = " + maxLeft + "," + minRight);
		out.println(minRight.subtract(maxLeft).add(ONE));
		return res;
	}
	
	void solve() {
		N1 = nextLong() - 1; F1 = nextLong(); D1 = nextLong();
		N2 = nextLong() - 1; F2 = nextLong(); D2 = nextLong();
//		out.println("D2 = " + D2);
		if (D1 == D2) {
			if ((F2 - F1) % D1 != 0) {
				out.println(0);
				return;
			}
			BigInteger maxLeft = BigInteger.valueOf( Math.max(F1, F2) );
			BigInteger r1 = BigInteger.valueOf(N1).multiply(BigInteger.valueOf(D1)).add(BigInteger.valueOf(F1));
			BigInteger r2 = BigInteger.valueOf(N2).multiply(BigInteger.valueOf(D2)).add(BigInteger.valueOf(F2));
			BigInteger minRight = r1.min(r2);
			out.println(minRight.subtract(maxLeft).divide(BigInteger.valueOf(D1)).add(ONE));
			return;
		}
		BigInteger res[] = doExGcd(D1, D2, F2 - F1);
		
		if (res == null) {
			out.println(0);
			return;
		}
//		out.flush();
	}

	public void run() {
		tokenizer = null;
		reader = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);

		int T = nextInt();
		for (int Case = 1; Case <= T; ++Case)
			solve();

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

	public long nextLong() {
		return Long.parseLong(next());
	}

	public BigInteger nextBigInteger() {
		return new BigInteger(next());
	}
}

