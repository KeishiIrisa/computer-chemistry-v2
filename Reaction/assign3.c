#include <stdio.h>
#include <math.h>

double C_0, Cs, Cs_old, Cp, Cp_old;
double Vmax, Km;
double t, dt, t_end;
double t_r[1001], Cp_r[1001];
double k1s, k2s, k3s, k4s;
double k1p, k2p, k3p, k4p;
int i, j, k, m;
char fname[100];
FILE * file;

double fCs(double t, double Cp, double Cs) {
    return - (Vmax * Cs) / (Km + Cs);
}

double fCp(double t, double Cp, double Cs) {
    return (Vmax * Cs) / (Km + Cs);
}

int main() {
    t     = 0;
    dt    = 0.001;
    t_end = 1000.0;
    j     = 1;
    k     = 0;
    m     = 1000;
    
    C_0 = 1.00;
    Cs  = C_0;
    Cp  = 0.1;
    
    t_r[0]  = t;
    Cp_r[0] = Cp;
    
    Vmax = 1.00;
    Km   = 10.0;
    
    do {
        Cs_old = Cs;
        Cp_old = Cp;
        
        k1s = fCs(t, Cp_old, Cs_old);
        k1p = fCp(t, Cp_old, Cs_old);
        
        k2s = fCs(t + 0.5*dt, Cp_old + 0.5*k1p*dt, Cs_old + 0.5*k1s*dt);
        k2p = fCp(t + 0.5*dt, Cp_old + 0.5*k1p*dt, Cs_old + 0.5*k1s*dt);
        
        k3s = fCs(t + 0.5*dt, Cp_old + 0.5*k2p*dt, Cs_old + 0.5*k2s*dt);
        k3p = fCp(t + 0.5*dt, Cp_old + 0.5*k2p*dt, Cs_old + 0.5*k2s*dt);
        
        k4s = fCs(t + dt, Cp_old + k3p*dt, Cs_old + k3s*dt);
        k4p = fCp(t + dt, Cp_old + k3p*dt, Cs_old + k3s*dt);
        
        Cs += (k1s + 2.0*k2s + 2.0*k3s + k4s) * dt / 6.0;
        Cp += (k1p + 2.0*k2p + 2.0*k3p + k4p) * dt / 6.0;
        
        t += dt;
        k += 1;
        
        if (k % m == 0) {
            t_r[j]  = t;
            Cp_r[j] = Cp;
            j += 1;
        }
    } while (t <= t_end);
    
    sprintf(fname, "read3.csv");
    file = fopen(fname, "w");
    for (i = 0; i < j; i++) {
        fprintf(file, "%f,%f\n", t_r[i], Cp_r[i]);
    }
    fclose(file);
    return 0;
}
