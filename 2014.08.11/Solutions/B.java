import java.math.*;
import java.io.*;
import java.util.*;

public class Main {

	static BigInteger[][] c = new BigInteger[105][105];

	static void init() {
		for (int i = 0; i <= 100; ++i) {
			c[i][0] = c[i][i] = BigInteger.ONE;
			for (int j = 1; j < i; ++j) {
				c[i][j] = c[i - 1][j - 1].add(c[i - 1][j]);
			}
		}
	}

	static public void main(String args[]) {
		init();
		Scanner input = new Scanner(System.in);
		while (input.hasNext()) {
			BigInteger n = input.nextBigInteger();
			int d = input.nextInt();
			BigInteger a = c[d][2].multiply(n.add(BigInteger.valueOf(4)).pow(2)),
					   b = n.pow(d).multiply(BigInteger.valueOf(9)),
					   g = a.gcd(b);
			a = a.divide(g); 
			b = b.divide(g);
			if (b.compareTo(BigInteger.ONE) == 0) {
				System.out.println("1");
			} else {
				System.out.println(a + "/" + b);
			}
		}
	}
}
