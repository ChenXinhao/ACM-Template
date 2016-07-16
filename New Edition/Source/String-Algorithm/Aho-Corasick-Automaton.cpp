int size, c[MAXT][26], f[MAXT], fail[MAXT], d[MAXT];

int alloc() {
	size++;
	std::fill(c[size], c[size] + 26, 0);
	f[size] = fail[size] = d[size] = 0;
	return size;
}

void insert(char *s) {
	int len = strlen(s + 1), p = 1;
	for (int i = 1; i <= len; i++) {
		if (c[p][s[i] - 'a']) p = c[p][s[i] - 'a'];
		else{
			int newnode = alloc();
			c[p][s[i] - 'a'] = newnode;
			d[newnode] = s[i] - 'a';
			f[newnode] = p;
			p = newnode;
		}
	}
}

void buildfail() {
	static int q[MAXT];
	int left = 0, right = 0;
	fail[1] = 0;
	for (int i = 0; i < 26; i++) {
		c[0][i] = 1;
		if (c[1][i]) q[++right] = c[1][i];
	}
	while (left < right) {
		left++;
		int p = fail[f[q[left]]];
		while (!c[p][d[q[left]]]) p = fail[p];
		fail[q[left]] = c[p][d[q[left]]];
		for (int i = 0; i < 26; i++) {
			if (c[q[left]][i]) {
				q[++right] = c[q[left]][i];
			}
		}
	}
	for (int i = 1; i <= size; i++)
		for (int j = 0; j < 26; j++) {
			int p = i;
			while (!c[p][j]) p = fail[p];
			c[i][j] = c[p][j];
		}
}
