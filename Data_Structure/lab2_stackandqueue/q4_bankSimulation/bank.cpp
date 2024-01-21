#include"bank.h"

void bank::initBank() {
	cout << "依次输入 客户总数 初始钱数 营业时间 交易时长 " << endl;
	cin >> N >> total >> close_time >> average_time;
	clock = 0;
	//记录每个客户的信息
	for (int i = 1; i <= N; i++) {
		cout << "输入第" << i << "个客户存（取）款金额 到达时间" << endl;
		cin >> client[i][0] >> client[i][1];
	}
	//再按时间先后对客户排序（选择排序法）
	for (int j = 1; j <= N; j++) {
		int min = j;
		for (int k = j + 1; k <= N; k++) {
			if (client[k][1] < client[min][1]) {
				min = k;
			}
		}
		//交换一下
		int m = client[j][0];
		int n = client[j][1];
		client[j][0] = client[min][0];
		client[j][1] = client[min][1];
		client[min][0] = m;
		client[min][1] = n;
	}
	//先给每个人的离开时间设为closetime
	for (int k = 1; k <= N; k++) {
		client[k][2] = close_time;
	}
}

void bank::showBank() {
	cout << "time:  " << clock<<"     total money:  "<<total<<endl;
	cout << "窗口一    ";
	for (int i = q1.base; i < q1.top; i++) {
		cout << q1.no[i] << "号客户"<<"("<<client[q1.no[i]][0]<<")  ";
	}
	cout << endl;
	cout << "窗口二    ";
	for (int j = q2.base; j < q2.top; j++) {
		cout << q2.no[j] << "号客户"<<"("<<client[q2.no[j]][0]<<")  ";
	}
	cout << endl << endl;
}

void bank::bankWorking() {
	//时间从0开始
	clock = 0;
	int c=1;//表示已经来的客户数量
	int key = 0;//表示正在工作的窗口，若为0则表示都不在工作
	int startTime = 0;//表示若正在给客户服务，开始服务的时间
	while (clock <= close_time) {
		//如果到了第c个客户到达的时间，将第c个客户排入第一个队列
		for (int t = c; t <= N; t++) {
			if (clock == client[c][1]) {
				cout << c << "号客户于 " << client[c][1] << " 时刻到达，";
				if (client[c][0] > 0) {
					cout << "想要存款 " << client[c][0];
				}
				else {
					cout << "想要取钱 " << (0-client[c][0]);
				}
				q1.push(c);
				c++;
				cout << endl;
				system("pause");
			}
		}
		
		if (key == 0) {//若都没在工作，则检查队列是否有客户排队
			while (!q1.isEmpty()) {//第一个队列有人排队
				if (total + client[q1.front()][0] < 0) {
					//表示第一个队列的最前面的人要取钱且银行钱不够
					q2.push(q1.front());//这个人排到q2去
					q1.pop();
				}
				else {
					//表示第一个队列最前面的人可以满足要求
					client[q1.front()][2] = clock;
					cout << q1.front() << " 号客户开始在一号窗口办理业务"<<endl;
					system("pause");
					startTime = clock;//表示现在开始工作
					key = 1;
					break;
				}
			}
			//若一队列没有客户或者没有能够满足的客户，那二队列也一定没有能满足的
		}
		else if (key == 1) {//刚刚在处理一队列的客户
			if ((startTime + average_time) == clock) {//刚好处理完上一个客户
				key = 0;
				total += client[q1.front()][0];
				cout << q1.front() << " 号客户办理完毕业务，当前银行总金额为：" << total<<endl;
				system("pause");
				
				if (client[q1.front()][0] > 0) {//如果刚刚处理完的是来送钱的，就开始检查第二个队列
					q1.pop();//先给上一个人出队列
					for (int i = 0; i < q2.size(); i++) {//防止全都不能满足就死循环了
						if (total + client[q2.front()][0] < 0) {//仍无法满足的第二个队列的人
							q2.push(q2.front());//重新排到q2队尾
							q2.pop();
						}
						else {//有能够满足的客户
							key = 2;
							startTime = clock;
							client[q2.front()][2] = clock;
							cout << q2.front() << " 号客户开始在二号窗口办理业务"<<endl;
							system("pause");
							break;
						}
					}
				}
				else {//刚刚处理完的是来要钱的
					q1.pop();//先给上一个人出队列
					while (!q1.isEmpty()) {//第一个队列有人排队
						if (total + client[q1.front()][0] < 0) {
							//表示第一个队列的最前面的人要取钱且银行钱不够
							q2.push(q1.front());//这个人排到q2去
							q1.pop();
						}
						else {
							//表示第一个队列最前面的人可以满足要求
							startTime = clock;//表示现在开始工作
							key = 1;
							client[q1.front()][2] = clock;
							cout << q1.front() << " 号客户开始在一号窗口办理业务"<<endl;
							system("pause");
							break;
						}
					}
				}
			}
		}
		else {//刚刚处理完的是第二个队列的客户
			if ((startTime + average_time) == clock) {
				cout << q2.front() << " 号客户办理完毕业务，当前银行总金额为：" << total << endl;
				system("pause");
				total += client[q2.front()][0];
				q2.pop();
				//先找第二个队列有没有客户能够满足
				int i;
				for (i = 0; i < q2.size(); i++) {//防止全都不能满足就死循环了
					if (total + client[q2.front()][0] < 0) {//仍无法满足的第二个队列的人
						q2.push(q2.front());//重新排到q2队尾
						q2.pop();
					}
					else {//有能够满足的客户
						key = 2;
						startTime = clock;
						client[q2.front()][2] = clock;
						cout << q2.front() << " 号客户开始在二号窗口办理业务"<<endl;
						system("pause");
						break;
					}
				}
				if (i >= q2.size()) {//二队列没有能满足的客户，就找一队列
					while (!q1.isEmpty()) {//第一个队列有人排队
						if (total + client[q1.front()][0] < 0) {
							//表示第一个队列的最前面的人要取钱且银行钱不够
							q2.push(q1.front());//这个人排到q2去
							q1.pop();
						}
						else {
							//表示第一个队列最前面的人可以满足要求
							startTime = clock;//表示现在开始工作
							key = 1;
							cout << q1.front() << " 号客户开始在一号窗口办理业务"<<endl;
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
		cout << t << " 号客户等待时间为：" << client[t][2] - client[t][1] << endl;
		sum += (client[t][2] - client[t][1]);
	}
	cout << "平均等待时间为： " << (sum / N);
}

