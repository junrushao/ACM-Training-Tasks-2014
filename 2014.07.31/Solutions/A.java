import java.io.*;
import java.util.*;
import java.math.*;

public class Main{

	final int maxn = 250;
	int[] sum = new int[maxn];
	BigInteger C[][] = new BigInteger[maxn][maxn];
	BigInteger f[][] = new BigInteger[maxn][maxn];

	void run(){
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), m = in.nextInt(), k = in.nextInt();
		for (int i = 0; i <= 200; ++i) sum[i] = 0;
		for (int i = 0; i < n; ++i){
			int x = in.nextInt();
			++sum[x];
		}
		for (int i = 0; i < maxn; ++i){
//			C[i] = new BigInteger[maxn];
//			f[i] = new BigInteger[maxn];
			for (int j = 0; j < maxn; ++j){
				f[i][j] = BigInteger.ZERO;
				C[i][j] = BigInteger.ZERO;
			}
		}
		for (int i = 0; i <= 200; ++i)
			C[i][0] = BigInteger.valueOf(1);
		for (int i = 1; i <= 200; ++i)
			for (int j = 1; j <= 200; ++j){
				C[i][j] = C[i - 1][j - 1].add(C[i - 1][j]);
			}
		f[0][0] = BigInteger.valueOf(1);
		for (int i = 1; i <= 200; ++i)
			for (int j = 0; j <= k; ++j)
				for (int kk = 0; kk <= sum[i]; ++kk){
					if (kk > j) break;
					f[i][j] = f[i][j].add(f[i - 1][j - kk].multiply(C[j][kk]));
				}
		System.out.println(f[200][k]);
	}

	public static void main(String args[]){
		new Main().run();
	}
}
