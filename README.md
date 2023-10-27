# Trabajo_CE
En este trabajo se pretende ajustar observaciones al modelo teórico de la función de luminosidad para cúmulos globulares de Virgo. El algoritmo crea una población inicial y, a lo largo de 500 generaciones, evalúa, selecciona y cruza individuos, incorporando mutaciones (valores a modificar de acuerdo a su preferencia). Luego el algoritmo estima los parámetros $m_0$ y $\sigma$ que mejor se ajustan a los datos observados al minimizar la función de aptitud, en este caso representada por el $\chi^{2}$. 

El código se puede compilar en una terminal de Linux con **gcc ajusteflcg.c -o ajusteflcg -lm** y luego **./ajusteflcg**.
Asegurarse de tener el archivo **Lfgc.txt** en el mismo directorio.

