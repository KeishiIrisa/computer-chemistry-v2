#include <stdio.h>
#include <math.h>

double k_lag, T, alpha, X_lag0;
double k_m, k_x0, k_x;
double t, dt, t_end;
double C_sug0;
double X_act0, X_lag, X_act, X_lag_old, X_act_old;
double t_r[1001], X_act_r[1001];
double k1_lag, k2_lag, k3_lag, k4_lag;
double k1_act, k2_act, k3_act, k4_act;
int j, k, m;
char fname[100];
FILE * file;

double fX_lag(double X_act, double X_lag);
double fX_act(double X_act, double X_lag);

int main() {
    T = 10.0 + 273.15;
    k_lag = exp(30.7 - 9.5*pow(10, 3)/T);
    // k_m = exp(1.30 * pow(10, 2) - 3.83*pow(10, 4)/T);
    // k_x0 = exp(1.08*pow(10, 2) - 3.19*pow(10, 4)/T);
    t = 0;
    dt = 0.001;
    t_end = 1000.0;
    j = 1;
    k = 0; 
    m = 1000;
    X_lag0 = 2.4;
    X_act0 = 0.1;
    C_sug0 = 1.60 * pow(10, 2);
    alpha = 0.2;

    X_lag = X_lag0;
    X_act = X_act0;
    t_r[0] = t;
    X_act_r[0] = X_act0;

    do {
        X_lag_old = X_lag;
        X_act_old = X_act;

        k1_lag = fX_lag(X_act_old, X_lag_old);
        k1_act = fX_act(X_act_old, X_lag_old);

        k2_lag = fX_lag(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt);
        k2_act = fX_act(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt);

        k3_lag = fX_lag(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt);
        k3_act = fX_act(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt);

        k4_lag = fX_lag(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt);
        k4_act = fX_act(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt);

        X_lag += (k1_lag + 2*k2_lag + 2*k3_lag + k4_lag) * dt / 6.0;
        X_act += (k1_act + 2*k2_act + 2*k3_act + k4_act) * dt / 6.0;

        t += dt;
        k += 1;

        if (k % m == 0) {
            t_r[j] = t;
            X_act_r[j] = X_act;
            j += 1;
        }
    } while (t <= t_end);
    sprintf(fname, "beer1.csv");
    file = fopen(fname, "w");
    for (int i = 0; i < j; ++i) {
        fprintf(file, "%f,%f\n", t_r[i], X_act_r[i]);
    }
    fclose(file);
    return 0;
}

double fX_lag(double X_act, double X_lag) {
    return -k_lag * X_lag;
}

double fX_act(double X_act, double X_lag) {
    // lag phaseのため
    return k_lag * X_lag;
}
