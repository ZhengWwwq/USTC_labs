#include"Huffmantree.h"

void HuffmanTree::CreateTree() {//����huffman��
	if (size < 3) {
		return;
	}
	//��ʼ��һ���������ÿһ�����
	for (int t = 1; t < 2 * size; t++) {
		huff[t].left = 0;
		huff[t].right = 0;
		huff[t].parent = 0;
	}
	int min1, min2;
	//������������
	for (int i = size + 1; i < 2 * size; i++) {
		select(i-1,min1, min2);//�ҵ�Ȩ����С����˫�׽����������
		huff[i].left = min1;
		huff[i].right = min2;
		huff[min1].parent = i;
		huff[min2].parent = i;
		huff[i].weight = huff[min1].weight + huff[min2].weight;
	}
}

void HuffmanTree::select(int length, int& no1, int& no2) {
	no1 = 0;
	no2 = 0;
	for (int i = 1; i <= length; i++) {
		if (huff[i].parent == 0) {
			if (no1 == 0) {
				no1 = i;
			}
			else {
				if (huff[i].weight < huff[no1].weight) {
					no1 = i;
				}
			}
		}
	}
	for (int j = 1; j <= length; j++) {
		if (huff[j].parent == 0 && j != no1) {
			if (no2 == 0) {
				no2 = j;
			}
			else {
				if (huff[j].weight < huff[no2].weight) {
					no2 = j;
				}
			}
		}
	}
}

void HuffmanTree::Input() {
	cin >> size;
	for (int i = 1; i <= size; i++) {
		cin >> huff[i].content >> huff[i].weight;
	}
}

void HuffmanTree::print() {
	for (int i = 1; i <= size; i++) {
		cout << i << " " << huff[i].content << " " << huff[i].weight << " " << huff[i].parent << " " << huff[i].left << " " << huff[i].right << endl;
	}
	for (int i = size+1; i < 2*size; i++) {
		cout << i << " " << "null" << " " << huff[i].weight << " " << huff[i].parent << " " << huff[i].left << " " << huff[i].right << endl;
	}
	for (int i = 1; i <= size; i++) {
		cout << i << " " << huff[i].huffcode << endl;
	}
}

void HuffmanTree::EnCode() {//����huffman������huffman����
	for (int i = 1; i <= size; i++) {//���α�������Ԫ��
		int p = huff[i].parent;
		int cur = i;
		while (p != 0) {
			if (huff[p].left == cur) {
				huff[i].huffcode.insert(huff[i].huffcode.begin(), '0');
			}
			else {
				huff[i].huffcode.insert(huff[i].huffcode.begin(), '1');
			}
			cur = p;
			p = huff[cur].parent;
		}
	}
}