#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include <string.h>
using namespace std;
map <int, vector<int> > Graph;
int test[100]={};
int vis[129];
double S[129][129];
bool G[129][129];
int mark_orgnzt = 0;
int num_node = 0;
double threshold = 0.19;
const int Max_Node = 34;
void init(){
    memset(vis,0,sizeof(vis));
    memset(S,0,sizeof (vis));
    memset(G,0,sizeof(G));
    Graph.clear();
    srand(time(0));
}
int get_point(){
    int num = (int)rand()%Max_Node+1;
    while(vis[num]){
        num = rand()%Max_Node+1;
    }
    return num;
}
void cal_similarity(){
    int intersection = 0,uni = 0;
    for(int i = 1;i<=Max_Node;i++){//������������
        for(int j = 1;j<=Max_Node;j++){
            if(S[i][j]) {//�Գƾ��� ����þͲ�����
                //S[i][j] = S[j][i];
                continue;
            }
            uni = 0;
            intersection = 0;
            set<int> temp;
            temp.clear();
            for(vector<int>::iterator it = Graph[i].begin();it!=Graph[i].end();it++){//
                temp.insert(*it);
                //cout<<*it<<" ";
                uni++;
            }
            for(vector<int>::iterator it = Graph[j].begin();it!=Graph[j].end();it++){//
                set<int>::iterator that=temp.find(*it);
                if( that!=temp.end() )//��i����������
                    intersection++;//�����ھ�+1
                else
                    uni++;//�ھӽڵ�Ĳ�+1
            }
            S[i][j] = S[j][i] = (double)((double)intersection/(double)uni);
        }
        //cout<<endl;
	}
}
void cluster(){
        int start = get_point();
        vis[start] = mark_orgnzt;//�����Ϳɫ 1~n
        num_node++;//ʹ���˵Ľ��������
        double midu = 1;//�����ܶ�
        int num = 1;//���������н��
        int ideal_egde = num*(num-1)/2;//��ȫ����
        int sum_edge = 0;//�����ܱ���
        set<int> adjoin;//�����ڽӵ�
        set<int> point;//�������е�
        adjoin.clear();
        point.clear();
        point.insert(start);//��ʼ��
        for(vector<int>::iterator it=Graph[start].begin();it!=Graph[start].end();it++){
            if(vis[*it]) continue;
            adjoin.insert(*it);
        }
        while(midu>=threshold){
            int temp_edge = 0;//�ô�������
            for(set<int>::iterator it = adjoin.begin();it!=adjoin.end();it++){//���ڽӽ�㼯ѡ��
                int temp = 0;//�ڽӵ�������ͼ�����ı���
                if(vis[*it]) continue;
                for(set<int>::iterator that = point.begin();that!=point.end();that++){//������������ͼ�������� һ��ʹͼ�ܶ��½�����
                    if(G[*it][*that])
                        temp++;
                }
                if(temp>temp_edge){
                    temp_edge = temp;
                    start = *it;
                }
            }
            ideal_egde = num*(num+1)/2;
            sum_edge+=temp_edge;
            midu = (double)sum_edge/(double)ideal_egde;
            if(midu<threshold){//����¼���ĵ�ʹ�ܶ�С����ֵ�����
                sum_edge-=temp_edge;
                break;
            }

            vis[start] = mark_orgnzt;
            num++;
            num_node++;
            adjoin.erase(start);//���ڽӵ㼯��ɾȥ
            point.insert(start);//���뵽���е㼯
            for(vector<int>::iterator it=Graph[start].begin();it!=Graph[start].end();it++){//�����ڽӵ�
                if(vis[*it]) continue;
                adjoin.insert(*it);
            }

        }


}
int main(){
	int a, b;
	freopen("H:\\��Ѷϵ��\\qq\\qq����\\112518345\\FileRecv\\���ݲֿ��������ھ�\\3\\karate.txt", "r", stdin);
	//freopen("H:\\��Ѷϵ��\\qq\\qq����\\112518345\\FileRecv\\���ݲֿ��������ھ�\\3\\S_karate.txt", "w", stdout);
	freopen("H:\\��Ѷϵ��\\qq\\qq����\\112518345\\FileRecv\\���ݲֿ��������ھ�\\3\\Answer_karate.txt", "w", stdout);
	init();
	while (scanf("%d %d",&a,&b) != EOF) {
		Graph[a].push_back(b);
		Graph[b].push_back(a);
		G[a][b] = G[b][a] = 1;
	}

    cal_similarity();
    /*
    for(int i = 1;i<=MAX_NODE;i++){
        for(int j = 1;j<=MAX_NODE;j++){
            cout<<S[i][j]<<" ";
        }
        cout<<endl;
    }
    */

    while(1){
        if(num_node>=Max_Node) break;
        mark_orgnzt++;
        cluster();
    }
/*
    int maxnum = 0;
    for(int i = 1;i<=MAX_NODE;i++){
        if(maxnum<vis[i]) maxnum=vis[i];//��¼�м��಻ͬ������
        test[vis[i]]++;//��¼ÿһ��Ľڵ����
        cout<<vis[i]<<endl;//���ÿһ���ڵ������
    }
    cout<<endl<<maxnum<<endl<<"^^^^^^^^"<<endl;
    for(int i = 0;i<=99;i++){//���ÿһ��ĸ���
        if(test[i])
        cout<<test[i]<<endl;
    }
*/
	//system("pause");
	printf("name\tclass\n");

	for(int i = 1;i<=34;i++){
        /*for(vector<int>::iterator it = Graph[i].begin();it!=Graph[i].end();it++){
            printf("")
            cout<<i<<","<<*it<<","<<vis[i]<<endl;
        }*/
        printf("%d\t%d\n",i,vis[i]);
	}

    return 0;
}
