#include"Compress.h"

using namespace std;

void Compress::compress() {
	cout << "请输入文件路径：";
	cin >> loca;

	//step1:将目的文件读入，并存储在数组中
	FILE* fp = fopen(loca.c_str(), "rb");//打开文件
	if (fp == nullptr) {
		cout << "文件路径不存在" << endl;
		return;
	}
	//读取文件内容，采用循环，一次读取1024个字节
	unsigned char readbuff[1024];//设置缓冲区
	unsigned long long int fullweight[256] = { 0 };
	unsigned char content[256];
	unsigned long long int weight[256] = { 0 };
	while (1) {
		//fread函数的返回值，表示成功读取的字节数量
		//用read_size来接收成功读取的字节数
		unsigned long long read_size = fread(readbuff, 1, 1024, fp);
		if (read_size == 0) {
			break;//read_size = 0表示已经读到了文件末尾
		}
		//统计出现字符的次数
		for (unsigned long long i = 0; i < read_size; ++i) {
			//利用字符的ASCII码值作为数组的下标统计次数
			fullweight[readbuff[i]]++;
		}
	}
	int charsize = 0;//表示一共出现的字符类型数量
	for (int i = 0; i < 256; i++) {
		if (fullweight[i]) {
			content[charsize] = i;
			weight[charsize] = fullweight[i];
			charsize++;
		}
	}
	
	//step2:根据权数和字符数构建huffman树
	for (int t = 0; t <= charsize; t++) {
		HuffT.huff[t + 1].content = content[t];
		HuffT.huff[t + 1].weight = weight[t];
	}
	HuffT.size = charsize;
	HuffT.CreateTree();
	HuffT.EnCode();

	//step3:生成压缩后的文件
	cout << "输入需要解压缩文件后的文件名";
	cin >> dest;
	FILE* fl = fopen(dest.c_str(), "wb");//fl文件指针指向打开的文件2.txt
	fseek(fp, 0, SEEK_SET);//使用rewind(fp)函数也行
	unsigned char ch = 0;//记录按位或后的字符
	int bitcount = 0;//记录按位或的比特位长度
	//采用循环读文件内容
	while (1) {
		//fread函数的返回值，表示成功读取的字节数量
		//用read_size来接收成功读取的字节数
		unsigned long long read_size = fread(readbuff, 1, 1024, fp);
		if (read_size == 0) {
			break;//read_size = 0表示已经读到了文件末尾
		}

		for (unsigned long long i = 0; i < read_size; ++i) {
			//获取对应的中的编码
			string strcode;
			//找到对应的编码
			for (int t = 1; t <= HuffT.size; t++) {
				if (HuffT.huff[t].content == readbuff[i]) {
					strcode.append(HuffT.huff[t].huffcode);
					break;
				}
			}
			for (size_t j = 0; j < strcode.size(); j++) {
				ch <<= 1;//先将ch左移一位
				if (strcode[j] == '1') {//再让strcode的每个比特位与1进行或操作
					ch |= 1;
				}
				bitcount++;//每按位或一次就对bitcount++
				if (bitcount == 8) {//一个字节放满8个比特位
					fputc(ch,fl);//往文件中进行写操作
					bitcount = 0;//比特位计数置0
				}
			}
		}
	}
	//检测ch放置的比特位个数，不够8个继续往文件中写
	if (bitcount > 0 && bitcount < 8) {
		ch <<= (8 - bitcount);
		fputc(ch, fl);
	}
	int fpSize = fpSize = ftell(fl);
	int outSize = outSize = ftell(fp);
	cout << "\n***********************************\n" << endl;
	cout << "压缩前：" << outSize << "B" << endl;
	cout << "压缩后：" << fpSize << "B" << endl;
	cout << "***********************************" << endl;
	fclose(fp);//关闭文件
	fclose(fl);
	cout << "压缩成功" << endl;
}

void Compress::uncompress() {
	//step1:打开待解压文件并读取内容
	cout << "请输入要解压的文件的地址：";
	cin >> loca;
	if (loca.size() < 5 || loca.compare(loca.size() - 5, loca.size() - 1, ".huff")) {
		//只能解压缩后缀名为.huff的文件
		cout << "只能解压缩后缀名为.huff的文件"<<endl;
		return;
	}
	FILE* FIn = fopen(loca.c_str(), "rb");//以读的方式打开文件
	if (FIn == nullptr) {//如果文件为空或者没有文件
		perror("fopen");
		return;
	}

	cout << "请输入解压缩到的地址及文件名：" ;
	cin >> dest;

	FILE* FOut = fopen(dest.c_str(), "wb");//以写的方式打开文件
	//step2:按huffman树找到对应源码进行写入
	unsigned char readbuff[1024];//写文件缓冲，一次写1024bits
	unsigned char bitcount = 0;
	int cur = HuffT.size * 2 - 1;//cur指向哈夫曼树的根节点(2n-1)
	const int FileSize = HuffT.huff[cur].weight;//根节点的权值即位原文件的大小
	int CompressSize = 0;//记录压缩后的大小
	while (1) {
		size_t read_size = fread(readbuff, 1, 1024, FIn);
		if (read_size == 0) {
			break;
		}
		for (size_t i = 0; i < read_size; i++) {
			unsigned char ch = readbuff[i];//ch来保存压缩后的每一个字节
			bitcount = 0;
			while (bitcount < 8) {
				if (ch & 0x80) {//每个比特位与1000 0000按位与
					cur = HuffT.huff[cur].right;
				}
				else {
					cur = HuffT.huff[cur].left;
				}
				if (HuffT.huff[cur].left == 0 && HuffT.huff[cur].right == 0) {//走到了叶子节点的位置
					fputc(HuffT.huff[cur].content, FOut);
					cur = HuffT.size * 2 - 1;//回到根节点的位置
					CompressSize++;
					if (CompressSize == FileSize) {//判断解压缩后的结果与原文件大小是否相同
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
	cout << "解压缩前：" << outSize << "B" << endl;
	cout << "解压缩后：" << fpSize << "B" << endl;
	cout << "***********************************" << endl;
	fclose(FIn);
	fclose(FOut);
	cout << "解压缩成功" << endl;
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
