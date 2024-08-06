#include <iostream>
#include <vector> 
#include <cmath> 
using namespace std; 

// C++ implementation of provided algorithm: 
// https://github.com/antek0308/Volatility_notebooks/blob/main/Medium/Finite_diff_explicit.ipynb
// "The implementation is the straightforward implementation of VBA code from "Paul Wilmott on Quantitative Finance". I highly reccomend this book for more details."



// function returns a 3-dimensional grid of estimated values of V(S, T); 

// PARAMETERS: 

// vol: volatility. 
// intRate: interest rate. 
// putCall: if true, call option. if false, put option. 
// strike: strikeprice. 
// expiration: time to expiration for the option. 
// NAS: Number of asset Steps. 


vector<vector<float>> V(float vol, float intRate, bool putCall, float strike, int expiration, int nas){

    
    // initialized number values. 
    vector<float> S(nas + 1, 0); 
    
    float dS = 3 * strike / nas; 
    float dT = 0.9 / (vol * vol) / (nas * nas);
    int nts = (expiration / dT) + 1;
    dT = expiration / nts; 
    vector<vector<float>> V(nts + 1, S); 

    int q = (putCall) ? 1 : -1; 

    float delta; 
    float gamma; 
    float theta; 

    for (int i = 1; i < nas + 1; i++) {
        S[i] = i * dS; 
        V[0][i] = max((double) q * (S[i] * strike), 0.0 ); 
    }

    // finite difference method: 
    
    for (int timeStep = 1; timeStep <= nts; timeStep++){
        for (int assetStep = 1; assetStep < nas; assetStep++) {
            delta = (V[timeStep - 1][assetStep + 1] - V[timeStep - 1][assetStep - 1]) / 2 / dS;   
            gamma = ( V[timeStep - 1][assetStep + 1] - (2 * V[timeStep-1][assetStep]) + V[timeStep-1][assetStep-1]) / dS / dS;  
            theta = -0.5 * vol * vol * S[assetStep] * S[assetStep] * gamma - intRate * S[assetStep] * delta + intRate * V[timeStep-1][assetStep]; 
            V[timeStep][assetStep] = V[timeStep - 1][assetStep] - dT * theta; 
        }
    }


    return V; 
}


int main() {

    int nas = 20; 
    float intRate = 0.05;  
    bool optionType = true; 
    float volatility = 0.2; 
    int K = 100;
    int T = 1; 
    
    vector<vector<float>> x = V(volatility, intRate, optionType, K, T, nas);


    return 0; 
}
