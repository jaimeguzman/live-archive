#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <stdio.h>

using namespace std;


//const double pi = 2*acos(0);
const double pi = 3.14159265;

struct point{
  int x,y;
  point() {}
  point(int X, int Y) : x(X), y(Y) {}
};

point pivot;

ostream& operator<< (ostream& out, const point& c)
{
  out << "(" << c.x << "," << c.y << ")";
  return out;
}

inline double dist(const point &a, const point &b){
  return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}


//retorna si c esta a la izquierda de el segmento AB
inline int cross(const point &a, const point &b, const point &c){
  return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

//Self < that si esta a la derecha del segmento Pivot-That
bool angleCmp(const point &self, const point &that){
  return( cross(pivot, that, self) < 0 );
}

inline int distsqr(const point &a, const point &b){
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

//vector p tiene los puntos ordenados anticlockwise
vector<point> graham(vector<point> p){
  pivot = p[0];
  sort(p.begin(), p.end(), angleCmp);
  //Ordenar por ángulo y eliminar repetidos.
  //Si varios puntos tienen el mismo angulo se borran todos excepto el que esté más lejos
  for (int i=1; i<p.size()-1; ++i){    
    if (cross(p[0], p[i], p[i+1]) == 0){ //Si son colineales...
      if (distsqr(p[0], p[i]) < distsqr(p[0], p[i+1])){ //Borrar el mas cercano
	p.erase(p.begin() + i);
      }else{
	p.erase(p.begin() + i + 1);
      }
      i--;
    }
  }
  
  vector<point> chull(p.begin(), p.begin()+3);

  //Ahora sí!!!
  for (int i=3; i<p.size(); ++i){
    while ( chull.size() >= 2 && cross(chull[chull.size()-2], chull[chull.size()-1], p[i]) < 0){
      chull.erase(chull.end() - 1);
    }
    chull.push_back(p[i]);
  }

  return chull;
}

int main(){
  int cases;
  cin >> cases;
  bool first = true;
  while (cases--){
    if (!first) cout << endl;
    first = false;
    int n, l;
    cin >> n >> l;
    vector<point> p;
    point min(10000000, 10000000);
    int minPos;
    for (int i=0; i<n; ++i){
      int x, y;
      cin >> x >> y;
      p.push_back(point(x,y));      
      if (y < min.y || (y == min.y && x < min.x )){
	min = point(x,y);
	minPos = i;
      }
    }

    swap(p[0], p[minPos]);
    pivot = p[0];
    vector<point> chull = graham(p);
     
    /*cout << "chull es:  " << endl;
      for (int i=0; i<chull.size(); ++i){
      cout << chull[i] << " ";
      }
      cout <<  endl;*/

    double perimeter = 0.0;
    for (int i=0; i<chull.size(); ++i){
      int j = (i+1)%chull.size();
      perimeter += dist(chull[i], chull[j]);
      //cout << " sumando " << hypot(p[i].y - p[j].y, p[i].x - p[j].x) << " entre " << p[i] << " y " << p[j] << endl;
    }

    //cout << "Perimeter es: " << perimeter << endl;
      
    //printf("%.0f\n", floor(perimeter + 2*pi*l + 0.5));
    printf("%.0lf\n", perimeter + 2*pi*l);
    //cout << (perimeter + 2*pi*l) << endl;
  }
  return 0;
}
