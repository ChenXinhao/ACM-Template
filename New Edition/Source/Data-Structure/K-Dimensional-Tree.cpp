struct Heapnode{
	long long d;
	int pos;
	bool operator <(const Heapnode &p)const {
		return d > p.d || (d == p.d && pos < p.pos);
	}
};

struct MsgNode{
	int xmin, xmax, ymin, ymax;
	MsgNode() {}
	MsgNode(const Point &a) : xmin(a.x), xmax(a.x), ymin(a.y), ymax(a.y) {}
	long long dist(const Point &a) {
		int dx = std::max(std::abs(a.x - xmin), std::abs(a.x - xmax));
		int dy = std::max(std::abs(a.y - ymin), std::abs(a.y - ymax));
		return (long long)dx * dx + (long long)dy * dy;
	}
	MsgNode operator +(const MsgNode &rhs)const {
		MsgNode ret;
		ret.xmin = std::min(xmin, rhs.xmin);
		ret.xmax = std::max(xmax, rhs.xmax);
		ret.ymin = std::min(ymin, rhs.ymin);
		ret.ymax = std::max(ymax, rhs.ymax);
		return ret;
	}
};

struct TNode{
	int l, r;
	Point p;
	MsgNode d;
}tree[MAXN];

void buildtree(int &rt, int l, int r, int pivot) {
	if (l > r) return;
	rt = ++size;
	int mid = l + r >> 1;
	if (pivot == 1) std::nth_element(p + l, p + mid, p + r + 1, cmpx);
	if (pivot == 0) std::nth_element(p + l, p + mid, p + r + 1, cmpy);
	tree[rt].d = MsgNode(tree[rt].p = p[mid]);
	buildtree(tree[rt].l, l, mid - 1, pivot ^ 1);
	buildtree(tree[rt].r, mid + 1, r, pivot ^ 1);
	if (tree[rt].l) tree[rt].d = tree[rt].d + tree[tree[rt].l].d;
	if (tree[rt].r) tree[rt].d = tree[rt].d + tree[tree[rt].r].d;
}

void query(int rt, const Point &a, int k, int pivot) {
	Heapnode now = (Heapnode){dist(a, tree[rt].p), tree[rt].p.pos};
	if (heap.size() < k) heap.push(now);
	else if (now < heap.top()) {heap.pop(); heap.push(now);}
	int lson = tree[rt].l, rson = tree[rt].r;
	if (pivot == 1 && cmpx(a, tree[rt].p)) std::swap(lson, rson);
	if (pivot == 0 && cmpy(a, tree[rt].p)) std::swap(lson, rson);
	if (lson && (heap.size() < k || tree[lson].d.dist(a) >= heap.top().d)) query(lson, a, k, pivot ^ 1);
	if (rson && (heap.size() < k || tree[rson].d.dist(a) >= heap.top().d)) query(rson, a, k, pivot ^ 1);
}

int main() {
	for (int i = 1; i <= q; i++) {
		int k;
		Point now;
		now.read();
		scanf("%d", &k);
		while (!heap.empty()) heap.pop();
		query(rt, now, k, 1);
		printf("%d\n", heap.top().pos);
	}
	return 0;
}
