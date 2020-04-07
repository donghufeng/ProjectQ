<!-- # __m256d 包含4个double类型数字的向量

# __m256d neg = _mm256_setr_pd(1.0, -1.0, 1.0, -1.0)
# 初始化一个__m256d

# _mm256_add_pd 两个__m256d相加
# _mm256_mul_pd 。。。

import numpy as np

def mul(a, b, c):
    ac_bd = a*b
    multbmadmc = a*c
    return np.array([ac_bd[1]-ac_bd[0],
                     multbmadmc[1]-multbmadmc[0],
                     ac_bd[3]-ac_bd[2],
                     multbmadmc[3]-multbmadmc[2]]) -->

$$v_0=[e_r,e_i,e_r,e_i]$$
$$v_1=[f_r,f_i,f_r,f_i]$$
$$m=\begin{pmatrix}
a&b\\
c&d
\end{pmatrix}$$
$$mm=[[a_r,a_i,c_r,c_i],[b_r,b_i,d_r,d_i]]$$
$$mmt=[[a_i,-a_r,c_i,-c_r],[b_i,-b_r,d_i,-d_r]]$$

# 1
$$mul(v_0,m_0,mt_0)=[e_ia_i-e_ra_r,-e_ia_r-e_ra_i,e_ic_i-e_rc_r,-e_ic_r-e_rc_i]=[-(ea)_r,-(ea)_i,-(ec)_r,-(ec)_i]$$
$$acbd=[e_ra_r,e_ia_i,e_rc_r,e_ic_i]$$
$$multbmadmc=[e_ra_i,-e_ia_r,e_rc_i,-e_ic_r]$$

# 2
$$mul(v_1,m_1,mt_1)=[f_ib_i-f_rb_r,-f_ib_r-f_rb_i,0,0]=[-(fb)_r,-(fb)_i,-(fd)_r,-(fd)_i]$$
$$acbd=[f_rb_r,f_ib_i,0,0]$$
$$multbmadmc=[f_rb_i,-f_ib_r,0,0]$$

# 3
$$add=[-(ea+fb)_r,-(ea+fb)_i,-(ec+fd)_r,-(ec+fd)_i]=[-g_r,-g_i,-h_r,-h_i]$$