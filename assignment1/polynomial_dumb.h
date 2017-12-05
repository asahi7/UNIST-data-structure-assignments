
// CSE221 Assignment 1

#ifndef polynomial_h
#define polynomial_h

#include <typeinfo>
#include <iostream>
#include <math.h>

template <typename T>
class Polynomial
{
public:
    
    // Default constructor p(x) = 0
	Polynomial();

	// Copy constructor
	Polynomial(const Polynomial& source);

	// Destructor
	~Polynomial();

	// Assignment operator
	Polynomial& operator = (const Polynomial& source);

	// Sum of *this and source polynomials
	Polynomial operator+(const Polynomial& source);
	
	// Subtract of source polynomials from *this
	Polynomial operator-(const Polynomial& source);

	// Product of *this and source polynomials
	Polynomial operator*(const Polynomial& source);

	// Evaluate polynomial *this at x and return the result
	T Eval(T x);

	// Print polynomial
	void Print();

	// Create a new term. If the term exists, overwrite its coefficient.
	void CreateTerm(const T coef, const int exp);

    T* coefs;
    int* exps;
    int size;

    void deleteZeros();
    void getNewSize();
};

//
// Implementation
//
template<typename T>
Polynomial<T>::Polynomial()
{
    size = 0;
    coefs = NULL;
    exps = NULL;
}

// Copy constructor
template <typename T>
Polynomial<T>::Polynomial(const Polynomial& source)
{
	this.size = source.size;
    this.coefs = new T[this.size];
    this.exps = new int[this.size];
    for(int i = 0; i < this.size; i++)
    {
        this.coefs[i] = source.coefs[i];
        this.exps[i] = source.exps[i];
    } 
}	

template <typename T>
Polynomial<T>& Polynomial<T>::operator = (const Polynomial& source)
{
	if(this != &source){
        delete[] this.coefs;
        delete[] this.exps;
        this.size = 0;
        
        this.size = source.size;
        this.coefs = new T[this.size];
        this.exps = new int[this.size];

        for(int i = 0; i < this.size; i++){
            this.coefs[i] = source.coefs[i];
            this.exps[i] = source.exps[i];
        }
    }
    return *this;
}

template <typename T>
Polynomial<T>::~Polynomial()
{
	delete[] this.coefs;
    delete[] this.exps;
}

template <typename T>
void Polynomial<T>::Print()
{
    for(int i = 0; i < this.size; i++){
        if(i != 0 && coefs[i] > 0) cout << '+';
        if(coefs[i] > 0) cout << coefs[i];
        if(exps[i] > 0) << "x^" << exps[i];
    }
    cout << endl;
}

int Polynomial<T>::getNewSize(Polynomial & left, Polynomial & right){
    int newSize = left.size + right.size;
	for(int l = 0, r = 0; l < left.size || r < right.size;){
        if(l >= left.size){
            r++;
            continue;
        }
        if(r >= rigth.size){
            l++;
            continue;
        }
        if(left.exps[l] == right.exps[r]){
            newSize--;
            l++;
            r++;
        }
        else if(left.exps[l] > right.exps[r]){
            l++;
        }
        else if(left.exps[l] < right.exps[r]){
            r++;
        }
    }
    return newSize;
}

void Polynomial<T>::deleteZeros(){
    bool* checker = new bool[this.size];
    for(int i = 0; i < this.size; i++) checker[i] = 0;
    int newSize = this.size;
    for(int i = 0; i < this.size; i++){
        if(is_same<T, double>::value && fabs(this.coefs[i]) < pow(10, -15)){
             checker[i] = 1;
             newSize--;
        }
        else if(is_same<T, int>::value && this.coefs[i] == 0){
            checker[i] = 1;
            newSize--;
        }
    }
    Polynomial<T> temp;
    temp.size = newSize;
    temp.coefs = new T[newSize];
    temp.exps = new int[newSize];
    for(int i = 0, j = 0; i < this.size; i++){
        if(checker[i] == 0){
            temp.coefs[j] = this.coefs[i];
            temp.exps[j] = this.exps[i];
            j++;
        }
    }
    *this = temp;
}

// Sum of *this and source polynomials
template <typename T>
Polynomial<T> 
Polynomial<T>::operator+(const Polynomial& source)
{
    Polynomial<T> newPolynomial;
    int newSize = getNewSize(*this, source);
    newPolynomial.size = newSize;
    newPolynomial.exps = new int[newSize];
    newPolynomial.coefs = new T[newSize];
    for(int l = 0, r = 0, i = 0; l < this.size || r < source.size;){
        if(l >= this.size){
            newPolynomial.coefs[i] = source.coefs[r];
            newPolynomial.exps[i] = source.exps[r];
            i++;
            r++;
            continue;
        }
        if(r >= this.size){
            newPolynomial.coefs[i] = this.coefs[l];
            newPolynomial.exps[i] = this.exps[l];
            l++;
            i++;
            continue;
        }
        if(this.exps[l] == source.exps[r]){
            newPolynomial.exps[i] = this.exps[l];
            newPolynomial.coefs[i] = this.coefs[l] + source.coefs[r];
            l++;
            r++;
            i++;
        }
        else if(this.exps[l] > source.exps[r]){
            newPolynomial.exps[i] = this.exps[l];
            newPolynomial.coefs[i] = this.coefs[i];
            i++;
            l++;
        }
        else{
            newPolynomial.exps[i] = source.exps[r];
            newPolynomial.coefs[i] = source.coefs[r];
            i++;
            r++;
        }
    }
    newPolynomial.deleteZeros();
    return newPolynomial;
}

template <typename T>
Polynomial<T> 
Polynomial<T>::operator-(const Polynomial& source)
{
    Polynomial<T> newPolynomial;
    int newSize = getNewSize(*this, source);
    newPolynomial.size = newSize;
    newPolynomial.exps = new int[newSize];
    newPolynomial.coefs = new T[newSize];
    for(int l = 0, r = 0, i = 0; l < this.size || r < source.size;){
        if(l >= this.size){
            newPolynomial.coefs[i] = source.coefs[r];
            newPolynomial.exps[i] = -source.exps[r];
            i++;
            r++;
            continue;
        }
        if(r >= this.size){
            newPolynomial.coefs[i] = this.coefs[l];
            newPolynomial.exps[i] = this.exps[l];
            l++;
            i++;
            continue;
        }
        if(this.exps[l] == source.exps[r]){
            newPolynomial.exps[i] = this.exps[l];
            newPolynomial.coefs[i] = this.coefs[l] - source.coefs[r];
            l++;
            r++;
            i++;
        }
        else if(this.exps[l] > source.exps[r]){
            newPolynomial.exps[i] = this.exps[l];
            newPolynomial.coefs[i] = this.coefs[i];
            i++;
            l++;
        }
        else{
            newPolynomial.exps[i] = source.exps[r];
            newPolynomial.coefs[i] = -source.coefs[r];
            i++;
            r++;
        }
    }
    newPolynomial.deleteZeros();
    return newPolynomial;

}

template <typename T>
Polynomial<T> 
Polynomial<T>::operator*(const Polynomial& source)
{
    Polynomial<T> newPolynomial;
    for(int i = 0; i < this.size; i++){
        Polynomial<T> mul;
        mul.size = source.size;
        mul.exps = new int[mul.size];
        mul.coefs = new T[mul.size];
        for(int j = 0; j < source.size; j++){
            mul.exps[j] = source.exps[j] + this.exps[i];
            mul.coefs[j] = source.coefs[j] * this.coefs[i];
        }
        newPolynomial = newPolynomial + mul;
    }
    newPolynomial.deleteZeros();
    return newPolynomial;
}

template <typename T>
T Polynomial<T>::Eval(T x)
{
    T result = 0;
    for(int i = 0; i < this.size; i++){
        result += this.coefs[i] * pow(x, this.epxs[i]);    
    }
    return result;
}

template <typename T>
void Polynomial<T>::CreateTerm(const T coef, const int exp)
{
    Polynomial<T> temp(*this); // Copy constructor, makes equal all the fields
    delete[] this.coefs; 
    delete[] this.exps;
    this.coefs = new T[this.size + 1];
    this.exps = new int[this.size + 1];
    bool duplicate = false;
    for(int i = 0; i < this.size + 1; i++){
        this.coefs[i] = temp.coefs[i];
        this.exps[i] = temp.exps[i];

        if(this.exps[i] == exp){
            this.coefs[i] = coef;
            duplicate = true;
        }
    }
    if(! duplicate){
        this.coefs[this.size] = coef;
        this.exps[this.size] = exp;
        this.size++;

        for(int i = this.size - 1; i > 0; i--){
            if(this.exps[i] > this.exps[i - 1]){
                swap(this.coefs[i], this.coefs[i - 1]);
                swap(this.exps[i], this.exps[i - 1]);
            }
        }
    }
}   


#endif
