#include <stdio.h>
#include <math.h>

double k_lag, T, alpha, X_lag0;
double k_m, k_x0, k_x;
double t, dt, t_end;
double C_sug, C_sug_old, C_eth, C_eth_old, C_ace, C_ace_old, C_dia, C_dia_old;
double C_sug0, C_eth0, C_ace0, C_dia0;
double X_act0, X_lag, X_act, X_lag_old, X_act_old;
double t_r[101];
double k1_lag, k2_lag, k3_lag, k4_lag;
double k1_act, k2_act, k3_act, k4_act;
double k1_sug, k2_sug, k3_sug, k4_sug;
double k1_eth, k2_eth, k3_eth, k4_eth;
double k1_ace, k2_ace, k3_ace, k4_ace;
double k1_dia, k2_dia, k3_dia, k4_dia;
double k_sug, k_eth, k_ace, k_dia, k_dc, k_dm;
double k_sug0, k_eth0, k_ace0, k_dia0;
double sigma_sug, ganmma_sug, ganmma_eth, ganmma_ace, ganmma_dia;
double T_options[6];
double T_pre, T_post;

int m;
char fname[100];
FILE * file;

double fX_lag(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia);
double fX_act(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia);
double fC_sug(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia);
double fC_eth(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia);
double fC_ace(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia);
double fC_dia(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia);

int main() {
    T_options[0] = 13.0 + 273.15;
    T_options[1] = 14.0 + 273.15;
    T_options[2] = 15.0 + 273.15;
    T_options[3] = 16.0 + 273.15;
    T_options[4] = 17.0 + 273.15;
    T_options[5] = 18.0 + 273.15;
    t_r[0] = t;

    sprintf(fname, "beer_manufacturing_results.csv");
    file = fopen(fname, "w");
    fprintf(file, "T_pre,T_post,ManufacturingTime,C_dia\n");
    for (int ip = 0; ip < 6; ip++) {
        for (int jp = 0; jp < 6; jp++) {
            double T_pre = T_options[ip];
            double T_post = T_options[jp];
            T = T_pre;
            k_lag = exp(30.7 - 9.5*pow(10, 3)/T);
            k_m = exp(1.30 * pow(10, 2) - 3.83 * pow(10, 4)/T);
            k_x0 = exp(1.08 * pow(10, 2) - 3.19 * pow(10, 4)/T);
            k_m = exp(1.30 * pow(10, 2) - 3.83 * pow(10, 4) / T);
            k_sug0 = exp(-41.9 + 1.17 * pow(10, 4) / T);
            sigma_sug = exp(-1.20 * pow(10, 2) + 3.42 * pow(10, 4) / T);
            k_eth0 = exp(3.27 - 1.27 * pow(10, 3) / T);
            ganmma_ace = exp(89.9 - 2.76 * pow(10, 4) / T);
            k_dc = 1.28 * pow(10, -4);
            k_dm = 1.20 * pow(10, -3);
            t = 0;
            dt = 0.001;
            t_end = 100;
            m = 1000;
            X_lag0 = 2.4;
            X_act0 = 0.1;
            C_sug0 = 1.60 * pow(10, 2);
            C_eth0 = 0.0;
            C_ace0 = 0.0;
            C_dia0 = 0.0;
            alpha = 0.2;
        
            X_lag = X_lag0;
            X_act = X_act0;
            C_sug = C_sug0;
            C_eth = C_eth0;
            C_ace = C_ace0;
            C_dia = C_dia0;

            do {
                X_lag_old = X_lag;
                X_act_old = X_act;
                C_sug_old = C_sug;
                C_eth_old = C_eth;
                C_ace_old = C_ace;
                C_dia_old = C_dia;
                k_x = k_x0 * C_sug_old / (0.5 * C_sug0 + C_eth_old);
                k_sug = k_sug0 * C_sug_old / (sigma_sug + C_sug_old);
                k_eth = (1 - C_eth_old / (0.5 * C_sug0)) * k_eth0 * C_sug_old / (sigma_sug + C_sug_old);
        
                k1_lag = fX_lag(X_act_old, X_lag_old, C_sug_old, C_eth_old, C_ace_old, C_dia_old);
                k1_act = fX_act(X_act_old, X_lag_old, C_sug_old, C_eth_old, C_ace_old, C_dia_old);
                k1_sug = fC_sug(X_act_old, X_lag_old, C_sug_old, C_eth_old, C_ace_old, C_dia_old);
                k1_eth = fC_eth(X_act_old, X_lag_old, C_sug_old, C_eth_old, C_ace_old, C_dia_old);
                k1_ace = fC_ace(X_act_old, X_lag_old, C_sug_old, C_eth_old, C_ace_old, C_dia_old);
                k1_dia = fC_dia(X_act_old, X_lag_old, C_sug_old, C_eth_old, C_ace_old, C_dia_old);
        
                k2_lag = fX_lag(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt, C_sug_old + 0.5 * k1_sug * dt, C_eth_old + 0.5 * k1_eth * dt, C_ace_old + 0.5 * k1_ace * dt, C_dia_old + 0.5 * k1_dia * dt);
                k2_act = fX_act(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt, C_sug_old + 0.5 * k1_sug * dt, C_eth_old + 0.5 * k1_eth * dt, C_ace_old + 0.5 * k1_ace * dt, C_dia_old + 0.5 * k1_dia * dt);
                k2_sug = fC_sug(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt, C_sug_old + 0.5 * k1_sug * dt, C_eth_old + 0.5 * k1_eth * dt, C_ace_old + 0.5 * k1_ace * dt, C_dia_old + 0.5 * k1_dia * dt);
                k2_eth = fC_eth(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt, C_sug_old + 0.5 * k1_sug * dt, C_eth_old + 0.5 * k1_eth * dt, C_ace_old + 0.5 * k1_ace * dt, C_dia_old + 0.5 * k1_dia * dt);
                k2_ace = fC_ace(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt, C_sug_old + 0.5 * k1_sug * dt, C_eth_old + 0.5 * k1_eth * dt, C_ace_old + 0.5 * k1_ace * dt, C_dia_old + 0.5 * k1_dia * dt);
                k2_dia = fC_dia(X_act_old + 0.5 * k1_act * dt, X_lag_old + 0.5 * k1_lag * dt, C_sug_old + 0.5 * k1_sug * dt, C_eth_old + 0.5 * k1_eth * dt, C_ace_old + 0.5 * k1_ace * dt, C_dia_old + 0.5 * k1_dia * dt);
        
                k3_lag = fX_lag(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt, C_sug_old + 0.5 * k2_sug * dt, C_eth_old + 0.5 * k2_eth * dt, C_ace_old + 0.5 * k2_ace * dt, C_dia_old + 0.5 * k2_dia * dt);
                k3_act = fX_act(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt, C_sug_old + 0.5 * k2_sug * dt, C_eth_old + 0.5 * k2_eth * dt, C_ace_old + 0.5 * k2_ace * dt, C_dia_old + 0.5 * k2_dia * dt);
                k3_sug = fC_sug(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt, C_sug_old + 0.5 * k2_sug * dt, C_eth_old + 0.5 * k2_eth * dt, C_ace_old + 0.5 * k2_ace * dt, C_dia_old + 0.5 * k2_dia * dt);
                k3_eth = fC_eth(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt, C_sug_old + 0.5 * k2_sug * dt, C_eth_old + 0.5 * k2_eth * dt, C_ace_old + 0.5 * k2_ace * dt, C_dia_old + 0.5 * k2_dia * dt);
                k3_ace = fC_ace(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt, C_sug_old + 0.5 * k2_sug * dt, C_eth_old + 0.5 * k2_eth * dt, C_ace_old + 0.5 * k2_ace * dt, C_dia_old + 0.5 * k2_dia * dt);
                k3_dia = fC_dia(X_act_old + 0.5 * k2_act * dt, X_lag_old + 0.5 * k2_lag * dt, C_sug_old + 0.5 * k2_sug * dt, C_eth_old + 0.5 * k2_eth * dt, C_ace_old + 0.5 * k2_ace * dt, C_dia_old + 0.5 * k2_dia * dt);
        
                k4_lag = fX_lag(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt, C_sug_old + k3_sug * dt, C_eth_old + k3_eth * dt, C_ace_old + k3_ace * dt, C_dia_old + k3_dia * dt);
                k4_act = fX_act(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt, C_sug_old + k3_sug * dt, C_eth_old + k3_eth * dt, C_ace_old + k3_ace * dt, C_dia_old + k3_dia * dt);
                k4_sug = fC_sug(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt, C_sug_old + k3_sug * dt, C_eth_old + k3_eth * dt, C_ace_old + k3_ace * dt, C_dia_old + k3_dia * dt);
                k4_eth = fC_eth(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt, C_sug_old + k3_sug * dt, C_eth_old + k3_eth * dt, C_ace_old + k3_ace * dt, C_dia_old + k3_dia * dt);
                k4_ace = fC_ace(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt, C_sug_old + k3_sug * dt, C_eth_old + k3_eth * dt, C_ace_old + k3_ace * dt, C_dia_old + k3_dia * dt);
                k4_dia = fC_dia(X_act_old + k3_act * dt, X_lag_old + k3_lag * dt, C_sug_old + k3_sug * dt, C_eth_old + k3_eth * dt, C_ace_old + k3_ace * dt, C_dia_old + k3_dia * dt);
        
                X_lag += (k1_lag + 2*k2_lag + 2*k3_lag + k4_lag) * dt / 6.0;
                X_act += (k1_act + 2*k2_act + 2*k3_act + k4_act) * dt / 6.0;
                C_sug += (k1_sug + 2*k2_sug + 2*k3_sug + k4_sug) * dt / 6.0;
                C_eth += (k1_eth + 2*k2_eth + 2*k3_eth + k4_eth) * dt / 6.0;
                C_ace += (k1_ace + 2*k2_ace + 2*k3_ace + k4_ace) * dt / 6.0;
                C_dia += (k1_dia + 2*k2_dia + 2*k3_dia + k4_dia) * dt / 6.0;
        
                if (X_lag < alpha * X_lag0 && T != 18.0 + 273.15) {
                    T = T_post;
                    k_lag = exp(30.7 - 9.5*pow(10, 3)/T);
                    k_m = exp(1.30 * pow(10, 2) - 3.83 * pow(10, 4)/T);
                    k_x0 = exp(1.08 * pow(10, 2) - 3.19 * pow(10, 4)/T);
                    k_m = exp(1.30 * pow(10, 2) - 3.83 * pow(10, 4) / T);
                    k_sug0 = exp(-41.9 + 1.17 * pow(10, 4) / T);
                    sigma_sug = exp(-1.20 * pow(10, 2) + 3.42 * pow(10, 4) / T);
                    k_eth0 = exp(3.27 - 1.27 * pow(10, 3) / T);
                    ganmma_ace = exp(89.9 - 2.76 * pow(10, 4) / T);     
                }
        
                t += dt;
            } while (C_eth < 50.0 && t < t_end);
            fprintf(file, "%f,%f,%f,%f\n", T_options[ip], T_options[jp], t, C_dia);
        }
    }
    fclose(file);
    return 0;
}

double fX_lag(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia) {
    return -k_lag * X_lag;
}

double fX_act(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia) {
    if (X_lag > alpha * X_lag0) {
        return k_lag * X_lag;
    } else {
        return k_lag * X_lag - k_m * X_act + k_x * X_act;
    }
}

double fC_sug(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia) {
    return -k_sug * X_act;
}

double fC_eth(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia) {
    return k_eth * X_act;
}

double fC_ace(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia) {
    return ganmma_ace * k_sug * X_act;
}

double fC_dia(double X_act, double X_lag, double C_sug, double C_eth, double C_ace, double C_dia) {
    return k_dc * C_sug * X_act - k_dm * C_dia * C_eth;
}

