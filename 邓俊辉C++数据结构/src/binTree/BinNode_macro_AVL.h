#pragma once

// AVL������ƽ�����������

/*DSA*/#define HeightUpdated(x) /*�߶ȸ��³�������*/ \
/*DSA*/        ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //����ƽ������
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //ƽ������
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVLƽ������
