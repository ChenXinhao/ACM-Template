lenA = strlen(A); lenB = strlen(B);
nxt[0] = lenB,nxt[1] = lenB - 1;
for (int i = 0;i <= lenB;i ++)
	if (B[i] != B[i + 1]) {nxt[1] = i; break;}
int j, k = 1, p, L;
for (int i = 2;i < lenB;i ++) {
	p = k + nxt[k] - 1; L = nxt[i - k];
	if (i + L <= p) nxt[i] = L;
	else {
		j = p - i + 1;
		if (j < 0) j = 0;
		while (i + j < lenB && B[i + j] == B[j]) j++;
		nxt[i] = j; k = i;
	}
}
int minlen = lenA <= lenB ? lenA : lenB; ex[0] = minlen;
for (int i = 0;i < minlen;i ++)
	if (A[i] != B[i]) {ex[0] = i; break;}
k = 0;
for (int i = 1;i < lenA;i ++){
	p = k + ex[k] - 1; L = next[i - k];
	if (i + L <= p) ex[i] = L;
	else {
		j = p - i + 1;
		if (j < 0) j = 0;
		while (i + j < lenA && j < lenB && A[i + j] == B[j]) j++;
		ex[i] = j; k = i;
	}
}
