struct pv
{
    double x,y;
    pv():x(0),y(0){}
    pv(double xx,double yy):x(xx),y(yy){}
    inline pv operator+(const pv &i)const
    {
        return pv(x+i.x,y+i.y);
    }
    inline pv operator-(const pv &i)const
    {
        return pv(x-i.x,y-i.y);
    }
    inline bool operator ==(const pv &i)const
    {
        return fabs(x-i.x)<eps && fabs(y-i.y)<eps;
    }
    inline bool operator<(const pv &i)const
    {
        return y==i.y?x<i.x:y<i.y;
    }
    inline double cross(const pv &i)const
    {
        return x*i.y-y*i.x;
    }
    inline int dot(const pv &i)const
    {
        return x*i.x+y*i.y;
    }
    inline double len()
    {
        return sqrt(x*x+y*y);
    }
    inline pv rotate(pv p,double theta)
    {
        static pv v;
        v=*this-p;
        static double c,s;
        c=cos(theta);
        s=sin(theta);
        return pv(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
    }
};

inline int dblcmp(double d)
{
    if(fabs(d)<eps)
        return 0;
    return d>eps?1:-1;
}

inline int cross(pv *a,pv *b) // 0不相交 1不规范 2规范
{
    int d1=dblcmp((a[1]-a[0]).cross(b[0]-a[0]));
    int d2=dblcmp((a[1]-a[0]).cross(b[1]-a[0]));
    int d3=dblcmp((b[1]-b[0]).cross(a[0]-b[0]));
    int d4=dblcmp((b[1]-b[0]).cross(a[1]-b[0]));
    if((d1^d2)==-2 && (d3^d4)==-2)
        return 2;
    return ((d1==0 && dblcmp((b[0]-a[0]).dot(b[0]-a[1]))<=0 )||
            (d2==0 && dblcmp((b[1]-a[0]).dot(b[1]-a[1]))<=0 )||
            (d3==0 && dblcmp((a[0]-b[0]).dot(a[0]-b[1]))<=0 )||
            (d4==0 && dblcmp((a[1]-b[0]).dot(a[1]-b[1]))<=0));
}

pv rotate(pv v,pv p,double theta,double sc=1) // rotate vector v, theta∈[0,2π]
{
    static pv re;
    re=p;
    v=v-p;
    p.x=sc*cos(theta);
    p.y=sc*sin(theta);
    re.x+=v.x*p.x-v.y*p.y;
    re.y+=v.x*p.y+v.y*p.x;
    return re;
}
