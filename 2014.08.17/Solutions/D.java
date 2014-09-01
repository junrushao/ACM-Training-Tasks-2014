import java.util.*;
import java.math.*;
import java.io.*;

public class Main
{
	Scanner cin;
	void solve() {
		int k = cin.nextInt();
		int n = cin.nextInt();
		BigInteger a[][] = new BigInteger[n + 1][k + 1];
		for(int i = 0; i <= n; ++ i) {
			for(int j = 0; j <= k; ++ j) {
				a[i][j] = BigInteger.ZERO;
			}
		}
		a[0][0] = BigInteger.ONE;
		for(int i = 0; i < n; ++ i) {
			for(int j = 0; j <= k; ++ j) {
				if (j < k) {
					a[i + 1][j + 1] = a[i + 1][j + 1].add(a[i][j].multiply(BigInteger.valueOf(k - j)));
				}
				if (j > 0) {
					a[i + 1][j] = a[i + 1][j].add(a[i][j].multiply(BigInteger.valueOf(j)));
				}
			}
		}
		System.out.println(a[n][k]);
	}
	void run() {
		cin = new Scanner(new BufferedInputStream(System.in));
		solve();
	}
	public static void main(String args[]) {
		new Main().run();
	}
}
