#include <bits/stdc++.h>

#define fa (x >> 1)
#define ls (x << 1)
#define rs (x << 1 | 1)

static constexpr int N = 2e5 + 5;
int n;
int a[N], now[N], ans[N], type[N];
// 0 -> both 1 -> left 2 -> right
bool vis[N], use[N];

void cmin(int &x, int y) {x = std::min(x, y);}
int find(int x, int from) {

}
int find(int u,int from){
	int mn=MAXN;
	for(;u;u=fa){
		if(type[u]==1) break;
		if(from==1&&type[u]==2) break;
		if(from==1){
			if(!vis[x[u]]) 
				if (type[u]==3)
					if (!(type[fa]==3&&now[fa]==1)&&now[u]!=1&&!use[u])
						cmin(mn,x[u]);
			if(!vis[x[lson]]&&type[u]==3&&now[u]!=2&&lson<=N) cmin(mn,x[lson]);
		}
		else if(from==2){
			if(lson<=N) cmin(mn,x[lson]);
			if(rson<=N) cmin(mn,x[rson]);
			if(!vis[x[u]]&&!(type[fa]==3&&now[fa]==1)) cmin(mn,x[u]);
		}
		else{
			if(!vis[x[u]]&&((type[u]==2&&now[u]==0)||(type[u]==3&&now[u]!=2&&!use[u]))&&!(type[fa]==3&&now[fa]==1)) 
			cmin(mn,x[u]);
		}
		if(type[u]==2&&now[u]==1) break;
		if(type[u]==3&&now[u]&&(use[u]||now[u]!=from+1)) break;
		from=u&1;
	}
	return mn;
}
void change(int u){
	if(ans[u]==x[lson]) type[u]=2;
	else if(ans[u]==x[rson]) type[u]=3;
	else type[u]=1;
}
void update(int u){
	int from=u&1,t=ans[u];
	if(type[u]==2||type[u]==3) return;
	if(x[u]==t) return;
	for(u=fa;u;u=fa){
        printf("%d\n", u);
		if(x[u]==t){
			use[u]=1;
			if(type[u]==2) now[u]=1;
			else now[u]=from+1;
			return;
		}
		else if(x[lson]==t){
			now[u]=1;
			return;
		}
		else{
			use[u]=1;
			now[u]=from+1;
		}
        from=u&1;
	}
}   
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) {
		ans[i] = find(i, 2);
		vis[ans[i]] = 1;
		change(i);
		update(i); 
	}
	for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}