#pragma once
// ���ȼ�����(priority first search , pfs)


//���ȼ�������ȫͼ��
template <typename Tv, typename Te> template <typename PU> 
void Graph<Tv, Te>::pfs ( int s, PU prioUpdater ) 
{
   reset(); 
   int v = s;  
   do //��һ������ж���
      if ( UNDISCOVERED == status ( v ) ) //һ��������δ���ֵĶ���
         PFS ( v, prioUpdater ); //���Ӹö����������һ��PFS
   while ( s != ( v = ( ++v % n ) ) ); //����ż�飬�ʲ�©����
}


template <typename Tv, typename Te> template <typename PU>  //�������͡������͡����ȼ�������
void Graph<Tv, Te>::PFS ( int s, PU prioUpdater ) 
{ 
    //���ȼ�������������ͨ��
   priority ( s ) = 0; 
   status ( s ) = VISITED; 
   parent ( s ) = -1; //��ʼ�������s����PFS����

   while ( 1 ) 
   { 
       //����һ����ͱ߼���PFS����
      for ( int w = firstNbr ( s ); -1 < w; w = nextNbr ( s, w ) ) //ö��s�������ھ�w
         prioUpdater ( this, s, w ); //���¶���w�����ȼ����丸����

      for ( int shortest = INT_MAX, w = 0; w < n; w++ )
         if ( UNDISCOVERED == status ( w ) ) //����δ����������Ķ�����
            if ( shortest > priority ( w ) ) //ѡ����һ��
            { 
                shortest = priority ( w ); 
                s = w; 
            } //���ȼ���ߵĶ���s
      if ( VISITED == status ( s ) ) 
          break; //ֱ�����ж�����Ѽ���
      status ( s ) = VISITED; 
      type ( parent ( s ), s ) = TREE; //��s�����丸�����߼��������
   }
}   //ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����
