#include"bank.h"

void bank::initBank() {
	cout << "�������� �ͻ����� ��ʼǮ�� Ӫҵʱ�� ����ʱ�� " << endl;
	cin >> N >> total >> close_time >> average_time;
	clock = 0;
	//��¼ÿ���ͻ�����Ϣ
	for (int i = 1; i <= N; i++) {
		cout << "�����" << i << "���ͻ��棨ȡ������ ����ʱ��" << endl;
		cin >> client[i][0] >> client[i][1];
	}
	//�ٰ�ʱ���Ⱥ�Կͻ�����ѡ�����򷨣�
	for (int j = 1; j <= N; j++) {
		int min = j;
		for (int k = j + 1; k <= N; k++) {
			if (client[k][1] < client[min][1]) {
				min = k;
			}
		}
		//����һ��
		int m = client[j][0];
		int n = client[j][1];
		client[j][0] = client[min][0];
		client[j][1] = client[min][1];
		client[min][0] = m;
		client[min][1] = n;
	}
	//�ȸ�ÿ���˵��뿪ʱ����Ϊclosetime
	for (int k = 1; k <= N; k++) {
		client[k][2] = close_time;
	}
}

void bank::showBank() {
	cout << "time:  " << clock<<"     total money:  "<<total<<endl;
	cout << "����һ    ";
	for (int i = q1.base; i < q1.top; i++) {
		cout << q1.no[i] << "�ſͻ�"<<"("<<client[q1.no[i]][0]<<")  ";
	}
	cout << endl;
	cout << "���ڶ�    ";
	for (int j = q2.base; j < q2.top; j++) {
		cout << q2.no[j] << "�ſͻ�"<<"("<<client[q2.no[j]][0]<<")  ";
	}
	cout << endl << endl;
}

void bank::bankWorking() {
	//ʱ���0��ʼ
	clock = 0;
	int c=1;//��ʾ�Ѿ����Ŀͻ�����
	int key = 0;//��ʾ���ڹ����Ĵ��ڣ���Ϊ0���ʾ�����ڹ���
	int startTime = 0;//��ʾ�����ڸ��ͻ����񣬿�ʼ�����ʱ��
	while (clock <= close_time) {
		//������˵�c���ͻ������ʱ�䣬����c���ͻ������һ������
		for (int t = c; t <= N; t++) {
			if (clock == client[c][1]) {
				cout << c << "�ſͻ��� " << client[c][1] << " ʱ�̵��";
				if (client[c][0] > 0) {
					cout << "��Ҫ��� " << client[c][0];
				}
				else {
					cout << "��ҪȡǮ " << (0-client[c][0]);
				}
				q1.push(c);
				c++;
				cout << endl;
				system("pause");
			}
		}
		
		if (key == 0) {//����û�ڹ�������������Ƿ��пͻ��Ŷ�
			while (!q1.isEmpty()) {//��һ�����������Ŷ�
				if (total + client[q1.front()][0] < 0) {
					//��ʾ��һ�����е���ǰ�����ҪȡǮ������Ǯ����
					q2.push(q1.front());//������ŵ�q2ȥ
					q1.pop();
				}
				else {
					//��ʾ��һ��������ǰ����˿�������Ҫ��
					client[q1.front()][2] = clock;
					cout << q1.front() << " �ſͻ���ʼ��һ�Ŵ��ڰ���ҵ��"<<endl;
					system("pause");
					startTime = clock;//��ʾ���ڿ�ʼ����
					key = 1;
					break;
				}
			}
			//��һ����û�пͻ�����û���ܹ�����Ŀͻ����Ƕ�����Ҳһ��û���������
		}
		else if (key == 1) {//�ո��ڴ���һ���еĿͻ�
			if ((startTime + average_time) == clock) {//�պô�������һ���ͻ�
				key = 0;
				total += client[q1.front()][0];
				cout << q1.front() << " �ſͻ��������ҵ�񣬵�ǰ�����ܽ��Ϊ��" << total<<endl;
				system("pause");
				
				if (client[q1.front()][0] > 0) {//����ոմ������������Ǯ�ģ��Ϳ�ʼ���ڶ�������
					q1.pop();//�ȸ���һ���˳�����
					for (int i = 0; i < q2.size(); i++) {//��ֹȫ�������������ѭ����
						if (total + client[q2.front()][0] < 0) {//���޷�����ĵڶ������е���
							q2.push(q2.front());//�����ŵ�q2��β
							q2.pop();
						}
						else {//���ܹ�����Ŀͻ�
							key = 2;
							startTime = clock;
							client[q2.front()][2] = clock;
							cout << q2.front() << " �ſͻ���ʼ�ڶ��Ŵ��ڰ���ҵ��"<<endl;
							system("pause");
							break;
						}
					}
				}
				else {//�ոմ����������ҪǮ��
					q1.pop();//�ȸ���һ���˳�����
					while (!q1.isEmpty()) {//��һ�����������Ŷ�
						if (total + client[q1.front()][0] < 0) {
							//��ʾ��һ�����е���ǰ�����ҪȡǮ������Ǯ����
							q2.push(q1.front());//������ŵ�q2ȥ
							q1.pop();
						}
						else {
							//��ʾ��һ��������ǰ����˿�������Ҫ��
							startTime = clock;//��ʾ���ڿ�ʼ����
							key = 1;
							client[q1.front()][2] = clock;
							cout << q1.front() << " �ſͻ���ʼ��һ�Ŵ��ڰ���ҵ��"<<endl;
							system("pause");
							break;
						}
					}
				}
			}
		}
		else {//�ոմ�������ǵڶ������еĿͻ�
			if ((startTime + average_time) == clock) {
				cout << q2.front() << " �ſͻ��������ҵ�񣬵�ǰ�����ܽ��Ϊ��" << total << endl;
				system("pause");
				total += client[q2.front()][0];
				q2.pop();
				//���ҵڶ���������û�пͻ��ܹ�����
				int i;
				for (i = 0; i < q2.size(); i++) {//��ֹȫ�������������ѭ����
					if (total + client[q2.front()][0] < 0) {//���޷�����ĵڶ������е���
						q2.push(q2.front());//�����ŵ�q2��β
						q2.pop();
					}
					else {//���ܹ�����Ŀͻ�
						key = 2;
						startTime = clock;
						client[q2.front()][2] = clock;
						cout << q2.front() << " �ſͻ���ʼ�ڶ��Ŵ��ڰ���ҵ��"<<endl;
						system("pause");
						break;
					}
				}
				if (i >= q2.size()) {//������û��������Ŀͻ�������һ����
					while (!q1.isEmpty()) {//��һ�����������Ŷ�
						if (total + client[q1.front()][0] < 0) {
							//��ʾ��һ�����е���ǰ�����ҪȡǮ������Ǯ����
							q2.push(q1.front());//������ŵ�q2ȥ
							q1.pop();
						}
						else {
							//��ʾ��һ��������ǰ����˿�������Ҫ��
							startTime = clock;//��ʾ���ڿ�ʼ����
							key = 1;
							cout << q1.front() << " �ſͻ���ʼ��һ�Ŵ��ڰ���ҵ��"<<endl;
							system("pause");
							break;
						}
					}
				}
			}
		}
		system("cls");
		showBank();
		Sleep(10);
		clock++;
	}
	int sum = 0;
	for (int t = 1; t <= N; t++) {
		cout << t << " �ſͻ��ȴ�ʱ��Ϊ��" << client[t][2] - client[t][1] << endl;
		sum += (client[t][2] - client[t][1]);
	}
	cout << "ƽ���ȴ�ʱ��Ϊ�� " << (sum / N);
}

