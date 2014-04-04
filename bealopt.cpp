// bealopt - Application to verify Beal's conjecture, as an example of program optimization
// Author: fwjmath (fwjmath - replace.by.at - gmail.com)

#include <stdio.h>
#include "mpir/mpir.h"
#include <unordered_set>

#define BASE_MAX 1000
#define EXPO_MAX 1000
#define MODP1(X) ((X) % 4294967291ULL)
#define MODP2(X) ((X) % 4294967279ULL)
#define YIELD(X,A,Y,B) printf("%u ^ %u + %u ^ %u\n", X, A, Y, B);

using namespace std;

unordered_set< unsigned long long > p1hash, p2hash;

unsigned long long h1cnt, h2cnt, candcnt;

void build_hash(){
	p1hash.clear();
	p2hash.clear();
	for(unsigned int z=1; z<=BASE_MAX; z++){
		unsigned long long zp1=MODP1(MODP1(z*z)*z), zp2=MODP2(MODP2(z*z)*z);
		p1hash.insert(zp1);
		p2hash.insert(zp2);
		for(unsigned int c=4; c<=EXPO_MAX; c++){
			zp1=MODP1(zp1*z);
			zp2=MODP2(zp2*z);
			p1hash.insert(zp1);
			p2hash.insert(zp2);
		}
	}
	printf("Finished constructing lookup table.\n");
	return;
}

void init(){
	h1cnt=0; h2cnt=0; candcnt=0;
	build_hash();
	return;
}

unsigned long long ullgcd(unsigned long long a, unsigned long long b){
	unsigned long long c,d,e;
	if(a>b){ c=b; d=a; } else { c=a; d=b; }
	while(c){
		d-=c;
		if(d>c){
			d-=c;
			if(d>c){
				d-=c;
				if(d>c){
					d%=c;
				}
			}
		}
		e=c;
		c=d;
		d=e;
	}
	return d;
}

unsigned long long fastexpP2(unsigned int base, unsigned int expo){
	unsigned long long res=1, tmp=base;
	unsigned int c=expo;
	if(c&1) res=MODP2(tmp*res);
	c>>=1;
	while(c){
		tmp=MODP2(tmp*tmp);
		if(c&1) res=MODP2(tmp*res);
		c>>=1;
	}
	return res;
}

void search(){
	unsigned long long xp1, xp2, yp1, yp2;
	for(unsigned int x=2; x < BASE_MAX; x++){
		xp1=MODP1(x*x);
		for(unsigned int a=3; a <= EXPO_MAX; a++){
			xp1=MODP1(xp1*x);
			for(unsigned int y=x+1; y <= BASE_MAX; y++){
				if(ullgcd(x,y)!=1) continue;
				yp1=MODP1(y*y);
				for(unsigned int b=3; b <= EXPO_MAX; b++){
					yp1=MODP1(yp1*y);
					candcnt++;
					if(p1hash.find(MODP1(xp1+yp1))!=p1hash.end()){
						h1cnt++;
						xp2=fastexpP2(x,a);
						yp2=fastexpP2(y,b);
						if(p2hash.find(MODP2(xp2+yp2))!=p2hash.end()){
							h2cnt++;
							YIELD(x,a,y,b);
						}
					}
				}
			}
		}
	}
	return;
}

int main(){
	init();
	search();
	printf("Candidates: %llu\nHash1: %llu\nHash2: %llu\n", candcnt, h1cnt, h2cnt);
	return 0;
}