#include <stdio.h>
#include <math.h>

double C_0, C, C_old, k_r;
double t, dt, t_end;
double t_r[1001], n_C[1001];
double k1, k2, k3, k4;
int i, j, k, m;
char fname[100];
FILE * file;

double f(double t, double y_C);

int main() {
    t = 0;
    dt = 0.001;
    t_end = 1000.0;
    j = 1;
    k = 0;
    m = 1000;
    k_r = 0.01;
    C_0 = 1.0;
    C = C_0;
    t_r[0] = t;
    n_C[0] = C_0;
    
    do {
        C_old = C;
        k1 = f(t, C_old);
        k2 = f(t + 0.5 * dt, C_old + 0.5 * k1 * dt);
        k3 = f(t + 0.5 * dt, C_old + 0.5 * k2 * dt);
        k4 = f(t + dt, C_old + k3 * dt);
        C += (k1 + 2 * k2 + 2 * k3 + k4) * dt / 6.0;

        t += dt;
        k += 1;

        if (k % m == 0) {
            t_r[j] = t;
            n_C[j] = C;
            j += 1;
        }
    } while(t <= t_end);
    
    sprintf(fname, "read1.csv");
    file = fopen(fname, "w");
    for (i = 0; i <= 1000; ++i) {
        fprintf(file, "%f,%f\n", t_r[i], n_C[i]);
    }

    fclose(file);
    return 0;
}


double f(double t, double y_C) {
    double f;
    f = -k_r * y_C;
    return f;
}
