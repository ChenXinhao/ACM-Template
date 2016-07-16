Point getmid(Point a,Point b) {
	return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}
Point getcross(Point a, Point vA, Point b, Point vB) {
	Point u = a - b;
	double t = det(vB, u) / det(vA, vB);
	return a + vA * t;
}
Point getcir(Point a,Point b,Point c) {
	Point midA = getmid(a,b), vA = Point(-(b - a).y, (b - a).x);
	Point midB = getmid(b,c), vB = Point(-(c - b).y, (c - b).x);
	return getcross(midA, vA, midB, vB);
}
double mincir(Point *p,int n) {
	std::random_shuffle(p + 1, p + n + 1);
	Point O = p[1];
	double r = 0;
	for (int i = 2; i <= n; i++) {
		if (dist(O, p[i]) <= r) continue;
		O = p[i]; r = 0;
		for (int j = 1; j < i; j++) {
			if (dist(O, p[j]) <= r) continue;
			O = getmid(p[i], p[j]); r = dist(O,p[i]);
			for (int k = 1; k < j; k++) {
				if (dist(O,p[k]) <= r) continue;
				O = getcir(p[i], p[j], p[k]);
				r = dist(O,p[i]);
			}
		}
	}
	return r;
}
