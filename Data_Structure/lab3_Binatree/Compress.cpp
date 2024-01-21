#include"Compress.h"

using namespace std;

void Compress::compress() {
	cout << "�������ļ�·����";
	cin >> loca;

	//step1:��Ŀ���ļ����룬���洢��������
	FILE* fp = fopen(loca.c_str(), "rb");//���ļ�
	if (fp == nullptr) {
		cout << "�ļ�·��������" << endl;
		return;
	}
	//��ȡ�ļ����ݣ�����ѭ����һ�ζ�ȡ1024���ֽ�
	unsigned char readbuff[1024];//���û�����
	unsigned long long int fullweight[256] = { 0 };
	unsigned char content[256];
	unsigned long long int weight[256] = { 0 };
	while (1) {
		//fread�����ķ���ֵ����ʾ�ɹ���ȡ���ֽ�����
		//��read_size�����ճɹ���ȡ���ֽ���
		unsigned long long read_size = fread(readbuff, 1, 1024, fp);
		if (read_size == 0) {
			break;//read_size = 0��ʾ�Ѿ��������ļ�ĩβ
		}
		//ͳ�Ƴ����ַ��Ĵ���
		for (unsigned long long i = 0; i < read_size; ++i) {
			//�����ַ���ASCII��ֵ��Ϊ������±�ͳ�ƴ���
			fullweight[readbuff[i]]++;
		}
	}
	int charsize = 0;//��ʾһ�����ֵ��ַ���������
	for (int i = 0; i < 256; i++) {
		if (fullweight[i]) {
			content[charsize] = i;
			weight[charsize] = fullweight[i];
			charsize++;
		}
	}
	
	//step2:����Ȩ�����ַ�������huffman��
	for (int t = 0; t <= charsize; t++) {
		HuffT.huff[t + 1].content = content[t];
		HuffT.huff[t + 1].weight = weight[t];
	}
	HuffT.size = charsize;
	HuffT.CreateTree();
	HuffT.EnCode();

	//step3:����ѹ������ļ�
	cout << "������Ҫ��ѹ���ļ�����ļ���";
	cin >> dest;
	FILE* fl = fopen(dest.c_str(), "wb");//fl�ļ�ָ��ָ��򿪵��ļ�2.txt
	fseek(fp, 0, SEEK_SET);//ʹ��rewind(fp)����Ҳ��
	unsigned char ch = 0;//��¼��λ�����ַ�
	int bitcount = 0;//��¼��λ��ı���λ����
	//����ѭ�����ļ�����
	while (1) {
		//fread�����ķ���ֵ����ʾ�ɹ���ȡ���ֽ�����
		//��read_size�����ճɹ���ȡ���ֽ���
		unsigned long long read_size = fread(readbuff, 1, 1024, fp);
		if (read_size == 0) {
			break;//read_size = 0��ʾ�Ѿ��������ļ�ĩβ
		}

		for (unsigned long long i = 0; i < read_size; ++i) {
			//��ȡ��Ӧ���еı���
			string strcode;
			//�ҵ���Ӧ�ı���
			for (int t = 1; t <= HuffT.size; t++) {
				if (HuffT.huff[t].content == readbuff[i]) {
					strcode.append(HuffT.huff[t].huffcode);
					break;
				}
			}
			for (size_t j = 0; j < strcode.size(); j++) {
				ch <<= 1;//�Ƚ�ch����һλ
				if (strcode[j] == '1') {//����strcode��ÿ������λ��1���л����
					ch |= 1;
				}
				bitcount++;//ÿ��λ��һ�ξͶ�bitcount++
				if (bitcount == 8) {//һ���ֽڷ���8������λ
					fputc(ch,fl);//���ļ��н���д����
					bitcount = 0;//����λ������0
				}
			}
		}
	}
	//���ch���õı���λ����������8���������ļ���д
	if (bitcount > 0 && bitcount < 8) {
		ch <<= (8 - bitcount);
		fputc(ch, fl);
	}
	int fpSize = fpSize = ftell(fl);
	int outSize = outSize = ftell(fp);
	cout << "\n***********************************\n" << endl;
	cout << "ѹ��ǰ��" << outSize << "B" << endl;
	cout << "ѹ����" << fpSize << "B" << endl;
	cout << "***********************************" << endl;
	fclose(fp);//�ر��ļ�
	fclose(fl);
	cout << "ѹ���ɹ�" << endl;
}

void Compress::uncompress() {
	//step1:�򿪴���ѹ�ļ�����ȡ����
	cout << "������Ҫ��ѹ���ļ��ĵ�ַ��";
	cin >> loca;
	if (loca.size() < 5 || loca.compare(loca.size() - 5, loca.size() - 1, ".huff")) {
		//ֻ�ܽ�ѹ����׺��Ϊ.huff���ļ�
		cout << "ֻ�ܽ�ѹ����׺��Ϊ.huff���ļ�"<<endl;
		return;
	}
	FILE* FIn = fopen(loca.c_str(), "rb");//�Զ��ķ�ʽ���ļ�
	if (FIn == nullptr) {//����ļ�Ϊ�ջ���û���ļ�
		perror("fopen");
		return;
	}

	cout << "�������ѹ�����ĵ�ַ���ļ�����" ;
	cin >> dest;

	FILE* FOut = fopen(dest.c_str(), "wb");//��д�ķ�ʽ���ļ�
	//step2:��huffman���ҵ���ӦԴ�����д��
	unsigned char readbuff[1024];//д�ļ����壬һ��д1024bits
	unsigned char bitcount = 0;
	int cur = HuffT.size * 2 - 1;//curָ����������ĸ��ڵ�(2n-1)
	const int FileSize = HuffT.huff[cur].weight;//���ڵ��Ȩֵ��λԭ�ļ��Ĵ�С
	int CompressSize = 0;//��¼ѹ����Ĵ�С
	while (1) {
		size_t read_size = fread(readbuff, 1, 1024, FIn);
		if (read_size == 0) {
			break;
		}
		for (size_t i = 0; i < read_size; i++) {
			unsigned char ch = readbuff[i];//ch������ѹ�����ÿһ���ֽ�
			bitcount = 0;
			while (bitcount < 8) {
				if (ch & 0x80) {//ÿ������λ��1000 0000��λ��
					cur = HuffT.huff[cur].right;
				}
				else {
					cur = HuffT.huff[cur].left;
				}
				if (HuffT.huff[cur].left == 0 && HuffT.huff[cur].right == 0) {//�ߵ���Ҷ�ӽڵ��λ��
					fputc(HuffT.huff[cur].content, FOut);
					cur = HuffT.size * 2 - 1;//�ص����ڵ��λ��
					CompressSize++;
					if (CompressSize == FileSize) {//�жϽ�ѹ����Ľ����ԭ�ļ���С�Ƿ���ͬ
						break;
					}
				}
				bitcount++;
				ch <<= 1;
			}
		}
	}
	int fpSize = fpSize = ftell(FOut);
	int outSize = outSize = ftell(FIn);
	cout << "\n***********************************\n" << endl;
	cout << "��ѹ��ǰ��" << outSize << "B" << endl;
	cout << "��ѹ����" << fpSize << "B" << endl;
	cout << "***********************************" << endl;
	fclose(FIn);
	fclose(FOut);
	cout << "��ѹ���ɹ�" << endl;
	return;
}

void Compress::GetLine(FILE* FIn, string& strContent) {
	unsigned char ch;
	while (!feof(FIn)) {
		ch = fgetc(FIn);
		if (ch == '\n') {
			break;
		}
		else {
			strContent += ch;
		}
	}
}
