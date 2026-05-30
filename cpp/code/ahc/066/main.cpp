#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <climits>
#include <chrono>
#include <random>
#include <cmath>
#include <unordered_map>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;

int N,M,T; vector<string> v,h;
const int dr[]={0,1,0,-1},dc2[]={1,0,-1,0};
bool canMove(int i,int j,int d){
    int ni=i+dr[d],nj=j+dc2[d];
    if(ni<0||ni>=N||nj<0||nj>=N) return false;
    switch(d){case 0:return v[i][j]=='0';case 1:return h[i][j]=='0';
              case 2:return v[i][nj]=='0';case 3:return h[ni][j]=='0';}return false;
}
inline int cellId(int i,int j){return i*N+j;}
inline int stateId(int i,int j,int d){return cellId(i,j)*4+d;}
string moveTo(int& ri,int& rj,int& rdir,int ti,int tj){
    if(ri==ti&&rj==tj) return "";
    int S4=N*N*4; vector<int> dist(S4,-1),ps(S4,-1); vector<char> po(S4,0);
    int src=stateId(ri,rj,rdir); queue<int> q; q.push(src); dist[src]=0;
    while(!q.empty()){
        int s=q.front();q.pop(); int ci=s/4/N,cj=(s/4)%N,cd=s%4;
        auto add=[&](int ns,char op){if(dist[ns]==-1){dist[ns]=dist[s]+1;ps[ns]=s;po[ns]=op;q.push(ns);}};
        add(stateId(ci,cj,(cd+1)%4),'R'); add(stateId(ci,cj,(cd+3)%4),'L');
        if(canMove(ci,cj,cd)) add(stateId(ci+dr[cd],cj+dc2[cd],cd),'F');
    }
    int dc=cellId(ti,tj),bs=-1,bd=INT_MAX;
    for(int d=0;d<4;d++){int s=dc*4+d;if(dist[s]!=-1&&dist[s]<bd){bd=dist[s];bs=s;}}
    string ops; int s=bs;
    while(s!=src){ops+=po[s];s=ps[s];} reverse(ops.begin(),ops.end());
    ri=ti;rj=tj;rdir=bs%4; return ops;
}
// マクロ圧縮: 文字列sの中で節約最大の繰り返しパターンを1つ見つけてM/Pで圧縮
// 節約 = (k-1)*(L-1)-2 > 0 のとき適用 (k=非重複出現回数, L=パターン長)
// 圧縮後長さが T_lim 以下の場合のみ採用
string macroCompress(const string& s, int T_lim){
    int A=(int)s.size();
    int bsave=0; string bpat;
    int maxL=min(A/2,200);
    for(int L=4;L<=maxL;L++){
        unordered_map<string,vector<int>> occ;
        for(int i=0;i+L<=A;i++) occ[s.substr(i,L)].push_back(i);
        for(auto& [pat,ps]:occ){
            if((int)ps.size()<2) continue;
            int cnt=0,prev=-L;
            for(int p:ps) if(p>=prev+L){cnt++;prev=p;}
            int save=(cnt-1)*(L-1)-2;
            if(save>bsave){bsave=save;bpat=pat;}
        }
    }
    if(bsave<=0) return s;
    string res; bool first=true; size_t sc=0,A2=s.size();
    while(sc<=A2){
        size_t f=s.find(bpat,sc);
        if(f==string::npos||f>A2){res+=s.substr(sc);break;}
        res+=s.substr(sc,f-sc);
        if(first){res+='M';res+=bpat;res+='M';first=false;}
        else res+='P';
        sc=f+bpat.size();
    }
    return ((int)res.size()<=T_lim) ? res : s;
}
void solve(){
    auto t0=chrono::steady_clock::now();
    auto ms=[&]()->double{return chrono::duration<double,milli>(chrono::steady_clock::now()-t0).count();};
    cin>>N>>M>>T; v.resize(N);h.resize(N-1);
    for(int i=0;i<N;i++) cin>>v[i]; for(int i=0;i<N-1;i++) cin>>h[i];
    vector<array<int,4>> balls(M);
    for(int k=0;k<M;k++) cin>>balls[k][0]>>balls[k][1]>>balls[k][2]>>balls[k][3];
    int C=N*N,S4=C*4;
    vector<vector<int>> dadist(S4,vector<int>(C,INT_MAX)),dafdir(S4,vector<int>(C,0));
    for(int si=0;si<N;si++) for(int sj=0;sj<N;sj++) for(int sd=0;sd<4;sd++){
        int src=stateId(si,sj,sd); vector<int> dist(S4,-1); queue<int> q; q.push(src); dist[src]=0;
        while(!q.empty()){
            int s=q.front();q.pop(); int ci=s/4/N,cj=(s/4)%N,cd=s%4;
            auto add=[&](int ns){if(dist[ns]==-1){dist[ns]=dist[s]+1;q.push(ns);}};
            add(stateId(ci,cj,(cd+1)%4)); add(stateId(ci,cj,(cd+3)%4));
            if(canMove(ci,cj,cd)) add(stateId(ci+dr[cd],cj+dc2[cd],cd));
        }
        for(int ti=0;ti<N;ti++) for(int tj=0;tj<N;tj++){
            int dst=cellId(ti,tj),bc=INT_MAX,bd=0;
            for(int td=0;td<4;td++){int s=dst*4+td;if(dist[s]!=-1&&dist[s]<bc){bc=dist[s];bd=td;}}
            dadist[src][dst]=bc;dafdir[src][dst]=bd;
        }
    }
    auto dc=[&](int s,int d)->int{return dadist[s][d];};
    auto df=[&](int s,int d)->int{return dafdir[s][d];};
    using Plan=vector<pair<int,int>>;
    auto planCost=[&](const Plan& p)->int{
        int cost=0,pI=0,pJ=0,pD=0;
        for(int ei=0;ei<(int)p.size();ei++){
            int k=p[ei].first,j=p[ei].second;
            auto nav=[&](int ti,int tj){
                int s=stateId(pI,pJ,pD),d=cellId(ti,tj);
                cost+=dc(s,d)+1; pD=df(s,d); pI=ti; pJ=tj;
            };
            if(j<0){nav(balls[k][0],balls[k][1]);nav(balls[k][2],balls[k][3]);}
            else{nav(balls[k][0],balls[k][1]);nav(balls[j][0],balls[j][1]);
                 nav(balls[j][2],balls[j][3]);nav(balls[j][0],balls[j][1]);
                 nav(balls[k][2],balls[k][3]);}
        } return cost;
    };
    auto orderCost=[&](const vector<int>& ord)->int{
        int cost=0,ci=0,cj=0,cd=0;
        for(int k:ord){
            int src=stateId(ci,cj,cd); int db=cellId(balls[k][0],balls[k][1]);
            cost+=dc(src,db)+1; cd=df(src,db); ci=balls[k][0];cj=balls[k][1];
            src=stateId(ci,cj,cd); int dk=cellId(balls[k][2],balls[k][3]);
            cost+=dc(src,dk)+1; cd=df(src,dk); ci=balls[k][2];cj=balls[k][3];
        } return cost;
    };
    // Step1: 2-step lookahead greedy
    vector<int> order; order.reserve(M);
    {
        vector<bool> done(M,false); int ri=0,rj=0,rd=0;
        for(int iter=0;iter<M;iter++){
            int cs=stateId(ri,rj,rd),bk=-1,bc=INT_MAX;
            for(int k1=0;k1<M;k1++){
                if(done[k1]) continue;
                int b1=cellId(balls[k1][0],balls[k1][1]),s1=cellId(balls[k1][2],balls[k1][3]);
                int cb=dc(cs,b1),s1st=s1*4+df(b1*4+df(cs,b1),s1);
                int mn=0;bool hk=false;
                for(int k2=0;k2<M;k2++){
                    if(done[k2]||k2==k1) continue;
                    int t=dc(s1st,cellId(balls[k2][0],balls[k2][1]));
                    if(!hk||t<mn){mn=t;hk=true;}
                }
                int tot=cb+mn; if(tot<bc){bc=tot;bk=k1;}
            }
            if(bk==-1) break; done[bk]=true; order.push_back(bk);
            int b=cellId(balls[bk][0],balls[bk][1]),s=cellId(balls[bk][2],balls[bk][3]);
            rd=df(cs,b); rd=df(b*4+rd,s); ri=balls[bk][2];rj=balls[bk][3];
        }
    }
    // Step2: 山登り法 warm-start
    int best_cost=orderCost(order);
    {
        bool impr=true;
        while(impr){
            impr=false; int bi=-1,bj=-1,bd=0;
            for(int i=0;i<M;i++) for(int j=i+1;j<M;j++){
                swap(order[i],order[j]); int d=orderCost(order)-best_cost;
                if(d<bd){bd=d;bi=i;bj=j;} swap(order[i],order[j]);
            }
            if(bi!=-1){swap(order[bi],order[bj]);best_cost+=bd;impr=true;}
        }
        impr=true;
        while(impr){
            impr=false; int bf=-1,bt=-1,bd=0;
            for(int i=0;i<M;i++){
                int ki=order[i]; vector<int> tmp; tmp.reserve(M-1);
                for(int x=0;x<M;x++) if(x!=i) tmp.push_back(order[x]);
                for(int j=0;j<=M-1;j++){
                    tmp.insert(tmp.begin()+j,ki); int d=orderCost(tmp)-best_cost;
                    if(d<bd){bd=d;bf=i;bt=j;} tmp.erase(tmp.begin()+j);
                }
            }
            if(bf!=-1){int ki=order[bf];order.erase(order.begin()+bf);order.insert(order.begin()+bt,ki);best_cost+=bd;impr=true;}
        }
    }
    // Step3: Plan初期化 + 貪欲リレー warm-start
    Plan gbest; for(int k:order) gbest.push_back({k,-1});
    int gbest_c=planCost(gbest);
    auto greedyRelay=[&](Plan& p,int& pc){
        bool impr=true;
        while(impr){
            impr=false; int bi=-1,bj=-1,bd=0;
            for(int i=0;i<(int)p.size();i++){
                if(p[i].second>=0) continue;
                for(int jp=0;jp<(int)p.size();jp++){
                    if(jp==i||p[jp].second>=0) continue;
                    Plan np; np.reserve(p.size()-1);
                    for(int x=0;x<(int)p.size();x++){
                        if(x==jp) continue;
                        np.push_back(x==i?make_pair(p[i].first,p[jp].first):p[x]);
                    }
                    int d=planCost(np)-pc; if(d<bd){bd=d;bi=i;bj=jp;}
                }
            }
            if(bi>=0){
                Plan np; np.reserve(p.size()-1);
                for(int x=0;x<(int)p.size();x++){
                    if(x==bj) continue;
                    np.push_back(x==bi?make_pair(p[bi].first,p[bj].first):p[x]);
                }
                p=np; pc+=bd; impr=true;
            }
        }
    };
    greedyRelay(gbest,gbest_c);
    // Step4: リレー統合 ILS SA
    if(M>=2){
        const double TE=0.1,TB=1750.0; const int NR=3;
        double TS=max(5.0,(double)gbest_c/(int)gbest.size()*0.4);
        mt19937 rng(12345); uniform_real_distribution<double> uni(0.0,1.0);
        for(int run=0;run<NR;run++){
            double tl=TB-ms(); if(tl<50) break;
            double rb=tl/(NR-run),rs=ms(),re=rs+rb;
            Plan cur=gbest;
            if(run>0){
                int kicks=max(2,(int)cur.size()/4);
                for(int k=0;k<kicks;k++){
                    int n2=(int)cur.size(),i=rng()%n2;
                    if(cur[i].second>=0&&rng()%3==0){
                        int j=cur[i].second; cur[i].second=-1;
                        cur.insert(cur.begin()+(rng()%(cur.size()+1)),{j,-1});
                    } else {
                        auto e=cur[i]; cur.erase(cur.begin()+i);
                        cur.insert(cur.begin()+(rng()%(cur.size()+1)),e);
                    }
                }
            }
            int cur_c=planCost(cur); Plan rbest=cur; int rbest_c=cur_c;
            double crt=rs,temp=TS; long long iter=0;
            while(true){
                if((++iter&1023)==0){crt=ms();if(crt>=re)break;temp=TS*pow(TE/TS,min((crt-rs)/rb,1.0));}
                int n=(int)cur.size(); if(n<1) continue;
                Plan nc; bool ok=true; int mt=rng()%5;
                if(mt<=1){
                    if(n<2){ok=false;}
                    else if(mt==0){int i=rng()%n,j=rng()%n;if(i==j){ok=false;}else{nc=cur;swap(nc[i],nc[j]);}}
                    else{int i=rng()%n;nc=cur;auto e=nc[i];nc.erase(nc.begin()+i);nc.insert(nc.begin()+(rng()%(nc.size()+1)),e);}
                } else if(mt==2){
                    vector<int> fi; for(int i=0;i<n;i++) if(cur[i].second<0) fi.push_back(i);
                    if((int)fi.size()<2){ok=false;}
                    else{int a=rng()%fi.size(),b=rng()%(fi.size()-1);if(b>=a)b++;
                         int pi=fi[a],pj=fi[b];
                         for(int x=0;x<n;x++){if(x==pj)continue;nc.push_back(x==pi?make_pair(cur[pi].first,cur[pj].first):cur[x]);}
                    }
                } else if(mt==3){
                    vector<int> ri2; for(int i=0;i<n;i++) if(cur[i].second>=0) ri2.push_back(i);
                    if(ri2.empty()){ok=false;}
                    else{int idx=ri2[rng()%ri2.size()],k=cur[idx].first,j=cur[idx].second;
                         for(int x=0;x<n;x++){if(x==idx)nc.push_back({k,-1});else nc.push_back(cur[x]);}
                         nc.insert(nc.begin()+(rng()%(nc.size()+1)),{j,-1});}
                } else {
                    vector<int> ri2,fi;
                    for(int i=0;i<n;i++){if(cur[i].second>=0)ri2.push_back(i);else fi.push_back(i);}
                    if(ri2.empty()||fi.empty()){ok=false;}
                    else{int ridx=ri2[rng()%ri2.size()],fidx=fi[rng()%fi.size()];
                         int k=cur[ridx].first,oj=cur[ridx].second,nj=cur[fidx].first;
                         for(int x=0;x<n;x++){if(x==fidx)continue;nc.push_back(x==ridx?make_pair(k,nj):cur[x]);}
                         nc.insert(nc.begin()+(rng()%(nc.size()+1)),{oj,-1});}
                }
                if(!ok) continue;
                int new_c=planCost(nc),delta=new_c-cur_c;
                if(delta<0||uni(rng)<exp(-delta/temp)){
                    cur=nc;cur_c=new_c;if(cur_c<rbest_c){rbest_c=cur_c;rbest=cur;}
                }
            }
            if(rbest_c<gbest_c){gbest_c=rbest_c;gbest=rbest;}
        }
    }
    // Step5: 操作列生成 (T文字を上限に生成してからマクロ圧縮)
    // T文字分のF/R/L/S = T回のbasic操作を生成し、圧縮で短縮する
    // ※T切り捨て後に圧縮すると、M/P文字がbasic操作数を消費しないため
    //   T文字の出力でbasic操作 < T になりボール配達数が減るため、この順序が正しい
    string result; int ri=0,rj=0,rd=0;
    for(int ei=0;ei<(int)gbest.size();ei++){
        int k=gbest[ei].first,j=gbest[ei].second;
        if(j<0){result+=moveTo(ri,rj,rd,balls[k][0],balls[k][1]);result+='S';
                 result+=moveTo(ri,rj,rd,balls[k][2],balls[k][3]);result+='S';}
        else{result+=moveTo(ri,rj,rd,balls[k][0],balls[k][1]);result+='S';
             result+=moveTo(ri,rj,rd,balls[j][0],balls[j][1]);result+='S';
             result+=moveTo(ri,rj,rd,balls[j][2],balls[j][3]);result+='S';
             result+=moveTo(ri,rj,rd,balls[j][0],balls[j][1]);result+='S';
             result+=moveTo(ri,rj,rd,balls[k][2],balls[k][3]);result+='S';}
        if((int)result.size()>=T) break;
    }
    if((int)result.size()>T) result.resize(T);
    // Step6: マクロ圧縮 (T以内のF/R/L/S列に対して適用)
    result = macroCompress(result, T);
    for(char c:result) cout<<c<<'\n';
}
int main(){ios_base::sync_with_stdio(false);cin.tie(nullptr);solve();return 0;}