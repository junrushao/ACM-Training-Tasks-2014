import java.util.*;
import java.io.*;
import java.math.*;

public class Main{
	public static BigInteger work(Scanner in) {
		int n = in.nextInt();
		int m = in.nextInt();
		String[] a = new String[500];
		for (int i = n; i >= 1; --i)
			a[i] = in.next();
		BigInteger ret = BigInteger.valueOf(0);
		BigInteger[][] g = new BigInteger[500][500];
		g[1][1] = BigInteger.valueOf(1);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
			{
				if (i == 1 && j == 1) continue;
				if (j == 1)
					g[i][j] = g[i - 1][j].multiply(BigInteger.valueOf(3));
				else
					g[i][j] = g[i][j - 1].multiply(BigInteger.valueOf(2));
			}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				if (a[i].charAt(j - 1) == '#')
					ret = ret.add(g[i][j]);
		return ret;
	}

	public static void main(String args[]) {
		Scanner in = new Scanner(System.in);
		if (work(in).equals(work(in)))
			System.out.println("Yes");
		else
			System.out.println("No");
	}
}

