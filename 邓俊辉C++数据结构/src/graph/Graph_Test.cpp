#include "Graph_test.h"

// 生成由v个顶点、e条边构成的随机图
template <typename Tv, typename Te>         //顶点类型、边类型
void randomGraph ( GraphMatrix<Tv, Te> & g, int n, int e )
{ 
   while ( ( g.n < n ) || ( g.e < e ) ) 
   {
       //随机测试
      if ( g.n < n )
      { 
          //顶点
         if ( dice ( 100 ) < 65 )
         { 
             //65%概率插入顶点
            Tv vertex = ( Tv ) ( 'A' + dice ( 26 ) );     
            g.insert ( vertex );               
         } 
         else
         { 
             //35%概率删除顶点
            if ( 1 > g.n ) 
                continue;
            int i = dice ( g.n );       
            Tv v = g.remove ( i );        
         }
      }

      if ( ( 1 < g.n ) && ( g.e < e ) ) 
      { 
          //边
         if ( dice ( 100 ) < 65 )
         { 
             //65%概率插入边
            int i = dice ( g.n ), j = dice ( g.n ); 
            Te e = dice ( ( Te ) 3 * n );
             if (!g.exists(i, j))
            {
               //g.insert ( e, e, i, j );     
                 g.insert(e, 1, i, j);
            }
         } 
         else 
         { 
             //35%概率删除边
            int i = dice ( g.n ), j = dice ( g.n );
            if ( g.exists ( i, j ) )
            {
               Te e = g.remove ( i, j );  
            } 
         }
      }
   }

   for ( int i = 0; i < n; i++ ) 
       g.vertex ( i ) = 'A' + i;
}


// 从命令行（文件重定向）中导入图
void importGraph ( GraphMatrix<char, int> & g ) 
{
   int n; 
   scanf ( "%d\n", &n ); 
   printf ( "%d vertices\n", n );
   for ( int i = 0; i < n; i++ ) 
   { 
       //插入v个顶点
      char vertex; 
      scanf ( "%c", &vertex );  
      printf ( "Inserting vertex" ); 
      print ( vertex ); 
      printf ( " ..." );
      g.insert ( vertex );                  
      printf ( "done\n" ); 
      print ( g );
   }

   for ( int i = 0; i < n; i++ )
   { 
      for ( int j = 0; j < n; j++ )
      { 
          //插入边
         int edge; 
         scanf ( "%d", &edge );

         if ( 0 > edge ) 
             continue;     

         printf ( "Inserting edge (%d, %d) = ", i, j ); 
         print ( edge ); 
         printf ( " ..." );
         g.insert ( edge, edge, i, j );       
         printf ( "done\n" );
      }
   }
}


// 统一随机测试：
void test1() 
{
    srand((unsigned int)time(NULL));
    GraphMatrix<char, int> g;

    int versCount = 8;
    int edgesCount = 20;
    randomGraph<char, int>(g, versCount, edgesCount);    //顶点以字符编号，边为整数权重

    printf("\n");
    print(g);
    printf("=== BFS\n");
    g.bfs(0);
    print(g);
    printf("=== BFS (PFS)\n");
    g.pfs(0, BfsPU<char, int>()); print(g);
    printf("=== DFS\n");
    g.dfs(0); print(g);
    printf("=== DFS (PFS)\n");
    g.pfs(0, DfsPU<char, int>()); print(g);
    printf("=== TopoSort\n");
    Stack<char>* ts = g.tSort(0);  print(ts); print(g); release(ts);
    printf("=== BCC\n");
    g.bcc(0); print(g);
    printf("=== Prim\n");
    g.prim(0); print(g);
    printf("=== Prim (PFS)\n");
    g.pfs(0, PrimPU<char, int>()); print(g);
    printf("=== Dijkstra\n");
    g.dijkstra(0); print(g);
    printf("=== Dijkstra (PFS)\n");
    g.pfs(0, DijkPU<char, int>()); print(g);
}


// 从数组中读取数据生成图：
void test2() 
{
        


}


// 图结构的统一测试
int main ( int argc, char* argv[] ) 
{
    srand((unsigned int)time(NULL));
    GraphMatrix<char, int> g;

    int versCount = 8;
    int edgesCount = 20;
    randomGraph<char, int>(g, versCount, edgesCount);           // 顶点以字符编号，边为整数权重

    print(g);

   return 0;
}