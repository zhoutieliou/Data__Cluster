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
    for(int i = 1;i<=Max_Node;i++){//计算结点相似性
        for(int j = 1;j<=Max_Node;j++){
            if(S[i][j]) {//对称矩阵 算过得就不算了
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
                if( that!=temp.end() )//在i中有这个结点
                    intersection++;//公共邻居+1
                else
                    uni++;//邻居节点的并+1
            }
            S[i][j] = S[j][i] = (double)((double)intersection/(double)uni);
        }
        //cout<<endl;
	}
}
void cluster(){
        int start = get_point();
        vis[start] = mark_orgnzt;//给结点涂色 1~n
        num_node++;//使用了的结点数增加
        double midu = 1;//社团密度
        int num = 1;//该社团所有结点
        int ideal_egde = num*(num-1)/2;//完全边数
        int sum_edge = 0;//已有总边数
        set<int> adjoin;//所有邻接点
        set<int> point;//社团所有点
        adjoin.clear();
        point.clear();
        point.insert(start);//初始化
        for(vector<int>::iterator it=Graph[start].begin();it!=Graph[start].end();it++){
            if(vis[*it]) continue;
            adjoin.insert(*it);
        }
        while(midu>=threshold){
            int temp_edge = 0;//该次最大边数
            for(set<int>::iterator it = adjoin.begin();it!=adjoin.end();it++){//从邻接结点集选择
                int temp = 0;//邻接点与已有图相连的边数
                if(vis[*it]) continue;
                for(set<int>::iterator that = point.begin();that!=point.end();that++){//新增点与已有图边数最多的 一定使图密度下降最少
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
            if(midu<threshold){//如果新加入的点使密度小于阈值则结束
                sum_edge-=temp_edge;
                break;
            }

            vis[start] = mark_orgnzt;
            num++;
            num_node++;
            adjoin.erase(start);//从邻接点集中删去
            point.insert(start);//加入到已有点集
            for(vector<int>::iterator it=Graph[start].begin();it!=Graph[start].end();it++){//新增邻接点
                if(vis[*it]) continue;
                adjoin.insert(*it);
            }

        }


}
int main(){
	int a, b;
	freopen("H:\\腾讯系列\\qq\\qq下载\\112518345\\FileRecv\\数据仓库与数据挖掘\\3\\karate.txt", "r", stdin);
	//freopen("H:\\腾讯系列\\qq\\qq下载\\112518345\\FileRecv\\数据仓库与数据挖掘\\3\\S_karate.txt", "w", stdout);
	freopen("H:\\腾讯系列\\qq\\qq下载\\112518345\\FileRecv\\数据仓库与数据挖掘\\3\\Answer_karate.txt", "w", stdout);
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
        if(maxnum<vis[i]) maxnum=vis[i];//记录有几类不同的社团
        test[vis[i]]++;//记录每一类的节点个数
        cout<<vis[i]<<endl;//输出每一个节点的类别号
    }
    cout<<endl<<maxnum<<endl<<"^^^^^^^^"<<endl;
    for(int i = 0;i<=99;i++){//输出每一类的个数
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
