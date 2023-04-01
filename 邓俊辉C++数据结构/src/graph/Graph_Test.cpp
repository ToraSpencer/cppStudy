#include "Graph_test.h"

// ������v�����㡢e���߹��ɵ����ͼ
template <typename Tv, typename Te>         //�������͡�������
void randomGraph ( GraphMatrix<Tv, Te> & g, int n, int e )
{ 
   while ( ( g.n < n ) || ( g.e < e ) ) 
   {
       //�������
      if ( g.n < n )
      { 
          //����
         if ( dice ( 100 ) < 65 )
         { 
             //65%���ʲ��붥��
            Tv vertex = ( Tv ) ( 'A' + dice ( 26 ) );     
            g.insert ( vertex );               
         } 
         else
         { 
             //35%����ɾ������
            if ( 1 > g.n ) 
                continue;
            int i = dice ( g.n );       
            Tv v = g.remove ( i );        
         }
      }

      if ( ( 1 < g.n ) && ( g.e < e ) ) 
      { 
          //��
         if ( dice ( 100 ) < 65 )
         { 
             //65%���ʲ����
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
             //35%����ɾ����
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


// �������У��ļ��ض����е���ͼ
void importGraph ( GraphMatrix<char, int> & g ) 
{
   int n; 
   scanf ( "%d\n", &n ); 
   printf ( "%d vertices\n", n );
   for ( int i = 0; i < n; i++ ) 
   { 
       //����v������
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
          //�����
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


// ͳһ������ԣ�
void test1() 
{
    srand((unsigned int)time(NULL));
    GraphMatrix<char, int> g;

    int versCount = 8;
    int edgesCount = 20;
    randomGraph<char, int>(g, versCount, edgesCount);    //�������ַ���ţ���Ϊ����Ȩ��

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


// �������ж�ȡ��������ͼ��
void test2() 
{
        


}


// ͼ�ṹ��ͳһ����
int main ( int argc, char* argv[] ) 
{
    srand((unsigned int)time(NULL));
    GraphMatrix<char, int> g;

    int versCount = 8;
    int edgesCount = 20;
    randomGraph<char, int>(g, versCount, edgesCount);           // �������ַ���ţ���Ϊ����Ȩ��

    print(g);

   return 0;
}