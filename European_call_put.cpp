#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
using namespace std;

//standard normal probability density function
double norm_pdf(const double &x)
{
	return (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*x*x);
}


// An approximation to the cumulative distribution function 
// for the standard normal distribution 
// Note : This is a recursive function 
double norm_cdf(const double & x)
{
	double k = 1.0 / (1.0 + 0.2316419 * x);
	double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + k * 1.330274429))));
	if (x >= 0.0)
	{
		return (1.0 - (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*x*x)*k_sum);
	}
	else
	{
		return 1.0 / norm_cdf(-x);
	}
}

double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T)
{
	return (log(S / K) + (r + (pow(-1, j - 1))*0.5*v*v) * T) / (v * pow(T, 0.5));
}

double call_price(const double& S, const double& K, const double& r, const double& v, const double& T)
{
	return S * norm_cdf(d_j(1, S, K, r, v, T)) - K * exp(-r * T) * norm_cdf(d_j(2, S, K, r, v, T));
}

double put_price(const double& S, const double& K, const double& r, const double& v, const double& T)
{
	return S * norm_cdf(-d_j(1, S, K, r, v, T)) + K * exp(-r * T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

int main()
{
	double S, K, r, v, T, call,put; 
	char ch;
	cout << "Enter Option Price-- " ; cin >> S;
	cout << "Enter Strike Price-- " ; cin >> K;
	cout << "Enter Risk Free Rate-- " ; cin >> r;
	cout << "Enter Volatility of Underlying-- " ; cin >> v;
	cout << "Enter Time Period-- " ; cin >> T;

	call = call_price(S, K, r, v, T);
	put = put_price(S, K, r, v, T);
	cout << "call_price:"<< call<< endl;
	cout << "put_price:" << put << endl;
	
	cout << "Enter x to exit" << endl;
	cin >> ch;
	if (ch == 'x')
	{
		return 0;
	}
	
}