int getInside(int n, Point *P) {  // 求多边形P内有多少个整数点
	int OnEdge = n;
	double area = getArea(n, P);
	for (int i = 0; i < n - 1; i++) {
		Point now = P[i + 1] - P[i];
		int y = (int)now.y, x = (int)now.x;
		OnEdge += abs(gcd(x, y)) - 1;
	}
	Point now = P[0] - P[n - 1];
	int y = (int)now.y, x = (int)now.x;
	OnEdge += abs(gcd(x, y)) - 1;
	double ret = area - (double)OnEdge / 2 + 1;
	return (int)ret;
}
