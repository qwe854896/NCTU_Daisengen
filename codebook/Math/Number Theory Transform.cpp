//(2^16)+1, 65537, 3
//7*17*(2^23)+1, 998244353, 3
//1255*(2^20)+1, 1315962881, 3
//51*(2^25)+1, 1711276033, 29
template<int MAXN, LL P, LL RT> //MAXN must be 2^k
struct NTT {
  LL w[MAXN];
  LL mpow(LL a, LL n);
  LL minv(LL a) { return mpow(a, P - 2); }
  NTT() {
    LL dw = mpow(RT, (P - 1) / MAXN);
    w[0] = 1;
    for (int i = 1; i < MAXN; ++i) w[i] = w[i - 1] * dw % P;
  }
  void bitrev(LL *a, int n) {
    for (int i = 1, j = 0; i < n; ++i) {
			for (int l = n >> 1; (j ^= l) < l; l >>= 1);
			if (i > j) swap(a[i], a[j]);
		}
  }
  void operator()(LL *a, int n, bool inv = false) { //0 <= a[i] < P
    bitrev(a, n);
    for (int L = 2; L <= n; L <<= 1) { // block size
      int dx = MAXN / L, dl = L >> 1;
      for (int i = 0; i < n; i += L) { // block start
        for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
          LL z = a[j + dl] * w[x] % P;
          if ((a[j + dl] = a[j] - z) < 0) a[j + dl] += P;
          if ((a[j] += z) >= P) a[j] -= P;
        }
      }
    }
    if (inv) {
      reverse(a + 1, a + n);
      LL invn = minv(n);
      for (int i = 0; i < n; ++i) a[i] = a[i] * invn % P;
    }
  }
};
