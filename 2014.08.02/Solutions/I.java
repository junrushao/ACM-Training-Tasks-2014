import java.io.*;
import java.util.*;
import java.math.*;

public class Main{

	final BigInteger TWO = BigInteger.valueOf(2);
	final BigInteger ONE = BigInteger.valueOf(1);

	void run(){
		Scanner in = new Scanner(System.in);
		BigInteger n = in.nextBigInteger();
		BigInteger ans = BigInteger.valueOf(0);
		for (BigInteger now = ONE; now.compareTo(n) < 0; now = now.multiply(TWO)){
			BigInteger len = now.multiply(TWO);
			BigInteger num = n.add(ONE).divide(len), res = n.mod(now), R = n.add(ONE).mod(len);
			if (n.divide(now).mod(TWO).compareTo(ONE) == 0){
				BigInteger tmp = res.add(ONE).multiply(TWO);
				ans = ans.add(tmp.multiply(num).multiply(now));
				if (R.compareTo(res.add(ONE)) <= 0){
					ans = ans.add(R.multiply(now));
				} else if (R.compareTo(now) <= 0){
					ans = ans.add(res.add(ONE).multiply(now));
				} else if (R.compareTo(now.add(res.add(ONE))) <= 0){
					ans = ans.add(R.add(res).add(ONE).subtract(now).multiply(now));
				} else {
					ans = ans.add(res.add(ONE).multiply(TWO).multiply(now));
				}
				ans = ans.subtract(now.multiply(TWO));
			} else {
				BigInteger tmp = now.subtract(res.add(ONE)).multiply(TWO);
				ans = ans.add(tmp.multiply(num).multiply(now));
				if (R.compareTo(res.add(ONE)) <= 0){
				} else if (R.compareTo(now) <= 0){
					ans = ans.add(R.subtract(res.add(ONE)).multiply(now));
				} else if (R.compareTo(res.add(ONE).add(now)) <= 0){
					ans = ans.add(now.subtract(res.add(ONE)).multiply(now));
				} else {
					ans = ans.add(R.subtract(res.add(ONE).multiply(TWO)).multiply(now));
				}
			}
		}
		System.out.println(ans);
	}

	public static void main(String args[]){
		new Main().run();
	}
}
