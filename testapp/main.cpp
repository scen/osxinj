#include <cstdio>
#include <unistd.h>

int sigscan_me()
{
    int ret = printf("sigscan_me()\n");
    ret += 3;
    ret *= 3;
    ret ^= 3;
    ret &= 3;
    return ret;
}

//class entity
//{
//public:
//    entity(int x) { a = x; }
//    
//    virtual void aa() {}
//    virtual int bb(int cc){return cc;}
//    virtual void cc(int dd) {return;}
//    virtual float ff(int ee) {return (float)ee;}
//    virtual double lol(int test) {return (double)test;}
//    virtual void test(int x, int y, int z, int zz) { printf("abcd %d %d %d %d %d\n", a, x, y, z, zz); }
//    virtual long long gg(int jj) { return jj + 3; }
//    
//    int a, b, c, d, e;
//};

int main(int argc, char* argv[])
{
    printf("testapp reporting in!\n");
//    int x;
//    scanf("%d", &x);
//    entity* e = new entity(x);
//    e->test(1, 2, 3, 4);
    sleep(100000000);
    return 0;
}