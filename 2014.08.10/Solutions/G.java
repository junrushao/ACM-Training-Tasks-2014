// Java solution for problem G
// Author: Grzegorz Guspiel

import java.io.*;
import java.util.*;

class Util {
    static final int INF = 1100100100;
    static void out(String s) { System.out.println(s); }
}

class IntReader {
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer tokenizer = new StringTokenizer("");

    int next() throws IOException {
        while (!tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return Integer.parseInt(tokenizer.nextToken());
    }
}

class MinTree {
    int s;
    int[] t;
    int[] where;
    int neutral;
    MinTree(int n) {
        s = 1;
        while (s <= n + 1) s *= 2;
        neutral = 2 * s - 1;
        t = new int[s * 2];
        where = new int[s * 2];
        for (int i = s; i < 2 * s; i++) t[i] = Util.INF;
        for (int i = s; i < 2 * s; i++) where[i] = i;
        for (int i = s - 1; i >= 0; i--) tupdStep(i);
    }
    void tupdStep(int a) {
        if (t[2 * a] < t[2 * a + 1]) {
            where[a] = where[2 * a];
            t[a] = t[2 * a];
        } else {
            where[a] = where[2 * a + 1];
            t[a] = t[2 * a + 1];
        }
    }
    void tupd(int a) {
        if (a == 0) return;
        tupdStep(a);
        tupd(a / 2);
    }
    void update(int a, int b) {
        t[s + a] = b;
        tupd((s + a) / 2);
    }
    int better(int a, int b) {
        if (t[a] < t[b]) return a;
        else return b;
    }
    int tquery(int a, int b) {
        if (a > b) return neutral;
        if (a == b) return where[a];
        int r = neutral;
        if (a % 2 == 1) r = better(r, where[a++]);
        if (b % 2 == 0) r = better(r, where[b--]);
        r = better(r, tquery(a / 2, b / 2));
        return r;
    }
    int queryWhere(int a, int b) {
        return tquery(a + s, b + s) - s;
    }
}

class Interval {
    final int a, b;
    boolean processed;
    boolean infected;
    int where;

    Interval(int a, int b) {
        this.a = a;
        this.b = b;
    }
}

class ByIncreasingRightEnds implements Comparator<Interval> {
    @Override
    public int compare(Interval i1, Interval i2) {
        if (i1.b == i2.b) return i1.a - i2.a; // we want a total order and intervals are distinct
        else return i1.b - i2.b;
    }
}

class ByIncreasingLeftEnds implements Comparator<Interval> {
    @Override
    public int compare(Interval i1, Interval i2) {
        if (i1.a == i2.a) return i1.b - i2.b;
        else return i1.a - i2.a;
    }
}

class Tree {
    int s;
    int[] min;
    int[] plus;
    int[] where;

    Tree(int n) {
        s = 1;
        while (s <= n + 1) s *= 2;
        min = new int[2 * s];
        plus = new int[2 * s];
        where = new int[2 * s];
        for (int i = s; i < 2 * s; i++) {
            min[i] = 0;
            plus[i] = 3;
            where[i] = i;
        } 
        for (int i = 0; i < n; i++) plus[s + 1 + i] = i + 1;
        for (int i = s - 1; i >= 0; i--) restore(i);
    }

    void restore(int a) {
        int l = min[2 * a] + plus[2 * a];
        int r = min[2 * a + 1] + plus[2 * a + 1];
        if (l <= r) { // prefer left!
            min[a] = l;
            where[a] = where[2 * a];
        } else {
            min[a] = r;
            where[a] = where[2 * a + 1];
        }
    }

    void add(int a, int b, int v) {
        a += s + 1; b += s + 1;
        a--; b++;
        while (b - a > 1) {
            if (a % 2 == 0) plus[a + 1] += v;
            if (b % 2 == 1) plus[b - 1] += v;
            a /= 2; b /= 2;
            restore(a); restore(b);
        }
        while (b - a > 0) {
            a /= 2; b /= 2;
            restore(a); restore(b);
        }
        while (a != 1) {
            a /= 2;
            restore(a);
        }
    }

    int minValue() { return min[1] + plus[1]; }
    int minWhere() { return where[1] - s - 1; }
}

class Solver {
    final int n;
    final int k;
    final ArrayList<Interval> intervals;

    Solver(int k, ArrayList<Interval> intervals) {
        this.n = intervals.size();
        this.k = k;
        this.intervals = intervals;
    }

    Interval peekNotProcessed(PriorityQueue<Interval> q) {
        while (q.peek() != null && q.peek().processed) q.poll();
        return q.peek();
    }

    int bOrInf(Interval i) { 
        if (i == null) return Util.INF;
        else return i.b;
    }

    ArrayList<Interval> possible() {
        // allocate containers
        for (Interval interval : intervals) {
            interval.processed = false;
            interval.infected = false;
            interval.where = n;
        }
        ArrayList<PriorityQueue<Interval>> containers = new ArrayList<PriorityQueue<Interval>>();
        for (int i = 0; i < n; i++){
            containers.add(new PriorityQueue<Interval>(1, new ByIncreasingRightEnds()));
        }
        PriorityQueue<Interval> globalContainer = new PriorityQueue<Interval>(n, new ByIncreasingRightEnds());
        PriorityQueue<Interval> toInfect = new PriorityQueue<Interval>(n, new ByIncreasingLeftEnds());
        Tree tree = new Tree(n);
        MinTree minTree = new MinTree(n);

        // fill containers
        for (Interval interval : intervals) {
            globalContainer.add(interval);
            toInfect.add(interval);
        }

        // solve
        int currentContainer = 0;
        ArrayList<Interval> result = new ArrayList<Interval>();
        for (int i = 0; i < n; i++) {
            Interval chosen = null;

            if (tree.minValue() < 0) {
                return null;
            } else if (tree.minValue() == 0) {
                int maxWhere = tree.minWhere();
                int where = minTree.queryWhere(0, maxWhere);
                peekNotProcessed(containers.get(where));
                chosen = containers.get(where).poll();
            } else {
                peekNotProcessed(globalContainer);
                chosen = globalContainer.poll();
            }

            chosen.processed = true;
            result.add(chosen);

            if (chosen.infected) {
                minTree.update(chosen.where, bOrInf(peekNotProcessed(containers.get(chosen.where))));
                Interval j = containers.get(chosen.where).peek();
                tree.add(chosen.where, n - 1, 1);
            }
        
            while (toInfect.size() > 0) {
                if (toInfect.peek().processed) {
                    toInfect.poll();
                } else if (toInfect.peek().a <= chosen.b) {
                    if (k == 0) {
                        return null;
                    }
                    Interval infectee = toInfect.poll();
                    // infect it!
                    int where = i + k;
                    if (where < n) {
                        infectee.infected = true;
                        infectee.where = where;
                        containers.get(where).add(infectee);
                        minTree.update(where, bOrInf(peekNotProcessed(containers.get(where))));
                        tree.add(where, n - 1, -1);
                    }
                } else {
                    break;
                }
            }
       
            tree.add(i + 1, n - 1, -1);
        }
        return result;
    }
}

public class g {
    static IntReader reader = new IntReader();

    ArrayList<Interval> intervals = new ArrayList<Interval>();

    void solve() throws IOException {
        int n = reader.next();
        for (int i = 0; i < n; i++) {
            int a = reader.next();
            int b = reader.next();
            intervals.add(new Interval(a, b));
        }

        int b = 0;
        int e = n;
        while (b < e) {
            int s = (b + e) / 2;
            if (new Solver(s, intervals).possible() != null) e = s;
            else b = s + 1; 
        }
        int result = b;

        ArrayList<Interval> proof = new Solver(result, intervals).possible();
        Util.out("" + result);
        for (Interval interval : proof) {
            Util.out(interval.a + " " + interval.b);
        }
    }

    public static void main(String[] args) throws IOException {
        int z = reader.next();
        for (int zz = 0; zz < z; zz++) {
            new g().solve();
        }
    }
} // class g
