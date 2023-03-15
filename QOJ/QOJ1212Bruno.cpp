#include <bits/stdc++.h>
#include "Brunolib.h"

void Bruno(int K, int S, int F, int L, int P[], int Q[])
{
    for (int i = 0; i < L; ++i)
    {
        if ((S <= P[i]) != (F == Q[i]))
        {
            Answer(P[i]);
            return void();
        }
    }
    Answer(S);
}